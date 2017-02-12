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

namespace texture
{
enum class type: int
{
    FAILBACK=0,

    ANGAR_BACKGROUND, STORE_BACKGROUND, SHOP_BACKGROUND, GOVERMENT_BACKGROUND,
    NATURELAND_BACKGROUND,
    NEBULA_BACKGROUND, DISTANTSTAR,
    FACE,

    VEHICLE_SLOT, ITEM_SLOT, TURREL,
    
    SPACESTATION, SATELLITE, SHIP, STAR, PLANET,

    ATMOSPHERE,
    RING,

    ASTEROID, MINERAL, CONTAINER, BOMB, BLACKHOLE,
    
    PARTICLE_EFFECT, LAZER_EFFECT, SHIELD_EFFECT,

    
    DRIVE_EQUIPMENT, LAZER_EQUIPMENT, ROCKET_EQUIPMENT, PROTECTOR_EQUIPMENT, DROID_EQUIPMENT, GRAPPLE_EQUIPMENT,
    BAK_EQUIPMENT, ENERGIZER_EQUIPMENT, FREEZER_EQUIPMENT, RADAR_EQUIPMENT, SCANER_EQUIPMENT,
    
    MODULE,
    
    ROCKET_BULLET,

    LAST
};

} // namespace texture



std::string to_string(texture::type);

