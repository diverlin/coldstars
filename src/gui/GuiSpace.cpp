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

#include "GuiSpace.hpp"
#include "GuiGalaxyMap.hpp"
#include "GuiSkills.hpp"
#include "UserInput.hpp"

#include "ButtonTrigger.hpp"
#include "ButtonSingle.hpp"

#include "../managers/EntityManager.hpp"

#include "../common/myStr.hpp"
#include "../common/constants.hpp"
#include "../common/GameDate.hpp"
#include "../common/Logger.hpp"

#include "../resources/GuiTextureObCollector.hpp"

#include "../render/Screen.hpp"
#include "../render/Render.hpp"

#include "../pilots/Player.hpp"
#include "../pilots/Npc.hpp"

#include "../world/starsystem.hpp"

#include "../slots/ItemSlot.hpp"

GuiSpace::GuiSpace():
gui_galaxymap_shared(NULL),
gui_vehicle_scan_shared(NULL),
gui_skills_shared(NULL),
slider_shared(NULL),
init_done(false)
{   	
    	int screen_w = Screen::Instance().GetWindow().GetWidth();
    	int screen_h = Screen::Instance().GetWindow().GetHeight();
    	
    	ButtonTrigger* galaxymap_button = new ButtonTrigger(GuiTextureObCollector::Instance().icon_map, GUI::BUTTON::GALAXYMAP_ID, "galaxy map");    
    	galaxymap_button->SetRect(Rect(screen_w - (GUI::ICON_SIZE + 5),
    				       screen_h - (GUI::ICON_SIZE + 5), 
    				       GUI::ICON_SIZE,  
    				       GUI::ICON_SIZE));		     								     
    	button_map.insert(std::make_pair(GUI::BUTTON::GALAXYMAP_ID, galaxymap_button));

    	ButtonSingle* load_button = new ButtonSingle(GuiTextureObCollector::Instance().icon_plus, GUI::BUTTON::LOAD_ID, "load");    
    	load_button->SetRect(Rect(screen_w - 2*(GUI::ICON_SIZE + 5),
    			          screen_h - (GUI::ICON_SIZE + 5), 
    			          GUI::ICON_SIZE,  
    			          GUI::ICON_SIZE));					     
    	button_map.insert(std::make_pair(GUI::BUTTON::LOAD_ID, load_button));
    	
    	ButtonSingle* save_button = new ButtonSingle(GuiTextureObCollector::Instance().icon_minus, GUI::BUTTON::SAVE_ID, "save");    
        save_button->SetRect(Rect(screen_w - 3*(GUI::ICON_SIZE + 5),
    				  screen_h - (GUI::ICON_SIZE + 5), 
    				  GUI::ICON_SIZE,  
    				  GUI::ICON_SIZE));					     
    	button_map.insert(std::make_pair(GUI::BUTTON::SAVE_ID, save_button));
    	    		
       	textureOb_bar_top 	= GuiTextureObCollector::Instance().bar_bottom;
       	textureOb_bar_bottom 	= GuiTextureObCollector::Instance().bar_bottom;

       	Resize(screen_w, screen_h);
       	
       	show_gui_radar = true;
}

/*virtual*/
GuiSpace::~GuiSpace()
{}

void GuiSpace::SetPlayer(Player* player)
{	
	this->player = player;

	gui_radar.SetPlayer(player); 
}

void GuiSpace::BindSharedGuis(GuiGalaxyMap* gui_galaxymap_shared, GuiVehicle* gui_vehicle_scan_shared, GuiSkills* gui_skills_shared, Slider* slider_shared)
{
        this->gui_galaxymap_shared    = gui_galaxymap_shared;
        this->gui_vehicle_scan_shared = gui_vehicle_scan_shared;
        this->gui_skills_shared       = gui_skills_shared;
        this->slider_shared           = slider_shared;
        
        init_done = true;
}

void GuiSpace::UnbindSharedGuis()
{
        gui_galaxymap_shared    = NULL;
        gui_vehicle_scan_shared = NULL;
        gui_skills_shared       = NULL;
        slider_shared           = NULL;
        
        init_done = false;
}

