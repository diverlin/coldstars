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

#include "TextureType.hpp"

#include <cassert>

namespace texture {

std::string str(Type type_id)
{
    switch(type_id)
    {
        case Type::FAILBACK: return "texture::Type::FAILBACK";

        case Type::ANGAR_BACKGROUND: return "texture::Type::ANGAR_BACKGROUND";
        case Type::STORE_BACKGROUND: return "texture::Type::STORE_BACKGROUND";
        case Type::SHOP_BACKGROUND: return "texture::Type::SHOP_BACKGROUND";
        case Type::GOVERMENT_BACKGROUND: return "texture::Type::GOVERMENT_BACKGROUND";

        case Type::NATURELAND_BACKGROUND: return "texture::Type::NATURELAND_BACKGROUND";

        case Type::NEBULA_BACKGROUND: return "texture::Type::NEBULA_BACKGROUND";
        case Type::DISTANTSTAR: return "texture::Type::DISTANTSTAR";

        case Type::FACE: return "texture::Type::FACE";

        case Type::VEHICLE_SLOT: return "texture::Type::VEHICLE_SLOT";
        case Type::ITEM_SLOT: return "texture::Type::ITEM_SLOT";
        case Type::TURREL: return "texture::Type::TURREL";

        case Type::SPACESTATION: return "texture::Type::SPACESTATION";
        case Type::SATELLITE: return "texture::Type::SATELLITE";
        case Type::SHIP: return "texture::Type::SHIP";
        case Type::STAR: return "texture::Type::STAR";
        case Type::PLANET: return "texture::Type::PLANET";

        case Type::ATMOSPHERE: return "texture::Type::ATMOSPHERE";
        case Type::RING: return "texture::Type::RING";

        case Type::ASTEROID: return "texture::Type::ASTEROID";
        case Type::MINERAL: return "texture::Type::MINERAL";
        case Type::CONTAINER: return "texture::Type::CONTAINER";
        case Type::BOMB: return "texture::Type::BOMB";
        case Type::BLACKHOLE: return "texture::Type::BLACKHOLE";

        case Type::PARTICLE_EFFECT: return "texture::Type::PARTICLE_EFFECT";
        case Type::LAZER_EFFECT: return "texture::Type::LAZER_EFFECT";
        case Type::SHIELD_EFFECT: return "texture::Type::SHIELD_EFFECT";

        case Type::DRIVE_EQUIPMENT: return "texture::Type::DRIVE_EQUIPMENT";
        case Type::LAZER_EQUIPMENT: return "texture::Type::LAZER_EQUIPMENT";
        case Type::ROCKET_EQUIPMENT: return "texture::Type::ROCKET_EQUIPMENT";
        case Type::PROTECTOR_EQUIPMENT: return "texture::Type::PROTECTOR_EQUIPMENT";
        case Type::DROID_EQUIPMENT: return "texture::Type::DROID_EQUIPMENT";
        case Type::GRAPPLE_EQUIPMENT: return "texture::Type::GRAPPLE_EQUIPMENT";
        case Type::BAK_EQUIPMENT: return "texture::Type::BAK_EQUIPMENT";
        case Type::ENERGIZER_EQUIPMENT: return "texture::Type::ENERGIZER_EQUIPMENT";
        case Type::FREEZER_EQUIPMENT: return "texture::Type::FREEZER_EQUIPMENT";
        case Type::RADAR_EQUIPMENT: return "texture::Type::RADAR_EQUIPMENT";
        case Type::SCANER_EQUIPMENT: return "texture::Type::SCANER_EQUIPMENT";

        case Type::MODULE: return "texture::Type::MODULE";

        case Type::ROCKET_BULLET: return "texture::Type::ROCKET_BULLET";
    }
    assert(false);
}

} // namespace type
