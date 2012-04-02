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

void StarSystemBuilder::CreateNewStarSystem()
{
        starsystem = new StarSystem();
} 
        	
void StarSystemBuilder::CreateInternals()
{
        vec2f center(getRandInt(GUI::MAP::BORDER_X, Config::Instance().SCREEN_WIDTH - 2*GUI::MAP::BORDER_X), 
        	     getRandInt(GUI::MAP::BORDER_Y, Config::Instance().SCREEN_HEIGHT - 2*GUI::MAP::BORDER_Y) );			 
        starsystem->GetPoints().setCenter(center);

        this->CreateStar();
        
        int distNebula_num = getRandInt(4,7);
        int distStar_num = getRandInt(40, 60);
        this->CreateBackground(distNebula_num, distStar_num, starsystem->GetStar()->getColorId());
          
        int planet_num = getRandInt(ENTITY::STARSYSTEM::PLANET_MIN, ENTITY::STARSYSTEM::PLANET_MAX);
        this->CreatePlanets(planet_num);
        
        for (int i = 0; i < 10; i++)
        {
        	BlackHole* bh = getNewBlackHole();
        	starsystem->AddToSpace(bh, vec2f((float)getRandInt(0, 3000), (float)getRandInt(0, 3000)));
        }

        if (getRandBool())
        {
                int npc_race_id = RACES_GOOD_LIST[getRandInt(0, RACES_GOOD_LIST.size())];
                int ship_num = getRandInt(ENTITY::STARSYSTEM::SHIP_INIT_MIN, ENTITY::STARSYSTEM::SHIP_INIT_MAX);
                this->CreateShips(npc_race_id, ship_num);
        }
        else
        {
                int npc_race_id = RACES_EVIL_LIST[getRandInt(0, RACES_EVIL_LIST.size())];
                int ship_num = getRandInt(ENTITY::STARSYSTEM::SHIP_INIT_MIN, ENTITY::STARSYSTEM::SHIP_INIT_MAX);
                this->CreateShips(npc_race_id, ship_num);    
        }
                      
        this->CreateSpaceStations(3);
}

void StarSystemBuilder::CreateBackground(int distNebula_num, int distStar_num, int color_id)
{
        for(int i = 0; i < distNebula_num; i++)
        { 
		DistantNebulaBgEffect* dn = createDistantNebula(color_id);
                starsystem->AddToSpace(dn);
        } 

        for(int i = 0; i < distStar_num; i++)
        { 
		DistantStarBgEffect* ds = getNewDistantStarBgEffect();
                starsystem->AddToSpace(ds);
        } 
}
                        	                
void StarSystemBuilder::CreateStar()
{
        Star* star = getNewStar();    
        starsystem->AddToSpace(star);
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

                Planet* planet = getNewPlanet(orbit_radius);

                starsystem->AddToSpace(planet, starsystem->GetStar());
                
                Satellite* satellite = VehicleBuilder::Instance().GetNewSatellite();
                VehicleBuilder::Instance().Equip(satellite);           		// improove
                        	
                starsystem->AddToSpace((Vehicle*)satellite, vec2f(0, 0), 0, planet);
        }
        
}

void StarSystemBuilder::CreateSattelites()
{}