bool GuiSpace::UpdateMouseInteractionWithPreciseWeaponTarget(const MouseData& data_mouse)
{
	gui_vehicle_target.UpdateEquipmentIcons();

	ItemSlot* selected_item_slot = gui_vehicle_target.GetInreactedItemSlot(data_mouse);
	if (selected_item_slot != NULL)
	{
		if (selected_item_slot->GetItem() != NULL)
		{
			player->GetNpc()->GetVehicle()->GetWeaponComplex().SetTarget(selected_item_slot->GetOwnerVehicle(), selected_item_slot);
			gui_vehicle_target.Reset();
			return true;
		}
	}

	return false;
}

void GuiSpace::EnterGalaxyMap()
{        
	#if GUI_LOG_ENABLED == 1
	Logger::Instance().Log("GuiSpace::EnterGalaxyMap", GUI_LOG_DIP);
	#endif
	
        if (gui_vehicle_scan_shared->GetVehicle() != NULL)
        {
                ExitGuiScan();
        }

        show_gui_radar = false;          
        gui_galaxymap_shared->BindGalaxy(player->GetNpc()->GetStarSystem()->GetGalaxy());
}

void GuiSpace::ExitGalaxyMap()
{
	#if GUI_LOG_ENABLED == 1
	Logger::Instance().Log("GuiSpace::ExitGalaxyMap", GUI_LOG_DIP);
	#endif
	
        show_gui_radar = true;       
        gui_galaxymap_shared->UnbindGalaxy();
}
    
void GuiSpace::EnterGuiScan()
{
	#if GUI_LOG_ENABLED == 1
	Logger::Instance().Log("GuiSpace::EnterGuiScan", GUI_LOG_DIP);
	#endif
	
        int screen_w = Screen::Instance().GetWindow().GetWidth();
        int screen_h = Screen::Instance().GetWindow().GetHeight();
	vec2f center_screen(screen_w/2, screen_h/2);
        
        bool allow_full_control = player->IsAbleToGetFullControlOnScanedVehicle();
        gui_vehicle_scan_shared->BindVehicle(player->GetNpc()->GetScanTarget(), center_screen + GUI_VEHICLE_INSPACE_OFFSET, allow_full_control);
        gui_skills_shared->SetOffset(center_screen + GUI_SKILLS_INSPACE_OFFSET);
                        
        show_gui_radar = false;
}

void GuiSpace::ExitGuiScan()
{       
	#if GUI_LOG_ENABLED == 1
	Logger::Instance().Log("GuiSpace::ExitGuiScan", GUI_LOG_DIP);
	#endif
	
        if (gui_vehicle_scan_shared->GetVehicle() == player->GetNpc()->GetVehicle())
       	{
                gui_skills_shared->Acknowledge();
       	}
        gui_vehicle_scan_shared->UnbindVehicle();

        player->GetNpc()->ResetScanTarget();
                
        show_gui_radar = true;
}

void GuiSpace::ButtonsAction(Player* player) const
{
	for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	{
		BaseButton* button = iterator->second;
       		switch(button->GetSubTypeId())
       		{
       			case GUI::BUTTON::GALAXYMAP_ID:   
       			{ 
                                if (button->GetPressed() == true)
       				{
                                        if (player->GetGuiManager().GetGuiGalaxyMap()->GetGalaxy() == NULL)
                                        {
                                                player->GetGuiManager().GetGuiSpace().EnterGalaxyMap();
                                        }
                                }
                                else
                                {
                                        if (player->GetGuiManager().GetGuiGalaxyMap()->GetGalaxy() != NULL)
                                        {
                                                player->GetGuiManager().GetGuiSpace().ExitGalaxyMap();
                                        }
                                }

       				break; 
       			}   

     			case GUI::BUTTON::SAVE_ID:   
       			{
       				if (button->GetPressed() == true) 
       				{
       					EntityManager::Instance().SaveRequest();
       				} 
                                break;
       			}   

     			case GUI::BUTTON::LOAD_ID:   
       			{ 
       			       	if (button->GetPressed() == true) 
       				{
       					EntityManager::Instance().LoadRequest();
       				} 
                                break;
       			}   
       		}
	}
}

void GuiSpace::Resize(int screen_w, int screen_h)
{
	rect_bar_bottom.Set(0, 0, screen_w, GUI::BAR_HEIGHT);
	rect_bar_top.Set(0, screen_h, screen_w, -GUI::BAR_HEIGHT);
}


