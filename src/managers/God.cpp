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

#include "../world/starsystem.hpp"

God& God::Instance()
{
	static God instance;
	return instance;
}

God::~God()
{}

void God::UpdateInStatic()
{
	//war manager
}

void God::CreateLifeInStarSystem(StarSystem* starsystem) const
{
	CreateLifeToPlanets(starsystem);
	if (getRandInt(1,7) == 1)
	{
		int race_id = getRandInt(RACE::R6_ID, RACE::R7_ID);
		int ship_num = getRandInt(ENTITY::STARSYSTEM::SHIPENEMY_INIT_MIN, ENTITY::STARSYSTEM::SHIPENEMY_INIT_MAX);
	        CreateShipsInSpace(starsystem, race_id, ship_num);   
	}
	else
	{
		int spacestation_num = getRandInt(ENTITY::STARSYSTEM::SPACESTATION_INIT_MIN, ENTITY::STARSYSTEM::SPACESTATION_INIT_MAX);
	        CreateSpaceStations(starsystem, spacestation_num);
	}	
}
        
void God::CreateLifeToPlanets(StarSystem* starsystem) const
{
        for(int i=0; i<starsystem->PLANET_vec.size(); i++)
        {        
                Planet* planet = starsystem->PLANET_vec[i];
                
                unsigned long int population = 0;
                getRandBool() ? population = getRandInt(1000, 4000) : population = 1;
                planet->SetPopulation(population);
                
                BaseLand* land = NULL;
                if (population > 0) { land = KosmoportBuilder::Instance().GetNewKosmoport(); }
                else                { land = NatureLandBuilder::Instance().GetNewNatureLand(); }
                        
                planet->BindLand(land);
        
                if (population > 0) 
                {
                        for (int j=0; j<1; j++)
                        {      
                                Satellite* satellite = SatelliteBuilder::Instance().GetNewSatellite();
                                SatelliteBuilder::Instance().Equip(satellite);           		// improove
                         
                                {
                                        int npc_race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
                                        int npc_subtype_id = ENTITY::WARRIOR_ID;
                        
                                        Npc* npc = NpcBuilder::Instance().GetNewNpc(npc_race_id, npc_subtype_id);
                                        satellite->BindOwnerNpc(npc);
                                }
                        
                                starsystem->AddVehicle(satellite, vec2f(0, 0), 0, planet);
                        }
                        
                        for (int j=0; j<4; j++)
                        {
                                int npc_race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
                                int npc_subtype_id = getRandNpcSubTypeId(npc_race_id);
                                
                                int ship_race_id = npc_race_id;         
                                int ship_subtype_id = npc_subtype_id;  
                                int ship_size_id = getRandInt(SIZE_1_ID, SIZE_9_ID);
                                int weapons_num = getRandInt(1, 5);
                
                                Ship* new_ship = ShipBuilder::Instance().GetNewShip(ship_race_id, ship_subtype_id, ship_size_id, weapons_num);
                                ShipBuilder::Instance().Equip(new_ship); // improove
                
                                Npc* new_npc = NpcBuilder::Instance().GetNewNpc(npc_race_id, npc_subtype_id);
                                new_ship->BindOwnerNpc(new_npc);
                                
                                planet->AddVehicle(new_ship);
                        }
                }
        }
}

void God::CreateSpaceStations(StarSystem* starsystem, int spacestation_per_system) const
{       
    	for (int i=0; i<spacestation_per_system; i++)
    	{     
    		int npc_race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
                int npc_subtype_id = ENTITY::WARRIOR_ID;

        	int ship_race_id = npc_race_id;         // RACES_ALL_vec[getRandInt(0, RACES_ALL_vec.size())];
        	int ship_subtype_id = npc_subtype_id;   // SHIP_SUBTYPE_vec[getRandInt(0, SHIP_SUBTYPE_vec.size())];
        	int ship_size_id = getRandInt(1, 9);
        	int weapons_num = 5;
        	
        	SpaceStation* spacestation = SpaceStationBuilder::Instance().GetNewSpaceStation();
        	SpaceStationBuilder::Instance().Equip(spacestation);       	// improove

                Npc* npc = NpcBuilder::Instance().GetNewNpc(npc_race_id, npc_subtype_id);
        	spacestation->BindOwnerNpc(npc);

		vec2f center = getRandVec2f(700, 1500);
		float angle = getRandInt(0, 360);  
                
        	starsystem->AddVehicle(spacestation, center, angle, NULL);
        	
        	{  
                Satellite* satellite = SatelliteBuilder::Instance().GetNewSatellite();
                SatelliteBuilder::Instance().Equip(satellite);           		// improove

                Npc* new_npc = NpcBuilder::Instance().GetNewNpc(npc_race_id, npc_subtype_id);
                satellite->BindOwnerNpc(new_npc);
                
                starsystem->AddVehicle(satellite, vec2f(0, 0), 0, spacestation);
    		}
    	}        
}

void God::CreateShipsInSpace(StarSystem* starsystem, int npc_race_id, int ship_num, int requestedclass) const
{
    	int npc_subtype_id = NONE_ID;

    	for (int i=0; i<ship_num; i++)
    	{     
    		if (requestedclass == NONE_ID)
    		{
			npc_subtype_id = getRandNpcSubTypeId(npc_race_id);
                }
                else
                {
                	npc_subtype_id = requestedclass;
                }   

        	int ship_race_id = npc_race_id;         
        	int ship_subtype_id = npc_subtype_id;  
        	int ship_size_id = getRandInt(1, 9);
        	int weapons_num = getRandInt(1, 5);

        	Ship* new_ship = ShipBuilder::Instance().GetNewShip(ship_race_id, ship_subtype_id, ship_size_id, weapons_num);
        	ShipBuilder::Instance().Equip(new_ship); // improove

        	Npc* new_npc = NpcBuilder::Instance().GetNewNpc(npc_race_id, npc_subtype_id);
        	new_ship->BindOwnerNpc(new_npc);

		vec2f center = getRandVec2f(300, 1200);
		float angle = getRandInt(0, 360);  
		
        	starsystem->AddVehicle(new_ship, center, angle, NULL);
    	}
}