void StarSystemBuilder::CreateSpaceStations(int spacestation_per_system)
{
        int npc_subtype_id;
    	int npc_race_id = RACES_EVIL_LIST[getRandInt(0, RACES_EVIL_LIST.size())];
        
    	for (int i=0; i<spacestation_per_system; i++)
    	{     
       		//npc_subtype_id = SHIP_SUBTYPE_LIST[getRandInt(0, RACES_EVIL_LIST.size())];
                npc_subtype_id = CLASS::WARRIOR_ID;

        	Npc* npc = getNewNpc(npc_race_id, npc_subtype_id);

        	int ship_race_id = npc_race_id;         // RACES_ALL_LIST[getRandInt(0, RACES_ALL_LIST.size())];
        	int ship_subtype_id = npc_subtype_id;   // SHIP_SUBTYPE_LIST[getRandInt(0, SHIP_SUBTYPE_LIST.size())];
        	int ship_size_id = getRandInt(1, 9);
        	int weapons_num = 5;
        	SpaceStation* spacestation = VehicleBuilder::Instance().GetNewSpaceStation();
       
        	VehicleBuilder::Instance().Equip(spacestation);       	// improove
        	spacestation->UpdateAllPropertiesAndAbilities(); 	// improove
        
        	npc->Bind(spacestation);

		vec2f center(getRandInt(0, 800), getRandInt(0, 800));
		float angle = getRandInt(0, 360);  
                
        	starsystem->AddToSpace(spacestation, center, angle, NULL);
        	
		Satellite* satellite = VehicleBuilder::Instance().GetNewSatellite();
                VehicleBuilder::Instance().Equip(satellite);           		// improove
                        	
                starsystem->AddToSpace((Vehicle*)satellite, vec2f(0, 0), 0, spacestation);
    	}        
}

void StarSystemBuilder::CreateShips(int npc_race_id, int ship_num)
{
    	int npc_subtype_id;

    	for (int i=0; i<ship_num; i++)
    	{     
                switch(npc_race_id)
                {
                        case RACE::R0_ID: { npc_subtype_id = RACE0_ALLOWED_SUBTYPE_LIST[getRandInt(0, RACE0_ALLOWED_SUBTYPE_LIST.size())];  break; }
                        case RACE::R1_ID: { npc_subtype_id = RACE1_ALLOWED_SUBTYPE_LIST[getRandInt(0, RACE1_ALLOWED_SUBTYPE_LIST.size())];  break; }
                        case RACE::R2_ID: { npc_subtype_id = RACE2_ALLOWED_SUBTYPE_LIST[getRandInt(0, RACE2_ALLOWED_SUBTYPE_LIST.size())];  break; }
                        case RACE::R3_ID: { npc_subtype_id = RACE3_ALLOWED_SUBTYPE_LIST[getRandInt(0, RACE3_ALLOWED_SUBTYPE_LIST.size())];  break; }
                        case RACE::R4_ID: { npc_subtype_id = RACE4_ALLOWED_SUBTYPE_LIST[getRandInt(0, RACE4_ALLOWED_SUBTYPE_LIST.size())];  break; }
                        case RACE::R6_ID: { npc_subtype_id = RACE6_ALLOWED_SUBTYPE_LIST[getRandInt(0, RACE6_ALLOWED_SUBTYPE_LIST.size())];  break; }
                        case RACE::R7_ID: { npc_subtype_id = RACE7_ALLOWED_SUBTYPE_LIST[getRandInt(0, RACE7_ALLOWED_SUBTYPE_LIST.size())];  break; }
                }   
           		
        	Npc* npc = getNewNpc(npc_race_id, npc_subtype_id);

        	int ship_race_id = npc_race_id;         // RACES_ALL_LIST[getRandInt(0, RACES_ALL_LIST.size())];
        	int ship_subtype_id = npc_subtype_id;   // SHIP_SUBTYPE_LIST[getRandInt(0, SHIP_SUBTYPE_LIST.size())];
        	int ship_size_id = getRandInt(1, 9);
        	int weapons_num = getRandInt(1, 5);
        	Ship* ship = VehicleBuilder::Instance().GetNewShip(ship_race_id, ship_subtype_id, ship_size_id, weapons_num);
       
        	VehicleBuilder::Instance().Equip(ship);            	// improove
        	ship->UpdateAllPropertiesAndAbilities(); 		// improove
        
        	npc->Bind(ship);

		vec2f center(getRandInt(0, 800), getRandInt(0, 800));
		float angle = getRandInt(0, 360);  
		
        	starsystem->AddToSpace(ship, center, angle, NULL);
    	}
}


