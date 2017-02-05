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

        case texture::type::ANGAR_BACKGROUND_ID: return "TYPE::TEXTURE::ANGAR_BACKGROUND_ID";
        case texture::type::STORE_BACKGROUND_ID: return "TYPE::TEXTURE::STORE_BACKGROUND_ID";
        case texture::type::SHOP_BACKGROUND_ID: return "TYPE::TEXTURE::SHOP_BACKGROUND_ID";
        case texture::type::GOVERMENT_BACKGROUND_ID: return "TYPE::TEXTURE::GOVERMENT_BACKGROUND_ID";

        case texture::type::NATURELAND_BACKGROUND_ID: return "TYPE::TEXTURE::NATURELAND_BACKGROUND_ID";

        case texture::type::NEBULA_BACKGROUND_ID: return "TYPE::TEXTURE::NEBULA_BACKGROUND_ID";
        case texture::type::DISTANTSTAR_ID: return "TYPE::TEXTURE::DISTANTSTAR_ID";

        case texture::type::FACE_ID: return "TYPE::TEXTURE::FACE_ID";

        case texture::type::VEHICLE_SLOT_ID: return "TYPE::TEXTURE::VEHICLE_SLOT_ID";
        case texture::type::ITEM_SLOT_ID: return "TYPE::TEXTURE::ITEM_SLOT_ID";
        case texture::type::TURREL_ID: return "TYPE::TEXTURE::TURREL_ID";

        case texture::type::SPACESTATION_ID: return "TYPE::TEXTURE::SPACESTATION_ID";
        case texture::type::SATELLITE_ID: return "TYPE::TEXTURE::SATELLITE_ID";
        case texture::type::SHIP_ID: return "TYPE::TEXTURE::SHIP_ID";
        case texture::type::STAR_ID: return "TYPE::TEXTURE::STAR_ID";
        case texture::type::PLANET_ID: return "TYPE::TEXTURE::PLANET_ID";

        case texture::type::ATMOSPHERE_ID: return "TYPE::TEXTURE::ATMOSPHERE_ID";
        case texture::type::RING_ID: return "TYPE::TEXTURE::RING_ID";

        case texture::type::ASTEROID_ID: return "TYPE::TEXTURE::ASTEROID_ID";
        case texture::type::MINERAL_ID: return "TYPE::TEXTURE::MINERAL_ID";
        case texture::type::CONTAINER_ID: return "TYPE::TEXTURE::CONTAINER_ID";
        case texture::type::BOMB_ID: return "TYPE::TEXTURE::BOMB_ID";
        case texture::type::BLACKHOLE_ID: return "TYPE::TEXTURE::BLACKHOLE_ID";

        case texture::type::PARTICLE_EFFECT_ID: return "TYPE::TEXTURE::PARTICLE_EFFECT_ID";
        case texture::type::LAZER_EFFECT_ID: return "TYPE::TEXTURE::LAZER_EFFECT_ID";
        case texture::type::SHIELD_EFFECT_ID: return "TYPE::TEXTURE::SHIELD_EFFECT_ID";

        case texture::type::DRIVE_EQUIPMENT_ID: return "TYPE::TEXTURE::DRIVE_EQUIPMENT_ID";
        case texture::type::LAZER_EQUIPMENT_ID: return "TYPE::TEXTURE::LAZER_EQUIPMENT_ID";
        case texture::type::ROCKET_EQUIPMENT_ID: return "TYPE::TEXTURE::ROCKET_EQUIPMENT_ID";
        case texture::type::PROTECTOR_EQUIPMENT_ID: return "TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID";
        case texture::type::DROID_EQUIPMENT_ID: return "TYPE::TEXTURE::DROID_EQUIPMENT_ID";
        case texture::type::GRAPPLE_EQUIPMENT_ID: return "TYPE::TEXTURE::GRAPPLE_EQUIPMENT_ID";
        case texture::type::BAK_EQUIPMENT_ID: return "TYPE::TEXTURE::BAK_EQUIPMENT_ID";
        case texture::type::ENERGIZER_EQUIPMENT_ID: return "TYPE::TEXTURE::ENERGIZER_EQUIPMENT_ID";
        case texture::type::FREEZER_EQUIPMENT_ID: return "TYPE::TEXTURE::FREEZER_EQUIPMENT_ID";
        case texture::type::RADAR_EQUIPMENT_ID: return "TYPE::TEXTURE::RADAR_EQUIPMENT_ID";
        case texture::type::SCANER_EQUIPMENT_ID: return "TYPE::TEXTURE::SCANER_EQUIPMENT_ID";

        case texture::type::MODULE_ID: return "TYPE::TEXTURE::MODULE_ID";

        case texture::type::ROCKET_BULLET_ID: return "TYPE::TEXTURE::ROCKET_BULLET_ID";
    }
    assert(false);
}

} // namespace type
