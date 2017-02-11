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

namespace control {
class ItemSlot;
class VehicleSlot;
class Vehicle;
namespace item {
class Item;
} // namespace item
}

class Npc;

class Store : public Room
{
public:
    Store(int);
    ~Store();

    virtual void putChildrenToGarbage() const;

    void addVehicleSlot(control::VehicleSlot*);
    void addItemSlot(control::ItemSlot*);
    bool addItem(control::item::Item*);
    bool addVehicle(control::Vehicle*);

    control::ItemSlot* freeItemSlot() const;
    control::VehicleSlot* freeVehicleSlot() const;

    int buyItem(control::item::Item*);
    void sellVehicle(Npc*, control::VehicleSlot*, int);

    void Save(boost::property_tree::ptree&) const;
    void Load(const boost::property_tree::ptree&);
    void Resolve();

private:
    std::vector<control::ItemSlot*> m_itemslots;
    std::vector<control::VehicleSlot*> m_vehicleslots;

    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();

    friend class GuiStore;
};





