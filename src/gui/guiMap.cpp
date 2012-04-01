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
    	rect = Rect(GUI::MAP::BORDER_X, GUI::MAP::BORDER_Y, (Config::Instance().SCREEN_WIDTH - 2 * GUI::MAP::BORDER_X), (Config::Instance().SCREEN_HEIGHT - 2 * GUI::MAP::BORDER_X));
}

GuiMap :: ~GuiMap()
{}

bool GuiMap :: update()
{
	Galaxy* galaxy = player->GetNpc()->GetStarSystem()->GetGalaxy();

     	if (player->GetNpc()->GetVehicle()->ableTo.HJUMP == true)
     	{
        	int mx  = player->GetCursor()->getMousePos().x;
        	int my  = player->GetScreen()->getHeight() - player->GetCursor()->getMousePos().y; 
        	int lmb = player->GetCursor()->getMouseLeftButton();
   
        	for (unsigned int si = 0; si < galaxy->STARSYSTEM_vec.size(); si++)
        	{
            		//if (STARSYSTEM_pList[si]->id != pTo_PLAYER->pTo_starsystem->id)
            		{
                		float ss_cursor_dist = distBetweenPoints(galaxy->STARSYSTEM_vec[si]->GetPoints().getCenter(), mx, my);
                		if (ss_cursor_dist < 10)
                		{ 
                   			int ss_ss_dist = distBetweenPoints(galaxy->STARSYSTEM_vec[si]->GetPoints().getCenter(), 
                   				       			   player->GetNpc()->GetStarSystem()->GetPoints().getCenter() );
                   				       
                   			if ( (ss_ss_dist < player->GetNpc()->GetVehicle()->GetDriveComplex()->GetDriveSlot().GetDriveEquipment()->getHyper()) && (ss_ss_dist < player->GetNpc()->GetVehicle()->GetDriveComplex()->GetBakSlot().GetBakEquipment()->getFuel()) )
                      			{
                      				if (lmb == true)
                      				{ 
                                                        // debug
                                                        player->GetNpc()->GetStarSystem()->RemoveShip(player->GetNpc()->GetVehicle()->GetId());  
                                                        player->GetNpc()->GetStarSystem()->RemoveNpc(player->GetNpc()->GetId(), player->GetNpc()->GetSubTypeId());  
                                                        galaxy->STARSYSTEM_vec[si]->AddToHyperJumpQueue(player->GetNpc()->GetVehicle());    
                                                        // debug
                                                        
                          				//player.hyperJumpPreparation(ss)
                          				//#player.calculateTraceToCoord((player.jump_pos_x, player.jump_pos_y))
                          				printf("ss_id = %i\n", galaxy->STARSYSTEM_vec[si]->GetId());    // debug

                          				return true;
                      				} 
                      			}
                		}
            		}
        	}

     	}
     	
     	return false;
}



void GuiMap :: Render()
{
    	TextureOb* texOb_textBg = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::TEXT_BACKGROUND_ID);
    	Galaxy* galaxy = player->GetNpc()->GetStarSystem()->GetGalaxy();
      
        resetRenderTransformation();
    	        
        enable_BLEND();                              

    		drawTexturedRect(texOb_textBg, rect, -1);
    	
    		enable_POINTSPRITE();
    		
    			for (unsigned int si = 0; si < galaxy->STARSYSTEM_vec.size(); si++)
    			{
   		
        			TextureOb* texOb_particle = g_TEXTURE_MANAGER.getTexObByColorId(TEXTURE::DISTANTSTAR_ID, galaxy->STARSYSTEM_vec[si]->STAR_vec[0]->getColorId()); 
                                        
        			drawTexturedPoint(texOb_particle->texture, galaxy->STARSYSTEM_vec[si]->GetPoints().getCenter(), 30.0, -2.0);
        	       
        			if (galaxy->STARSYSTEM_vec[si]->GetCaptured() == true)
        			{
        				drawTexturedPoint(g_UNIQUE_TEXTURE_COLLECTOR.texOb_mark_enemy_ss->texture, galaxy->STARSYSTEM_vec[si]->GetPoints().getCenter(), 40.0, -2.0);
           			}
           	
    			}	 
           		drawTexturedPoint(g_UNIQUE_TEXTURE_COLLECTOR.texOb_mark_player_ss->texture, player->GetNpc()->GetStarSystem()->GetPoints().getCenter(), 40.0, -2.0);

    			//if self.GL_LIST_range_ID != None:
       				//glCallList(self.GL_LIST_range_ID)
       		
        	disable_POINTSPRITE();
        	
        	int font_size = 10;     
        	for (unsigned int si = 0; si < galaxy->STARSYSTEM_vec.size(); si++)
    		{
	  		drawSimpleText(int2str(galaxy->STARSYSTEM_vec[si]->GetId()), 
        	       	      		 font_size, 
        	       	       		 galaxy->STARSYSTEM_vec[si]->GetPoints().getCenter().x - 20, 
        	       	       		 galaxy->STARSYSTEM_vec[si]->GetPoints().getCenter().y - 20);
    		} 
    		
    	disable_BLEND();  
}










      //def UpdateRange(self, k):
          //if k.korpus.drive_slot.item != None and k.korpus.bak_slot.item != None:
             //radius_min = min(k.korpus.drive_slot.item.hyper , k.korpus.bak_slot.item.fuel)
             //self.range_list_x, self.range_list_y = getCircleCoordinateRangeLowPrecision(k.starsystem.rectOnMap.centerx, k.starsystem.rectOnMap.centery, radius_min)
             //self.GL_LIST_range_ID = GlListCompileDirection(DOT_RED_TEX, self.range_list_x, self.range_list_y, len(self.range_list_x), 1, 10)
          //else:
             //self.GL_LIST_range_ID = None











