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

#include "galaxy.hpp"

Galaxy :: Galaxy()
{ 
    	starsytem_counter = 0;
    	star_counter      = 0;
    	ship_counter      = 0;
    	planet_counter    = 0;

     	//allow_single_calc_inDynamic = true;
     	//allow_single_calc_inStatic  = true;
     		
    	while(starsytem_counter < STARSYSTEM_TOTAL_NUM)
    	{  
        	
        	STARSYSTEM_vec.push_back(generateEntireStarSystem());
        	starsytem_counter++;
    	}
}



StarSystem* Galaxy :: getRandomStarSystem()
{
	return STARSYSTEM_vec[getRandInt(0, STARSYSTEM_vec.size())];
}


StarSystem* Galaxy :: getRandomCapturedStarSystem()
{
	std::vector<StarSystem*> ss_vec;
	
	for (unsigned int i = 0; i<STARSYSTEM_vec.size(); i++)
	{
		if (STARSYSTEM_vec[i]->getCaptured() == true)
		{
			ss_vec.push_back(STARSYSTEM_vec[i]);
		}
	}
	
	return ss_vec[getRandInt(0, ss_vec.size())];
}
     		

void Galaxy :: update(int timer)
{
	for (unsigned int si = 0; si < STARSYSTEM_vec.size(); si++)
     	{
     		if (g_DEBUG == false)
     		{
     			if (STARSYSTEM_vec[si]->getDetailedSimulationFlag() == true)
     				STARSYSTEM_vec[si]->update_TRUE(timer);
     			else
     		     		STARSYSTEM_vec[si]->update_FALSE(timer);     		     	
     		}
     	}
     	
	if (g_DEBUG == true)
	{
		pPLAYER->getStarSystem()->update_TRUE(timer);
	}
}
























StarSystem* generateEntireStarSystem()
{  
        StarSystem* starsystem = new StarSystem();   
        
        vec2f _center(getRandInt(MAP_OFFSET_X, g_VIEW_WIDTH - 3*MAP_OFFSET_X), g_VIEW_HEIGHT - getRandInt(MAP_OFFSET_Y, g_VIEW_HEIGHT - 2*MAP_OFFSET_Y) );			 
        starsystem->setPosition(_center);

        Star* star = createStar();    
        starsystem->add(star);
        
        int distNebula_maxNum = getRandInt(4,7);
        int distStar_maxNum = getRandInt(40, 60);
        generateBackground(starsystem, distNebula_maxNum, distStar_maxNum, star->getColorId());
          
        generateNumPlanets(starsystem, getRandInt(PLANET_PER_SYSTEM_MIN, PLANET_PER_SYSTEM_MAX));

	starsystem->setCapturedFlag(getRandBool());
        if (starsystem->getCaptured() == false)
                generateNumFriendlyNPC(starsystem, getRandInt(SHIP_PER_SYSTEM_MIN, SHIP_PER_SYSTEM_MAX));
        else
                generateNumEnemyNPC(starsystem, getRandInt(ENEMY_SHIP_PER_SYSTEM_MIN, ENEMY_SHIP_PER_SYSTEM_MAX));
                      
        return starsystem; 
}




void generateBackground(StarSystem* starsystem, int distNebula_maxNum, int distStar_maxNum, int _color_id)
{
        for(int i = 0; i < distNebula_maxNum; i++)
        { 
		DistantNebulaBgEffect* dn = createDistantNebula(_color_id);
                starsystem->add(dn);
        } 

        for(int i = 0; i < distStar_maxNum; i++)
        { 
		DistantStarBgEffect* ds = createDistantStar();
                starsystem->add(ds);
        } 
}


void generateNumPlanets(StarSystem* starsystem, int planet_per_system)
{   
        int orbit_radius;
        int offset = 0;

        for(int pi = 0; pi < planet_per_system; pi++)
        {             
                if (pi == 0)
                        orbit_radius = getRandInt(2 * PLANET_DISTANCE_MIN, 2 * PLANET_DISTANCE_MAX);
                else
                        orbit_radius = offset + getRandInt(PLANET_DISTANCE_MIN, PLANET_DISTANCE_MAX);

                offset = orbit_radius;

                Planet* planet = createPlanet(orbit_radius);
                starsystem->add(planet);
        }
}

    


void generateNumFriendlyNPC(StarSystem* starsystem, int ship_per_system)
{
    	int npc_subtype_id;
    	int npc_race_id = RACES_GOOD_LIST[getRandInt(0, RACES_GOOD_LIST.size())];

    	for (int i=0; i<ship_per_system; i++)
    	{     
        	if (npc_race_id != RACE_4_ID)
           		npc_subtype_id = SHIP_SUBTYPE_LIST[getRandInt(0, SHIP_SUBTYPE_LIST.size())];
        	else
           		npc_subtype_id = RACE4_ALLOWED_SUBTYPE_LIST[getRandInt(0, RACE4_ALLOWED_SUBTYPE_LIST.size())];

        	Npc* npc = generateNpc(npc_race_id, npc_subtype_id);

        	int ship_race_id = npc_race_id;         // RACES_ALL_LIST[getRandInt(0, RACES_ALL_LIST.size())];
        	int ship_subtype_id = npc_subtype_id;   // SHIP_SUBTYPE_LIST[getRandInt(0, SHIP_SUBTYPE_LIST.size())];
        	int ship_size_id = getRandInt(1, 9);
        	Ship* ship = shipGenerator(ship_race_id, ship_subtype_id, ship_size_id);
       
        	equip(ship);            		// improove
        	ship->updateAllStuff(); 		// improove
        
        	npc->bind(ship);

        	starsystem->moveToSpace(ship);
        	starsystem->moveToSpace(npc);
    	}
}

         

void generateNumEnemyNPC(StarSystem* starsystem, int ship_per_system)
{
	int npc_subtype_id;
    	int npc_race_id = RACES_EVIL_LIST[getRandInt(0, RACES_EVIL_LIST.size())];
        
    	for (int i=0; i<ship_per_system; i++)
    	{     
       		//npc_subtype_id = SHIP_SUBTYPE_LIST[getRandInt(0, RACES_EVIL_LIST.size())];
                npc_subtype_id = WARRIOR_ID;

        	Npc* npc = generateNpc(npc_race_id, npc_subtype_id);

        	int ship_race_id = npc_race_id;         // RACES_ALL_LIST[getRandInt(0, RACES_ALL_LIST.size())];
        	int ship_subtype_id = npc_subtype_id;   // SHIP_SUBTYPE_LIST[getRandInt(0, SHIP_SUBTYPE_LIST.size())];
        	int ship_size_id = getRandInt(1, 9);
        	Ship* ship = shipGenerator(ship_race_id, ship_subtype_id, ship_size_id);
       
        	equip(ship);            		// improove
        	ship->updateAllStuff(); 		// improove
        
        	npc->bind(ship);

        	starsystem->moveToSpace(ship);
        	starsystem->moveToSpace(npc);
    	}

}

