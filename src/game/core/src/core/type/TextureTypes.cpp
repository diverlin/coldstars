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

#include "TextureTypes.hpp"

#include <cassert>

namespace texture {

std::string str(texture::type type_id)
{
    switch(type_id)
    {
        case texture::type::FAILBACK: return "TYPE::TEXTURE::FAILBACK";

        case texture::type::ANGAR_BACKGROUND: return "TYPE::TEXTURE::ANGAR_BACKGROUND";
        case texture::type::STORE_BACKGROUND: return "TYPE::TEXTURE::STORE_BACKGROUND";
        case texture::type::SHOP_BACKGROUND: return "TYPE::TEXTURE::SHOP_BACKGROUND";
        case texture::type::GOVERMENT_BACKGROUND: return "TYPE::TEXTURE::GOVERMENT_BACKGROUND";

        case texture::type::NATURELAND_BACKGROUND: return "TYPE::TEXTURE::NATURELAND_BACKGROUND";

        case texture::type::NEBULA_BACKGROUND: return "TYPE::TEXTURE::NEBULA_BACKGROUND";
        case texture::type::DISTANTSTAR: return "TYPE::TEXTURE::DISTANTSTAR";

        case texture::type::FACE: return "TYPE::TEXTURE::FACE";

        case texture::type::VEHICLE_SLOT: return "TYPE::TEXTURE::VEHICLE_SLOT";
        case texture::type::ITEM_SLOT: return "TYPE::TEXTURE::ITEM_SLOT";
        case texture::type::TURREL: return "TYPE::TEXTURE::TURREL";

        case texture::type::SPACESTATION: return "TYPE::TEXTURE::SPACESTATION";
        case texture::type::SATELLITE: return "TYPE::TEXTURE::SATELLITE";
        case texture::type::SHIP: return "TYPE::TEXTURE::SHIP";
        case texture::type::STAR: return "TYPE::TEXTURE::STAR";
        case texture::type::PLANET: return "TYPE::TEXTURE::PLANET";

        case texture::type::ATMOSPHERE: return "TYPE::TEXTURE::ATMOSPHERE";
        case texture::type::RING: return "TYPE::TEXTURE::RING";

        case texture::type::ASTEROID: return "TYPE::TEXTURE::ASTEROID";
        case texture::type::MINERAL: return "TYPE::TEXTURE::MINERAL";
        case texture::type::CONTAINER: return "TYPE::TEXTURE::CONTAINER";
        case texture::type::BOMB: return "TYPE::TEXTURE::BOMB";
        case texture::type::BLACKHOLE: return "TYPE::TEXTURE::BLACKHOLE";

        case texture::type::PARTICLE_EFFECT: return "TYPE::TEXTURE::PARTICLE_EFFECT";
        case texture::type::LAZER_EFFECT: return "TYPE::TEXTURE::LAZER_EFFECT";
        case texture::type::SHIELD_EFFECT: return "TYPE::TEXTURE::SHIELD_EFFECT";

        case texture::type::DRIVE_EQUIPMENT: return "TYPE::TEXTURE::DRIVE_EQUIPMENT";
        case texture::type::LAZER_EQUIPMENT: return "TYPE::TEXTURE::LAZER_EQUIPMENT";
        case texture::type::ROCKET_EQUIPMENT: return "TYPE::TEXTURE::ROCKET_EQUIPMENT";
        case texture::type::PROTECTOR_EQUIPMENT: return "TYPE::TEXTURE::PROTECTOR_EQUIPMENT";
        case texture::type::DROID_EQUIPMENT: return "TYPE::TEXTURE::DROID_EQUIPMENT";
        case texture::type::GRAPPLE_EQUIPMENT: return "TYPE::TEXTURE::GRAPPLE_EQUIPMENT";
        case texture::type::BAK_EQUIPMENT: return "TYPE::TEXTURE::BAK_EQUIPMENT";
        case texture::type::ENERGIZER_EQUIPMENT: return "TYPE::TEXTURE::ENERGIZER_EQUIPMENT";
        case texture::type::FREEZER_EQUIPMENT: return "TYPE::TEXTURE::FREEZER_EQUIPMENT";
        case texture::type::RADAR_EQUIPMENT: return "TYPE::TEXTURE::RADAR_EQUIPMENT";
        case texture::type::SCANER_EQUIPMENT: return "TYPE::TEXTURE::SCANER_EQUIPMENT";

        case texture::type::MODULE: return "TYPE::TEXTURE::MODULE";

        case texture::type::ROCKET_BULLET: return "TYPE::TEXTURE::ROCKET_BULLET";
    }
    assert(false);
}

} // namespace type
