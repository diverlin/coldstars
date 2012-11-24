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

#include "../docking/Goverment.hpp"
#include "../pilots/Npc.hpp"

GuiManager::GuiManager()
{
	player = NULL;
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

bool GuiManager::UpdateMouseInteractionWithScanVehicle(const MouseData& data_mouse, Vehicle* scan_vehicle, bool allow_full_control)
{
	if (allow_full_control == false)
	{
        	if (scan_vehicle->GetId() == player->GetNpc()->GetVehicle()->GetId())
    		{
        		allow_full_control = true;  
        	    	// modify full control for friend ships         
        	}
        }

	bool interaction = gui_vehicle_scan.UpdateMouseInteractionInSpace(data_mouse, allow_full_control);        
	if ( (interaction == true) and (allow_full_control == true) )
	{
		interaction = gui_skill.UpdateButtonsMouseInteraction(data_mouse);
		gui_skill.ButtonsAction(scan_vehicle->GetOwnerNpc()->GetSkill());
	}

	return interaction;
}

bool GuiManager::UpdateMouseInteractionWithPreciseWeaponTarget(const MouseData& data_mouse)
{
	gui_vehicle_target.UpdateEquipmentIcons();

	ItemSlot* selected_item_slot = gui_vehicle_target.GetInreactedItemSlot(data_mouse);	
	if (selected_item_slot != NULL)
	{
		if (selected_item_slot->GetEquiped() == true)
		{
			player->GetNpc()->GetVehicle()->GetWeaponComplex().SetPreciseFireTarget(selected_item_slot->GetOwnerVehicle(), selected_item_slot);
			gui_vehicle_target.Reset();
			return true;
		}
	}	
	
	return false;
}

void GuiManager::RenderScanVehicle(const MouseData& data_mouse, Vehicle* vehicle, bool show_skill) const
{	
if (vehicle == NULL)
return;	
	if (player->GetCursor().GetItemSlot()->GetEquiped() == true)
	{
       		gui_vehicle_scan.RenderVehicle(data_mouse, player->GetCursor().GetItemSlot()->GetItem()->GetParentSubTypeId());
		player->GetCursor().GetItemSlot()->GetItem()->Render(player->GetCursor().GetRect(), vec2f(0, 0));		
	}
	else
	{
		gui_vehicle_scan.RenderVehicle(data_mouse, NONE_ID);
	}
					
	if ( (show_skill == true) and (vehicle->GetOwnerNpc() != NULL) )
	{
		gui_skill.RenderButtons();
		gui_skill.RenderSkills(vehicle->GetOwnerNpc()->GetSkill());
		gui_skill.RenderFocusedButtonInfo(data_mouse);
	}   					                 
}

bool GuiManager::UpdateInSpace(const MouseData& data_mouse)
{
	Rect screen_rect(0, 0, Screen::Instance().GetWindow().GetWidth(), Screen::Instance().GetWindow().GetHeight());   
	vec2f center_screen(Screen::Instance().GetWindow().GetWidth()/2, Screen::Instance().GetWindow().GetHeight()/2);        			
                            
       	UserInput::Instance().UpdateInSpace(player, *this);
     	player->GetCursor().Update();  
     	       	
        // configure which part of gui should be managed/drawn       	
        show_gui_galaxymap = false;                                                                                
        show_gui_scan = false;
        show_gui_radar = false;

        show_gui_galaxymap = player->GetShow().GetGuiGalaxyMap();  

        if ( (player->GetNpc()->GetScanTarget() != NULL) and (show_gui_galaxymap == false) )
        {
        	show_gui_scan = true;
	}                        
               
        if ( (show_gui_scan == false) and (show_gui_galaxymap == false) )
        {
        	show_gui_radar = true;  
        }             
        //

	if (gui_vehicle_player.GetVehicle() == NULL)
	{
		gui_vehicle_player.BindVehicle(player->GetNpc()->GetVehicle(), 0.6f);
         	gui_vehicle_player.SetOffset(gui_radar.GetRect().GetCenter());                        
	}
	gui_vehicle_player.UpdateEquipmentIcons();
			
                        
        if (show_gui_scan)
        {
               	gui_vehicle_scan.SetOffset(center_screen + GUI_VEHICLE_INSPACE_OFFSET);
		gui_skill.SetOffset(center_screen + GUI_SKILL_INSPACE_OFFSET);
	}
			
	if (gui_vehicle_target.GetVehicle() != NULL)
	{
		gui_vehicle_target.UpdateOffset();
	}

	//update
        bool interaction = gui_space.UpdateButtonsMouseInteraction(data_mouse);				
        gui_space.ButtonsAction(player);   
                                               
	if (show_gui_galaxymap == true)  
	{
		if (interaction == false)
                {
                	interaction = gui_galaxymap.UpdateMouseInteraction(data_mouse, player->GetNpc()->GetStarSystem()->GetGalaxy()); 	
                }
        }
			
        if (show_gui_scan == true)
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
                 	interaction = gui_vehicle_player.UpdateButtonsMouseInteraction(data_mouse);
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
			gui_galaxymap.Render(player->GetNpc()->GetStarSystem()->GetGalaxy());    
		}
	                                
		if (show_gui_scan == true)
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
        			
 	UserInput::Instance().UpdateInKosmoport(player);
     	player->GetCursor().Update(); 
     	    	       	
	bool interaction = gui_kosmoport.UpdateButtonsMouseInteraction(data_mouse);
	gui_kosmoport.ButtonsAction();
													
	switch(gui_kosmoport.GetActiveScreenId())
	{
		case GUI::SCREEN::ANGAR_ID:
		{
			gui_vehicle_scan.SetOffset(center_screen + GUI_VEHICLE_INANGAR_OFFSET);
			gui_skill.SetOffset(center_screen + GUI_SKILL_INANGAR_OFFSET);
										
			Angar* angar = ((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand())->GetAngar();
			Vehicle* scan_vehicle = player->GetNpc()->GetScanTarget();
			gui_angar.BindAngar(angar);

			//update  
			gui_angar.CheckButtonsLock();
			if (interaction == false)
			{					
				interaction = gui_angar.UpdateButtonsMouseInteraction(data_mouse);
				if (interaction == false)
				{
					interaction = gui_angar.UpdateMouseVehicleSlotsInteraction(data_mouse);
				}

				gui_angar.ButtonsAction();
			    	if ( interaction == false)
			    	{
					if (scan_vehicle != NULL) 
					{ 
						interaction = UpdateMouseInteractionWithScanVehicle(data_mouse, scan_vehicle);
					}					    	
			    	} 
	        	}
	        	
	        	//render
			resetRenderTransformation();
			angar->RenderBackground(screen_rect);
			enable_BLEND();   
	        		gui_angar.RenderVehicleSlots();
	        		
				if (scan_vehicle != NULL) 	
				{ 
					RenderScanVehicle(data_mouse, scan_vehicle); 
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
			gui_vehicle_scan.SetOffset(center_screen + GUI_VEHICLE_INSTORE_OFFSET);
			gui_store.SetOffset(center_screen + GUI_STORE_OFFSET);
					
			//if (npc->GetScanTarget() != npc->GetVehicle())
			{
				player->GetNpc()->SetScanTarget(player->GetNpc()->GetVehicle());
			}
		    
			Store* store = ((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand())->GetStore();
			Vehicle* vehicle = player->GetNpc()->GetScanTarget();    
			gui_store.BindStore(store);    				
			gui_vehicle_scan.BindVehicle(vehicle);
			
			//update
			if (interaction == false)
			{
				interaction = gui_store.UpdateMouseInteraction(data_mouse, store);
			    	if (interaction == false)
			    	{
			    		interaction = gui_vehicle_scan.UpdateMouseInteractionInStore(data_mouse, vehicle, store);
			    	}
			}
						        	
	        	//render
			resetRenderTransformation();
			store->RenderBackground(screen_rect);

			enable_BLEND();
				gui_store.RenderSlots(player->GetNpc()->GetCredits());

				bool show_skill = false;
				RenderScanVehicle(data_mouse, vehicle, show_skill);
				
	        		gui_kosmoport.RenderButtons(); 
				gui_kosmoport.RenderFocusedButtonInfo(data_mouse); 
			disable_BLEND();
			drawSimpleText("credits:"+int2str(player->GetNpc()->GetCredits()), 12, 600, 200);
			//
			
			player->GetNpc()->ResetScanTarget();
			
			break;
		}

		case GUI::SCREEN::SHOP_ID:
		{
			Shop* shop = ((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand())->GetShop();
			
			//update	
			gui_shop.UpdateLables(shop);			
			gui_shop.ButtonsAction(shop, slider);
			if (slider.GetSubTypeId() != NONE_ID)
			{
				slider.CheckButtonsLock();
				slider.ButtonsAction(shop);
			}
			
			if (interaction == false)
			{
				interaction = gui_shop.UpdateButtonsMouseInteraction(data_mouse);
				if (interaction == false)
				{
					if (slider.GetSubTypeId() != NONE_ID)
					{
						slider.UpdateSlidePosition(data_mouse);
						interaction = slider.UpdateButtonsMouseInteraction(data_mouse);
					}
				}	
	        	}
	        	
	        	//render
			resetRenderTransformation();
			shop->RenderBackground(screen_rect);
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
			Galaxy* galaxy = player->GetNpc()->GetStarSystem()->GetGalaxy();
			//update
			if ( interaction == false)
			{
				interaction = gui_galaxymap.UpdateMouseInteraction(data_mouse, galaxy);
	        	}					   
		
			//render
			clearScreen(); //becase there is no background
	        	resetRenderTransformation();
			enable_BLEND();   
				gui_galaxymap.Render(galaxy);
				
				gui_kosmoport.RenderButtons(); 
				gui_kosmoport.RenderFocusedButtonInfo(data_mouse); 
				    
			disable_BLEND();    
					
			break;
		}

		case GUI::SCREEN::GOVERMENT_ID:
		{
			Goverment* goverment = ((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand())->GetGoverment();
			
			//update
			if (interaction == false)
			{
				//interaction = gui_goverment->UpdateMouseInteraction(goverment, mxvp, myvp, lmb, rmb);
	        	}
	        	
	        	//render
	        	resetRenderTransformation();
			goverment->RenderBackground(screen_rect);
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
        			
 	UserInput::Instance().UpdateInKosmoport(player);
     	player->GetCursor().Update(); 
     	    	       	
	//bool interaction = gui_kosmoport.UpdateButtonsMouseInteraction(data_mouse);
	//gui_kosmoport.ButtonsAction();
	
									
			NatureLand* natureland = (NatureLand*)player->GetNpc()->GetVehicle()->GetLand();
			gui_natureland.BindNatureLand(natureland);

			//update  
			bool interaction = gui_natureland.UpdateButtonsMouseInteraction(data_mouse);
			gui_natureland.ButtonsAction();
	        	
	        	//render
			resetRenderTransformation();
			gui_natureland.RenderBackground(screen_rect);
			enable_BLEND();   
	        		gui_natureland.RenderButtons();
				gui_natureland.RenderFocusedButtonInfo(data_mouse); 
			disable_BLEND(); 
}
