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
}

GuiManager :: ~GuiManager()
{
	delete gui_vehicle;
	delete gui_skill;
	delete gui_store;
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
	gui_store->Update();
	gui_vehicle->Update(player->GetNpc()->GetVehicle(), ((Kosmoport*)player->GetNpc()->GetLand())->GetStore());
	
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
	resetRenderTransformation();

	gui_store->RenderBackground();
	
	enable_BLEND();

		gui_vehicle->Render();
		gui_store->RenderSlots();
		
		player->GetCursor()->GetItemSlot()->RenderEquipedItem();	

		gui_store->RenderFocusedItemInfo();	
		if (player->GetCursor()->GetItemSlot()->GetEquipedStatus() == false)
		{
			gui_vehicle->RenderFocusedItemInfo();
		}

	disable_BLEND();
}


void GuiManager::RenderInScan() const
{
	resetRenderTransformation();
	enable_BLEND();

		gui_vehicle->Render();
		gui_skill->Render();
		
		player->GetCursor()->GetItemSlot()->RenderEquipedItem();		
	
		if (player->GetCursor()->GetItemSlot()->GetEquipedStatus() == false)
		{
			gui_vehicle->RenderFocusedItemInfo();
		}
	disable_BLEND();
}

