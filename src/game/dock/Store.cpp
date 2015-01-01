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
//#include <ceti/StringUtils.hpp>
#include "../world/EntityManager.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../items/BaseItem.hpp"
#include "../slots/ItemSlot.hpp"
#include "../slots/VehicleSlot.hpp"
#include "../pilots/Npc.hpp"

#include "../garbage/EntityGarbage.hpp"

Store::Store(int id)
{
    SetId(id);
    SetTypeId(TYPE::ENTITY::STORE_ID);
}

Store::~Store()
{}

/* virtual */
void Store::PutChildsToGarbage() const
{            
    for(unsigned int i=0; i<item_slot_vec.size(); i++)
    {
        EntityGarbage::Instance().Add(item_slot_vec[i]);
    }
}

void Store::AddItemSlot(ItemSlot* item_slot) 
{ 
    item_slot->SetOwner(this);
    item_slot_vec.push_back(item_slot); 
};     

void Store::AddVehicleSlot(VehicleSlot* vehicle_slot) 
{ 
    vehicle_slot->SetOwner(this);
    vehicle_slot_vec.push_back(vehicle_slot); 
}; 
        
bool Store::AddItem(BaseItem* item)
{
    ItemSlot* item_slot = GetEmptyItemSlot();
    if (item_slot) 
    {
        item_slot->InsertItem(item);
        return true;
    }
         
    return true;
}

bool Store::AddVehicle(Vehicle* vehicle)
{
    VehicleSlot* vehicle_slot = GetEmptyVehicleSlot();
    if (vehicle_slot) 
    {
        //vehicle->SetLand(GetOwnerKosmoport());        
            //if (vehicle->GetStarSystem() == nullptr) // used if vehicle added directly after creation
            //{
                    //vehicle->SetStarSystem(GetOwnerKosmoport()->GetOwner()->GetStarSystem());
            //}        
        vehicle_slot->InsertVehicle(vehicle);
        return true;
    }
         
    return true;
}

ItemSlot* Store::GetEmptyItemSlot() const
{
        for (unsigned int i=0; i<item_slot_vec.size(); i++)
        {
                if (item_slot_vec[i]->GetItem() == nullptr)
                {
                        return item_slot_vec[i];
            }
        }
      
        return nullptr;
}

VehicleSlot* Store::GetEmptyVehicleSlot() const
{
        for (unsigned int i=0; i<vehicle_slot_vec.size(); i++)
        {
                if (vehicle_slot_vec[i]->GetVehicle() == nullptr)
                {
                        return vehicle_slot_vec[i];
            }
        }
      
        return nullptr;
}

int Store::BuyItem(BaseItem* item)
{
    ItemSlot* item_slot = GetEmptyItemSlot();    
    if (item_slot != nullptr)
    {
        if (item_slot->InsertItem(item) == true)
        {
            return item->GetPrice();
        }
    }

    return 0;
}

void Store::SellVehicle(Npc* npc, VehicleSlot* vehicle_slot, int price)
{
    vehicle_slot->GetVehicle()->GetAllItemsFromVehicle(npc->GetVehicle());
    vehicle_slot->GetVehicle()->SetStarSystem(npc->GetVehicle()->GetStarSystem());
    vehicle_slot->GetVehicle()->SetLand(npc->GetVehicle()->GetLand());
    vehicle_slot->GetVehicle()->SetPlaceTypeId(TYPE::PLACE::KOSMOPORT_ID);
    
    VehicleSlot* npc_vehicle_slot = npc->GetVehicle()->GetParentVehicleSlot();
    npc->GetVehicle()->GetParentVehicleSlot()->SwapVehicle(vehicle_slot);
    npc_vehicle_slot->GetVehicle()->BindOwnerNpc(npc);  
        
    npc->WithdrawCredits(price);      
}
                

void Store::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    //save_ptree.put(root+"unresolved.angar_id",     angar->GetId());
}

void Store::LoadData(const boost::property_tree::ptree& load_ptree)
{
    //data_unresolved_Kosmoport.angar_id = load_ptree.get<int>("unresolved.angar_id");
}

void Store::ResolveData()
{
    ((Kosmoport*)EntityManager::Instance().GetEntityById(data_unresolved_Room.owner_kosmoport_id))->BindStore(this); 
}

void Store::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "store." + std::to_string(GetId())+".";
    Base::SaveData(save_ptree, root);
    Room::SaveData(save_ptree, root);
    Store::SaveData(save_ptree, root);
}

void Store::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Room::LoadData(load_ptree);
    Store::LoadData(load_ptree);
}

void Store::Resolve()
{
    Base::ResolveData();
    Room::ResolveData();
    Store::ResolveData();
}
