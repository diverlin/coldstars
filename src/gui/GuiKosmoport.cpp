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

#include "GuiKosmoport.hpp"
#include "ButtonSingle.hpp"
#include "UserInput.hpp"

#include "../resources/GuiTextureObCollector.hpp"
#include "../render/Screen.hpp"
#include "../common/constants.hpp"
#include "../common/myStr.hpp"

#include "../pilots/Player.hpp"
#include "../pilots/Npc.hpp"

#include "../spaceobjects/Vehicle.hpp"
#include "../world/starsystem.hpp"

#include "../docking/Kosmoport.hpp"
#include "../slots/ItemSlot.hpp"
#include "../items/BaseItem.hpp"

#include "../render/Render.hpp"

#include "../docking/Angar.hpp"
#include "../docking/Goverment.hpp"

#include "../gui/GuiVehicle.hpp"
#include "../gui/GuiSkill.hpp"
#include "../gui/GuiGalaxyMap.hpp"
#include "../gui/Slider.hpp"

GuiKosmoport::GuiKosmoport():
init_done(false), 
kosmoport(NULL),
gui_galaxymap(NULL),
gui_vehicle_scan(NULL),
gui_skill(NULL),
slider(NULL)
{
	int screen_w = Screen::Instance().GetWindow().GetWidth();
	int screen_h = Screen::Instance().GetWindow().GetHeight();
	
        TextureOb* texOb_button = GuiTextureObCollector::Instance().dot_green; // fake

    	ButtonSingle* angar_screen_button = new ButtonSingle(texOb_button, GUI::BUTTON::ANGAR_ID, "angar"); 
    	angar_screen_button->SetRect(Rect(screen_w - 1 * (GUI::ICON_SIZE + 5), 
    					  GUI::ICON_SIZE, 
    					  GUI::ICON_SIZE,  
    					  GUI::ICON_SIZE));   					     
    	button_map.insert(std::make_pair(GUI::BUTTON::ANGAR_ID, angar_screen_button));
    	
    	ButtonSingle* store_screen_button = new ButtonSingle(texOb_button, GUI::BUTTON::STORE_ID, "store");
    	store_screen_button->SetRect(Rect(screen_w - 2 * (GUI::ICON_SIZE + 5),
    					  GUI::ICON_SIZE, 
    					  GUI::ICON_SIZE,  
    					  GUI::ICON_SIZE));		     
    	button_map.insert(std::make_pair(GUI::BUTTON::STORE_ID, store_screen_button));
    					        	
    	ButtonSingle* shop_screen_button = new ButtonSingle(texOb_button, GUI::BUTTON::SHOP_ID, "shop");
    	shop_screen_button->SetRect(Rect(screen_w - 3 * (GUI::ICON_SIZE + 5), 
    					 GUI::ICON_SIZE, 
    					 GUI::ICON_SIZE,  
    					 GUI::ICON_SIZE));
    	button_map.insert(std::make_pair(GUI::BUTTON::SHOP_ID, shop_screen_button));
    					     
    	ButtonSingle* galaxymap_screen_button = new ButtonSingle(texOb_button, GUI::BUTTON::GALAXYMAP_ID, "galaxymap");
   	galaxymap_screen_button->SetRect(Rect(screen_w - 4 * (GUI::ICON_SIZE + 5), 
    					      GUI::ICON_SIZE, 
    					      GUI::ICON_SIZE,  
    					      GUI::ICON_SIZE));
   	button_map.insert(std::make_pair(GUI::BUTTON::GALAXYMAP_ID, galaxymap_screen_button));
    					     
    	ButtonSingle* goverment_screen_button = new ButtonSingle(texOb_button, GUI::BUTTON::GOVERMENT_ID, "goverment");
    	goverment_screen_button->SetRect(Rect(screen_w - 5 * (GUI::ICON_SIZE + 5), 
    					      GUI::ICON_SIZE,
    					      GUI::ICON_SIZE,  
    					      GUI::ICON_SIZE));
   	button_map.insert(std::make_pair(GUI::BUTTON::GOVERMENT_ID, goverment_screen_button));
}


GuiKosmoport::~GuiKosmoport()
{}
	
