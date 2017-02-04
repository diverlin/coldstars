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

#include <ceti/type/IdType.hpp>

#include <string>

namespace type
{
enum class texture: int
{
    FAILBACK=0,

    ANGAR_BACKGROUND_ID, STORE_BACKGROUND_ID, SHOP_BACKGROUND_ID, GOVERMENT_BACKGROUND_ID,
    NATURELAND_BACKGROUND_ID,
    NEBULA_BACKGROUND_ID, DISTANTSTAR_ID,
    FACE_ID,

    VEHICLE_SLOT_ID, ITEM_SLOT_ID, TURREL_ID,
    
    SPACESTATION_ID, SATELLITE_ID, SHIP_ID, STAR_ID, PLANET_ID,

    ATMOSPHERE_ID,
    RING_ID,

    ASTEROID_ID, MINERAL_ID, CONTAINER_ID, BOMB_ID, BLACKHOLE_ID,
    
    PARTICLE_EFFECT_ID, LAZER_EFFECT_ID, SHIELD_EFFECT_ID,

    
    DRIVE_EQUIPMENT_ID, LAZER_EQUIPMENT_ID, ROCKET_EQUIPMENT_ID, PROTECTOR_EQUIPMENT_ID, DROID_EQUIPMENT_ID, GRAPPLE_EQUIPMENT_ID,
    BAK_EQUIPMENT_ID, ENERGIZER_EQUIPMENT_ID, FREEZER_EQUIPMENT_ID, RADAR_EQUIPMENT_ID, SCANER_EQUIPMENT_ID,
    
    MODULE_ID,
    
    ROCKET_BULLET_ID,

    LAST_ID
};

} // namespace type



std::string to_string(type::texture);

