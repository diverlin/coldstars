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

#include "../spaceobjects/IncludeSpaceObjects.hpp"

#include "../dock/Kosmoport.hpp"
#include "../dock/NatureLand.hpp"

#include "../builder/dock/KosmoportBuilder.hpp"
#include "../builder/dock/NatureLandBuilder.hpp"
#include "../builder/pilots/NpcBuilder.hpp"
#include "../builder/spaceobjects/ShipBuilder.hpp"
#include "../builder/spaceobjects/SpaceStationBuilder.hpp"
#include "../builder/spaceobjects/SatelliteBuilder.hpp"

#include "../common/Logger.hpp"
#include "../common/rand.hpp"
#include "../common/constants.hpp"
#include "../common/Date.hpp"

#include "../world/galaxy.hpp"
#include "../world/Sector.hpp"
#include "../world/starsystem.hpp"

#include "../ai/Task.hpp"
#include "../pilots/Npc.hpp"
#include "../struct/GalaxyDescription.hpp"

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
	
	galaxy = nullptr;
}
		
God::~God()
{}

void God::Init(Galaxy* galaxy, const GalaxyDescription& galaxy_description)
{
	this->galaxy = galaxy;
	CreateLife(galaxy_description);
	if (galaxy_description.allow_invasion == true)
	{
		CreateInvasion(galaxy_description);
	}
}

void God::CreateLife(const GalaxyDescription& galaxy_description) const
{
    for(unsigned int i=0; i<galaxy->SECTOR_vec.size(); i++)
    {
        for(unsigned int j=0; j<galaxy->SECTOR_vec[i]->STARSYSTEM_vec.size(); j++)
        {	        
            const StarSystemDescription& starsystem_description = galaxy_description.sector_descriptions[i].starsystem_descriptions[j];
            StarSystem* starsystem = galaxy->SECTOR_vec[i]->STARSYSTEM_vec[j];
        
            for(unsigned int j=0; j<starsystem->PLANET_vec.size(); j++)
            {        
                CreateLifeAtPlanet(starsystem->PLANET_vec[j], starsystem_description);
            }

            CreateSpaceStations(starsystem, starsystem_description.spacestation_num);
        }
    }
}

void God::CreateInvasion(const GalaxyDescription& galaxy_description) const
{
	for (unsigned int i=0; i<INITIATE_STARSYSTEM_IVASION_NUM; i++)
	{
		StarSystem* starsystem = galaxy->GetRandomSector()->GetRandomStarSystem(ENTITY::STARSYSTEM::CONDITION::SAFE_ID);
		TYPE::RACE race_id = (TYPE::RACE)getRandInt((int)TYPE::RACE::R6_ID, (int)TYPE::RACE::R7_ID);
        int ship_num = getRandInt(ENTITY::STARSYSTEM::SHIPENEMY_INIT_MIN, ENTITY::STARSYSTEM::SHIPENEMY_INIT_MAX);
        CreateShipsInSpace(starsystem, ship_num, race_id);
	}
}

void God::ProceedInvasion() const
{
	StarSystem* starsystem_invade_from = galaxy->GetRandomSector()->GetRandomStarSystem(ENTITY::STARSYSTEM::CONDITION::CAPTURED_ID);
	if (starsystem_invade_from == nullptr)
	{
		return;
	}
	
	StarSystem* starsystem_invade_to   = galaxy->GetClosestSectorTo(starsystem_invade_from->GetSector())->GetClosestStarSystemTo(starsystem_invade_from, ENTITY::STARSYSTEM::CONDITION::SAFE_ID);
	if (starsystem_invade_to == nullptr)
	{
		return;
	}
	
	Npc* npc_leader = starsystem_invade_from->GetFreeLeaderByRaceId(starsystem_invade_from->GetConquerorRaceId());
	Task macrotask(TYPE::AISCENARIO::MACRO_STARSYSTEMLIBERATION_ID, starsystem_invade_to->GetId());
	npc_leader->GetStateMachine().SetCurrentMacroTask(macrotask);
	
	int num_max= 10;
	starsystem_invade_from->CreateGroupAndShareTask(npc_leader, starsystem_invade_to, num_max);
}

