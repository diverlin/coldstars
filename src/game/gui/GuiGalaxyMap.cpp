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

#include "GuiGalaxyMap.hpp"
#include "MouseData.hpp"
#include "../config/config.hpp"
#include "../common/constants.hpp"
#include "../common/myStr.hpp"
#include "../resources/GuiTextureObCollector.hpp"
#include "../pilots/Player.hpp"
#include "../world/starsystem.hpp"
#include "../world/Sector.hpp"
#include "../world/galaxy.hpp"
#include "../render/Render.hpp"
#include "../render/Screen.hpp"
#include "../resources/TextureManager.hpp"
#include "../ai/Task.hpp"
#include "../ai/StateMachine.hpp"

#include "../spaceobjects/Star.hpp"
#include "../pilots/Npc.hpp"

GuiGalaxyMap::GuiGalaxyMap():galaxy(nullptr)
{ 
    	rect.Set(GUI::MAP::BORDER_X, 
    		 GUI::MAP::BORDER_Y, 
    		 (Config::Instance().SCREEN_WIDTH  - 2 * GUI::MAP::BORDER_X), 
    		 (Config::Instance().SCREEN_HEIGHT - 2 * GUI::MAP::BORDER_X));
    			
    	texOb_background = GuiTextureObCollector::Instance().text_background;
    	scale_parsec2screencoord = 2*Config::Instance().SCREEN_WIDTH/(float)ENTITY::GALAXY::PARSEC;
}

GuiGalaxyMap::~GuiGalaxyMap()
{}

void GuiGalaxyMap::BindGalaxy(Galaxy* galaxy)
{
        this->galaxy = galaxy;
}
                
void GuiGalaxyMap::UnbindGalaxy()
{
        galaxy = nullptr;
}
                
bool GuiGalaxyMap::UpdateMouseInteraction(const MouseData& data_mouse)
{
     	if (player->GetNpc()->GetVehicle()->GetProperties().hyper > 0)
     	{      
        	for (unsigned int i=0; i<galaxy->SECTOR_vec.size(); i++)
        	{
        		for (unsigned int j=0; j<galaxy->SECTOR_vec[i]->STARSYSTEM_vec.size(); j++)
        		{
            			StarSystem* starsystem = galaxy->SECTOR_vec[i]->STARSYSTEM_vec[j]; // shortcut
            		
	            		if (starsystem->GetId() != player->GetNpc()->GetVehicle()->GetStarSystem()->GetId())
	            		{	            			
	                		float ss_cursor_dist = distanceBetween(starsystem->GetCenter(), data_mouse.mx, data_mouse.my);
	                		if (ss_cursor_dist < 10)
	                		{ 
	                   			int ss_ss_dist = distanceBetween(starsystem->GetCenter(), player->GetNpc()->GetStarSystem()->GetCenter());
	                   			if (ss_ss_dist < player->GetNpc()->GetVehicle()->GetProperties().hyper)
	                      			{
	                      				if (data_mouse.left_click == true)
	                      				{ 
	              						Task microtask(MICROSCENARIO::JUMP_ID, starsystem->GetId());
	               						player->GetNpc()->GetStateMachine().SetCurrentMicroTask(microtask);
	               						player->GetNpc()->GetVehicle()->GetDriveComplex().UpdatePath();
	               				
	                          				return true;
	                      				} 
	                                                if (data_mouse.right_click == true)
	                                                {
	                                                        // DEBUG WAY
	                                                        player->GetNpc()->GetVehicle()->HyperJumpEvent(starsystem);
	                                                }
	                      			}
	                		}
	            		}
	            	}
        	}

     	}
     	
     	return false;
}