void GuiKosmoport::SetPlayer(Player* player)
{	
	this->player = player;
	
	gui_angar.SetPlayer(player);
	gui_store.SetPlayer(player);
}	

void GuiKosmoport::BindKosmoport(Kosmoport* kosmoport)
{
        this->kosmoport = kosmoport;     
                
	gui_angar.BindAngar(kosmoport->GetAngar());
        gui_store.BindStore(kosmoport->GetStore());
        gui_shop.BindShop(kosmoport->GetShop()); 
        gui_goverment.BindGoverment(kosmoport->GetGoverment());
        
        active_screen_id = GUI::SCREEN::ANGAR_ID; 
        
        init_done     = true;
}

void GuiKosmoport::UnbindKosmoport()
{
        ExitCurrentScreen();
        
        kosmoport = NULL;
        
        gui_angar.UnbindAngar();
        gui_store.UnbindStore();
        gui_shop.UnbindShop();
        gui_goverment.UnbindGoverment();
        
        init_done = false;
}


void GuiKosmoport::BindSharedGuis(GuiGalaxyMap* gui_galaxymap, GuiVehicle* gui_vehicle_scan, GuiSkill* gui_skill, Slider* slider)
{
        this->gui_galaxymap    = gui_galaxymap;
        this->gui_vehicle_scan = gui_vehicle_scan;
        this->gui_skill        = gui_skill;
        this->slider           = slider;
}

void GuiKosmoport::UnbindSharedGuis()
{
        gui_galaxymap    = NULL;
        gui_vehicle_scan = NULL;
        gui_skill        = NULL;
        slider           = NULL;
}

void GuiKosmoport::EnterGuiScanInAngar()
{
        int screen_w = Screen::Instance().GetWindow().GetWidth();
        int screen_h = Screen::Instance().GetWindow().GetHeight();
	vec2f center_screen(screen_w/2, screen_h/2);
        
        gui_vehicle_scan->BindVehicle(player->GetNpc()->GetScanTarget(), center_screen + GUI_VEHICLE_INSPACE_OFFSET);
        gui_skill->SetOffset(center_screen + GUI_SKILL_INSPACE_OFFSET);
}

void GuiKosmoport::ExitGuiScan()
{       
        if (gui_vehicle_scan->GetVehicle() == player->GetNpc()->GetVehicle())
       	{
                gui_skill->Acknowledge();
       	}
        gui_vehicle_scan->UnbindVehicle();

        player->GetNpc()->ResetScanTarget();
}
               
void GuiKosmoport::EnterGuiAngarScreen()
{        
        active_screen_id = GUI::SCREEN::ANGAR_ID;
}

void GuiKosmoport::ExitGuiAngarScreen()
{
	if (gui_vehicle_scan->GetVehicle() != NULL)
	{
		ExitGuiScan();
	}
}


void GuiKosmoport::EnterGuiStoreScreen()
{
        int screen_w = Screen::Instance().GetWindow().GetWidth();
        int screen_h = Screen::Instance().GetWindow().GetHeight();
	vec2f center_screen(screen_w/2, screen_h/2);
        
        gui_store.SetOffset(center_screen + GUI_STORE_OFFSET);

	player->GetNpc()->SetScanTarget(player->GetNpc()->GetVehicle());
        bool lock_gui_scan_vehicle = true;
        gui_vehicle_scan->BindVehicle(player->GetNpc()->GetVehicle(), center_screen + GUI_VEHICLE_INSTORE_OFFSET, lock_gui_scan_vehicle);
        
        active_screen_id = GUI::SCREEN::STORE_ID;
}

void GuiKosmoport::ExitGuiStoreScreen()
{
        ExitGuiScan();
}

void GuiKosmoport::EnterGuiShopScreen()
{       
        active_screen_id = GUI::SCREEN::SHOP_ID;
}

void GuiKosmoport::ExitGuiShopScreen()
{}

void GuiKosmoport::EnterGuiGalaxyMapScreen()
{       
        active_screen_id = GUI::SCREEN::GALAXYMAP_ID;        
        gui_galaxymap->BindGalaxy(player->GetNpc()->GetVehicle()->GetStarSystem()->GetGalaxy());
}