void God::Update(const Date& date)
{
	if (last_update_date.GetDaysPassSince(date) >= GOD_REST_IN_DAYS)
	{
		#if GOD_LOG_ENABLED == 1
		Logger::Instance().Log("God::Update", GOD_LOG_DIP);
		#endif
			
		galaxy->FillStarSystemsCondition(data_starsystems_condition);
		last_update_date = date;
		
		ProceedInvasion();

		#if GOD_LOG_ENABLED == 1
		Logger::Instance().Log(data_starsystems_condition.GetStr(), GOD_LOG_DIP);
		#endif
	}
}                
     
void God::CreateLifeAtPlanet(Planet* planet, const StarSystemDescription& starsystem_description) const
{            
	unsigned long int population = 0;
	getRandBool() ? population = getRandInt(POPULATION_MIN, POPULATION_MAX) : population = 0;
	planet->SetPopulation(population);
	
	BaseLand* land = nullptr;
	if (population > 0) { land = KosmoportBuilder::Instance().GetNewKosmoport(); }
	else                { land = NatureLandBuilder::Instance().GetNewNatureLand(); }
		
	planet->BindLand(land);

	if (population > 0) 
	{
		if (starsystem_description.allow_satellites == true)
		{
			int sattelitewarriors_num = 1; //getRandInt(SATELLITEWARRIORS_PER_PLANET_MIN, SATELLITEWARRIORS_PER_PLANET_MAX);
			for (int j=0; j<sattelitewarriors_num; j++)
			{      
				Satellite* satellite = SatelliteBuilder::Instance().GetNewSatellite();
				SatelliteBuilder::Instance().EquipEquipment(satellite); // improove
	        
				{
					TYPE::RACE npc_race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
					TYPE::ENTITY npc_subtype_id    = TYPE::ENTITY::WARRIOR_ID;
					TYPE::ENTITY npc_subsubtype_id = TYPE::ENTITY::WARRIOR_ID;
			
					Npc* npc = NpcBuilder::Instance().GetNewNpc(npc_race_id, npc_subtype_id, npc_subsubtype_id);
					satellite->BindOwnerNpc(npc);
				}
			
				Vec3<float> orbit_center(0, 0, -500);
				Vec3<float> angle(0,0,0);
				planet->GetStarSystem()->AddVehicle(satellite, orbit_center, angle, planet);
			}
		}
		
		if (starsystem_description.allow_ships == true)
		{
			std::vector<TYPE::ENTITY> allowed_subtypes;
			if (starsystem_description.allow_ship_ranger == true)  	{ allowed_subtypes.push_back(TYPE::ENTITY::RANGER_ID); }		
			if (starsystem_description.allow_ship_warrior == true) 	{ allowed_subtypes.push_back(TYPE::ENTITY::WARRIOR_ID); }	
			if (starsystem_description.allow_ship_trader == true) 	{ allowed_subtypes.push_back(TYPE::ENTITY::TRADER_ID); }	
			if (starsystem_description.allow_ship_pirat == true) 	{ allowed_subtypes.push_back(TYPE::ENTITY::PIRAT_ID); }	
			if (starsystem_description.allow_ship_diplomat == true) { allowed_subtypes.push_back(TYPE::ENTITY::DIPLOMAT_ID); }	
			
			int ship_num = getRandInt(SHIPINIT_PER_PLANET_MIN, SHIPINIT_PER_PLANET_MAX);
			for (int j=0; j<ship_num; j++)
			{
				TYPE::RACE npc_race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
				TYPE::ENTITY npc_subtype_id    = getRandNpcSubTypeId(npc_race_id, allowed_subtypes);
				TYPE::ENTITY npc_subsubtype_id = getRandNpcSubSubTypeId(npc_subtype_id);
				
				TYPE::RACE ship_race_id = npc_race_id;         
				TYPE::ENTITY ship_subtype_id = npc_subtype_id;  
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
}

void God::CreateSpaceStations(StarSystem* starsystem, int spacestation_per_system) const
{       
    for (int i=0; i<spacestation_per_system; i++)
    {     
        TYPE::RACE npc_race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
        TYPE::ENTITY npc_subtype_id    = TYPE::ENTITY::WARRIOR_ID;
        TYPE::ENTITY npc_subsubtype_id = TYPE::ENTITY::WARRIOR_ID;
            
        //TYPE::RACE ship_race_id = npc_race_id;         // RACES_ALL_vec[getRandInt(0, RACES_ALL_vec.size())];
        //TYPE::ENTITY ship_subtype_id = npc_subtype_id;   // SHIP_SUBTYPE_vec[getRandInt(0, SHIP_SUBTYPE_vec.size())];
        //int weapons_num = 5;
        
        SpaceStation* spacestation = SpaceStationBuilder::Instance().GetNewSpaceStation();
        SpaceStationBuilder::Instance().EquipEquipment(spacestation);  // improove

        Npc* npc = NpcBuilder::Instance().GetNewNpc(npc_race_id, npc_subtype_id, npc_subsubtype_id);
        spacestation->BindOwnerNpc(npc);

		Vec2<float> center = getRandVec2f(700, 1500);
        Vec3<float> center3(center.x, center.y, DEFAULT_ENTITY_ZPOS);
		Vec3<float> angle(0,0,getRandInt(0, 360));  
		                
        starsystem->AddVehicle(spacestation, center3, angle, nullptr);
        
        {  
            Satellite* satellite = SatelliteBuilder::Instance().GetNewSatellite();
            SatelliteBuilder::Instance().EquipEquipment(satellite);           		// improove

            Npc* new_npc = NpcBuilder::Instance().GetNewNpc(npc_race_id, npc_subtype_id, npc_subsubtype_id);
            satellite->BindOwnerNpc(new_npc);
            
            Vec3<float> center(0, 0, DEFAULT_ENTITY_ZPOS);
            Vec3<float> angle(0, 0, 0);
                            
            starsystem->AddVehicle(satellite, center, angle, spacestation);
        }
    }        
}

void God::CreateShipsInSpace(StarSystem* starsystem, int ship_num, TYPE::RACE npc_race_id, TYPE::ENTITY subtype_id, TYPE::ENTITY subsubtype_id) const
{
    TYPE::ENTITY npc_subtype_id = TYPE::ENTITY::NONE_ID;
    TYPE::ENTITY npc_subsubtype_id = TYPE::ENTITY::NONE_ID;

    for (int i=0; i<ship_num; i++)
    {     
        if (subtype_id == TYPE::ENTITY::NONE_ID)
        {
            npc_subtype_id    = getRandNpcSubTypeId(npc_race_id);
            npc_subsubtype_id = getRandNpcSubSubTypeId(npc_subtype_id);
        }
        else
        {
            npc_subtype_id    = subtype_id;
            npc_subsubtype_id = subsubtype_id;
        }   

        TYPE::RACE ship_race_id    = npc_race_id;         
        TYPE::ENTITY ship_subtype_id = npc_subtype_id;  
        int ship_size_id = getRandInt(1, 9);
        int weapons_num = getRandInt(1, 5);

        Ship* new_ship = ShipBuilder::Instance().GetNewShip(ship_race_id, ship_subtype_id, ship_size_id, weapons_num);
        ShipBuilder::Instance().EquipEquipment(new_ship); // improove

        Npc* new_npc = NpcBuilder::Instance().GetNewNpc(npc_race_id, npc_subtype_id, npc_subsubtype_id);
        new_ship->BindOwnerNpc(new_npc);

        Vec2<float> center = getRandVec2f(300, 1200);
        Vec3<float> center3(center.x, center.y, DEFAULT_ENTITY_ZPOS);
        Vec3<float> angle(0,0,getRandInt(0, 360));		
        starsystem->AddVehicle(new_ship, center3, angle, nullptr);
    }
}


