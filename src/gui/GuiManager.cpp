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



GuiManager :: GuiManager()
{
	player = NULL;
}

GuiManager :: ~GuiManager()
{}

void GuiManager::SetPlayer(Player* player)
{	
	this->player = player;
	
	gui_angar.SetPlayer(player);
	gui_store.SetPlayer(player);
	
	gui_vehicle.SetPlayer(player);
      	//gui_skill.SetPlayer(player);
      	
      	gui_kosmoport.SetPlayer(player);
	gui_map.SetPlayer(player); 
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

	bool interaction = false;        
	if (allow_full_control == true)
	{
		interaction = gui_vehicle.UpdateMouseInteraction(data_mouse, scan_vehicle);
		if (scan_vehicle->GetOwnerNpc() != NULL)
		{
			interaction = gui_skill.UpdateButtonsMouseInteraction(data_mouse);
			gui_skill.ButtonsAction(scan_vehicle->GetOwnerNpc()->GetSkill());
		}
	}

	player->GetNpc()->GetVehicle()->GetWeaponComplex()->PrepareWeapons(); // this action is needed to watch waht weapons items has been removed within gui_vehicle 
		
	return interaction;
}

void GuiManager::RenderScanVehicle(const MouseData& data_mouse, Vehicle* vehicle, bool show_skill) const
{		
	if (player->GetCursor().GetItemSlot()->GetEquipedStatus() == true)
	{
       		gui_vehicle.RenderVehicle(data_mouse, vehicle, player->GetCursor().GetItemSlot()->GetItem()->GetFunctionalSlotSubTypeId());
		player->GetCursor().GetItemSlot()->GetItem()->Render(player->GetCursor().GetItemSlot()->GetRect());		
	}
	else
	{
		gui_vehicle.RenderVehicle(data_mouse, vehicle, NONE_ID);
	}
					
	if ( (show_skill == true) and (vehicle->GetOwnerNpc() != NULL) )
	{
		gui_skill.RenderButtons();
		gui_skill.RenderSkills(vehicle->GetOwnerNpc()->GetSkill());
		gui_skill.RenderFocusedButtonInfo(data_mouse);
	}   					                 

	if (player->GetCursor().GetItemSlot()->GetEquipedStatus() == false)
	{
		gui_vehicle.RenderFocusedItemInfo(data_mouse, vehicle);					
		//gui_skill
	}
}