void GuiKosmoport::ExitGuiGalaxyMapScreen()
{
        gui_galaxymap->UnbindGalaxy(); 
}

void GuiKosmoport::EnterGuiGovermentScreen()
{        
        active_screen_id = GUI::SCREEN::GOVERMENT_ID;
}

void GuiKosmoport::ExitGuiGovermentScreen()
{}    

void GuiKosmoport::ExitCurrentScreen()
{
	switch (active_screen_id)
	{
		case GUI::SCREEN::ANGAR_ID: { ExitGuiAngarScreen(); break; }
		case GUI::SCREEN::STORE_ID: { ExitGuiStoreScreen(); break; }
		case GUI::SCREEN::SHOP_ID:  { ExitGuiShopScreen(); break; }
		case GUI::SCREEN::GALAXYMAP_ID: { ExitGuiGalaxyMapScreen(); break; }
		case GUI::SCREEN::GOVERMENT_ID: { ExitGuiGovermentScreen(); break; }
	}
}


void GuiKosmoport::ButtonsAction()
{
	for (std::map<int, BaseButton*>::const_iterator iterator = button_map.begin(); iterator!=button_map.end(); iterator++)
	{
		BaseButton* button = iterator->second;
		if (button->GetPressed() == true)
		{
			switch(button->GetSubTypeId())
	   		{
	   			case GUI::BUTTON::ANGAR_ID: 
	   			{
   				      	button->PressEvent();   
                                        ExitCurrentScreen();
                                        EnterGuiAngarScreen();
                                        
   					return; break;
	  	 		}

	   			case GUI::BUTTON::STORE_ID: 
	   			{
   				      	button->PressEvent();
                                        ExitCurrentScreen();
                                        EnterGuiStoreScreen();
                                        
   					return; break;
	  	 		}

	   			case GUI::BUTTON::SHOP_ID: 
	   			{
   				      	button->PressEvent();
                                        ExitCurrentScreen();
                                        EnterGuiShopScreen();
                                        
   					return; break;
	  	 		}

	   			case GUI::BUTTON::GALAXYMAP_ID: 
	   			{
   				      	button->PressEvent();
                                        ExitCurrentScreen();                                                                                
                                        EnterGuiGalaxyMapScreen();
                                        
   					return; break;
	  	 		}

	   			case GUI::BUTTON::GOVERMENT_ID: 
	   			{
   				      	button->PressEvent();
                                        ExitCurrentScreen();
                                        EnterGuiGovermentScreen();
                                        
   					return; break;
	  	 		}
	  	 	}
	  	 }
	  }
}


bool GuiKosmoport::Update(const MouseData& data_mouse)
{
 	UserInput::Instance().UpdateInKosmoport(player, player->GetGuiManager());
     	player->GetCursor().Update(); 
     	    	       	
	bool interaction = UpdateMouseInteractionWithButtons(data_mouse);
	ButtonsAction();

	switch(active_screen_id)
	{
		case GUI::SCREEN::ANGAR_ID:
		{
			gui_angar.CheckButtonsLock();
			if (interaction == false)
			{					
				interaction = gui_angar.UpdateMouseInteractionWithButtons(data_mouse);
				if (interaction == false)
				{
					interaction = gui_angar.UpdateMouseInteractionWithVehicleSlots(data_mouse);
				}

				gui_angar.ButtonsAction();
			    	if (interaction == false)
			    	{
					if (gui_vehicle_scan->GetVehicle() != NULL) 
					{ 
						interaction = player->GetGuiManager().UpdateMouseInteractionWithScanVehicle(data_mouse, gui_vehicle_scan);
					}
			    	} 
	        	}

			break;
		}

		case GUI::SCREEN::STORE_ID:
		{
			if (interaction == false)
			{
				interaction = gui_store.UpdateMouseInteraction(data_mouse);
			    	if (interaction == false)
			    	{
			    		interaction = gui_vehicle_scan->UpdateMouseInteractionInStore(data_mouse, gui_store.GetStore());
			    	}
			}

			break;
		}

		case GUI::SCREEN::SHOP_ID:
		{
			gui_shop.UpdateLables();
			gui_shop.ButtonsAction(*slider);
			if (slider->GetSubTypeId() != NONE_ID)
			{
				slider->CheckButtonsLock();
				slider->ButtonsAction(gui_shop.GetShop());
			}
			
			if (interaction == false)
			{
				interaction = gui_shop.UpdateMouseInteractionWithButtons(data_mouse);
				if (interaction == false)
				{
					if (slider->GetSubTypeId() != NONE_ID)
					{
						slider->UpdateSlidePosition(data_mouse);
						interaction = slider->UpdateMouseInteractionWithButtons(data_mouse);
					}
				}
	        	}

			break;
		}

		case GUI::SCREEN::GALAXYMAP_ID:
		{
			//update
			if ( interaction == false)
			{
				interaction = gui_galaxymap->UpdateMouseInteraction(data_mouse);
	        	}					   

			break;
		}

		case GUI::SCREEN::GOVERMENT_ID:
		{
			//update
			if (interaction == false)
			{
				//interaction = gui_goverment.UpdateMouseInteraction(data_mouse);
	        	}

			break;
		}
	}
	
	return interaction;
}

