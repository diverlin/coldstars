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

#pragma once

#include "Room.hpp"

namespace descriptor {
class Angar;
} // namespace descriptor

namespace model {
class Angar;
} // namespace model

namespace core {

namespace slot {
class VehicleSlot;
} // namespace slot

class ItemSlot;

namespace control {

namespace item {
class Rocket;
} // namespace item

class Vehicle;
class Item;
class Npc;

class Angar : public Room
{
public:
    Angar(descriptor::Angar*, model::Angar*);
    ~Angar();

    virtual void putChildrenToGarbage() const;

    void add(core::slot::VehicleSlot*);
    void add(ItemSlot*);

    void updateInStatic() const;

    bool add(Vehicle*);
    bool remove(Vehicle*);
    int shipsNum() const;

    bool repairItem(Npc*, Item*) const;
    bool chargeRocketEquipment(Npc*, item::Rocket*) const;

    bool repairVehicle(Vehicle*) const;
    bool tankUpVehicle(Vehicle*) const;

    int freeVehicleSlotTotalNum() const;

    int fuelPrice() const { return m_fuelPrice; }

    std::string vehiclesStr() const;

//    void Save(boost::property_tree::ptree&) const;
//    void Load(const boost::property_tree::ptree&);
//    void Resolve();

    descriptor::Angar* desriptor() const { return m_descriptor_angar; }
    model::Angar* model() const { return m_model_angar; }

    const std::vector<core::slot::VehicleSlot*>& vehicleSlots() const { return m_vehicle_slots; }
    const std::vector<ItemSlot*>& itemSlots() const { return m_item_slots; }

private:
    descriptor::Angar* m_descriptor_angar = nullptr;
    model::Angar* m_model_angar = nullptr;

    std::vector<core::slot::VehicleSlot*> m_vehicle_slots;
    std::vector<ItemSlot*> m_item_slots;

    int m_fuelPrice = 0;

    core::slot::VehicleSlot* __freeSlot() const;
    core::slot::VehicleSlot* __slot(Vehicle*) const;

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
};

} // namespace control
} // namespace core
