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

#include <common/constants.hpp>

/* this data is changed during game play, the propetries depends on many factors */
struct VehiclePropetries
{
    int free_space = 0;

    int protection = 0;
    int radar = VISIBLE_DISTANCE_WITHOUT_RADAR;
    float speed = 0;  // depends on mass and drive

    int energy = 0;
    int hyper = 0;  // depends on drive and bak
    //int fuel = 0;   // depends on bak
    int repair = 0; // depends on droid
    int freeze = 0; // depends on freezer
    int scan = 0;   // depends on scaner

    int grab_strength = 0;
    int grab_radius = 0;

    int temperature = 0;

    int artefact_gravity = 0;
    int artefact_protection = 0;

    // simplification
    int total_damage = 0;
    int fire_radius_min = 0;
    int fire_radius_max = 0;

    bool equipment_radar = 0;
    [[deprecated("deprecated")]]
    bool shield_effect_enabled = 0;
    bool hibernate_mode_enabled = 0;

    VehiclePropetries()=default;
    ~VehiclePropetries()=default;
};

