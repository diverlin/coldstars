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



void GuiManager :: updateInStore()
{        	
	gui_store->update();
	gui_vehicle->update();
	
	player->getCursor()->update();
}

void GuiManager :: updateInScan(bool allow_full_control)
{
        if ( (player->getNpc()->getVehicle() == player->getNpc()->getScanTarget()) and (allow_full_control == false) )
    	{
        	allow_full_control = true;  
        }    	// modify full control for friend ships         
        	
               
	if (allow_full_control == true)
	{
		gui_vehicle->update();
		gui_skill->update();
	}
	
	player->getCursor()->update();
}



void GuiManager :: renderInStore() const
{
	resetRenderTransformation();

	gui_store->renderBackground();
	
	enable_BLEND();

		gui_vehicle->Render();
		gui_store->Render();
		
		player->getCursor()->getSlot()->RenderEquipedItem();	

		gui_store->renderFocusedItemInfo();	
		if (player->getCursor()->getSlot()->GetEquipedStatus() == false)
		{
			gui_vehicle->renderFocusedItemInfo();
		}

	disable_BLEND();
}


void GuiManager :: renderInScan() const
{
	resetRenderTransformation();
	enable_BLEND();

		gui_vehicle->Render();
		gui_skill->Render();
		
		player->getCursor()->getSlot()->RenderEquipedItem();		
	
		if (player->getCursor()->getSlot()->GetEquipedStatus() == false)
		{
			gui_vehicle->renderFocusedItemInfo();
		}
	disable_BLEND();
}

