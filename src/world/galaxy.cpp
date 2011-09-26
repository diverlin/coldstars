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
    	// map
    	map_rect = Rect(MAP_OFFSET_X, MAP_OFFSET_Y, (g_VIEW_WIDTH - 2 * MAP_OFFSET_X), (g_VIEW_HEIGHT - 2 * MAP_OFFSET_X));

    	RACES_ALL_LIST.push_back(RACE_0_ID);
    	RACES_ALL_LIST.push_back(RACE_1_ID);
    	RACES_ALL_LIST.push_back(RACE_2_ID);
    	RACES_ALL_LIST.push_back(RACE_3_ID);
    	RACES_ALL_LIST.push_back(RACE_4_ID);
   	RACES_ALL_LIST.push_back(RACE_6_ID);
    	RACES_ALL_LIST.push_back(RACE_7_ID);

    	RACES_GOOD_LIST.push_back(RACE_0_ID);
    	RACES_GOOD_LIST.push_back(RACE_1_ID);
   	RACES_GOOD_LIST.push_back(RACE_2_ID);
    	RACES_GOOD_LIST.push_back(RACE_3_ID);
    	RACES_GOOD_LIST.push_back(RACE_4_ID);

    	RACES_EVIL_LIST.push_back(RACE_6_ID);
    	RACES_EVIL_LIST.push_back(RACE_7_ID);

    	SHIP_SUBTYPE_LIST.push_back(RANGER_ID);
    	SHIP_SUBTYPE_LIST.push_back(WARRIOR_ID);
    	SHIP_SUBTYPE_LIST.push_back(PIRAT_ID);
    	SHIP_SUBTYPE_LIST.push_back(TRADER_ID);
   	SHIP_SUBTYPE_LIST.push_back(DIPLOMAT_ID);
            
    	RACE4_ALLOWED_SUBTYPE_LIST.push_back(WARRIOR_ID);
    	RACE4_ALLOWED_SUBTYPE_LIST.push_back(TRADER_ID);
    	RACE4_ALLOWED_SUBTYPE_LIST.push_back(DIPLOMAT_ID);

    	starsytem_counter = 0;
    	star_counter      = 0;
    	ship_counter      = 0;
    	planet_counter    = 0;

    	while(starsytem_counter < STARSYSTEM_TOTAL_NUM)
    	{  
        	generateEntireStarSystem();
        	starsytem_counter++;
    	}

   	//manageHiddenStarSystemList(ss_active);
}



StarSystem* Galaxy :: getRandomStarSystem()
{
	if (STARSYSTEM_pList.size() == 1)
       		return STARSYSTEM_pList[0];
    	else
      		return STARSYSTEM_pList[randIntInRange(0, STARSYSTEM_pList.size())];
}
     		

void Galaxy :: generateEntireStarSystem()
{  
        StarSystem* _starsystem = new StarSystem();   
        STARSYSTEM_pList.push_back(_starsystem);

        Rect ssOnMapRect = Rect( randIntInRange( MAP_OFFSET_X, (g_VIEW_WIDTH - 3*MAP_OFFSET_X)),
        			 g_VIEW_HEIGHT - randIntInRange( MAP_OFFSET_Y, (g_VIEW_HEIGHT - 2*MAP_OFFSET_Y)),
        			 40, 40);
        			 
        _starsystem->setPositionOnWorldMap(ssOnMapRect);

        Star* _star = createStar();    
        _starsystem->addStar(_star);
        
        int distNebula_maxNum = randIntInRange(4,7);
        int distStar_maxNum = randIntInRange(40, 60);
        generateBackground(_starsystem, distNebula_maxNum, distStar_maxNum, _star->getColorId());
          
        generateNumPlanets(_starsystem, randIntInRange(PLANET_PER_SYSTEM_MIN, PLANET_PER_SYSTEM_MAX));

        if (_starsystem->is_CAPTURED == false)
                generateNumFriendlyNPC(_starsystem, randIntInRange(SHIP_PER_SYSTEM_MIN, SHIP_PER_SYSTEM_MAX));
        else
                generateNumEnemyNPC(_starsystem, randIntInRange(ENEMY_SHIP_PER_SYSTEM_MIN, ENEMY_SHIP_PER_SYSTEM_MAX));
       
        if (USE_MODERN_HW == true)
                _starsystem->createPostProcessStuff();  // remove
}




void Galaxy :: generateBackground(StarSystem* _starsystem, int distNebula_maxNum, int distStar_maxNum, int _color_id)
{
        for(int i = 0; i < distNebula_maxNum; i++)
        { 
		DistantNebulaBgEffect* dn = createDistantNebula(_color_id);
                _starsystem->addDistantNebula(dn);
        } 

        for(int i = 0; i < distStar_maxNum; i++)
        { 
		DistantStarBgEffect* ds = createDistantStar();
                _starsystem->addDistantStar(ds);
        } 
}


void Galaxy :: generateNumPlanets(StarSystem* _starsystem, int planet_per_system)
{   
        int orbit_radius;
        int offset = 0;

        for(int pi = 0; pi< planet_per_system; pi++)
        {             
                if (pi == 0)
                        orbit_radius = randIntInRange(2 * PLANET_DISTANCE_MIN, 2 * PLANET_DISTANCE_MAX);
                else
                        orbit_radius = offset + randIntInRange(PLANET_DISTANCE_MIN, PLANET_DISTANCE_MAX);

                offset = orbit_radius;

                Planet* _planet = createPlanet(orbit_radius);
                _starsystem->addPlanet(_planet);
        }
}

    


