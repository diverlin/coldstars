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

#include "Store.hpp"
#include "Kosmoport.hpp"
#include "../common/constants.hpp"
#include "../common/myStr.hpp"
#include "../common/EntityManager.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../items/BaseItem.hpp"
#include "../slots/ItemSlot.hpp"
#include "../pilots/Npc.hpp"

Store::Store(int id)
{
	data_id.id = id;
	data_id.type_id  = ENTITY::STORE_ID;
}

Store::~Store()
{
	EntityManager::Instance().RemoveEntity(this);
			
	for(unsigned int i=0; i<slot_total_vec.size(); i++)
	{
		delete slot_total_vec[i];
	}
	slot_total_vec.clear();
}

void Store::AddItemSlot(ItemSlot* slot) 
{ 
	slot->SetOwner(this);
	//change slot->SetRect(rect.GetBottomLeft().x, rect.GetBottomLeft().y, rect.GetWidth(), rect.GetHeight()); 
	        
	slot_total_vec.push_back(slot); 
};     
		
bool Store::AddItem(BaseItem* item)
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
        for (unsigned int i=0; i<slot_total_vec.size(); i++)
        {
                if (slot_total_vec[i]->GetEquiped() == false)
                {
                        return slot_total_vec[i];
        	}
        }
      
        return NULL;
}

void Store::SellItemFromSlot(Npc* npc, ItemSlot* slot)
{
	npc->IncreaseCredits(-slot->GetItem()->GetPrice()); 
        npc->GetVehicle()->GetEmptyCargoSlot()->SwapItemWith(slot);  
}		

bool Store::BuyItemFromSlot(Npc* npc, ItemSlot* slot)
{
	ItemSlot* empty_slot = GetEmptySlot();	
	if (empty_slot != NULL)
	{
		npc->IncreaseCredits(slot->GetItem()->GetPrice());
		return empty_slot->SwapItemWith(slot);
	}
        else
        {
               	return false;
	}
}

void Store::SaveDataUniqueStore(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	//save_ptree.put(root+"unresolved.angar_id",     angar->GetId());
}

void Store::LoadDataUniqueStore(const boost::property_tree::ptree& load_ptree)
{
	//data_unresolved_Kosmoport.angar_id = load_ptree.get<int>("unresolved.angar_id");
}

void Store::ResolveDataUniqueStore()
{
	((Kosmoport*)EntityManager::Instance().GetEntityById(data_unresolved_Room.owner_kosmoport_id))->BindStore(this); 
}

void Store::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "store." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueRoom(save_ptree, root);
	SaveDataUniqueStore(save_ptree, root);
}

void Store::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueRoom(load_ptree);
	LoadDataUniqueStore(load_ptree);
}

void Store::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueRoom();
	ResolveDataUniqueStore();
}
