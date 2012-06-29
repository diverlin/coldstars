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

bool GuiManager::CheckInteractionAccessToScanVehicle(Vehicle* vehicle, bool allow_full_control)
{
	if (allow_full_control == false)
	{
        	if (vehicle->GetId() == player->GetNpc()->GetVehicle()->GetId())
    		{
        		allow_full_control = true;  
        	    	// modify full control for friend ships         
        	}
        }
        
        return allow_full_control;
}

void GuiManager::RenderScanVehicle(Vehicle* vehicle) const
{
	resetRenderTransformation();
	enable_BLEND();
		gui_vehicle->RenderVehicle(vehicle);
		if (vehicle->GetOwnerNpc() != NULL)
		{
			gui_skill->Render();
		}
		
		player->GetCursor()->GetItemSlot()->RenderEquipedItem();		
	
		if (player->GetCursor()->GetItemSlot()->GetEquipedStatus() == false)
		{
			gui_vehicle->RenderFocusedItemInfo(vehicle);
		}
	disable_BLEND();
}

void GuiManager::RunSession()
{
	int mxvp = player->GetCursor()->GetMousePos().x;
     	int myvp = player->GetScreen()->GetHeight() - player->GetCursor()->GetMousePos().y;         
     	int lmb  = player->GetCursor()->GetMouseLeftButton();
     	int rmb  = player->GetCursor()->GetMouseRightButton();
     			
     	player->GetCursor()->Update(); 
     								
	switch(player->GetNpc()->GetPlaceTypeId())
	{
		case ENTITY::SPACE_ID:
		{
			//////////// SCAN ///////////////
			Vehicle* scan_vehicle = player->GetNpc()->GetScanTarget(); 
			if (scan_vehicle != NULL )
			{
				bool allow_full_control = CheckInteractionAccessToScanVehicle(scan_vehicle);
				if (allow_full_control == true)
				{
					gui_vehicle->UpdateMouseInteraction(mxvp, myvp, lmb, rmb, scan_vehicle);
					gui_skill->update();
				}
	
				RenderScanVehicle(scan_vehicle);     
					                 
			}

			//////////// WORLDMAP ///////////
			if (player->GetWorldMapShowFlag() == true )  
			{
				gui_map->update();   
				gui_map->Render();   
			}

			gui_space->update();    
			gui_space->Render();
		
			break;
		}
		
		case ENTITY::KOSMOPORT_ID:
		{    								
			switch(gui_kosmoport->GetActiveScreenId())
        		{
        			case GUI::SCREEN::ANGAR_ID:
        			{
        				Angar* angar = ((Kosmoport*)player->GetNpc()->GetLand())->GetAngar();
					Vehicle* scan_vehicle = player->GetNpc()->GetScanTarget();

					//update  
					if (gui_kosmoport->UpdateMouseInteraction(mxvp, myvp, lmb, rmb) == false)
					{
					    	if (gui_angar->UpdateMouseInteraction(angar, mxvp, myvp, lmb, rmb) == false)
					    	{
							if (scan_vehicle != NULL) 
							{ 
								bool allow_full_control = CheckInteractionAccessToScanVehicle(scan_vehicle);
								if (allow_full_control == true)
								{
									gui_vehicle->UpdateMouseInteraction(mxvp, myvp, lmb, rmb, scan_vehicle);
									gui_skill->update();
								}
							}					    	
					    	} 
			        	}
			        	
			        	//render
        				resetRenderTransformation();
        				Rect screen_rect = Rect(0, 0, player->GetScreen()->GetWidth(), player->GetScreen()->GetHeight());    
        				angar->RenderBackground(screen_rect);
               				enable_BLEND();   
			        		gui_angar->RenderInternal(angar);
			        		
						if (scan_vehicle != NULL) 	{ RenderScanVehicle(scan_vehicle); }
						else 				{ gui_angar->RenderItemInfo(angar, mxvp, myvp); }

			        		gui_kosmoport->RenderButtons(); 
			        		gui_angar->RenderButtons();
                				gui_kosmoport->RenderButtonInfo(mxvp, myvp); 
                				gui_angar->RenderButtonInfo(mxvp, myvp); 
               				disable_BLEND(); 
	        		
					break;
				}
		
				case GUI::SCREEN::STORE_ID:
        			{
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
					Rect screen_rect(0, 0, player->GetScreen()->GetWidth(), player->GetScreen()->GetHeight()); 
					store->RenderBackground(screen_rect);
					enable_BLEND();
						gui_vehicle->RenderVehicle(vehicle);
						gui_store->RenderSlots(store);
		
						player->GetCursor()->GetItemSlot()->RenderEquipedItem();	

						gui_store->RenderFocusedItemInfo(store, mxvp, myvp);	
						if (player->GetCursor()->GetItemSlot()->GetEquipedStatus() == false)
						{
							gui_vehicle->RenderFocusedItemInfo(vehicle);
						}

			        		gui_kosmoport->RenderButtons(); 
                				gui_kosmoport->RenderButtonInfo(mxvp, myvp); 
					disable_BLEND();
	
					player->GetNpc()->ResetScanTarget();
        				
					break;
				}

        			case GUI::SCREEN::SHOP_ID:
        			{
        				((Kosmoport*)player->GetNpc()->GetLand())->GetShop()->Update();
                			((Kosmoport*)player->GetNpc()->GetLand())->GetShop()->Render(player);
		
        				//gui_kosmoport->UpdateMouseInteraction(); 
        				//gui_kosmoport->Render(); 
        				
					break;
				}

        			case GUI::SCREEN::GALAXYMAP_ID:
        			{
        				clearScreen();
        				gui_map->update();
                			gui_map->Render();   

        				//gui_kosmoport->UpdateMouseInteraction(); 
        				//gui_kosmoport->Render(); 
        				         	
         				break;
         			}

         			case GUI::SCREEN::GOVERMENT_ID:
         			{
         				((Kosmoport*)player->GetNpc()->GetLand())->GetGoverment()->Update();
                			((Kosmoport*)player->GetNpc()->GetLand())->GetGoverment()->Render(player);
         	
         	        		//gui_kosmoport->UpdateMouseInteraction(); 
        				//gui_kosmoport->Render(); 
        				
         				break;
         			}
			}
			
		break;		
		}
	}

}
