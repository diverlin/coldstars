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
#include "../world/EntityManager.hpp"
//#include <ceti/StringUtils.hpp>
#include "../common/Logger.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../slots/VehicleSlot.hpp" 
#include "../slots/ItemSlot.hpp" 
#include "../pilots/Npc.hpp"

#include "../garbage/EntityGarbage.hpp"
#include "../items/BaseItem.hpp"
#include "../items/equipment/BakEquipment.hpp"
#include "../items/equipment/RocketEquipment.hpp"

Angar::Angar(int id)
    :
      price_fuel(PRICE_FUEL)
{
    setId(id);
    setTypeId(TYPE::ENTITY::ANGAR_ID);
}

Angar::~Angar()
{        
#if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~Angar(), id="+std::to_string(id()));
#endif
}

/* virtual */
void Angar::putChildrenToGarbage() const
{
    for(unsigned int i=0; i<vehicle_total_slot_vec.size(); i++)
    {
        EntityGarbage::Instance().Add(vehicle_total_slot_vec[i]);
    }

    for(unsigned int i=0; i<item_slot_vec.size(); i++)
    {
        EntityGarbage::Instance().Add(item_slot_vec[i]);
    }
}

void Angar::AddVehicleSlot(VehicleSlot* vehicle_slot) 
{ 
    vehicle_slot->SetOwner(this);

    if (vehicle_slot->subTypeId() == TYPE::ENTITY::VEHICLE_MILITARY_SLOT_ID)
    {
        vehicle_military_slot_vec.push_back(vehicle_slot);
    }

    if (vehicle_slot->subTypeId() == TYPE::ENTITY::VEHICLE_VISITORS_SLOT_ID)
    {
        vehicle_visitors_slot_vec.push_back(vehicle_slot);
    }

    vehicle_total_slot_vec.push_back(vehicle_slot);
};


void Angar::AddItemSlot(ItemSlot* item_slot)
{
    item_slot->SetOwner(this);
    item_slot_vec.push_back(item_slot);
}

bool Angar::RepairItem(Npc* npc, BaseItem* item) const
{
    int price = item->GetPrice() * REPAIR_ITEM_PRICE_RATE;
    if (npc->WithdrawCredits(price) == true)
    {
        return item->RepairEvent();
    }

    return false;
}         

bool Angar::ChargeRocketEquipment(Npc* npc, RocketEquipment* rocket_equipment) const
{
    int price_for_one = rocket_equipment->GetPrice() * AMMO_PRICE_RATE;
    int ammo_max = npc->GetCredits() / price_for_one;
    int ammo_need = rocket_equipment->GetAmmoMax() - rocket_equipment->GetAmmo();

    int ammo_amount = 0;
    if (ammo_max > ammo_need) { ammo_amount = ammo_need; }
    else                      { ammo_amount = ammo_max; }
    
    if (npc->WithdrawCredits(ammo_amount*price_for_one) == true)
    {
        rocket_equipment->SetAmmo(rocket_equipment->GetAmmo() + ammo_amount);
        return true;
    }

    return false;
}

bool Angar::RepairVehicle(Vehicle* vehicle) const
{        
    int price_for_one = vehicle->GetDataKorpus().price * REPAIR_VEHICLEKORPUS_PRICE_RATE;
    int repair_max =  vehicle->GetOwnerNpc()->GetCredits() / price_for_one;
    int repair_need = vehicle->GetDataKorpus().armor - vehicle->armor();
    
    int repair_amount = 0;
    if (repair_max > repair_need) { repair_amount = repair_need; }
    else                          { repair_amount = repair_max; }
    
    if (vehicle->GetOwnerNpc()->WithdrawCredits(repair_amount*price_for_one) == true) {
        vehicle->RepairKorpusOnAmount(repair_amount);
        return true;
    }
    
    return false;
}

bool Angar::TankUpVehicle(Vehicle* vehicle) const
{
    int fuel_to_buy_max =  vehicle->GetOwnerNpc()->GetCredits() / price_fuel;
    int fuel_to_buy_need = vehicle->GetFuelMiss();
    
    int fuel = 0;
    if (fuel_to_buy_max > fuel_to_buy_need) { fuel = fuel_to_buy_need; }
    else                                    { fuel = fuel_to_buy_max; }

    if (vehicle->GetOwnerNpc()->WithdrawCredits(fuel*price_fuel) == true) {
        vehicle->GetComplexDrive().GetBakSlot()->GetBakEquipment()->IncreaseFuel(fuel);
        return true;
    }

    return false;
}

void Angar::UpdateInStatic() const
{
    for (unsigned int i=0; i<vehicle_visitors_slot_vec.size(); i++) {
        if (vehicle_visitors_slot_vec[i]->GetVehicle() != nullptr)  {
            if (vehicle_visitors_slot_vec[i]->GetVehicle()->GetOwnerNpc() != nullptr) {
                vehicle_visitors_slot_vec[i]->GetVehicle()->GetOwnerNpc()->UpdateInKosmoportInStatic();
            }
        }
    }
}

int Angar::GetFreeVehicleSlotTotalNum() const
{
    int sum_free = 0;
    for (unsigned int i=0; i<vehicle_visitors_slot_vec.size(); i++) {
        if (vehicle_visitors_slot_vec[i]->GetVehicle() == nullptr) {
            sum_free++;
        }
    }
    return sum_free;
}

bool Angar::AddVehicle(Vehicle* vehicle)
{
    if (vehicle->subSubTypeId() == TYPE::ENTITY::WARRIOR_ID) {
        for (unsigned int i=0; i<vehicle_military_slot_vec.size(); i++) {
            if (vehicle_military_slot_vec[i]->GetVehicle() == nullptr) {
                vehicle_military_slot_vec[i]->InsertVehicle(vehicle);
                return true;
            }
        }
    } else {
        for (unsigned int i=0; i<vehicle_visitors_slot_vec.size(); i++) {
            if (vehicle_visitors_slot_vec[i]->GetVehicle() == nullptr) {
                vehicle_visitors_slot_vec[i]->InsertVehicle(vehicle);
                return true;
            }
        }
    }

    return false;
}

std::string Angar::GetDockVehicleStr() const
{
    std::string str;
    for (unsigned int i=0; i<vehicle_military_slot_vec.size(); i++) {
        if (vehicle_military_slot_vec[i]->GetVehicle() != nullptr) {
            str += "_m" + std::to_string(vehicle_military_slot_vec[i]->GetVehicle()->id());
        }
    }
    for (unsigned int i=0; i<vehicle_visitors_slot_vec.size(); i++) {
        if (vehicle_visitors_slot_vec[i]->GetVehicle() != nullptr) {
            str += "_v" + std::to_string(vehicle_visitors_slot_vec[i]->GetVehicle()->id());
        }
    }
    return str;
}


void Angar::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{}

void Angar::LoadData(const boost::property_tree::ptree& load_ptree)
{}

void Angar::ResolveData()
{
    ((Kosmoport*)EntityManager::Instance().GetEntityById(data_unresolved_Room.owner_kosmoport_id))->BindAngar(this);
}


void Angar::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "angar." + std::to_string(id())+".";

    Base::SaveData(save_ptree, root);
    Room::SaveData(save_ptree, root);
    Angar::SaveData(save_ptree, root);
}

void Angar::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Room::LoadData(load_ptree);
    Angar::LoadData(load_ptree);
}

void Angar::Resolve()
{
    Base::ResolveData();
    Room::ResolveData();
    Angar::ResolveData();
}