void GuiKosmoport::Render(const MouseData& data_mouse)
{    	
	Rect screen_rect(0, 0, Screen::Instance().GetWindow().GetWidth(), Screen::Instance().GetWindow().GetHeight());   
	vec2f center_screen(Screen::Instance().GetWindow().GetWidth()/2, Screen::Instance().GetWindow().GetHeight()/2);

	switch(active_screen_id)
	{
		case GUI::SCREEN::ANGAR_ID:
		{
			resetRenderTransformation();
			gui_angar.GetAngar()->RenderBackground(screen_rect);
			enable_BLEND();   
	        		gui_angar.RenderVehicleAndItemSlots();
	        		
				if (gui_vehicle_scan->GetVehicle() != NULL)
				{ 
					player->GetGuiManager().RenderScanVehicle(data_mouse, gui_vehicle_scan); 
				}
				
	        		RenderButtons(); 
	        		gui_angar.RenderButtons();
				RenderFocusedButtonInfo(data_mouse); 
				gui_angar.RenderFocusedButtonInfo(data_mouse); 
			disable_BLEND(); 
		
			break;
		}

		case GUI::SCREEN::STORE_ID:
		{
			resetRenderTransformation();
			gui_store.GetStore()->RenderBackground(screen_rect);

			enable_BLEND();
				gui_store.RenderSlots(player->GetNpc()->GetCredits());

				bool show_skill = false;
				player->GetGuiManager().RenderScanVehicle(data_mouse, show_skill);
				
	        		RenderButtons(); 
				RenderFocusedButtonInfo(data_mouse); 
			disable_BLEND();
			drawSimpleText("credits:"+int2str(player->GetNpc()->GetCredits()), 12, 600, 200);

			break;
		}

		case GUI::SCREEN::SHOP_ID:
		{
			resetRenderTransformation();
			gui_shop.GetShop()->RenderBackground(screen_rect);
			enable_BLEND();   
				gui_shop.RenderButtons();
				
				if (slider->GetSubTypeId() != NONE_ID)
				{
					slider->Render();
				}
				
				RenderButtons(); 
				RenderFocusedButtonInfo(data_mouse); 
				    
			disable_BLEND();  
			
			break;
		}

		case GUI::SCREEN::GALAXYMAP_ID:
		{
			clearScreen(); //becase there is no background
	        	resetRenderTransformation();
			enable_BLEND();   
				gui_galaxymap->Render();
				
				RenderButtons(); 
				RenderFocusedButtonInfo(data_mouse); 
				    
			disable_BLEND();    

			break;
		}

		case GUI::SCREEN::GOVERMENT_ID:
		{
	        	resetRenderTransformation();
			gui_goverment.GetGoverment()->RenderBackground(screen_rect);
			enable_BLEND();   
				//gui_goverment->RenderInternals(goverment);
				
				RenderButtons(); 
				RenderFocusedButtonInfo(data_mouse); 
				    
			disable_BLEND(); 

			break;
		}
	}
}
                
