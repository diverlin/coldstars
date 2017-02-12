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
#include <item/Item.hpp>
#include "../slots/ItemSlot.hpp"
#include "../slots/VehicleSlot.hpp"
#include "../pilots/Npc.hpp"

#include <managers/EntityManager.hpp>

#include <core/descriptor/item/Item.hpp>

Store::Store(int id)
{
    assert(false);
    //    setId(id);
    //    setTypeId(entity::Type::STORE_ID);
}

Store::~Store()
{}

/* virtual */
void Store::putChildrenToGarbage() const
{
    assert(false);
    //    for(unsigned int i=0; i<item_slot_vec.size(); i++) {
    //       core::global::get().entityManager().addToGarbage(item_slot_vec[i]);
    //    }
}

void Store::addItemSlot(control::ItemSlot* item_slot)
{ 
    assert(false);
    //    item_slot->setOwner(this);
    //    item_slot_vec.push_back(item_slot);
};     

void Store::addVehicleSlot(control::VehicleSlot* vehicle_slot)
{ 
    assert(false);
    //    vehicle_slot->setOwner(this);
    //    vehicle_slot_vec.push_back(vehicle_slot);
}; 

bool Store::addItem(control::Item* item)
{
    control::ItemSlot* slot = freeItemSlot();
    if (slot) {
        slot->insert(item);
        return true;
    }

    return true;
}

bool Store::addVehicle(control::Vehicle* vehicle)
{
    control::VehicleSlot* vehicle_slot = freeVehicleSlot();
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

control::ItemSlot*
Store::freeItemSlot() const
{
    for (auto* slot: m_itemslots) {
        if (!slot->item()) {
            return slot;
        }
    }
    return nullptr;
}

control::VehicleSlot*
Store::freeVehicleSlot() const
{
    for (auto* slot: m_vehicleslots) {
        if (!slot->vehicle()) {
            return slot;
        }
    }
    return nullptr;
}

int
Store::buyItem(control::Item* item)
{
    control::ItemSlot* slot = freeItemSlot();
    if (slot) {
        if (slot->insert(item)) {
            return item->descriptor()->price();
        }
    }

    return 0;
}

void Store::sellVehicle(Npc* npc, control::VehicleSlot* vehicle_slot, int price)
{
    assert(false);
    //    vehicle_slot->vehicle()->grabItemsFromVehicle(npc->vehicle());
    //    vehicle_slot->vehicle()->setStarSystem(npc->vehicle()->starsystem());
    //    vehicle_slot->vehicle()->setLand(npc->vehicle()->land());
    //    vehicle_slot->vehicle()->setPlaceTypeId(type::place::KOSMOPORT);
    
    //    VehicleSlot* npc_vehicle_slot = npc->vehicle()->parentVehicleSlot();
    //    npc->vehicle()->parentVehicleSlot()->SwapVehicle(vehicle_slot);
    //    npc_vehicle_slot->vehicle()->bindNpc(npc);

    assert(false);
    //    npc->withdrawCredits(price);
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
    //((Kosmoport*)core::global::get().entityManager().getEntity(data_unresolved_Room.owner_kosmoport_id))->BindStore(this);
}

void Store::Save(boost::property_tree::ptree& save_ptree) const
{
    //    std::string root = "store." + std::to_string(id())+".";
    //    Base::SaveData(save_ptree, root);
    //    Room::SaveData(save_ptree, root);
    //    Store::SaveData(save_ptree, root);
}

void Store::Load(const boost::property_tree::ptree& load_ptree)
{
    //    Base::LoadData(load_ptree);
    //    Room::LoadData(load_ptree);
    //    Store::LoadData(load_ptree);
}

void Store::Resolve()
{
    //    Base::ResolveData();
    //    Room::ResolveData();
    //    Store::ResolveData();
}
