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



void GuiVehicle :: update()
{
	Vehicle* vehicle = player->getNpc()->getScanTarget();

	Store* store = NULL;
	if (player->getNpc()->GetPlaceTypeId() == ENTITY::KOSMOPORT_ID)
	{
		store = ((Kosmoport*)player->getNpc()->getLand())->getStore();
	}
	
    	bool lmb = player->getCursor()->getMouseLeftButton();; 
    	//bool rmb = player->getCursor()->getMouseRightButton();; 

	for(unsigned int i = 0; i < vehicle->slot_total_vec.size(); i++)
	{ 
		if (vehicle->slot_total_vec[i]->interaction(player->getCursor()->getMousePos().x, (player->getScreen()->getHeight() - player->getCursor()->getMousePos().y)) == true)
		{  
			if (lmb == true)
			{
				if (store != NULL)
				{	
					if (vehicle->slot_total_vec[i]->getEquipedStatus() == true)
					{
						store->buyItemFromSlot(player->getNpc(), vehicle->slot_total_vec[i]);
					}
            			}          		
				else 
				{
					player->getCursor()->getSlot()->SwapItemWith(vehicle->slot_total_vec[i]);     
				}
			} 
       		}        	
        }         
                        

	// GATE SLOT
	if (vehicle->GetGateSlot()->interaction(player->getCursor()->getMousePos().x, (player->getScreen()->getHeight() - player->getCursor()->getMousePos().y)) == true)  
	{
		//// DROP ITEM TO OUTERSPACE ////
		if ( (lmb == true) and (store == NULL) )
		{
			if (player->getCursor()->getSlot()->getEquipedStatus() == true)
			{
				player->getCursor()->getSlot()->dropItemToSpace();	
			} 
		}
	}
}




void GuiVehicle :: render() const
{
	Vehicle* vehicle = player->getNpc()->getScanTarget();

	drawTexturedRect(vehicle->texOb_korpus, vehicle->kontur_rect, -1.0);

	for(unsigned int i = 0; i < vehicle->slot_total_vec.size(); i++)
	{
		vehicle->slot_total_vec[i]->render(-1);
	}
	
	vehicle->GetGateSlot()->render(-1);
}


void GuiVehicle :: renderFocusedItemInfo() const
{
	Vehicle* vehicle = player->getNpc()->getScanTarget();

	for(unsigned int i = 0; i < vehicle->slot_total_vec.size(); i++)
	{ 
		if (vehicle->slot_total_vec[i]->interaction(player->getCursor()->getMousePos().x, (player->getScreen()->getHeight()  - player->getCursor()->getMousePos().y)) == true)
		{  
			vehicle->slot_total_vec[i]->renderItemInfo();
		}
	}
}





