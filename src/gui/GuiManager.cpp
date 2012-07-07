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

void GuiManager::RenderScanVehicle(Vehicle* vehicle, int mxvp, int myvp) const
{
        resetRenderTransformation();
       	gui_vehicle->RenderVehicle(vehicle);
	if (vehicle->GetOwnerNpc() != NULL)
	{
		gui_skill->Render(vehicle->GetOwnerNpc()->GetSkill());
	}
		
	if (player->GetCursor()->GetItemSlot()->GetEquipedStatus() == true)
	{
		player->GetCursor()->GetItemSlot()->GetItem()->Render(player->GetCursor()->GetItemSlot()->GetRect());		
	}
	
	if (player->GetCursor()->GetItemSlot()->GetEquipedStatus() == false)
	{
		gui_vehicle->RenderFocusedItemInfo(vehicle, mxvp, myvp);
	}
}

void GuiManager::RunSession()
{
	int mxvp = player->GetCursor()->GetMousePos().x;
     	int myvp = Screen::Instance().GetWindow().GetHeight() - player->GetCursor()->GetMousePos().y;         
     	int lmb  = player->GetCursor()->GetMouseLeftButton();
     	int rmb  = player->GetCursor()->GetMouseRightButton();
     			
     	player->GetCursor()->Update(mxvp, myvp); 
     								
	switch(player->GetNpc()->GetPlaceTypeId())
	{
		case ENTITY::SPACE_ID:
		{
			gui_vehicle->SetOffset(GUI_VEHICLE_INSPACE_OFFSET);
			gui_skill->SetOffset(GUI_SKILL_INSPACE_OFFSET);
			        				
			//////////// SCAN ///////////////
			Vehicle* scan_vehicle = player->GetNpc()->GetScanTarget(); 
			if (scan_vehicle != NULL )
			{
				UpdateMouseInteractionWithScanVehicle(mxvp, myvp, lmb, rmb, scan_vehicle);
				enable_BLEND(); 
					RenderScanVehicle(scan_vehicle, mxvp, myvp);    					                 
				disable_BLEND();
			}

			//////////// WORLDMAP ///////////
			if (player->GetWorldMapShowFlag() == true )  
			{
				Galaxy* galaxy = player->GetNpc()->GetStarSystem()->GetGalaxy();
				//update
				gui_map->UpdateMouseInteraction(galaxy, mxvp, myvp, lmb, rmb);   
				
				//render
			        resetRenderTransformation();
        			enable_BLEND();   
     					gui_map->Render(galaxy);    
				disable_BLEND();  					
			}

			gui_space->UpdateMouseInteraction(mxvp, myvp, lmb, rmb);    
				
			resetRenderTransformation();
			enable_BLEND();    						
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
        				        						
        				Angar* angar = ((Kosmoport*)player->GetNpc()->GetLand())->GetAngar();
					Vehicle* scan_vehicle = player->GetNpc()->GetScanTarget();

					//update  
					if (gui_kosmoport->UpdateMouseInteraction(mxvp, myvp, lmb, rmb) == false)
					{
					    	if (gui_angar->UpdateMouseInteraction(angar, mxvp, myvp, lmb, rmb) == false)
					    	{
							if (scan_vehicle != NULL) 
							{ 
								UpdateMouseInteractionWithScanVehicle(mxvp, myvp, lmb, rmb, scan_vehicle);
							}					    	
					    	} 
			        	}
			        	
			        	//render
        				resetRenderTransformation();
        				angar->RenderBackground(screen_rect);
               				enable_BLEND();   
			        		gui_angar->RenderInternal(angar);
			        		
						if (scan_vehicle != NULL) 	{ RenderScanVehicle(scan_vehicle, mxvp, myvp); }
						else 				{ gui_angar->RenderFocusedItemInfo(angar, mxvp, myvp); }

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
                                    
                                        Store* store = ((Kosmoport*)player->GetNpc()->GetLand())->GetStore();
        				Vehicle* vehicle = player->GetNpc()->GetScanTarget();        				
		
					//update
					if (gui_kosmoport->UpdateMouseInteraction(mxvp, myvp, lmb, rmb) == false)
					{
					    	if (gui_store->UpdateMouseInteraction(store, mxvp, myvp, lmb, rmb) == false)
					    	{
					    		gui_vehicle->UpdateMouseInteraction(mxvp, myvp, lmb, rmb, vehicle, store);
					    	}
					}
								        	
			        	//render
        				resetRenderTransformation();
					store->RenderBackground(screen_rect);
					enable_BLEND();
						gui_vehicle->RenderVehicle(vehicle);
						gui_store->RenderSlots(store);
		
						if (player->GetCursor()->GetItemSlot()->GetEquipedStatus() == true)
						{
							player->GetCursor()->GetItemSlot()->GetItem()->Render(player->GetCursor()->GetItemSlot()->GetRect());		
						}	
						else
						{
							gui_vehicle->RenderFocusedItemInfo(vehicle, mxvp, myvp);
						}

						gui_store->RenderFocusedItemInfo(store, mxvp, myvp);
						
			        		gui_kosmoport->RenderButtons(); 
                				gui_kosmoport->RenderFocusedButtonInfo(mxvp, myvp); 
					disable_BLEND();
	
					player->GetNpc()->ResetScanTarget();
        				
					break;
				}

        			case GUI::SCREEN::SHOP_ID:
        			{
        				Shop* shop = ((Kosmoport*)player->GetNpc()->GetLand())->GetShop();
        				
        				//update        					
         	        		if (gui_kosmoport->UpdateMouseInteraction(mxvp, myvp, lmb, rmb) == false)
					{
						//gui_shop->UpdateMouseInternaction(shop, mxvp, myvp, lmb, rmb);	
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
					if (gui_kosmoport->UpdateMouseInteraction(mxvp, myvp, lmb, rmb) == false)
					{
						gui_map->UpdateMouseInteraction(galaxy, mxvp, myvp, lmb, rmb);
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
         				Goverment* goverment = ((Kosmoport*)player->GetNpc()->GetLand())->GetGoverment();
         				
         				//update
         				if (gui_kosmoport->UpdateMouseInteraction(mxvp, myvp, lmb, rmb) == false)
					{
						//gui_goverment->UpdateMouseInteraction(goverment, mxvp, myvp, lmb, rmb);
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

}
