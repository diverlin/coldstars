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

#include <core/spaceobjects/SpaceObject.hpp>

#include <core/parts/WeaponComplex.hpp>
#include <core/parts/DriveComplex.hpp>
#include <core/parts/ProtectionComplex.hpp>

#include <core/descriptor/VehicleDescriptor.hpp>
#include <core/struct/VehiclePropetries.hpp>
#include <core/struct/VehicleNeeds.hpp>

#include <core/types/StatusTypes.hpp>

class VehicleSlot;
class Land; 
class GoodsPack;

namespace model {
class Container;
class Starsystem;
class Item;
} // namespace model

namespace control {
class Container;
class Npc;
class Item;
} //namespace control

class Equipment;
class BaseParticleSystem;
class ShockWaveEffect;

//struct UnresolvedDataVehicle
//{
//    int drive_complex_target_id;
//    int drive_complex_action_id;

//    int starsystem_hyper_id;
//    int parent_vehicleslot_id;
//    int land_id;
//};

namespace model {

class Vehicle : public SpaceObject {
public:
    Vehicle()=default;
    ~Vehicle() = default;

    int_t npc() const { return m_npc; }
    int_t dock() const { return m_dock; }
    [[warning("do we need this? using dock will be sufficient probably")]]
    int_t land() const { return m_land; }

    std::vector<int_t> items() const { return m_items; }

//    int_t radarSlot() const { return m_radar_slot; }
//    int_t scanerSlot() const { return m_scaner_slot; }

//#ifdef USE_EXTRA_EQUIPMENT
//    int_t energizerSlot() const { return m_energizer_slot; }
//    int_t freezerSlot() const { return m_freezer_slot; }
//#endif // USE_EXTRA_EQUIPMENT
//    int_t grappleSlot() const { return m_grapple_slot; }
//    int_t droidSlot() const { return m_droid_slot; }

    VehiclePropetries& properties() { return m_properties; }
    VehicleNeeds& needs() { return m_needs; }

    [[warning("move out to control::")]]
    int_t descriptor() { return m_descriptor; }

private:
    int_t m_npc = NONE;
    int_t m_dock = NONE;
    int_t m_land = NONE;

    std::vector<int_t> m_items;

//    int_t m_radar_slot = NONE;
//    int_t m_scaner_slot = NONE;
//#ifdef USE_EXTRA_EQUIPMENT
//    int_t m_energizer_slot = NONE;
//    int_t m_freezer_slot = NONE;
//#endif // USE_EXTRA_EQUIPMENT
//    int_t m_grapple_slot = NONE;
//    int_t m_droid_slot = NONE;

//    std::vector<int_t> m_equipment_slots;
//    std::vector<int_t> m_artefact_slots;
//    std::vector<int_t> m_cargo_slots;

    VehiclePropetries m_properties;
    VehicleNeeds m_needs;
    int_t m_descriptor;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SpaceObject>(*this);
        ar & m_npc;
        ar & m_dock;
        ar & m_land;
        ar & m_items;
//        ar & m_properties;
//        ar & m_needs;
        ar & m_descriptor;
    }
};

} // namespace model

