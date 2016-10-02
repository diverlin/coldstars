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

#include <string>

#include <ceti/type/IdType.hpp>
#include <types/RaceTypes.hpp>
#include <types/EntityTypes.hpp>

class VehicleDescriptor
{
public:
    int_t id = 0;
    type::race race_id = type::race::R0_ID;
    type::entity type_id = type::entity::WARRIOR_ID;
    int size_id = 0;

    int space = 0;
    int armor = 0;
    int protection = 0;
    int temperature = 0;
    int price = 0;

    bool draw_turrels = false;

    int slot_bak_num = 0;
    int slot_drive_num = 0;
    int slot_droid_num = 0;
    int slot_energizer_num = 0;
    int slot_grapple_num = 0;
    int slot_protector_num = 0;
    int slot_radar_num = 0;
    int slot_scaner_num = 0;
    int slot_freezer_num = 0;
    int slot_weapon_num = 0;
    int slot_artefact_num = 0;
    int slot_otsec_num = 0;

    VehicleDescriptor() {}
    ~VehicleDescriptor() {}
};

