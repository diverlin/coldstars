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
#include "../common/Global.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include <item/BaseItem.hpp>
#include "../slots/ItemSlot.hpp"
#include "../slots/VehicleSlot.hpp"
#include "../pilots/Npc.hpp"

#include <managers/EntityManager.hpp>

Store::Store(int id)
{
    setId(id);
    setTypeId(type::entity::STORE_ID);
}

Store::~Store()
{}

/* virtual */
void Store::putChildrenToGarbage() const
{            
    for(unsigned int i=0; i<item_slot_vec.size(); i++)
    {
        global::get().entityManager().addToGarbage(item_slot_vec[i]);
    }
}

void Store::addItemSlot(ItemSlot* item_slot) 
{ 
    item_slot->setOwner(this);
    item_slot_vec.push_back(item_slot); 
};     

void Store::addVehicleSlot(VehicleSlot* vehicle_slot) 
{ 
    vehicle_slot->setOwner(this);
    vehicle_slot_vec.push_back(vehicle_slot); 
}; 
        
bool Store::addItem(item::Base* item)
{
    ItemSlot* item_slot = freeItemSlot();
    if (item_slot) 
    {
        item_slot->insert(item);
        return true;
    }
         
    return true;
}

bool Store::addVehicle(Vehicle* vehicle)
{
    VehicleSlot* vehicle_slot = freeVehicleSlot();
    if (vehicle_slot) 
    {
        //vehicle->SetLand(GetOwnerKosmoport());        
            //if (vehicle->starsystem() == nullptr) // used if vehicle added directly after creation
            //{
                    //vehicle->setStarSystem(GetOwnerKosmoport()->GetOwner()->starsystem());
            //}        
        vehicle_slot->InsertVehicle(vehicle);
        return true;
    }
         
    return true;
}

ItemSlot* Store::freeItemSlot() const
{
        for (unsigned int i=0; i<item_slot_vec.size(); i++)
        {
                if (item_slot_vec[i]->item() == nullptr)
                {
                        return item_slot_vec[i];
            }
        }
      
        return nullptr;
}

VehicleSlot* Store::freeVehicleSlot() const
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

int Store::buyItem(item::Base* item)
{
    ItemSlot* item_slot = freeItemSlot();    
    if (item_slot != nullptr)
    {
        if (item_slot->insert(item) == true)
        {
            return item->price();
        }
    }

    return 0;
}

void Store::sellVehicle(Npc* npc, VehicleSlot* vehicle_slot, int price)
{
    vehicle_slot->GetVehicle()->grabItemsFromVehicle(npc->GetVehicle());
    vehicle_slot->GetVehicle()->setStarSystem(npc->GetVehicle()->starsystem());
    vehicle_slot->GetVehicle()->setLand(npc->GetVehicle()->land());
    vehicle_slot->GetVehicle()->setPlaceTypeId(type::place::KOSMOPORT);
    
    VehicleSlot* npc_vehicle_slot = npc->GetVehicle()->parentVehicleSlot();
    npc->GetVehicle()->parentVehicleSlot()->SwapVehicle(vehicle_slot);
    npc_vehicle_slot->GetVehicle()->bindNpc(npc);  
        
    npc->WithdrawCredits(price);      
}
                

void Store::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    //save_ptree.put(root+"unresolved.angar_id",     angar->id());
}

void Store::LoadData(const boost::property_tree::ptree& load_ptree)
{
    //data_unresolved_Kosmoport.angar_id = load_ptree.get<int>("unresolved.angar_id");
}

void Store::ResolveData()
{
    ((Kosmoport*)global::get().entityManager().get(data_unresolved_Room.owner_kosmoport_id))->BindStore(this); 
}

void Store::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "store." + std::to_string(id())+".";
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
