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


#include "VehicleDescriptorGenerator.hpp"

#include <types/RaceTypes.hpp>
#include <types/EntityTypes.hpp>

#include <descriptors/RaceDescriptors.hpp>
#include <meti/RandUtils.hpp>

#include <common/Global.hpp>
#include <common/IdGenerator.hpp>


//VehicleDescriptor generateVehicleDescriptor()
//{
//    TYPE::RACE race_id = meti::getRand(global::get().raceDescriptors().getRaces(TYPE::KIND::GOOD));
//    type::entity type_id = type::entity::WARRIOR_ID;
//    int size_id = meti::getRandInt(1, 9);
//    int weapons_num = size_id;

//    float protection_rate = 1;
//    float otsec_rate      = 1;
//    switch (type_id) {
//        case type::entity::WARRIOR_ID: { protection_rate = 2; break; }
//        case type::entity::TRADER_ID:  { otsec_rate = 1.5; break; }
//    }

//    VehicleDescriptor descriptor;
//    descriptor.id = global::get().idGenerator().nextId();
//    descriptor.race_id = race_id;
//    descriptor.type_id = type_id;
//    descriptor.size_id = size_id;

//    descriptor.space       = size_id*100 + meti::getRandInt(100);
//    descriptor.armor       = descriptor.space;
//    descriptor.protection  = protection_rate*meti::getRandInt(size_id);
//    descriptor.temperature = 100;
//    descriptor.price       = meti::getRandInt(200, 400)*size_id;

//    descriptor.slot_bak_num       = 1;
//    descriptor.slot_drive_num     = 1;
//    descriptor.slot_droid_num     = 1;
//    descriptor.slot_energizer_num = 1;
//    descriptor.slot_grapple_num   = 1;
//    descriptor.slot_protector_num = 1;
//    descriptor.slot_radar_num     = 1;
//    descriptor.slot_scaner_num    = 1;
//    descriptor.slot_freezer_num   = 1;
//    descriptor.slot_weapon_num   = weapons_num;
//    descriptor.slot_artefact_num = meti::getRandInt(1, SLOT_ARTEFACT_TYPES.size());
//    descriptor.slot_otsec_num    = meti::getRandInt(SLOT_CARGO_TYPES.size()/2, SLOT_CARGO_TYPES.size()) * otsec_rate;

//    //int size_threshold = 2;
//    descriptor.draw_turrels = false;

//    return descriptor;
//}
