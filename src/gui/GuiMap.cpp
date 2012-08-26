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



GuiMap::GuiMap()
{ 
    	rect.Set(GUI::MAP::BORDER_X, 
    		 GUI::MAP::BORDER_Y, 
    		 (Config::Instance().SCREEN_WIDTH  - 2 * GUI::MAP::BORDER_X), 
    		 (Config::Instance().SCREEN_HEIGHT - 2 * GUI::MAP::BORDER_X));
    			
    	texOb_background = GuiTextureObCollector::Instance().text_background;
}

GuiMap::~GuiMap()
{}

bool GuiMap::UpdateMouseInteraction(const MouseData& data_mouse, Galaxy* galaxy)
{
     	//if (player->GetNpc()->GetVehicle()->GetAbilitiesStatus().HJUMP == true)
     	{  
        	for (unsigned int i=0; i<galaxy->STARSYSTEM_vec.size(); i++)
        	{
            		//if (STARSYSTEM_pList[si]->id != pTo_PLAYER->pTo_starsystem->id)
            		{
                		float ss_cursor_dist = distBetweenPoints(galaxy->STARSYSTEM_vec[i]->GetPoints().GetCenter(), data_mouse.mx, data_mouse.my);
                		if (ss_cursor_dist < 10)
                		{ 
                   			int ss_ss_dist = distBetweenPoints(galaxy->STARSYSTEM_vec[i]->GetPoints().GetCenter(), player->GetNpc()->GetStarSystem()->GetPoints().GetCenter() );
                   			if ( (ss_ss_dist < player->GetNpc()->GetVehicle()->GetDriveComplex()->GetDriveSlot()->GetDriveEquipment()->GetHyper()) && (ss_ss_dist < player->GetNpc()->GetVehicle()->GetDriveComplex()->GetBakSlot()->GetBakEquipment()->GetFuel()) )
                      			{
                      				if (data_mouse.left_click == true)
                      				{ 
                                                        // debug
                                                        //player->GetNpc()->GetStarSystem()->RemoveVehicle(player->GetNpc()->GetVehicle());  
                                                        //galaxy->STARSYSTEM_vec[i]->AddToHyperJumpQueue(player->GetNpc()->GetVehicle());    
                                                        // debug
                                                        
                          				//player.hyperJumpPreparation(ss)
                          				//#player.calculateTraceToCoord((player.jump_pos_x, player.jump_pos_y))

              						MicroTask* microtask = new MicroTask(MICROSCENARIO::JUMP_ID, galaxy->STARSYSTEM_vec[i]);
               						player->GetNpc()->GetStateMachine()->SetCurrentMicroTask(microtask);
               				
                          				return true;
                      				} 
                      			}
                		}
            		}
        	}

     	}
     	
     	return false;
}



void GuiMap::Render(Galaxy* galaxy)
{
	drawTexturedRect(texOb_background, rect, -1);
    	
    	enable_POINTSPRITE();
    		
    	for (unsigned int i = 0; i < galaxy->STARSYSTEM_vec.size(); i++)
    	{   		
        	TextureOb* texOb_particle = TextureManager::Instance().getTexObByColorId(TEXTURE::DISTANTSTAR_ID, galaxy->STARSYSTEM_vec[i]->STAR_vec[0]->GetColorId()); 
                                      
        	drawTexturedPoint(texOb_particle->texture, galaxy->STARSYSTEM_vec[i]->GetPoints().GetCenter(), 30.0, -2.0);
              
       		if (galaxy->STARSYSTEM_vec[i]->GetConquerorRaceId() != NONE_ID)
       		{
       			drawTexturedPoint(GuiTextureObCollector::Instance().starsystem_mark_captured->texture, galaxy->STARSYSTEM_vec[i]->GetPoints().GetCenter(), 20.0, -2.0);
      		}

       		if (galaxy->STARSYSTEM_vec[i]->GetConditionId() == ENTITY::STARSYSTEM::CONDITION::WAR_ID)
        	{
        		drawTexturedPoint(GuiTextureObCollector::Instance().starsystem_mark_war->texture, galaxy->STARSYSTEM_vec[i]->GetPoints().GetCenter()+vec2f(0.0,-13.0), 20.0, -2.0);
        	}        		
           	
    	}	 
        drawTexturedPoint(GuiTextureObCollector::Instance().starsystem_mark_player->texture, player->GetNpc()->GetStarSystem()->GetPoints().GetCenter(), 40.0, -2.0);

    	//if self.GL_LIST_range_ID != None:
       		//glCallList(self.GL_LIST_range_ID)
       		
        disable_POINTSPRITE();
        	
        int font_size = 10;     
        for (unsigned int i=0; i<galaxy->STARSYSTEM_vec.size(); i++)
    	{
		drawSimpleText(int2str(galaxy->STARSYSTEM_vec[i]->GetId()), 
        	       	      	       font_size, 
        	       	       	       galaxy->STARSYSTEM_vec[i]->GetPoints().GetCenter().x - 20, 
        	       	       	       galaxy->STARSYSTEM_vec[i]->GetPoints().GetCenter().y - 20);
   	} 
}










      //def UpdateRange(self, k):
          //if k.korpus.drive_slot.item != None and k.korpus.bak_slot.item != None:
             //radius_min = min(k.korpus.drive_slot.item.hyper , k.korpus.bak_slot.item.fuel)
             //self.range_list_x, self.range_list_y = getCircleCoordinateRangeLowPrecision(k.starsystem.rectOnMap.centerx, k.starsystem.rectOnMap.centery, radius_min)
             //self.GL_LIST_range_ID = GlListCompileDirection(DOT_RED_TEX, self.range_list_x, self.range_list_y, len(self.range_list_x), 1, 10)
          //else:
             //self.GL_LIST_range_ID = None











