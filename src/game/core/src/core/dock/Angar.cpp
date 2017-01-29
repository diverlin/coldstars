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

#include "Angar.hpp"
#include "Kosmoport.hpp"

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>
#include "../spaceobjects/Vehicle.hpp"
#include "../slots/VehicleSlot.hpp" 
#include "../slots/ItemSlot.hpp" 
#include "../pilots/Npc.hpp"

#include <item/BaseItem.hpp>
#include <item/equipment/Bak.hpp>
#include <item/equipment/Rocket.hpp>

Angar::Angar(int id)
    :
      price_fuel(PRICE_FUEL)
{
    assert(false);
//    setId(id);
//    setTypeId(type::entity::ANGAR_ID);
}

Angar::~Angar()
{        
//    LOG("___::~Angar(), id="+std::to_string(id()));
}

/* virtual */
void Angar::putChildrenToGarbage() const
{
    assert(false);
//    for(unsigned int i=0; i<vehicle_total_slot_vec.size(); i++)
//    {
//       core::global::get().entityManager().addToGarbage(vehicle_total_slot_vec[i]);
//    }

//    for(unsigned int i=0; i<item_slot_vec.size(); i++)
//    {
//       core::global::get().entityManager().addToGarbage(item_slot_vec[i]);
//    }
}

void Angar::AddVehicleSlot(control::VehicleSlot* vehicle_slot)
{
    assert(false);
//    vehicle_slot->setOwner(this);

//    if (vehicle_slot->subtype() == type::entity::VEHICLE_MILITARY_SLOT_ID)
//    {
//        vehicle_military_slot_vec.push_back(vehicle_slot);
//    }

//    if (vehicle_slot->subtype() == type::entity::VEHICLE_VISITORS_SLOT_ID)
//    {
//        vehicle_visitors_slot_vec.push_back(vehicle_slot);
//    }

//    vehicle_total_slot_vec.push_back(vehicle_slot);
};


void Angar::AddItemSlot(control::ItemSlot* item_slot)
{
    assert(false);
//    item_slot->setOwner(this);
//    item_slot_vec.push_back(item_slot);
}

bool Angar::RepairItem(Npc* npc, control::item::Base* item) const
{
    int price = item->price() * REPAIR_ITEM_PRICE_RATE;
    assert(false);
//    if (npc->withdrawCredits(price)) {
//        return item->doRepair();
//    }

    return false;
}         

bool Angar::chargeRocketEquipment(Npc* npc, item::equipment::Rocket* rocket_equipment) const
{
    assert(false);
//    int price_for_one = rocket_equipment->price() * AMMO_PRICE_RATE;
//    int ammo_max = npc->credits() / price_for_one;
//    int ammo_need = rocket_equipment->GetAmmoMax() - rocket_equipment->GetAmmo();

//    int ammo_amount = 0;
//    if (ammo_max > ammo_need) { ammo_amount = ammo_need; }
//    else                      { ammo_amount = ammo_max; }
    
//    if (npc->withdrawCredits(ammo_amount*price_for_one) == true) {
//        rocket_equipment->SetAmmo(rocket_equipment->GetAmmo() + ammo_amount);
//        return true;
//    }

    return false;
}

bool Angar::RepairVehicle(control::Vehicle* vehicle) const
{
        assert(false);
//    int price_for_one = vehicle->vehicleDescriptor().price * REPAIR_VEHICLEKORPUS_PRICE_RATE;
//    int repair_max =  vehicle->npc()->credits() / price_for_one;
//    int repair_need = vehicle->vehicleDescriptor().armor - vehicle->armor();
    
//    int repair_amount = 0;
//    if (repair_max > repair_need) { repair_amount = repair_need; }
//    else                          { repair_amount = repair_max; }
    
//    if (vehicle->npc()->withdrawCredits(repair_amount*price_for_one) == true) {
//        vehicle->repairKorpus(repair_amount);
//        return true;
//    }
    
    return false;
}

bool Angar::TankUpVehicle(control::Vehicle* vehicle) const
{
        assert(false);
//    int fuel_to_buy_max =  vehicle->npc()->credits() / price_fuel;
//    int fuel_to_buy_need = vehicle->fuelMiss();
    
//    int fuel = 0;
//    if (fuel_to_buy_max > fuel_to_buy_need) { fuel = fuel_to_buy_need; }
//    else                                    { fuel = fuel_to_buy_max; }

//    if (vehicle->npc()->withdrawCredits(fuel*price_fuel) == true) {
//        vehicle->driveComplex().bakSlot()->bakEquipment()->increaseFuel(fuel);
//        return true;
//    }

    return false;
}

void Angar::UpdateInStatic() const
{
    for (auto slot: vehicle_visitors_slot_vec) {
        assert(false);
//        if (slot->vehicle() != nullptr)  {
//            if (slot->vehicle()->npc() != nullptr) {
//                slot->vehicle()->npc()->updateInKosmoportInStatic();
//            }
//        }
    }
}

int Angar::GetFreeVehicleSlotTotalNum() const
{
    int sum_free = 0;
    for (auto* slot: vehicle_visitors_slot_vec) {
        if (!slot->vehicle()) {
            sum_free++;
        }
    }
    return sum_free;
}

bool Angar::AddVehicle(control::Vehicle* vehicle)
{
    assert(false);
//    if (vehicle->subsubtype() == type::entity::WARRIOR_ID) {
//        for (unsigned int i=0; i<vehicle_military_slot_vec.size(); i++) {
//            if (vehicle_military_slot_vec[i]->vehicle() == nullptr) {
//                vehicle_military_slot_vec[i]->InsertVehicle(vehicle);
//                return true;
//            }
//        }
//    } else {
//        for (unsigned int i=0; i<vehicle_visitors_slot_vec.size(); i++) {
//            if (vehicle_visitors_slot_vec[i]->vehicle() == nullptr) {
//                vehicle_visitors_slot_vec[i]->InsertVehicle(vehicle);
//                return true;
//            }
//        }
//    }

    return false;
}

std::string Angar::GetDockVehicleStr() const
{
    std::string str;
    assert(false);
//    for (unsigned int i=0; i<vehicle_military_slot_vec.size(); i++) {
//        if (vehicle_military_slot_vec[i]->vehicle() != nullptr) {
//            str += "_m" + std::to_string(vehicle_military_slot_vec[i]->vehicle()->id());
//        }
//    }
//    for (unsigned int i=0; i<vehicle_visitors_slot_vec.size(); i++) {
//        if (vehicle_visitors_slot_vec[i]->vehicle() != nullptr) {
//            str += "_v" + std::to_string(vehicle_visitors_slot_vec[i]->vehicle()->id());
//        }
//    }
    return str;
}


void Angar::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{}

void Angar::LoadData(const boost::property_tree::ptree& load_ptree)
{}

void Angar::ResolveData()
{
    //((Kosmoport*)core::global::get().entityManager().getEntity(data_unresolved_Room.owner_kosmoport_id))->BindAngar(this);
}


void Angar::Save(boost::property_tree::ptree& save_ptree) const
{
//    std::string root = "angar." + std::to_string(id())+".";

//    Base::SaveData(save_ptree, root);
//    Room::SaveData(save_ptree, root);
//    Angar::SaveData(save_ptree, root);
}

void Angar::Load(const boost::property_tree::ptree& load_ptree)
{
//    Base::LoadData(load_ptree);
//    Room::LoadData(load_ptree);
//    Angar::LoadData(load_ptree);
}

void Angar::Resolve()
{
//    Base::ResolveData();
//    Room::ResolveData();
//    Angar::ResolveData();
}

