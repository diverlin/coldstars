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
	
	gui_vehicle = new GuiVehicle(player);
      	gui_skill   = new GuiSkill(player);
      	gui_store   = new GuiStore(player);
      	
      	gui_kosmoport = new GuiKosmoport(player);
      	gui_space     = new GuiSpace(player);
	gui_map       = new GuiMap(player); 
}

GuiManager :: ~GuiManager()
{
	delete gui_vehicle;
	delete gui_skill;
	delete gui_store;
	
	delete gui_kosmoport;
	delete gui_space;
	delete gui_map;
}

void GuiManager::UpdateInAngar()
{
	UpdateInScan();
}

void GuiManager::UpdateInSpace()
{
	UpdateInScan();
}

void GuiManager::UpdateInStore()
{        	
	Store* store = ((Kosmoport*)player->GetNpc()->GetLand())->GetStore();
	Vehicle* vehicle = player->GetNpc()->GetScanTarget();
	
	gui_store->Update(store);
	gui_vehicle->Update(vehicle, store);
	
	player->GetCursor()->Update();
}

void GuiManager::UpdateInScan(bool allow_full_control)
{
	if (allow_full_control == false)
	{
        	if (player->GetNpc()->GetVehicle() == player->GetNpc()->GetScanTarget())
    		{
        		allow_full_control = true;  
        	    	// modify full control for friend ships         
        	}
        }
               
	if (allow_full_control == true)
	{
		gui_vehicle->Update(player->GetNpc()->GetScanTarget());
		gui_skill->update();
	}
	
	player->GetCursor()->Update();
}

void GuiManager::RenderInStore() const
{
	Store* store = ((Kosmoport*)player->GetNpc()->GetLand())->GetStore();
	Vehicle* vehicle = player->GetNpc()->GetScanTarget();
		
	resetRenderTransformation();

        Rect screen_rect = Rect(0, 0, player->GetScreen()->GetWidth(), player->GetScreen()->GetHeight()); 
	gui_store->RenderBackground(store, screen_rect);
	
	enable_BLEND();

		gui_vehicle->Render(vehicle);
		gui_store->RenderSlots(store);
		
		player->GetCursor()->GetItemSlot()->RenderEquipedItem();	

		gui_store->RenderFocusedItemInfo(store);	
		if (player->GetCursor()->GetItemSlot()->GetEquipedStatus() == false)
		{
			gui_vehicle->RenderFocusedItemInfo(vehicle);
		}

	disable_BLEND();
}


void GuiManager::RenderInScan() const
{
	Vehicle* vehicle = player->GetNpc()->GetScanTarget();
	
	resetRenderTransformation();
	enable_BLEND();

		gui_vehicle->Render(vehicle);
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
	switch(player->GetNpc()->GetPlaceTypeId())
	{
		case ENTITY::SPACE_ID:
		{
			//////////// SCAN ///////////////
			if (player->GetNpc()->GetScanTarget() != NULL )
			{
				UpdateInSpace();
				RenderInScan();                       
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
        				((Kosmoport*)player->GetNpc()->GetLand())->GetAngar()->MouseControl(player);                                
               				((Kosmoport*)player->GetNpc()->GetLand())->GetAngar()->Render(player);

					if (player->GetNpc()->GetScanTarget() != NULL) 
					{ 
						UpdateInAngar();
						RenderInScan(); 
					}
					else
					{
						((Kosmoport*)player->GetNpc()->GetLand())->GetAngar()->RenderItemInfo(player);
					}
			
					break;
				}
		
				case GUI::SCREEN::STORE_ID:
        			{
        				//if (npc->GetScanTarget() != npc->GetVehicle())
        				{
        					player->GetNpc()->SetScanTarget(player->GetNpc()->GetVehicle());
        				}
                                    
        				UpdateInStore();
                			RenderInStore(); 
		
					player->GetNpc()->ResetScanTarget();
		
					break;
				}

        			case GUI::SCREEN::SHOP_ID:
        			{
        				((Kosmoport*)player->GetNpc()->GetLand())->GetShop()->Update();
                			((Kosmoport*)player->GetNpc()->GetLand())->GetShop()->Render(player);
		
					break;
				}

        			case GUI::SCREEN::GALAXYMAP_ID:
        			{
        				clearScreen();
        				gui_map->update();
                			gui_map->Render();   
         	
         				break;
         			}

         			case GUI::SCREEN::GOVERMENT_ID:
         			{
         				((Kosmoport*)player->GetNpc()->GetLand())->GetGoverment()->Update();
                			((Kosmoport*)player->GetNpc()->GetLand())->GetGoverment()->Render(player);
         	
         				break;
         			}
			}
	
        		gui_kosmoport->UpdateMouseInteraction(); 
        		gui_kosmoport->Render(); 
			
		break;		
		}
	}

}
