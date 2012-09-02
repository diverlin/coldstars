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


bool GuiVehicle::UpdateMouseInteractionInSpace(const MouseData& data_mouse, Vehicle* vehicle)
{
	for(unsigned int i=0; i<vehicle->slot_total_vec.size(); i++)
	{ 
		if (vehicle->slot_total_vec[i]->GetRect().CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
		{  
			if (data_mouse.left_click == true)
			{
				player->GetCursor().GetItemSlot()->SwapItemWith(vehicle->slot_total_vec[i]);     
			} 
			
			#if DEBUG_ITEMDAMAGELOCKVIAGUI > 0
			{
				switch(DEBUG_ITEMDAMAGELOCKVIAGUI)
				{
					case 1:
					{
						if (vehicle->slot_total_vec[i]->GetEquiped() == true)
						{
							if (data_mouse.right_click == true)
							{
								std::cout<<"DEBUG ACTION in GuiVehicle::UpdateMouseInteractionInSpace, ItemLOck testing"<<std::endl;
								if (vehicle->slot_total_vec[i]->GetItem()->GetFunctioning() == true)
								{
									vehicle->slot_total_vec[i]->GetItem()->LockEvent(2);
								}
								else
								{
									vehicle->slot_total_vec[i]->GetItem()->LockEvent(0);
								}
							}
						}
						
						break;
					}
					
					case 2:
					{						
						if (vehicle->slot_total_vec[i]->GetEquiped() == true)
						{
							if (data_mouse.right_click == true)
							{
								std::cout<<"DEBUG ACTION in GuiVehicle::UpdateMouseInteractionInSpace, Item Damage testing"<<std::endl;
								if (vehicle->slot_total_vec[i]->GetItem()->GetFunctioning() == true)
								{
									vehicle->slot_total_vec[i]->GetItem()->SetCondition(0);
								}
								else
								{
									vehicle->slot_total_vec[i]->GetItem()->SetCondition(1000);
								}
							}
						}
						
						break;
					}
				}
			}
			#endif
			
			return true;
       		}
        }                       

	// GATE SLOT
	if (player->GetCursor().GetItemSlot()->GetEquiped() == true)
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


bool GuiVehicle::UpdateMouseInteractionInStore(const MouseData& data_mouse, Vehicle* vehicle, Store* store)
{
	for(unsigned int i=0; i<vehicle->slot_total_vec.size(); i++)
	{ 
		if (vehicle->slot_total_vec[i]->GetRect().CheckInteraction(data_mouse.mx - offset.x, data_mouse.my - offset.y) == true)
		{  
			if (data_mouse.left_click == true)
			{
				if (vehicle->slot_total_vec[i]->GetEquiped() == true)
				{
					if (vehicle->slot_total_vec[i]->GetItem()->GetTypeId() != ENTITY::GOODS_ID)
					{
						store->BuyItemFromSlot(player->GetNpc(), vehicle->slot_total_vec[i]);
					}
					else
					{
						store->GetOwnerKosmoport()->GetShop()->BuyGoods(player->GetNpc(), (GoodsPack*)vehicle->slot_total_vec[i]->GetItem());
					}
            			}
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

		RenderSlots(vehicle);
		if (requested_subtype_id != NONE_ID)
		{
			RenderMarksForEmptySlots(data_mouse, vehicle, requested_subtype_id);
		}
	glPopMatrix();
}

void GuiVehicle::RenderSlots(Vehicle* vehicle) const
{
	for(unsigned int i=0; i<vehicle->slot_total_vec.size(); i++)
	{
		vehicle->slot_total_vec[i]->Render(offset);
	}
	
	vehicle->GetGateSlot()->Render(offset);
}

void GuiVehicle::RenderMarksForEmptySlots(const MouseData& data_mouse, Vehicle* vehicle, int requested_subtype_id) const
{
	for(unsigned int i=0; i<vehicle->slot_total_vec.size(); i++)
	{
		if ( (vehicle->slot_total_vec[i]->GetEquiped() == false) and (vehicle->slot_total_vec[i]->GetSubTypeId() != ITEMSLOT::CARGO_ID) )
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





