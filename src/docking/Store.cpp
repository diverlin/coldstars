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



Store::Store(int id)
{
	data_id.id = id;
	data_id.type_id  = ENTITY::STORE_ID;
	data_id.subtype_id  = NONE_ID;
		
        textureOb_background = NULL; 
}

Store::~Store()
{}

bool Store::Add(BaseItem* item)
{
	ItemSlot* empty_slot = GetEmptySlot();
	if (empty_slot) 
	{
		empty_slot->InsertItem(item);
		return true;
	}
	     
	return true;
}

ItemSlot* Store::GetEmptySlot()
{
        for (unsigned int si = 0; si < slot_vec.size(); si++)
        {
                if (slot_vec[si]->GetEquipedStatus() == false)
                        return slot_vec[si];
        }
      
        return NULL;
}

bool Store::SellItemFromSlot(Npc* npc, ItemSlot* slot)
{
	unsigned int price = slot->GetItem()->GetPrice();
        if (npc->GetCredits() >= price)
        {
        	npc->GetVehicle()->GetEmptyOtsecSlot()->SwapItemWith(slot); 
                npc->IncreaseCredits(price);    
                
                return true;                 	                                       
        }
        
        return false;
}		

bool Store::BuyItemFromSlot(Npc* npc, ItemSlot* slot)
{
	unsigned int price = slot->GetItem()->GetPrice();
	
	ItemSlot* empty_slot = GetEmptySlot();	
	if (empty_slot != NULL)
	{
		npc->IncreaseCredits(price);
		return empty_slot->SwapItemWith(slot);
	}
	else
	{
		return false;
	}
}