void GuiSpace::RenderBar() const
{	
	drawTexturedRect(textureOb_bar_bottom, rect_bar_bottom, -1.5);
	drawTexturedRect(textureOb_bar_top, rect_bar_top, -1.5);
}


void GuiSpace::RenderText(const vec2f& scroll_coords) const
{
	std::string _coord_str = "date:"+ GameDate::Instance().GetDate().GetStr()+" world coord: " + int2str(scroll_coords.x) + "," + int2str(scroll_coords.y);

	sf::String _str(_coord_str, Screen::Instance().GetFont(), 12);
	_str.SetColor(sf::Color(255, 255, 255));
	_str.SetPosition(Screen::Instance().GetWindow().GetWidth() - 400, 5); 

	Screen::Instance().GetWindow().Draw(_str);    
}

                                            
bool GuiSpace::Update(const MouseData& data_mouse)
{
	int screen_w = Screen::Instance().GetWindow().GetWidth();
        int screen_h = Screen::Instance().GetWindow().GetHeight();
        Rect screen_rect(0, 0, screen_w, screen_h);   
	vec2f center_screen(screen_w/2, screen_h/2);
                            
       	UserInput::Instance().UpdateInSpace(player, player->GetGuiManager());
     	player->GetCursor().Update();  

	if (gui_vehicle_player.GetVehicle() == NULL)
	{
		gui_vehicle_player.BindVehicle(player->GetNpc()->GetVehicle(), 0.6f);
         	gui_vehicle_player.SetOffset(gui_radar.GetRect().GetCenter());                        
	}
	gui_vehicle_player.UpdateEquipmentIcons();

	if (gui_vehicle_target.GetVehicle() != NULL)
	{
		gui_vehicle_target.UpdateOffset();
	}

	//update
        bool interaction = UpdateMouseInteractionWithButtons(data_mouse);
        ButtonsAction(player);   
                                               
	if (gui_galaxymap_shared->GetGalaxy() != NULL)  
	{
		if (interaction == false)
                {
                	interaction = gui_galaxymap_shared->UpdateMouseInteraction(data_mouse);
                }
        }
			
        if (gui_vehicle_scan_shared->GetVehicle() != NULL)
	{	
		if (interaction == false)
		{
			interaction = player->GetGuiManager().UpdateMouseInteractionWithScanVehicle(data_mouse);
		}
	}

        gui_vehicle_player.ButtonsAction(player);
        if (show_gui_radar == true)
        {
        	if (interaction == false)
                {
                 	interaction = gui_vehicle_player.UpdateMouseInteractionWithButtons(data_mouse);
                }
                        
                gui_radar.Update();                                
                if (interaction == false)
                {
                	if (interaction == false)
                        {
                         	interaction = gui_radar.UpdateMouseInteraction(data_mouse);
                        }
                }
        }
                        
        if (gui_vehicle_target.GetVehicle() != NULL)
	{
		interaction = UpdateMouseInteractionWithPreciseWeaponTarget(data_mouse);
	}	

	return interaction;
}

void GuiSpace::Render(const MouseData& data_mouse)
{
	resetRenderTransformation();
	enable_BLEND();    
		if (show_gui_radar == true)  
		{
			gui_radar.Render();
	              	gui_vehicle_player.RenderButtons();
	      		gui_vehicle_player.RenderFocusedButtonInfo(data_mouse);    
		}
					
		if (gui_galaxymap_shared->GetGalaxy() != NULL)  
		{
			gui_galaxymap_shared->Render();    
		}
	                                
		if (gui_vehicle_scan_shared->GetVehicle() != NULL)
		{
			player->GetGuiManager().RenderScanVehicle(data_mouse, player->GetNpc()->GetScanTarget()); 				                 
		}
					
		if (gui_vehicle_target.GetVehicle() != NULL)
		{
	               	gui_vehicle_target.RenderButtons();
	       		gui_vehicle_target.RenderFocusedButtonInfo(data_mouse); 
		}

		RenderBar();
		RenderButtons();
		RenderFocusedButtonInfo(data_mouse);
	disable_BLEND();

	RenderText(Screen::Instance().GetRect().GetBottomLeft());
}