void Galaxy :: generateNumFriendlyNPC(StarSystem* _starsystem, int ship_per_system)
{
    	int npc_subtype_id;
    	int npc_race_id = RACES_GOOD_LIST[randIntInRange(0, RACES_GOOD_LIST.size())];

    	for (int i=0; i<ship_per_system; i++)
    	{     
        	if (npc_race_id != RACE_4_ID)
           		npc_subtype_id = SHIP_SUBTYPE_LIST[randIntInRange(0, RACES_GOOD_LIST.size())];
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

        	_starsystem->addShipToSpace(ship);
        	_starsystem->addNpcToSpace(npc);
    	}
}

         

void Galaxy :: generateNumEnemyNPC(StarSystem* _pTo_starsystem, int ship_per_system)
{}



void Galaxy :: manageHiddenStarSystemList(StarSystem* _ss_active)
{
     hSTARSYSTEM_pList.clear(); // should be improoved
     for (unsigned int ssi = 0; ssi < STARSYSTEM_pList.size(); ssi++)    // should be improoved
          if (STARSYSTEM_pList[ssi]->id != _ss_active->id)
             hSTARSYSTEM_pList.push_back(STARSYSTEM_pList[ssi]);
}


      //def updateRange(self, k):
          //if k.korpus.drive_slot.item != None and k.korpus.bak_slot.item != None:
             //radius_min = min(k.korpus.drive_slot.item.hyper , k.korpus.bak_slot.item.fuel)
             //self.range_list_x, self.range_list_y = getCircleCoordinateRangeLowPrecision(k.starsystem.rectOnMap.centerx, k.starsystem.rectOnMap.centery, radius_min)
             //self.GL_LIST_range_ID = GlListCompileDirection(DOT_RED_TEX, self.range_list_x, self.range_list_y, len(self.range_list_x), 1, 10)
          //else:
             //self.GL_LIST_range_ID = None

bool Galaxy :: manage_map()
{
     if (pPLAYER->getShip()->ableTo.HJUMP == true)
     {
        int mx  = g_MOUSE_POS_X;
        int my  = g_VIEW_HEIGHT - g_MOUSE_POS_Y; 
        int lmb = g_MOUSE_LEFT_BUTTON;
   
        for (unsigned int si = 0; si < STARSYSTEM_pList.size(); si++)
        {
            //if (STARSYSTEM_pList[si]->id != pTo_PLAYER->pTo_starsystem->id)
            {
                float ss_cursor_dist = distBetweenCenters(STARSYSTEM_pList[si]->rect_onMap.getCenter().x, STARSYSTEM_pList[si]->rect_onMap.getCenter().y, mx, my);
                if (ss_cursor_dist < 10)
                { 
                   int ss_ss_dist = distBetweenCenters(STARSYSTEM_pList[si]->rect_onMap.getCenter().x, 
                   				       STARSYSTEM_pList[si]->rect_onMap.getCenter().y,
                   				       pPLAYER->getPilot()->getStarSystem()->rect_onMap.getCenter().x,  
                   				       pPLAYER->getPilot()->getStarSystem()->rect_onMap.getCenter().y);
                   				       
                   if ( (ss_ss_dist < pPLAYER->getShip()->drive_slot.getDriveEquipment()->getHyper()) && (ss_ss_dist < pPLAYER->getShip()->bak_slot.getBakEquipment()->getFuel()) )
                      if (lmb == true)
                      { 
                          pPLAYER->setActiveStarSystem(STARSYSTEM_pList[si]);    // debug
                          //player.hyperJumpPreparation(ss)
                          //#player.calculateTraceToCoord((player.jump_pos_x, player.jump_pos_y))
                          printf("ss_id = %i\n", STARSYSTEM_pList[si]->id);    // debug
                          manageHiddenStarSystemList(pPLAYER->getActiveStarSystem());

                          return true;
                      } 
                }
            }
        }

     }
     return false;
}

void Galaxy :: render_map()
{
    glLoadIdentity();    // !!!!

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    TextureOb* pTo_textbg_texOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.textBackground_texOb_pList);
    TextureOb* pTo_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);  

    drawTexturedRect(pTo_textbg_texOb->texture, map_rect, -1);
    for (unsigned int si = 0; si < STARSYSTEM_pList.size(); si++)
    {
        int font_size = 10;
        drawTexturedRect(pTo_particleTexOb->texture, STARSYSTEM_pList[si]->rect_onMap, -1);
        drawSimpleText(int2str(STARSYSTEM_pList[si]->id), 
        	       font_size, 
        	       STARSYSTEM_pList[si]->rect_onMap.getBottomLeft().x, 
        	       STARSYSTEM_pList[si]->rect_onMap.getBottomLeft().y);
        	       
        //if ss.CAPTURED == True:
           //drawTexturedRect(mark_enemy_ss_tex, [ss.rectOnMap[0] - 10, ss.rectOnMap[1] - 10, ss.rectOnMap[2] + 20, ss.rectOnMap[3] + 20], -1)
    } 
           //drawTexturedRect(mark_ss_tex, [player.starsystem.rectOnMap[0] - 10, player.starsystem.rectOnMap[1] - 10, player.starsystem.rectOnMap[2] + 20, player.starsystem.rectOnMap[3] + 20], -1)

    //if self.GL_LIST_range_ID != None:
       //glCallList(self.GL_LIST_range_ID)
     
    //glDisable(GL_BLEND)
}


