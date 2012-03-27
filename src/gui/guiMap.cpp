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



GuiMap :: GuiMap(Player* player)
{ 
	this->player = player;
    	rect = Rect(GUI::MAP::BORDER_X, GUI::MAP::BORDER_Y, (Config::Instance().SCREEN_WIDTH_MIN - 2 * GUI::MAP::BORDER_X), (Config::Instance().SCREEN_HEIGHT_MIN - 2 * GUI::MAP::BORDER_X));
}

GuiMap :: ~GuiMap()
{}

bool GuiMap :: update()
{
	Galaxy* galaxy = player->getNpc()->getStarSystem()->getGalaxy();

     	if (player->getNpc()->getVehicle()->ableTo.HJUMP == true)
     	{
        	int mx  = player->getCursor()->getMousePos().x;
        	int my  = player->getScreen()->getHeight() - player->getCursor()->getMousePos().y; 
        	int lmb = player->getCursor()->getMouseLeftButton();
   
        	for (unsigned int si = 0; si < galaxy->STARSYSTEM_vec.size(); si++)
        	{
            		//if (STARSYSTEM_pList[si]->id != pTo_PLAYER->pTo_starsystem->id)
            		{
                		float ss_cursor_dist = distBetweenPoints(galaxy->STARSYSTEM_vec[si]->getPosition(), mx, my);
                		if (ss_cursor_dist < 10)
                		{ 
                   			int ss_ss_dist = distBetweenPoints(galaxy->STARSYSTEM_vec[si]->getPosition(), 
                   				       			   player->getNpc()->getStarSystem()->getPosition() );
                   				       
                   			if ( (ss_ss_dist < player->getNpc()->getVehicle()->GetDriveComplex()->GetDriveSlot().getDriveEquipment()->getHyper()) && (ss_ss_dist < player->getNpc()->getVehicle()->GetDriveComplex()->GetBakSlot().getBakEquipment()->getFuel()) )
                      			{
                      				if (lmb == true)
                      				{ 
                                                        // debug
                                                        player->getNpc()->getStarSystem()->removeShip(player->getNpc()->getVehicle()->getId());  
                                                        player->getNpc()->getStarSystem()->removeNpc(player->getNpc()->getId(), player->getNpc()->getSubTypeId());  
                                                        galaxy->STARSYSTEM_vec[si]->addToHyperJumpQueue(player->getNpc());    
                                                        // debug
                                                        
                          				//player.hyperJumpPreparation(ss)
                          				//#player.calculateTraceToCoord((player.jump_pos_x, player.jump_pos_y))
                          				printf("ss_id = %i\n", galaxy->STARSYSTEM_vec[si]->getId());    // debug

                          				return true;
                      				} 
                      			}
                		}
            		}
        	}

     	}
     	
     	return false;
}



void GuiMap :: render()
{
    	TextureOb* texOb_textBg = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::TEXT_BACKGROUND_ID);
    	Galaxy* galaxy = player->getNpc()->getStarSystem()->getGalaxy();
      
        resetRenderTransformation();
    	        
        enable_BLEND();                              

    		drawTexturedRect(texOb_textBg, rect, -1);
    	
    		enable_POINTSPRITE();
    		
    			for (unsigned int si = 0; si < galaxy->STARSYSTEM_vec.size(); si++)
    			{
   		
        			TextureOb* texOb_particle = g_TEXTURE_MANAGER.getTexObByColorId(TEXTURE::DISTANTSTAR_ID, galaxy->STARSYSTEM_vec[si]->STAR_vec[0]->getColorId()); 
                                        
        			drawTexturedPoint(texOb_particle->texture, galaxy->STARSYSTEM_vec[si]->getPosition(), 30.0, -2.0);
        	       
        			if (galaxy->STARSYSTEM_vec[si]->getCaptured() == true)
        			{
        				drawTexturedPoint(g_UNIQUE_TEXTURE_COLLECTOR.texOb_mark_enemy_ss->texture, galaxy->STARSYSTEM_vec[si]->getPosition(), 40.0, -2.0);
           			}
           	
    			}	 
           		drawTexturedPoint(g_UNIQUE_TEXTURE_COLLECTOR.texOb_mark_player_ss->texture, player->getNpc()->getStarSystem()->getPosition(), 40.0, -2.0);

    			//if self.GL_LIST_range_ID != None:
       				//glCallList(self.GL_LIST_range_ID)
       		
        	disable_POINTSPRITE();
        	
        	int font_size = 10;     
        	for (unsigned int si = 0; si < galaxy->STARSYSTEM_vec.size(); si++)
    		{
	  		drawSimpleText(int2str(galaxy->STARSYSTEM_vec[si]->getId()), 
        	       	      		 font_size, 
        	       	       		 galaxy->STARSYSTEM_vec[si]->getPosition().x - 20, 
        	       	       		 galaxy->STARSYSTEM_vec[si]->getPosition().y - 20);
    		} 
    		
    	disable_BLEND();  
}










      //def updateRange(self, k):
          //if k.korpus.drive_slot.item != None and k.korpus.bak_slot.item != None:
             //radius_min = min(k.korpus.drive_slot.item.hyper , k.korpus.bak_slot.item.fuel)
             //self.range_list_x, self.range_list_y = getCircleCoordinateRangeLowPrecision(k.starsystem.rectOnMap.centerx, k.starsystem.rectOnMap.centery, radius_min)
             //self.GL_LIST_range_ID = GlListCompileDirection(DOT_RED_TEX, self.range_list_x, self.range_list_y, len(self.range_list_x), 1, 10)
          //else:
             //self.GL_LIST_range_ID = None











