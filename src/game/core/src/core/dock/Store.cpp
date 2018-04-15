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
#include <core/spaceobject/Vehicle.hpp>
#include <core/item/Item.hpp>
#include <core/slot/ItemSlot.hpp>
#include <core/slot/VehicleSlot.hpp>
#include <core/pilot/Npc.hpp>

#include <core/manager/EntityManager.hpp>

#include <core/descriptor/item/Item.hpp>

#include <core/descriptor/dock/Store.hpp>
#include <core/model/dock/Store.hpp>

namespace core {
namespace control {

Store::Store(descriptor::StoreDescr* descr, model::Store* model)
    :
      Room(descr, model)
    , m_descriptor_store(descr)
    , m_model_store(model)
{
    for (unsigned int i=0; i<STORE_ITEM_SLOTS_NUM; i++) {
        ItemSlot* slot = new ItemSlot(SlotType::CARGO);
        __add(slot);
    }

    for (unsigned int i=0; i<STORE_VEHICLE_SLOTS_NUM; i++) {
        VehicleSlot* vehicle_slot = new VehicleSlot(i);
        __add(vehicle_slot);
    }

    //store->SetTextureObBackground(TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::STORE_BACKGROUND));

}

Store::~Store()
{}

/* virtual */
void Store::putChildrenToGarbage() const
{
    assert(false);
    //    for(unsigned int i=0; i<item_slot_vec.size(); i++) {
    //       manager::EntityManager::get().addToGarbage(item_slot_vec[i]);
    //    }
}

void Store::__add(ItemSlot* item_slot)
{ 
    item_slot->setOwner(this);
    m_item_slots.push_back(item_slot);
}

void Store::__add(VehicleSlot* vehicle_slot)
{ 
    vehicle_slot->setOwner(this);
    m_vehicle_slots.push_back(vehicle_slot);
}

bool Store::add(Item* item)
{
    ItemSlot* slot = freeItemSlot();
    if (slot) {
        slot->insert(item);
        return true;
    }

    return false;
}

bool Store::add(Vehicle* vehicle)
{
    VehicleSlot* vehicle_slot = freeVehicleSlot();
    if (vehicle_slot) {
        //vehicle->SetLand(GetOwnerKosmoport());
        //if (vehicle->starsystem() == nullptr) // used if vehicle added directly after creation
        //{
        //vehicle->setStarSystem(GetOwnerKosmoport()->GetOwner()->starsystem());
        //}
        vehicle_slot->insert(vehicle);
        return true;
    }

    return true;
}

ItemSlot*
Store::freeItemSlot() const
{
    for (auto* slot: m_item_slots) {
        if (!slot->item()) {
            return slot;
        }
    }
    return nullptr;
}

VehicleSlot*
Store::freeVehicleSlot() const
{
    for (auto* slot: m_vehicle_slots) {
        if (!slot->vehicle()) {
            return slot;
        }
    }
    return nullptr;
}

int
Store::buyItem(Item* item)
{
    ItemSlot* slot = freeItemSlot();
    if (slot) {
        if (slot->insert(item)) {
            return item->descriptor()->price();
        }
    }

    return 0;
}

void Store::sellVehicle(Npc* npc, VehicleSlot* vehicle_slot, int price)
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


//void Store::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
//    //save_ptree.put(root+"unresolved.angar_id",     angar->id());
//}

//void Store::LoadData(const boost::property_tree::ptree& load_ptree)
//{
//    //data_unresolved_Kosmoport.angar_id = load_ptree.get<int>("unresolved.angar_id");
//}

//void Store::ResolveData()
//{
//    //((Kosmoport*)manager::EntityManager::get().getEntity(data_unresolved_Room.owner_kosmoport_id))->BindStore(this);
//}

//void Store::Save(boost::property_tree::ptree& save_ptree) const
//{
//    //    std::string root = "store." + std::to_string(id())+".";
//    //    Base::SaveData(save_ptree, root);
//    //    Room::SaveData(save_ptree, root);
//    //    Store::SaveData(save_ptree, root);
//}

//void Store::Load(const boost::property_tree::ptree& load_ptree)
//{
//    //    Base::LoadData(load_ptree);
//    //    Room::LoadData(load_ptree);
//    //    Store::LoadData(load_ptree);
//}

//void Store::Resolve()
//{
//    //    Base::ResolveData();
//    //    Room::ResolveData();
//    //    Store::ResolveData();
//}

} // namespace control
} // namespace core
