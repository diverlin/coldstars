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

    	while(starsytem_counter < STARSYSTEM_TOTAL_NUM)
    	{  
        	
        	STARSYSTEM_pList.push_back(generateEntireStarSystem());
        	starsytem_counter++;
    	}
}



StarSystem* Galaxy :: getRandomStarSystem()
{
	if (STARSYSTEM_pList.size() == 1)
       		return STARSYSTEM_pList[0];
    	else
      		return STARSYSTEM_pList[randIntInRange(0, STARSYSTEM_pList.size())];
}
     		

void Galaxy :: update(int timer)
{
	for (unsigned int si = 0; si < STARSYSTEM_pList.size(); si++)
     	{
     		if (STARSYSTEM_pList[si]->getDetailedSimulation() == true)
     			STARSYSTEM_pList[si]->update_TRUE(timer);
     		else
     		     	STARSYSTEM_pList[si]->update_FALSE(timer);
     	}
}
























StarSystem* generateEntireStarSystem()
{  
        StarSystem* starsystem = new StarSystem();   
        Rect ssOnMapRect = Rect( randIntInRange( MAP_OFFSET_X, (g_VIEW_WIDTH - 3*MAP_OFFSET_X)),
        			 g_VIEW_HEIGHT - randIntInRange( MAP_OFFSET_Y, (g_VIEW_HEIGHT - 2*MAP_OFFSET_Y)),
        			 40, 40);
        			 
        starsystem->setPositionOnWorldMap(ssOnMapRect);

        Star* star = createStar();    
        starsystem->addStar(star);
        
        int distNebula_maxNum = randIntInRange(4,7);
        int distStar_maxNum = randIntInRange(40, 60);
        generateBackground(starsystem, distNebula_maxNum, distStar_maxNum, star->getColorId());
          
        generateNumPlanets(starsystem, randIntInRange(PLANET_PER_SYSTEM_MIN, PLANET_PER_SYSTEM_MAX));

	starsystem->is_CAPTURED = getRandomBool();
        if (starsystem->is_CAPTURED == false)
                generateNumFriendlyNPC(starsystem, randIntInRange(SHIP_PER_SYSTEM_MIN, SHIP_PER_SYSTEM_MAX));
        else
                generateNumEnemyNPC(starsystem, randIntInRange(ENEMY_SHIP_PER_SYSTEM_MIN, ENEMY_SHIP_PER_SYSTEM_MAX));
                      
        return starsystem; 
}




void generateBackground(StarSystem* starsystem, int distNebula_maxNum, int distStar_maxNum, int _color_id)
{
        for(int i = 0; i < distNebula_maxNum; i++)
        { 
		DistantNebulaBgEffect* dn = createDistantNebula(_color_id);
                starsystem->addDistantNebula(dn);
        } 

        for(int i = 0; i < distStar_maxNum; i++)
        { 
		DistantStarBgEffect* ds = createDistantStar();
                starsystem->addDistantStar(ds);
        } 
}


void generateNumPlanets(StarSystem* starsystem, int planet_per_system)
{   
        int orbit_radius;
        int offset = 0;

        for(int pi = 0; pi < planet_per_system; pi++)
        {             
                if (pi == 0)
                        orbit_radius = randIntInRange(2 * PLANET_DISTANCE_MIN, 2 * PLANET_DISTANCE_MAX);
                else
                        orbit_radius = offset + randIntInRange(PLANET_DISTANCE_MIN, PLANET_DISTANCE_MAX);

                offset = orbit_radius;

                Planet* planet = createPlanet(orbit_radius);
                starsystem->addPlanet(planet);
        }
}

    


void generateNumFriendlyNPC(StarSystem* starsystem, int ship_per_system)
{
    	int npc_subtype_id;
    	int npc_race_id = RACES_GOOD_LIST[randIntInRange(0, RACES_GOOD_LIST.size())];

    	for (int i=0; i<ship_per_system; i++)
    	{     
        	if (npc_race_id != RACE_4_ID)
           		npc_subtype_id = SHIP_SUBTYPE_LIST[randIntInRange(0, SHIP_SUBTYPE_LIST.size())];
        	else
           		npc_subtype_id = RACE4_ALLOWED_SUBTYPE_LIST[randIntInRange(0, RACE4_ALLOWED_SUBTYPE_LIST.size())];

        	TextureOb* texOb_npc  = g_TEXTURE_MANAGER.returnPointerToRandomFaceTexObWithFolloingAttributes(npc_race_id);
        	Npc* npc = new Npc(npc_race_id, npc_subtype_id, texOb_npc);

        	int ship_race_id = npc_race_id;         // RACES_ALL_LIST[randIntInRange(0, RACES_ALL_LIST.size())];
        	int ship_subtype_id = npc_subtype_id;   // SHIP_SUBTYPE_LIST[randIntInRange(0, SHIP_SUBTYPE_LIST.size())];
        	int ship_size_id = randIntInRange(1, 9);
        	Ship* ship = shipGenerator(ship_race_id, ship_subtype_id, ship_size_id);
       
        	equip(ship);            		// improove
        	ship->updateAllStuff(); 		// improove
        
        	npc->bind(ship);

        	starsystem->addShipToSpace(ship);
        	starsystem->addNpcToSpace(npc);
    	}
}

         

void generateNumEnemyNPC(StarSystem* starsystem, int ship_per_system)
{
	int npc_subtype_id;
    	int npc_race_id = RACES_EVIL_LIST[randIntInRange(0, RACES_EVIL_LIST.size())];
        
    	for (int i=0; i<ship_per_system; i++)
    	{     
       		//npc_subtype_id = SHIP_SUBTYPE_LIST[randIntInRange(0, RACES_EVIL_LIST.size())];
                npc_subtype_id = WARRIOR_ID;

        	TextureOb* texOb_npc  = g_TEXTURE_MANAGER.returnPointerToRandomFaceTexObWithFolloingAttributes(npc_race_id);
        	Npc* npc = new Npc(npc_race_id, npc_subtype_id, texOb_npc);

        	int ship_race_id = npc_race_id;         // RACES_ALL_LIST[randIntInRange(0, RACES_ALL_LIST.size())];
        	int ship_subtype_id = npc_subtype_id;   // SHIP_SUBTYPE_LIST[randIntInRange(0, SHIP_SUBTYPE_LIST.size())];
        	int ship_size_id = randIntInRange(1, 9);
        	Ship* ship = shipGenerator(ship_race_id, ship_subtype_id, ship_size_id);
       
        	equip(ship);            		// improove
        	ship->updateAllStuff(); 		// improove
        
        	npc->bind(ship);

        	starsystem->addShipToSpace(ship);
        	starsystem->addNpcToSpace(npc);
    	}

}

