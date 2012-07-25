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



GuiVehicle :: GuiVehicle()
{}

GuiVehicle :: ~GuiVehicle()
{}


bool GuiVehicle::UpdateMouseInteraction(const MouseData& data_mouse, Vehicle* vehicle, Store* store)
{
	for(unsigned int i=0; i<vehicle->slot_total_vec.size(); i++)
	{ 
		if (vehicle->slot_total_vec[i]->GetRect().CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
		{  
			if (data_mouse.left_click == true)
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
					player->GetCursor().GetItemSlot()->SwapItemWith(vehicle->slot_total_vec[i]);     
				}
			} 
			
			return true;
       		}        	
        }         
                        

	// GATE SLOT
	if ((player->GetCursor().GetItemSlot()->GetEquipedStatus() == true) and (store == NULL))
	{
		if (vehicle->GetGateSlot()->GetRect().CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)  
		{
			if (data_mouse.left_click == true)
			{
				player->GetCursor().GetItemSlot()->DropItemToSpace(player->GetNpc()->GetVehicle());	
			}
			
			return true;
		}
	}
	
	return false;
}


void GuiVehicle::RenderVehicle(const MouseData& data_mouse, Vehicle* vehicle, int requested_subtype_id) const
{
	glPushMatrix();
		glTranslatef(offset.x, offset.y, 0);
		drawTexturedRect(vehicle->textureOb_gui, vehicle->kontur_rect, -1.0);

		RenderSlotsAndItems(vehicle);
		if (requested_subtype_id != NONE_ID)
		{
			RenderMarksForEmptySlots(data_mouse, vehicle, requested_subtype_id);
		}
	glPopMatrix();
}

void GuiVehicle::RenderSlotsAndItems(Vehicle* vehicle) const
{
	for(unsigned int i=0; i<vehicle->slot_total_vec.size(); i++)
	{
		vehicle->slot_total_vec[i]->Render();
		if (vehicle->slot_total_vec[i]->GetEquipedStatus() == true)
               	{
               		vehicle->slot_total_vec[i]->GetItem()->Render(vehicle->slot_total_vec[i]->GetRect());	
               	}
	}
	
	vehicle->GetGateSlot()->Render();
}

void GuiVehicle::RenderMarksForEmptySlots(const MouseData& data_mouse, Vehicle* vehicle, int requested_subtype_id) const
{
	for(unsigned int i=0; i<vehicle->slot_total_vec.size(); i++)
	{
		if ( (vehicle->slot_total_vec[i]->GetEquipedStatus() == false) and (vehicle->slot_total_vec[i]->GetSubTypeId() != ITEMSLOT::CARGO_ID) )
               	{
               		if (requested_subtype_id == vehicle->slot_total_vec[i]->GetSubTypeId())
               		{
               			vehicle->slot_total_vec[i]->RenderMark(GuiTextureObCollector::Instance().slot_mark_accept);
               		}
               		else
               		{
               			if (vehicle->slot_total_vec[i]->GetRect().CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
               			{
               				vehicle->slot_total_vec[i]->RenderMark(GuiTextureObCollector::Instance().slot_mark_reject);
               			}
               		}
               	}
	}
}

void GuiVehicle::RenderFocusedItemInfo(const MouseData& data_mouse, Vehicle* vehicle) const
{
	for(unsigned int i=0; i<vehicle->slot_total_vec.size(); i++)
	{ 
		if (vehicle->slot_total_vec[i]->GetRect().CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
		{  
			vehicle->slot_total_vec[i]->RenderItemInfo(-offset.x, -offset.y);
		}
	}
}





