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



GuiManager :: GuiManager(Player* player)
{
	this->player = player;
	
	gui_angar = new GuiAngar(player);
	gui_store = new GuiStore(player);
	
	gui_vehicle = new GuiVehicle(player);
      	gui_skill   = new GuiSkill(player);
      	
      	gui_kosmoport = new GuiKosmoport(player);
      	gui_space     = new GuiSpace(player);
	gui_map       = new GuiMap(player); 
}

GuiManager :: ~GuiManager()
{
        delete gui_angar;
        delete gui_store;
        
	delete gui_vehicle;
	delete gui_skill;
	
	delete gui_kosmoport;
	delete gui_space;
	delete gui_map;
}

bool GuiManager::UpdateMouseInteractionWithScanVehicle(int mxvp, int myvp, int lmb, int rmb, Vehicle* scan_vehicle, bool allow_full_control)
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
		interaction = gui_vehicle->UpdateMouseInteraction(mxvp, myvp, lmb, rmb, scan_vehicle);
		if (scan_vehicle->GetOwnerNpc() != NULL)
		{
			interaction = gui_skill->UpdateMouseInteraction(mxvp, myvp, lmb, rmb, scan_vehicle->GetOwnerNpc()->GetSkill());
		}
	}
	
	return interaction;
}

void GuiManager::RenderScanVehicle(Vehicle* vehicle, int mxvp, int myvp, bool show_skill) const
{		
	if (player->GetCursor()->GetItemSlot()->GetEquipedStatus() == true)
	{
       		gui_vehicle->RenderVehicle(vehicle, mxvp, myvp, player->GetCursor()->GetItemSlot()->GetItem()->GetFunctionalSlotSubTypeId());
		player->GetCursor()->GetItemSlot()->GetItem()->Render(player->GetCursor()->GetItemSlot()->GetRect());		
	}
	else
	{
		gui_vehicle->RenderVehicle(vehicle, mxvp, myvp, NONE_ID);
	}
					
	if ( (show_skill == true) and (vehicle->GetOwnerNpc() != NULL) )
	{
		gui_skill->RenderButtons();
		gui_skill->RenderSkills(vehicle->GetOwnerNpc()->GetSkill());
		gui_skill->RenderFocusedButtonInfo(mxvp, myvp);
	}   					                 

	if (player->GetCursor()->GetItemSlot()->GetEquipedStatus() == false)
	{
		gui_vehicle->RenderFocusedItemInfo(vehicle, mxvp, myvp);					
		//gui_skill
	}
}

