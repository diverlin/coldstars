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

#include "GuiManager.hpp"
#include "UserInput.hpp"
#include "../slots/ItemSlot.hpp"
#include "../docking/Kosmoport.hpp"
#include "../world/starsystem.hpp"
#include "../common/myStr.hpp"
#include "../render/Screen.hpp"
#include "../render/Render.hpp"
#include "../parts/WeaponComplex.hpp"
#include "../items/BaseItem.hpp"

#include "../docking/Angar.hpp"
#include "../docking/Goverment.hpp"

#include "../pilots/Npc.hpp"

GuiManager::GuiManager()
{
	player = NULL;
        
        show_gui_scan = false;
}

GuiManager::~GuiManager()
{}

void GuiManager::SetPlayer(Player* player)
{	
	this->player = player;
	
	gui_angar.SetPlayer(player);
	gui_store.SetPlayer(player);
	
	gui_vehicle_scan.SetPlayer(player);
      	
      	gui_kosmoport.SetPlayer(player);
	gui_galaxymap.SetPlayer(player); 
	gui_radar.SetPlayer(player); 

	gui_natureland.SetPlayer(player); 
			
	slider.SetPlayer(player);
}		

bool GuiManager::UpdateMouseInteractionWithScanVehicle(const MouseData& data_mouse, bool allow_full_control)
{
	if (allow_full_control == false)
	{
        	if (gui_vehicle_scan.GetVehicle()->GetId() == player->GetNpc()->GetVehicle()->GetId())
    		{
        		allow_full_control = true;  
        	    	// modify full control for friend ships         
        	}
        }

	bool interaction = gui_vehicle_scan.UpdateMouseInteraction(data_mouse, allow_full_control);        
	if ( (interaction == true) and (allow_full_control == true) )
	{
		interaction = gui_skill.UpdateMouseInteractionWithButtons(data_mouse);
		gui_skill.ButtonsAction(gui_vehicle_scan.GetVehicle()->GetOwnerNpc()->GetSkill());
	}

	return interaction;
}

bool GuiManager::UpdateMouseInteractionWithPreciseWeaponTarget(const MouseData& data_mouse)
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

void GuiManager::RenderScanVehicle(const MouseData& data_mouse, bool show_skill) const
{	
	if (player->GetCursor().GetItemSlot()->GetItem() != NULL)
	{
       		gui_vehicle_scan.RenderVehicle(data_mouse, player->GetCursor().GetItemSlot()->GetItem()->GetParentSubTypeId());
		player->GetCursor().GetItemSlot()->GetItem()->Render(player->GetCursor().GetRect(), vec2f(0, 0));		
	}
	else
	{
		gui_vehicle_scan.RenderVehicle(data_mouse, NONE_ID);
	}
					
	if ( (show_skill == true) and (gui_vehicle_scan.GetVehicle()->GetOwnerNpc() != NULL) )
	{
		gui_skill.RenderButtons();
		gui_skill.RenderSkills(gui_vehicle_scan.GetVehicle()->GetOwnerNpc()->GetSkill());
		gui_skill.RenderFocusedButtonInfo(data_mouse);
	}   					                 
}

void GuiManager::EnterGalaxyMapInSpace()
{
        show_gui_galaxymap = true;
        
        if (show_gui_scan == true)
        {
                ExitGuiScan();
        }

        show_gui_radar = false;  
        
        Galaxy* galaxy = player->GetNpc()->GetStarSystem()->GetGalaxy();
        gui_galaxymap.BindGalaxy(galaxy);
}

void GuiManager::ExitGalaxyMapInSpace()
{
        show_gui_galaxymap = false;
        show_gui_radar = true;  
        
        gui_galaxymap.UnbindGalaxy();
}
    
void GuiManager::EnterGuiScanInSpace()
{
        int screen_w = Screen::Instance().GetWindow().GetWidth();
        int screen_h = Screen::Instance().GetWindow().GetHeight();
	vec2f center_screen(screen_w/2, screen_h/2);
        
        show_gui_scan = true;
        gui_vehicle_scan.BindVehicle(player->GetNpc()->GetScanTarget(), center_screen + GUI_VEHICLE_INSPACE_OFFSET);
        gui_skill.SetOffset(center_screen + GUI_SKILL_INSPACE_OFFSET);
                        
        show_gui_radar = false;
}

