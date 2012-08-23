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


StarSystemBuilder& StarSystemBuilder::Instance()
{
	static StarSystemBuilder instance;
	return instance;
}

StarSystemBuilder::~StarSystemBuilder()
{}

void StarSystemBuilder::CreateNewStarSystem(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	starsystem = new StarSystem(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        EntityManager::Instance().RegisterEntity(starsystem);
} 
        	
void StarSystemBuilder::CreateNewInternals()
{
        vec2f center(getRandInt(GUI::MAP::BORDER_X, Config::Instance().SCREEN_WIDTH -  2*GUI::MAP::BORDER_X), 
        	     getRandInt(GUI::MAP::BORDER_Y, Config::Instance().SCREEN_HEIGHT - 2*GUI::MAP::BORDER_Y) );			 
        starsystem->GetPoints().SetCenter(center);

        this->CreateStar();
        
        int distNebula_num = getRandInt(6,8);
        int distStar_num = getRandInt(40, 60);
        this->CreateBackground(distNebula_num, distStar_num, starsystem->GetStar()->GetColorId());
          
        int planet_num = getRandInt(ENTITY::STARSYSTEM::PLANET_MIN, ENTITY::STARSYSTEM::PLANET_MAX);
        this->CreatePlanets(planet_num);
        
        for (int i=0; i<SHOCKWAVESBLACKHOLES_MAX_NUM; i++)
        {
        	BlackHole* bh = GetNewBlackHole();
        	starsystem->Add(bh, getRandVec2f(1200, 2000));
        }

        //if (getRandBool())
        {
                int npc_race_id = getRandIntFromVec(RaceInformationCollector.RACES_GOOD_vec);
                int ship_num = getRandInt(ENTITY::STARSYSTEM::SHIP_INIT_MIN, ENTITY::STARSYSTEM::SHIP_INIT_MAX);
                this->CreateShips(npc_race_id, ship_num, CLASS::TRADER_ID);
        }
        //else
        //{
                //int npc_race_id = getRandIntFromVec(RaceInformationCollector.RACES_EVIL_vec);
                //int ship_num = getRandInt(ENTITY::STARSYSTEM::SHIP_INIT_MIN, ENTITY::STARSYSTEM::SHIP_INIT_MAX);
                //this->CreateShips(npc_race_id, ship_num);    
        //}
                      
        this->CreateSpaceStations(3);
}

  	
void StarSystemBuilder::CreateNewInternalsDebug()
{
        vec2f center(getRandInt(GUI::MAP::BORDER_X, Config::Instance().SCREEN_WIDTH -  2*GUI::MAP::BORDER_X), 
        	     getRandInt(GUI::MAP::BORDER_Y, Config::Instance().SCREEN_HEIGHT - 2*GUI::MAP::BORDER_Y) );			 
        starsystem->GetPoints().SetCenter(center);

        this->CreateStar();
        
        int distNebula_num = getRandInt(4,7);
        int distStar_num = getRandInt(40, 60);
        this->CreateBackground(distNebula_num, distStar_num, starsystem->GetStar()->GetColorId());
          
        //int planet_num = 1;//getRandInt(ENTITY::STARSYSTEM::PLANET_MIN, ENTITY::STARSYSTEM::PLANET_MAX);
        //this->CreatePlanets(planet_num);
        
        //this->CreateSpaceStations(3);
}

void StarSystemBuilder::CreateBackground(int distNebula_num, int distStar_num, int color_id)
{
        for(int i = 0; i < distNebula_num; i++)
        { 
		DistantNebulaEffect* dn = GetNewDistantNebulaEffect(-1);
                starsystem->Add(dn);
        } 

        for(int i = 0; i < distStar_num; i++)
        { 
		DistantStarEffect* ds = GetNewDistantStarEffect();
                starsystem->Add(ds);
        } 
}
                        	                
void StarSystemBuilder::CreateStar()
{
	StarBuilder::Instance().CreateNewStar();
	StarBuilder::Instance().CreateNewInternals();	
        Star* star = StarBuilder::Instance().GetStar();    
        starsystem->Add(star);
}

void StarSystemBuilder::CreatePlanets(int planet_per_system)
{
        int orbit_radius;
        int offset = 0;

        for(int pi = 0; pi < planet_per_system; pi++)
        {             
                if (pi == 0)
                        orbit_radius = getRandInt(2 * ENTITY::PLANET::DISTANCE_MIN, 2 * ENTITY::PLANET::DISTANCE_MAX);
                else
                        orbit_radius = offset + getRandInt(ENTITY::PLANET::DISTANCE_MIN, ENTITY::PLANET::DISTANCE_MAX);

                offset = orbit_radius;

                PlanetBuilder::Instance().CreateNewPlanet();
                PlanetBuilder::Instance().CreateNewInternals(orbit_radius);
                Planet* planet = PlanetBuilder::Instance().GetPlanet();

                starsystem->Add(planet, starsystem->GetStar());
                
                SatelliteBuilder::Instance().CreateNewSatellite();
                SatelliteBuilder::Instance().CreateNewInternals();
                Satellite* satellite = SatelliteBuilder::Instance().GetSatellite();
                SatelliteBuilder::Instance().Equip(satellite);           		// improove
                 
                {       	
                int npc_race_id = getRandIntFromVec(RaceInformationCollector.RACES_GOOD_vec);
                int npc_subtype_id = CLASS::WARRIOR_ID;
                
                NpcBuilder::Instance().CreateNewNpc();
        	NpcBuilder::Instance().CreateNewInternals(npc_race_id, npc_subtype_id);
                satellite->BindOwnerNpc(NpcBuilder::Instance().GetNpc());
                }
                
                starsystem->AddVehicle((Vehicle*)satellite, vec2f(0, 0), 0, planet);
        }
        
}

void StarSystemBuilder::CreateSpaceStations(int spacestation_per_system)
{       
    	for (int i=0; i<spacestation_per_system; i++)
    	{     
    		int npc_race_id = getRandIntFromVec(RaceInformationCollector.RACES_GOOD_vec);
                int npc_subtype_id = CLASS::WARRIOR_ID;

        	int ship_race_id = npc_race_id;         // RACES_ALL_vec[getRandInt(0, RACES_ALL_vec.size())];
        	int ship_subtype_id = npc_subtype_id;   // SHIP_SUBTYPE_vec[getRandInt(0, SHIP_SUBTYPE_vec.size())];
        	int ship_size_id = getRandInt(1, 9);
        	int weapons_num = 5;
        	
        	SpaceStationBuilder::Instance().CreateNewSpaceStation();
        	SpaceStationBuilder::Instance().CreateNewInternals();
        	SpaceStation* spacestation = SpaceStationBuilder::Instance().GetSpaceStation();
       
        	SpaceStationBuilder::Instance().Equip(spacestation);       	// improove
        	spacestation->UpdateAllPropertiesAndAbilities(); 	// improove

        	NpcBuilder::Instance().CreateNewNpc();
                NpcBuilder::Instance().CreateNewInternals(npc_race_id, npc_subtype_id); 
        	spacestation->BindOwnerNpc(NpcBuilder::Instance().GetNpc());

		vec2f center = getRandVec2f(700, 1500);
		float angle = getRandInt(0, 360);  
                
        	starsystem->AddVehicle(spacestation, center, angle, NULL);
        	
        	{  
                SatelliteBuilder::Instance().CreateNewSatellite();
                SatelliteBuilder::Instance().CreateNewInternals();
                Satellite* satellite = SatelliteBuilder::Instance().GetSatellite();
                SatelliteBuilder::Instance().Equip(satellite);           		// improove
                   	
                NpcBuilder::Instance().CreateNewNpc();
        	NpcBuilder::Instance().CreateNewInternals(npc_race_id, npc_subtype_id);
                satellite->BindOwnerNpc(NpcBuilder::Instance().GetNpc());
                
                starsystem->AddVehicle((Vehicle*)satellite, vec2f(0, 0), 0, spacestation);
    		}
    	}        
}

void StarSystemBuilder::CreateShips(int npc_race_id, int ship_num, int requestedclass)
{
    	int npc_subtype_id;

    	for (int i=0; i<ship_num; i++)
    	{     
    		if (requestedclass == NONE_ID)
    		{
                	switch(npc_race_id)
                	{
                        	case RACE::R0_ID: { npc_subtype_id = getRandIntFromVec(RaceInformationCollector.RACE0_ALLOWED_SUBTYPE_vec);  break; }
                        	case RACE::R1_ID: { npc_subtype_id = getRandIntFromVec(RaceInformationCollector.RACE1_ALLOWED_SUBTYPE_vec);  break; }
                        	case RACE::R2_ID: { npc_subtype_id = getRandIntFromVec(RaceInformationCollector.RACE2_ALLOWED_SUBTYPE_vec);  break; }
                        	case RACE::R3_ID: { npc_subtype_id = getRandIntFromVec(RaceInformationCollector.RACE3_ALLOWED_SUBTYPE_vec);  break; }
                        	case RACE::R4_ID: { npc_subtype_id = getRandIntFromVec(RaceInformationCollector.RACE4_ALLOWED_SUBTYPE_vec);  break; }
                        	case RACE::R6_ID: { npc_subtype_id = getRandIntFromVec(RaceInformationCollector.RACE6_ALLOWED_SUBTYPE_vec);  break; }
                        	case RACE::R7_ID: { npc_subtype_id = getRandIntFromVec(RaceInformationCollector.RACE7_ALLOWED_SUBTYPE_vec);  break; }
                	}
                }
                else
                {
                	npc_subtype_id = requestedclass;
                }   

        	int ship_race_id = npc_race_id;         
        	int ship_subtype_id = npc_subtype_id;  
        	int ship_size_id = getRandInt(1, 9);
        	int weapons_num = getRandInt(1, 5);
        	ShipBuilder::Instance().CreateNewShip();
        	ShipBuilder::Instance().CreateNewInternals(ship_race_id, ship_subtype_id, ship_size_id, weapons_num);
        	Ship* ship = ShipBuilder::Instance().GetShip();
       
        	ShipBuilder::Instance().Equip(ship);            	// improove

        	NpcBuilder::Instance().CreateNewNpc();
        	NpcBuilder::Instance().CreateNewInternals(npc_race_id, npc_subtype_id);
        	ship->BindOwnerNpc(NpcBuilder::Instance().GetNpc());

		vec2f center = getRandVec2f(300, 1200);
		float angle = getRandInt(0, 360);  
		
        	starsystem->AddVehicle(ship, center, angle, NULL);
    	}
}


