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

#include "spaceMap.hpp"

SpaceMap :: SpaceMap()
{ 
	galaxy = NULL;
    	rect = Rect(MAP_OFFSET_X, MAP_OFFSET_Y, (g_VIEW_WIDTH - 2 * MAP_OFFSET_X), (g_VIEW_HEIGHT - 2 * MAP_OFFSET_X));
}


void SpaceMap :: bindGalaxy(Galaxy* _galaxy)
{
	galaxy = _galaxy;
}


bool SpaceMap :: update()
{
     	if (pPLAYER->getShip()->ableTo.HJUMP == true)
     	{
        	int mx  = g_MOUSE_POS_X;
        	int my  = g_VIEW_HEIGHT - g_MOUSE_POS_Y; 
        	int lmb = g_MOUSE_LEFT_BUTTON;
   
        	for (unsigned int si = 0; si < galaxy->STARSYSTEM_pList.size(); si++)
        	{
            		//if (STARSYSTEM_pList[si]->id != pTo_PLAYER->pTo_starsystem->id)
            		{
                		float ss_cursor_dist = distBetweenCenters(galaxy->STARSYSTEM_pList[si]->getRectOnMap().getCenter(), mx, my);
                		if (ss_cursor_dist < 10)
                		{ 
                   			int ss_ss_dist = distBetweenCenters(galaxy->STARSYSTEM_pList[si]->getRectOnMap().getCenter(), 
                   				       			    pPLAYER->getPilot()->getStarSystem()->getRectOnMap().getCenter() );
                   				       
                   			if ( (ss_ss_dist < pPLAYER->getShip()->drive_slot.getDriveEquipment()->getHyper()) && (ss_ss_dist < pPLAYER->getShip()->bak_slot.getBakEquipment()->getFuel()) )
                      			{
                      				if (lmb == true)
                      				{ 
                          				pPLAYER->setActiveStarSystem(galaxy->STARSYSTEM_pList[si]);    // debug
                          				//player.hyperJumpPreparation(ss)
                          				//#player.calculateTraceToCoord((player.jump_pos_x, player.jump_pos_y))
                          				printf("ss_id = %i\n", galaxy->STARSYSTEM_pList[si]->getId());    // debug
                          				//manageHiddenStarSystemList(pPLAYER->getActiveStarSystem());

                          				return true;
                      				} 
                      			}
                		}
            		}
        	}

     	}
     	
     	return false;
}



void SpaceMap :: render(bool _clrscr)
{
        if (_clrscr)
        {
                clearScreen();
        }
        resetRenderTransformation();
        
        enable_BLEND();                                                

    	TextureOb* pTo_textbg_texOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.textBackground_texOb_pList);
    	TextureOb* pTo_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);  

    	drawTexturedRect(pTo_textbg_texOb->texture, rect, -1);
    	for (unsigned int si = 0; si < galaxy->STARSYSTEM_pList.size(); si++)
    	{
        	int font_size = 10;
        	drawTexturedRect(pTo_particleTexOb->texture, galaxy->STARSYSTEM_pList[si]->getRectOnMap(), -1);
        	drawSimpleText(int2str(galaxy->STARSYSTEM_pList[si]->getId()), 
        	       		font_size, 
        	       		galaxy->STARSYSTEM_pList[si]->getRectOnMap().getBottomLeft().x, 
        	       		galaxy->STARSYSTEM_pList[si]->getRectOnMap().getBottomLeft().y);
        	       
        	//if ss.CAPTURED == True:
           		//drawTexturedRect(mark_enemy_ss_tex, [ss.rectOnMap[0] - 10, ss.rectOnMap[1] - 10, ss.rectOnMap[2] + 20, ss.rectOnMap[3] + 20], -1)
    	} 
           	//drawTexturedRect(mark_ss_tex, [player.starsystem.rectOnMap[0] - 10, player.starsystem.rectOnMap[1] - 10, player.starsystem.rectOnMap[2] + 20, player.starsystem.rectOnMap[3] + 20], -1)

    	//if self.GL_LIST_range_ID != None:
       		//glCallList(self.GL_LIST_range_ID)
     
    	//glDisable(GL_BLEND)
}










      //def updateRange(self, k):
          //if k.korpus.drive_slot.item != None and k.korpus.bak_slot.item != None:
             //radius_min = min(k.korpus.drive_slot.item.hyper , k.korpus.bak_slot.item.fuel)
             //self.range_list_x, self.range_list_y = getCircleCoordinateRangeLowPrecision(k.starsystem.rectOnMap.centerx, k.starsystem.rectOnMap.centery, radius_min)
             //self.GL_LIST_range_ID = GlListCompileDirection(DOT_RED_TEX, self.range_list_x, self.range_list_y, len(self.range_list_x), 1, 10)
          //else:
             //self.GL_LIST_range_ID = None











