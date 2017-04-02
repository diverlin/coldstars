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

namespace slot {
class Vehicle;
class Item;
} // namespace slot

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

    void add(slot::Vehicle*);
    void add(slot::Item*);

    void updateInStatic() const;

    bool add(Vehicle*);

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

private:
    std::vector<slot::Vehicle*> m_vehicle_slots;
    std::vector<slot::Item*> m_item_slots;

    int m_fuelPrice;

    descriptor::Angar* m_descriptor_angar = nullptr;
    model::Angar* m_model_angar = nullptr;

    descriptor::Angar* desriptor() const { return m_descriptor_angar; }
    model::Angar* model() const { return m_model_angar; }

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();

//    friend class GuiAngar;
};

} // namespace control
