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



GuiVehicle :: GuiVehicle(Player* player)
{
	this->player = player;
}

GuiVehicle :: ~GuiVehicle()
{}


void GuiVehicle::Update(Vehicle* vehicle, Store* store)
{
    	bool lmb = player->GetCursor()->GetMouseLeftButton();; 
    	//bool rmb = player->GetCursor()->GetMouseRightButton();; 

	for(unsigned int i = 0; i < vehicle->slot_total_vec.size(); i++)
	{ 
		if (vehicle->slot_total_vec[i]->CheckInteraction(player->GetCursor()->GetMousePos().x, (player->GetScreen()->getHeight() - player->GetCursor()->GetMousePos().y)) == true)
		{  
			if (lmb == true)
			{
				if (store != NULL)
				{	
					if (vehicle->slot_total_vec[i]->GetEquipedStatus() == true)
					{
						store->BuyItemFromSlot(player->GetNpc(), vehicle->slot_total_vec[i]);
					}
            			}          		
				else 
				{
					player->GetCursor()->GetItemSlot()->SwapItemWith(vehicle->slot_total_vec[i]);     
				}
			} 
       		}        	
        }         
                        

	// GATE SLOT
	if ((player->GetCursor()->GetItemSlot()->GetEquipedStatus() == true) and (store == NULL))
	{
		if (vehicle->GetGateSlot()->CheckInteraction(player->GetCursor()->GetMousePos().x, (player->GetScreen()->getHeight() - player->GetCursor()->GetMousePos().y)) == true)  
		{
			if (lmb == true)
			{
				player->GetCursor()->GetItemSlot()->DropItemToSpace(player->GetNpc()->GetVehicle());	
			}
		}
	}
}




void GuiVehicle::Render(Vehicle* vehicle) const
{
	drawTexturedRect(vehicle->textureOb_gui, vehicle->kontur_rect, -1.0);

	for(unsigned int i = 0; i < vehicle->slot_total_vec.size(); i++)
	{
		vehicle->slot_total_vec[i]->Render(-1);
	}
	
	vehicle->GetGateSlot()->Render(-1);
}


void GuiVehicle::RenderFocusedItemInfo(Vehicle* vehicle) const
{
	for(unsigned int i = 0; i < vehicle->slot_total_vec.size(); i++)
	{ 
		if (vehicle->slot_total_vec[i]->CheckInteraction(player->GetCursor()->GetMousePos().x, (player->GetScreen()->getHeight()  - player->GetCursor()->GetMousePos().y)) == true)
		{  
			vehicle->slot_total_vec[i]->RenderItemInfo();
		}
	}
}





