/*
	Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "God.hpp"

#include "../spaceobjects/Ship.hpp"
#include "../spaceobjects/Planet.hpp"
#include "../spaceobjects/BlackHole.hpp"

#include "../docking/Kosmoport.hpp"
#include "../docking/NatureLand.hpp"

#include "../builder/KosmoportBuilder.hpp"
#include "../builder/NatureLandBuilder.hpp"
#include "../builder/NpcBuilder.hpp"
#include "../builder/ShipBuilder.hpp"
#include "../builder/SpaceStationBuilder.hpp"
#include "../builder/SatelliteBuilder.hpp"

#include "../common/Logger.hpp"
#include "../common/rand.hpp"
#include "../common/constants.hpp"
#include "../common/Date.hpp"

#include "../world/galaxy.hpp"
#include "../world/starsystem.hpp"

God& God::Instance()
{
	static God instance;
	return instance;
}

God::God() 
{ 
	last_update_date.day = 0;
	last_update_date.month = 0;
	last_update_date.year = 0;
	
	invasion_took_place = false;
	galaxy = NULL;
}
		
God::~God()
{}

StarSystem* God::GetProperStarSystemToInvade() const
{
	return galaxy->GetRandomStarSystem();
}

void God::Update(const Date& date)
{
	if (last_update_date.GetDaysPassSince(date) >= GOD_REST_IN_DAYS)
	{
		#if GOD_LOG_ENABLED == 1
		Logger::Instance().Log("God::Update", GOD_LOG_DIP);
		#endif
			
		if (invasion_took_place == false)
		{
			for (unsigned int i=0; i<3; i++)
			{
				StarSystem* starsystem = GetProperStarSystemToInvade();
				InvasionInStarSystem(starsystem);
			}
			invasion_took_place = true;
		}
		
		last_update_date = date;
	}
}

void God::CreateLife() const
{
        for(unsigned int i=0; i<galaxy->STARSYSTEM_vec.size(); i++)
        {
                CreateLifeInStarSystem1(galaxy->STARSYSTEM_vec[i]);
        }
}
                
void God::CreateLifeInStarSystem1(StarSystem* starsystem) const
{
	CreateLifeAtPlanets(starsystem);

	int spacestation_num = getRandInt(ENTITY::STARSYSTEM::SPACESTATION_INIT_MIN, ENTITY::STARSYSTEM::SPACESTATION_INIT_MAX);
        CreateSpaceStations(starsystem, spacestation_num);
}

void God::InvasionInStarSystem(StarSystem* starsystem) const
{
	int race_id = getRandInt(RACE::R6_ID, RACE::R7_ID);
        int ship_num = getRandInt(ENTITY::STARSYSTEM::SHIPENEMY_INIT_MIN, ENTITY::STARSYSTEM::SHIPENEMY_INIT_MAX);
        CreateShipsInSpace(starsystem, ship_num, race_id);   
}
        
void God::CreateLifeAtPlanets(StarSystem* starsystem) const
{
        for(int i=0; i<starsystem->PLANET_vec.size(); i++)
        {        
                CreateLifeAtPlanet(starsystem->PLANET_vec[i]);
        }
}

     
void God::CreateLifeAtPlanet(Planet* planet) const
{            
	unsigned long int population = 0;
	getRandBool() ? population = getRandInt(1000, 4000) : population = 0;
	planet->SetPopulation(population);
	
	BaseLand* land = NULL;
	if (population > 0) { land = KosmoportBuilder::Instance().GetNewKosmoport(); }
	else                { land = NatureLandBuilder::Instance().GetNewNatureLand(); }
		
	planet->BindLand(land);

	if (population > 0) 
	{
		int sattelitewarriors_num = 1; //getRandInt(SATELLITEWARRIORS_PER_PLANET_MIN, SATELLITEWARRIORS_PER_PLANET_MAX);
		for (int j=0; j<sattelitewarriors_num; j++)
		{      
			Satellite* satellite = SatelliteBuilder::Instance().GetNewSatellite();
			SatelliteBuilder::Instance().EquipEquipment(satellite); // improove
        
			{
				int npc_race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
				int npc_subtype_id    = ENTITY::WARRIOR_ID;
				int npc_subsubtype_id = ENTITY::WARRIOR_ID;
		
				Npc* npc = NpcBuilder::Instance().GetNewNpc(npc_race_id, npc_subtype_id, npc_subsubtype_id);
				satellite->BindOwnerNpc(npc);
			}
		
			planet->GetStarSystem()->AddVehicle(satellite, vec2f(0, 0), 0, planet);
		}
		
		int shipwarriors_num = getRandInt(SHIPWARRIORS_PER_PLANET_MIN, SHIPWARRIORS_PER_PLANET_MAX);
		for (int j=0; j<shipwarriors_num; j++)
		{
			int npc_race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
			int npc_subtype_id    = getRandNpcSubTypeId(npc_race_id);
			int npc_subsubtype_id = getRandNpcSubSubTypeId(npc_subtype_id);
			
			int ship_race_id = npc_race_id;         
			int ship_subtype_id = npc_subtype_id;  
			int ship_size_id = getRandInt(SIZE_1_ID, SIZE_9_ID);
			int weapons_num = getRandInt(1, 5);
	
			Ship* new_ship = ShipBuilder::Instance().GetNewShip(ship_race_id, ship_subtype_id, ship_size_id, weapons_num);
			ShipBuilder::Instance().EquipEquipment(new_ship); // improove
                        //ShipBuilder::Instance().EquipModules(ship, tech_level); 
                        //ShipBuilder::Instance().EquipArtefacts(ship, tech_level); 
                        //ShipBuilder::Instance().EquipBomb(ship, tech_level); 
        
			Npc* new_npc = NpcBuilder::Instance().GetNewNpc(npc_race_id, npc_subtype_id, npc_subsubtype_id);
			new_ship->BindOwnerNpc(new_npc);
			
			planet->AddVehicle(new_ship);
		}
     	}
}

void God::CreateSpaceStations(StarSystem* starsystem, int spacestation_per_system) const
{       
    	for (int i=0; i<spacestation_per_system; i++)
    	{     
    		int npc_race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
                int npc_subtype_id    = ENTITY::WARRIOR_ID;
                int npc_subsubtype_id = ENTITY::WARRIOR_ID;
                
        	int ship_race_id = npc_race_id;         // RACES_ALL_vec[getRandInt(0, RACES_ALL_vec.size())];
        	int ship_subtype_id = npc_subtype_id;   // SHIP_SUBTYPE_vec[getRandInt(0, SHIP_SUBTYPE_vec.size())];
        	int ship_size_id = getRandInt(1, 9);
        	int weapons_num = 5;
        	
        	SpaceStation* spacestation = SpaceStationBuilder::Instance().GetNewSpaceStation();
        	SpaceStationBuilder::Instance().EquipEquipment(spacestation);  // improove

                Npc* npc = NpcBuilder::Instance().GetNewNpc(npc_race_id, npc_subtype_id, npc_subsubtype_id);
        	spacestation->BindOwnerNpc(npc);

		vec2f center = getRandVec2f(700, 1500);
		float angle = getRandInt(0, 360);  
                
        	starsystem->AddVehicle(spacestation, center, angle, NULL);
        	
        	{  
                Satellite* satellite = SatelliteBuilder::Instance().GetNewSatellite();
                SatelliteBuilder::Instance().EquipEquipment(satellite);           		// improove

                Npc* new_npc = NpcBuilder::Instance().GetNewNpc(npc_race_id, npc_subtype_id, npc_subsubtype_id);
                satellite->BindOwnerNpc(new_npc);
                
                starsystem->AddVehicle(satellite, vec2f(0, 0), 0, spacestation);
    		}
    	}        
}

void God::CreateShipsInSpace(StarSystem* starsystem, int ship_num, int npc_race_id, int subtype_id, int subsubtype_id) const
{
    	int npc_subtype_id;
        int npc_subsubtype_id;

    	for (int i=0; i<ship_num; i++)
    	{     
    		if (subtype_id == NONE_ID)
    		{
			npc_subtype_id    = getRandNpcSubTypeId(npc_race_id);
                        npc_subsubtype_id = getRandNpcSubSubTypeId(npc_subtype_id);
                }
                else
                {
                	npc_subtype_id    = subtype_id;
                        npc_subsubtype_id = subsubtype_id;
                }   

        	int ship_race_id    = npc_race_id;         
        	int ship_subtype_id = npc_subtype_id;  
        	int ship_size_id = getRandInt(1, 9);
        	int weapons_num = getRandInt(1, 5);

        	Ship* new_ship = ShipBuilder::Instance().GetNewShip(ship_race_id, ship_subtype_id, ship_size_id, weapons_num);
        	ShipBuilder::Instance().EquipEquipment(new_ship); // improove

        	Npc* new_npc = NpcBuilder::Instance().GetNewNpc(npc_race_id, npc_subtype_id, npc_subsubtype_id);
        	new_ship->BindOwnerNpc(new_npc);

		vec2f center = getRandVec2f(300, 1200);
		float angle = getRandInt(0, 360);  
		
        	starsystem->AddVehicle(new_ship, center, angle, NULL);
    	}
}