void GuiManager::EnterGuiScanInAngar()
{        
        int screen_w = Screen::Instance().GetWindow().GetWidth();
        int screen_h = Screen::Instance().GetWindow().GetHeight();
	vec2f center_screen(screen_w/2, screen_h/2);
        
        show_gui_scan = true;
        gui_vehicle_scan.BindVehicle(player->GetNpc()->GetScanTarget(), center_screen + GUI_VEHICLE_INANGAR_OFFSET);
        gui_skill.SetOffset(center_screen + GUI_SKILL_INANGAR_OFFSET);
}

void GuiManager::ExitGuiScan()
{                
        show_gui_scan = false;
        player->GetNpc()->ResetScanTarget();
        gui_vehicle_scan.UnbindVehicle();
        
        show_gui_radar = true;
}

void GuiManager::EnterGuiAngarScreen()
{
	Angar* angar = ((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand())->GetAngar();
	gui_angar.BindAngar(angar);
}

void GuiManager::ExitGuiAngarScreen()
{
	gui_angar.UnbindAngar();
	if (show_gui_scan == true)
	{
		ExitGuiScan();
	}
}

void GuiManager::EnterGuiStoreScreen()
{
        int screen_w = Screen::Instance().GetWindow().GetWidth();
        int screen_h = Screen::Instance().GetWindow().GetHeight();
	vec2f center_screen(screen_w/2, screen_h/2);
        
        gui_store.SetOffset(center_screen + GUI_STORE_OFFSET);

	player->GetNpc()->SetScanTarget(player->GetNpc()->GetVehicle());
        gui_vehicle_scan.BindVehicle(player->GetNpc()->GetVehicle(), center_screen + GUI_VEHICLE_INSTORE_OFFSET);

        Store* store = ((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand())->GetStore();
        gui_store.BindStore(store);
}

void GuiManager::ExitGuiStoreScreen()
{
        ExitGuiScan();
        gui_store.UnbindStore();
}
		
void GuiManager::EnterGuiShopScreen()
{
        Shop* shop = ((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand())->GetShop();
        gui_shop.BindShop(shop);        
}

void GuiManager::ExitGuiShopScreen()
{
        gui_shop.UnbindShop();
}

void GuiManager::EnterGuiGalaxyMapScreen()
{
        Galaxy* galaxy = player->GetNpc()->GetStarSystem()->GetGalaxy();
        gui_galaxymap.BindGalaxy(galaxy);
}

void GuiManager::ExitGuiGalaxyMapScreen()
{
        gui_galaxymap.UnbindGalaxy();
}

void GuiManager::EnterGuiGovermentScreen()
{
        Goverment* goverment = ((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand())->GetGoverment();
        gui_goverment.BindGoverment(goverment);
}

void GuiManager::ExitGuiGovermentScreen()
{
        gui_goverment.UnbindGoverment();
}    

void GuiManager::ExitCurrentScreen()
{
	switch (gui_kosmoport.GetActiveScreenId())
	{
		case GUI::SCREEN::ANGAR_ID: { ExitGuiAngarScreen(); break; }
		case GUI::SCREEN::STORE_ID: { ExitGuiStoreScreen(); break; }
		case GUI::SCREEN::SHOP_ID:  { ExitGuiShopScreen(); break; }
		case GUI::SCREEN::GALAXYMAP_ID: { ExitGuiGalaxyMapScreen(); break; }
		case GUI::SCREEN::GOVERMENT_ID: { ExitGuiGovermentScreen(); break; }
	}
}
                            
bool GuiManager::UpdateInSpace(const MouseData& data_mouse)
{
	int screen_w = Screen::Instance().GetWindow().GetWidth();
        int screen_h = Screen::Instance().GetWindow().GetHeight();
        Rect screen_rect(0, 0, screen_w, screen_h);   
	vec2f center_screen(screen_w/2, screen_h/2);
                            
       	UserInput::Instance().UpdateInSpace(player, *this);
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
        bool interaction = gui_space.UpdateMouseInteractionWithButtons(data_mouse);				
        gui_space.ButtonsAction(player);   
                                               
	if (show_gui_galaxymap == true)  
	{
		if (interaction == false)
                {
                	interaction = gui_galaxymap.UpdateMouseInteraction(data_mouse); 	
                }
        }
			
        if (gui_vehicle_scan.GetVehicle() != NULL)
	{	
		if (interaction == false)
		{
			interaction = UpdateMouseInteractionWithScanVehicle(data_mouse, player->GetNpc()->GetScanTarget());
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



void GuiManager::RenderInSpace(const MouseData& data_mouse)
{
	resetRenderTransformation();
	enable_BLEND();    
		if (show_gui_radar == true)  
		{
			gui_radar.Render();
	              	gui_vehicle_player.RenderButtons();
	      		gui_vehicle_player.RenderFocusedButtonInfo(data_mouse);    
		}
					
		if (show_gui_galaxymap == true)  
		{
			gui_galaxymap.Render();    
		}
	                                
		if (gui_vehicle_scan.GetVehicle() != NULL)
		{
			RenderScanVehicle(data_mouse, player->GetNpc()->GetScanTarget()); 				                 
		}
					
		if (gui_vehicle_target.GetVehicle() != NULL)
		{
	               	gui_vehicle_target.RenderButtons();
	       		gui_vehicle_target.RenderFocusedButtonInfo(data_mouse); 
		}
						
		gui_space.RenderBar();	
		gui_space.RenderButtons();
		gui_space.RenderFocusedButtonInfo(data_mouse);
	disable_BLEND();

	gui_space.RenderText(Screen::Instance().GetRect().GetBottomLeft());
}


bool GuiManager::RunSessionInKosmoport(const MouseData& data_mouse)
{    	
	Rect screen_rect(0, 0, Screen::Instance().GetWindow().GetWidth(), Screen::Instance().GetWindow().GetHeight());   
	vec2f center_screen(Screen::Instance().GetWindow().GetWidth()/2, Screen::Instance().GetWindow().GetHeight()/2);       			
        			
 	UserInput::Instance().UpdateInKosmoport(player, *this);
     	player->GetCursor().Update(); 
     	    	       	
	bool interaction = gui_kosmoport.UpdateMouseInteractionWithButtons(data_mouse);
	gui_kosmoport.ButtonsAction();
													
	switch(gui_kosmoport.GetActiveScreenId())
	{
		case GUI::SCREEN::ANGAR_ID:
		{
			if (gui_angar.GetAngar() == NULL) // this needs to initialize gui_angar in first time when player has landed
			{
				EnterGuiAngarScreen();
			}
			
			//update  
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
					if (show_gui_scan == true) 
					{ 
						interaction = UpdateMouseInteractionWithScanVehicle(data_mouse, gui_vehicle_scan.GetVehicle());
					}
			    	} 
	        	}
	        	
	        	//render
			resetRenderTransformation();
			gui_angar.GetAngar()->RenderBackground(screen_rect);
			enable_BLEND();   
	        		gui_angar.RenderVehicleAndItemSlots();
	        		
				if (show_gui_scan == true)
				{ 
					RenderScanVehicle(data_mouse); 
				}
				
	        		gui_kosmoport.RenderButtons(); 
	        		gui_angar.RenderButtons();
				gui_kosmoport.RenderFocusedButtonInfo(data_mouse); 
				gui_angar.RenderFocusedButtonInfo(data_mouse); 
			disable_BLEND(); 
		
			break;
		}

		case GUI::SCREEN::STORE_ID:
		{
                        //update
			if (interaction == false)
			{
				interaction = gui_store.UpdateMouseInteraction(data_mouse);
			    	if (interaction == false)
			    	{
			    		interaction = gui_vehicle_scan.UpdateMouseInteractionInStore(data_mouse, gui_store.GetStore());
			    	}
			}

	        	//render
			resetRenderTransformation();
			gui_store.GetStore()->RenderBackground(screen_rect);

			enable_BLEND();
				gui_store.RenderSlots(player->GetNpc()->GetCredits());

				bool show_skill = false;
				RenderScanVehicle(data_mouse, show_skill);
				
	        		gui_kosmoport.RenderButtons(); 
				gui_kosmoport.RenderFocusedButtonInfo(data_mouse); 
			disable_BLEND();
			drawSimpleText("credits:"+int2str(player->GetNpc()->GetCredits()), 12, 600, 200);
			//

			break;
		}

		case GUI::SCREEN::SHOP_ID:
		{
			//update
			gui_shop.UpdateLables();
			gui_shop.ButtonsAction(slider);
			if (slider.GetSubTypeId() != NONE_ID)
			{
				slider.CheckButtonsLock();
				slider.ButtonsAction(gui_shop.GetShop());
			}
			
			if (interaction == false)
			{
				interaction = gui_shop.UpdateMouseInteractionWithButtons(data_mouse);
				if (interaction == false)
				{
					if (slider.GetSubTypeId() != NONE_ID)
					{
						slider.UpdateSlidePosition(data_mouse);
						interaction = slider.UpdateMouseInteractionWithButtons(data_mouse);
					}
				}	
	        	}
	        	
	        	//render
			resetRenderTransformation();
			gui_shop.GetShop()->RenderBackground(screen_rect);
			enable_BLEND();   
				gui_shop.RenderButtons();
				
				if (slider.GetSubTypeId() != NONE_ID)
				{
					slider.Render();
				}
				
				gui_kosmoport.RenderButtons(); 
				gui_kosmoport.RenderFocusedButtonInfo(data_mouse); 
				    
			disable_BLEND();  
			
			break;
		}

		case GUI::SCREEN::GALAXYMAP_ID:
		{
			//update
			if ( interaction == false)
			{
				interaction = gui_galaxymap.UpdateMouseInteraction(data_mouse);
	        	}					   
		
			//render
			clearScreen(); //becase there is no background
	        	resetRenderTransformation();
			enable_BLEND();   
				gui_galaxymap.Render();
				
				gui_kosmoport.RenderButtons(); 
				gui_kosmoport.RenderFocusedButtonInfo(data_mouse); 
				    
			disable_BLEND();    
					
			break;
		}

		case GUI::SCREEN::GOVERMENT_ID:
		{
			//update
			if (interaction == false)
			{
				//interaction = gui_goverment.UpdateMouseInteraction(data_mouse);
	        	}
	        	
	        	//render
	        	resetRenderTransformation();
			gui_goverment.GetGoverment()->RenderBackground(screen_rect);
			enable_BLEND();   
				//gui_goverment->RenderInternals(goverment);
				
				gui_kosmoport.RenderButtons(); 
				gui_kosmoport.RenderFocusedButtonInfo(data_mouse); 
				    
			disable_BLEND(); 

			break;
		}
	}
	
	return interaction;
}


bool GuiManager::RunSessionInNatureLand(const MouseData& data_mouse)
{    	
	Rect screen_rect(0, 0, Screen::Instance().GetWindow().GetWidth(), Screen::Instance().GetWindow().GetHeight());   
	vec2f center_screen(Screen::Instance().GetWindow().GetWidth()/2, Screen::Instance().GetWindow().GetHeight()/2);       			
        			
 	UserInput::Instance().UpdateInKosmoport(player, *this);
     	player->GetCursor().Update(); 
     	    	       	
	//bool interaction = gui_kosmoport.UpdateMouseInteractionWithButtons(data_mouse);
	//gui_kosmoport.ButtonsAction();
	
									
	NatureLand* natureland = (NatureLand*)player->GetNpc()->GetVehicle()->GetLand();
	gui_natureland.BindNatureLand(natureland);

	//update  
	bool interaction = gui_natureland.UpdateMouseInteractionWithButtons(data_mouse);
	if (interaction == false)
	{
		interaction = gui_natureland.UpdateMouseInteractionWithEquipedItemSlots(data_mouse);
	}
	gui_natureland.ButtonsAction();
	
	//render
	resetRenderTransformation();
	gui_natureland.RenderBackground(screen_rect);
	enable_BLEND();   
		gui_natureland.RenderEquipedItemSlots();
		gui_natureland.RenderButtons();
		gui_natureland.RenderFocusedButtonInfo(data_mouse); 
	disable_BLEND(); 
}
