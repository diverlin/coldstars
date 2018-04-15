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

namespace core {
class StoreDescr;
} // namespace core

namespace model {
class Store;
} // namespace model

namespace core {

class ItemSlot;
class VehicleSlot;

namespace control {

class Vehicle;
class Item;
class Npc;

class Store : public Room
{
public:
    Store(StoreDescr*, model::Store*);
    ~Store();

    virtual void putChildrenToGarbage() const;

    bool add(Item*);
    bool add(Vehicle*);

    ItemSlot* freeItemSlot() const;
    VehicleSlot* freeVehicleSlot() const;

    int buyItem(Item*);
    void sellVehicle(Npc*, VehicleSlot*, int);

    [[deprecated("tmp")]]
    const std::vector<ItemSlot*>& itemSlots() const { return m_item_slots; }
    [[deprecated("tmp")]]
    const std::vector<VehicleSlot*>& vehicleSlots() const { return m_vehicle_slots; }

//    void Save(boost::property_tree::ptree&) const;
//    void Load(const boost::property_tree::ptree&);
//    void Resolve();

private:
    std::vector<ItemSlot*> m_item_slots;
    std::vector<VehicleSlot*> m_vehicle_slots;

    StoreDescr* m_descriptor_store = nullptr;
    model::Store* m_model_store = nullptr;

    StoreDescr* descriptor() const { return m_descriptor_store; }
    model::Store* model() const { return m_model_store; }

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();
    void __add(VehicleSlot*);
    void __add(ItemSlot*);
};

} // namespace control
} // namespace core