bool GuiManager::RunSession()
{
	int mxvp = player->GetCursor()->GetMousePos().x;
     	int myvp = Screen::Instance().GetWindow().GetHeight() - player->GetCursor()->GetMousePos().y;         
     	int lmb  = player->GetCursor()->GetMouseLeftButton();
     	int rmb  = player->GetCursor()->GetMouseRightButton();
     		
     	bool interaction = false;
     		
     	player->GetCursor()->Update(mxvp, myvp); 
     								
	switch(player->GetNpc()->GetVehicle()->GetPlaceTypeId())
	{
		case ENTITY::SPACE_ID:
		{
			gui_vehicle->SetOffset(GUI_VEHICLE_INSPACE_OFFSET);
			gui_skill->SetOffset(GUI_SKILL_INSPACE_OFFSET);
			
			Vehicle* scan_vehicle = player->GetNpc()->GetScanTarget(); 
						        				
			//update
			if (player->GetControlFlags().GetShowGalaxyMapFlag() == true)  
			{
				interaction = gui_map->UpdateMouseInteraction(player->GetNpc()->GetStarSystem()->GetGalaxy(), mxvp, myvp, lmb, rmb); 	
			}
			else if (scan_vehicle != NULL )
			{
				interaction = UpdateMouseInteractionWithScanVehicle(mxvp, myvp, lmb, rmb, scan_vehicle);
			}

			interaction = gui_space->UpdateMouseInteraction(mxvp, myvp, lmb, rmb);    
				
			//render
			resetRenderTransformation();
			enable_BLEND();    
				if (player->GetControlFlags().GetShowGalaxyMapFlag() == true)  
				{					   
     					gui_map->Render(player->GetNpc()->GetStarSystem()->GetGalaxy());    
				}
				else if (scan_vehicle != NULL )
				{
					RenderScanVehicle(scan_vehicle, mxvp, myvp); 				                 
				}
						
				gui_space->RenderBar();	
				gui_space->RenderButtons();
				gui_space->RenderFocusedButtonInfo(mxvp, myvp);
			disable_BLEND();

			gui_space->RenderText(Screen::Instance().GetBottomLeftGlobalCoord());
		
			break;
		}
		
		case ENTITY::KOSMOPORT_ID:
		{    	
			Rect screen_rect = Rect(0, 0, Screen::Instance().GetWindow().GetWidth(), Screen::Instance().GetWindow().GetHeight());   
										
			switch(gui_kosmoport->GetActiveScreenId())
        		{
        			case GUI::SCREEN::ANGAR_ID:
        			{
        				gui_vehicle->SetOffset(GUI_VEHICLE_INANGAR_OFFSET);
        				gui_skill->SetOffset(GUI_SKILL_INANGAR_OFFSET);
        				        						
        				Angar* angar = ((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand())->GetAngar();
					Vehicle* scan_vehicle = player->GetNpc()->GetScanTarget();

					//update  
					interaction = gui_kosmoport->UpdateMouseInteraction(mxvp, myvp, lmb, rmb);
					if (interaction == false)
					{
						interaction = gui_angar->UpdateMouseInteraction(angar, mxvp, myvp, lmb, rmb);
					    	if ( interaction == false)
					    	{
							if (scan_vehicle != NULL) 
							{ 
								interaction = UpdateMouseInteractionWithScanVehicle(mxvp, myvp, lmb, rmb, scan_vehicle);
							}					    	
					    	} 
			        	}
			        	
			        	//render
        				resetRenderTransformation();
        				angar->RenderBackground(screen_rect);
               				enable_BLEND();   
			        		gui_angar->RenderVehicleSlots(angar);
			        		
						if (scan_vehicle != NULL) 	
						{ 
							RenderScanVehicle(scan_vehicle, mxvp, myvp); 
						}
						else
						{ 
							gui_angar->RenderFocusedItemInfo(angar, mxvp, myvp); 
						}

			        		gui_kosmoport->RenderButtons(); 
			        		gui_angar->RenderButtons();
                				gui_kosmoport->RenderFocusedButtonInfo(mxvp, myvp); 
                				gui_angar->RenderFocusedButtonInfo(mxvp, myvp); 
               				disable_BLEND(); 
	        		
					break;
				}
		
				case GUI::SCREEN::STORE_ID:
        			{
        				gui_vehicle->SetOffset(GUI_VEHICLE_INSTORE_OFFSET);
        				gui_store->SetOffset(GUI_STORE_OFFSET);
        						
        				//if (npc->GetScanTarget() != npc->GetVehicle())
        				{
        					player->GetNpc()->SetScanTarget(player->GetNpc()->GetVehicle());
        				}
                                    
                                        Store* store = ((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand())->GetStore();
        				Vehicle* vehicle = player->GetNpc()->GetScanTarget();        				
		
					//update
					interaction = gui_kosmoport->UpdateMouseInteraction(mxvp, myvp, lmb, rmb);
					if (interaction == false)
					{
						interaction = gui_store->UpdateMouseInteraction(store, mxvp, myvp, lmb, rmb);
					    	if (interaction == false)
					    	{
					    		interaction = gui_vehicle->UpdateMouseInteraction(mxvp, myvp, lmb, rmb, vehicle, store);
					    	}
					}
								        	
			        	//render
        				resetRenderTransformation();
					store->RenderBackground(screen_rect);
					enable_BLEND();
						gui_store->RenderSlots(store);
		
						bool show_skill = false;
						RenderScanVehicle(vehicle, mxvp, myvp, show_skill);

						gui_store->RenderFocusedItemInfo(store, mxvp, myvp);
						
			        		gui_kosmoport->RenderButtons(); 
                				gui_kosmoport->RenderFocusedButtonInfo(mxvp, myvp); 
					disable_BLEND();
	
					player->GetNpc()->ResetScanTarget();
        				
					break;
				}

        			case GUI::SCREEN::SHOP_ID:
        			{
        				Shop* shop = ((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand())->GetShop();
        				
        				//update
        				interaction = gui_kosmoport->UpdateMouseInteraction(mxvp, myvp, lmb, rmb);      					
         	        		if ( interaction == false)
					{
						//interaction = gui_shop->UpdateMouseInternaction(shop, mxvp, myvp, lmb, rmb);	
			        	}
			        	
			        	//render
        				resetRenderTransformation();
        				shop->RenderBackground(screen_rect);
        				enable_BLEND();   
     						//gui_shop->RenderInternals(shop);
     						
     						gui_kosmoport->RenderButtons(); 
                				gui_kosmoport->RenderFocusedButtonInfo(mxvp, myvp); 
                				    
					disable_BLEND();  
        				
					break;
				}

        			case GUI::SCREEN::GALAXYMAP_ID:
        			{
					Galaxy* galaxy = player->GetNpc()->GetStarSystem()->GetGalaxy();
					//update
					interaction = gui_kosmoport->UpdateMouseInteraction(mxvp, myvp, lmb, rmb);
					if ( interaction == false)
					{
						interaction = gui_map->UpdateMouseInteraction(galaxy, mxvp, myvp, lmb, rmb);
			        	}					   
				
					//render
        				clearScreen(); //becase there is no background
			        	resetRenderTransformation();
        				enable_BLEND();   
     						gui_map->Render(galaxy);
     						
     						gui_kosmoport->RenderButtons(); 
                				gui_kosmoport->RenderFocusedButtonInfo(mxvp, myvp); 
                				    
					disable_BLEND();    
        				         	
         				break;
         			}

         			case GUI::SCREEN::GOVERMENT_ID:
         			{
         				Goverment* goverment = ((Kosmoport*)player->GetNpc()->GetVehicle()->GetLand())->GetGoverment();
         				
         				//update
         				interaction = gui_kosmoport->UpdateMouseInteraction(mxvp, myvp, lmb, rmb);
         				if (interaction == false)
					{
						//interaction = gui_goverment->UpdateMouseInteraction(goverment, mxvp, myvp, lmb, rmb);
			        	}
			        	
			        	//render
			        	resetRenderTransformation();
        				goverment->RenderBackground(screen_rect);
        				enable_BLEND();   
						//gui_goverment->RenderInternals(goverment);
     						
     						gui_kosmoport->RenderButtons(); 
                				gui_kosmoport->RenderFocusedButtonInfo(mxvp, myvp); 
                				    
					disable_BLEND(); 

         				break;
         			}
			}
			
		break;		
		}
	}
	
	return interaction;
}