void GuiGalaxyMap::Render()
{
	drawTexturedRect(texOb_background, rect, -1.0);
    	
    	enable_POINTSPRITE();
    		
    	for (unsigned int i=0; i<galaxy->SECTOR_vec.size(); i++)
    	{   		
    		for (unsigned int j=0; j<galaxy->SECTOR_vec[i]->STARSYSTEM_vec.size(); j++)
    		{   	
    		        StarSystem* starsystem = galaxy->SECTOR_vec[i]->STARSYSTEM_vec[j]; // shortcut
    		           			
    	        	TextureOb* texOb_particle = TextureManager::Instance().GetTexObByColorId(TEXTURE::DISTANTSTAR_ID, starsystem->STAR_vec[0]->GetColorId()); 
	                                      
	        	drawTexturedPoint(texOb_particle->texture, starsystem->GetCenter()*scale_parsec2screencoord, 30.0, -2.0);
	              
	       		if (starsystem->GetConquerorRaceId() != NONE_ID)
	       		{
	       			drawTexturedPoint(GuiTextureObCollector::Instance().starsystem_mark_captured->texture, starsystem->GetCenter()*scale_parsec2screencoord, 20.0, -2.0);
	      		}
	
	       		if (starsystem->GetConditionId() == ENTITY::STARSYSTEM::CONDITION::WAR_ID)
	        	{
	        		drawTexturedPoint(GuiTextureObCollector::Instance().starsystem_mark_war->texture, starsystem->GetCenter()*scale_parsec2screencoord + Vec3<float>(0.0,-13.0, 0.0), 20.0, -2.0);
	        	}        		
		}           	
    	}	 
        drawTexturedPoint(GuiTextureObCollector::Instance().starsystem_mark_player->texture, player->GetNpc()->GetStarSystem()->GetCenter()*scale_parsec2screencoord, 40.0, -2.0);
        
        visual_hyperjump_range.FillData(GuiTextureObCollector::Instance().dot_yellow, 
        				scale_parsec2screencoord*player->GetNpc()->GetVehicle()->GetProperties().hyper, 
        				10);
	visual_hyperjump_range.Draw(player->GetNpc()->GetVehicle()->GetStarSystem()->GetCenter()*scale_parsec2screencoord);
       		
       	if (player->GetNpc()->GetStateMachine().GetMicroTaskManager().GetTask().GetScenarioTypeId() ==  MICROSCENARIO::JUMP_ID)
       	{
       		visual_hyperjump_path.FillData(GuiTextureObCollector::Instance().dot_green,
       					       player->GetNpc()->GetVehicle()->GetStarSystem()->GetCenter()*scale_parsec2screencoord,
       					       player->GetNpc()->GetStateMachine().GetMicroTaskManager().GetTarget()->GetCenter()*scale_parsec2screencoord,
       					       10,
       					       10);
       		visual_hyperjump_path.Draw();       	
        }       	        
               						
        disable_POINTSPRITE();
        	
        int font_size = 10;     
    	for (unsigned int i=0; i<galaxy->SECTOR_vec.size(); i++)
    	{   		
    		for (unsigned int j=0; j<galaxy->SECTOR_vec[i]->STARSYSTEM_vec.size(); j++)
    		{   	
    		        StarSystem* starsystem = galaxy->SECTOR_vec[i]->STARSYSTEM_vec[j]; // shortcut
    		        
    			Vec2<float> pos(starsystem->GetCenter().x*scale_parsec2screencoord - 20, starsystem->GetCenter().y*scale_parsec2screencoord - 20);
			Screen::Instance().DrawText(int2str(starsystem->GetId()), font_size, pos);
   		}
   	} 
}










      //def UpdateRange(self, k):
          //if k.korpus.drive_slot.item != None and k.korpus.bak_slot.item != None:
             //radius_min = min(k.korpus.drive_slot.item.hyper , k.korpus.bak_slot.item.fuel)
             //self.range_list_x, self.range_list_y = getCircleCoordinateRangeLowPrecision(k.starsystem.rectOnMap.centerx, k.starsystem.rectOnMap.centery, radius_min)
             //self.GL_LIST_range_ID = GlListCompileDirection(DOT_RED_TEX, self.range_list_x, self.range_list_y, len(self.range_list_x), 1, 10)
          //else:
             //self.GL_LIST_range_ID = None