bool GuiManager::RunSession(const MouseData& data_mouse)
{
     	bool interaction = false;
     		
     	player->GetCursor().Update(data_mouse); 
     								
	switch(player->GetNpc()->GetVehicle()->GetPlaceTypeId())
	{
		case ENTITY::SPACE_ID:
		{
			gui_vehicle.SetOffset(GUI_VEHICLE_INSPACE_OFFSET);
			gui_skill.SetOffset(GUI_SKILL_INSPACE_OFFSET);
		
		       	UserInput::Instance().UpdateInSpace(player, *this);
		       				
			Vehicle* scan_vehicle = player->GetNpc()->GetScanTarget(); 
						        				
			//update
			if (player->GetControlFlags().GetShowGalaxyMapFlag() == true)  
			{
				interaction = gui_map.UpdateMouseInteraction(data_mouse, player->GetNpc()->GetStarSystem()->GetGalaxy()); 	
			}
			else if (scan_vehicle != NULL )
			{				
				interaction = UpdateMouseInteractionWithScanVehicle(data_mouse, scan_vehicle);
			}

			if (interaction == false)
			{
				interaction = gui_space.UpdateButtonsMouseInteraction(data_mouse);
				if (interaction == false)
				{
					interaction = gui_radar.UpdateButtonsMouseInteraction(data_mouse);
					if (interaction == false)
					{
						interaction = gui_radar.UpdateMouseInteraction(data_mouse);
					}
				}
			}
			
			gui_space.ButtonsAction(player);    
			gui_radar.ButtonsAction(player);
			gui_radar.Update();
					
			//render
			resetRenderTransformation();
			enable_BLEND();    
				if (player->GetControlFlags().GetShowGalaxyMapFlag() == false)  
				{
					gui_radar.Render();
				}
				
				if (player->GetControlFlags().GetShowGalaxyMapFlag() == true)  
				{					   
     					gui_map.Render(player->GetNpc()->GetStarSystem()->GetGalaxy());    
				}
				else if (scan_vehicle != NULL )
				{
					RenderScanVehicle(data_mouse, scan_vehicle); 				                 
				}
						
				gui_space.RenderBar();	
				gui_space.RenderButtons();
				gui_space.RenderFocusedButtonInfo(data_mouse);
			disable_BLEND();

			gui_space.RenderText(Screen::Instance().GetBottomLeftGlobalCoord());
		
			break;
		}
		
		case ENTITY::KOSMOPORT_ID:
		{    	
			Rect screen_rect = Rect(0, 0, Screen::Instance().GetWindow().GetWidth(), Screen::Instance().GetWindow().GetHeight());   
			
			UserInput::Instance().UpdateInKosmoport(player);
					       	
			interaction = gui_kosmoport.UpdateButtonsMouseInteraction(data_mouse);
			gui_kosmoport.ButtonsAction();
													
			switch(gui_kosmoport.GetActiveScreenId())
        		{
        			case GUI::SCREEN::ANGAR_ID:
        			{
        				gui_vehicle.SetOffset(GUI_VEHICLE_INANGAR_OFFSET);
        				gui_skill.SetOffset(GUI_SKILL_INANGAR_OFFSET);
        				        						
        				Angar* angar = ((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand())->GetAngar();
					Vehicle* scan_vehicle = player->GetNpc()->GetScanTarget();

					//update  
					gui_angar.CheckButtonsLock();
					if (interaction == false)
					{					
						interaction = gui_angar.UpdateButtonsMouseInteraction(data_mouse);
						if (interaction == false)
						{
							interaction = gui_angar.UpdateMouseVehicleSlotsInteraction(data_mouse, angar);
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
			        		gui_angar.RenderVehicleSlots(angar);
			        		
						if (scan_vehicle != NULL) 	
						{ 
							RenderScanVehicle(data_mouse, scan_vehicle); 
						}
						else
						{ 
							gui_angar.RenderFocusedItemInfo(data_mouse, angar); 
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
        				gui_vehicle.SetOffset(GUI_VEHICLE_INSTORE_OFFSET);
        				gui_store.SetOffset(GUI_STORE_OFFSET);
        						
        				//if (npc->GetScanTarget() != npc->GetVehicle())
        				{
        					player->GetNpc()->SetScanTarget(player->GetNpc()->GetVehicle());
        				}
                                    
                                        Store* store = ((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand())->GetStore();
        				Vehicle* vehicle = player->GetNpc()->GetScanTarget();        				
		
					//update
					if (interaction == false)
					{
						interaction = gui_store.UpdateMouseInteraction(data_mouse, store);
					    	if (interaction == false)
					    	{
					    		interaction = gui_vehicle.UpdateMouseInteraction(data_mouse, vehicle, store);
					    	}
					}
								        	
			        	//render
        				resetRenderTransformation();
					store->RenderBackground(screen_rect);
					enable_BLEND();
						gui_store.RenderSlots(store);
		
						bool show_skill = false;
						RenderScanVehicle(data_mouse, vehicle, show_skill);

						gui_store.RenderFocusedItemInfo(data_mouse, store);
						
			        		gui_kosmoport.RenderButtons(); 
                				gui_kosmoport.RenderFocusedButtonInfo(data_mouse); 
					disable_BLEND();
	
					player->GetNpc()->ResetScanTarget();
        				
					break;
				}

        			case GUI::SCREEN::SHOP_ID:
        			{
        				Shop* shop = ((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand())->GetShop();
        				
        				//update				
         	        		if ( interaction == false)
					{
						//interaction = gui_shop->UpdateMouseInternaction(shop, mxvp, myvp, lmb, rmb);	
			        	}
			        	
			        	//render
        				resetRenderTransformation();
        				shop->RenderBackground(screen_rect);
        				enable_BLEND();   
     						//gui_shop->RenderInternals(shop);
     						
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
						interaction = gui_map.UpdateMouseInteraction(data_mouse, galaxy);
			        	}					   
				
					//render
        				clearScreen(); //becase there is no background
			        	resetRenderTransformation();
        				enable_BLEND();   
     						gui_map.Render(galaxy);
     						
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
			
			break;		
		}
	}
	
	return interaction;
}
