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

namespace type {

std::string str(type::texture type_id)
{
    switch(type_id)
    {
        case type::texture::FAILBACK: return "TYPE::TEXTURE::FAILBACK";

        case type::texture::ANGAR_BACKGROUND_ID: return "TYPE::TEXTURE::ANGAR_BACKGROUND_ID";
        case type::texture::STORE_BACKGROUND_ID: return "TYPE::TEXTURE::STORE_BACKGROUND_ID";
        case type::texture::SHOP_BACKGROUND_ID: return "TYPE::TEXTURE::SHOP_BACKGROUND_ID";
        case type::texture::GOVERMENT_BACKGROUND_ID: return "TYPE::TEXTURE::GOVERMENT_BACKGROUND_ID";

        case type::texture::NATURELAND_BACKGROUND_ID: return "TYPE::TEXTURE::NATURELAND_BACKGROUND_ID";

        case type::texture::NEBULA_BACKGROUND_ID: return "TYPE::TEXTURE::NEBULA_BACKGROUND_ID";
        case type::texture::DISTANTSTAR_ID: return "TYPE::TEXTURE::DISTANTSTAR_ID";

        case type::texture::FACE_ID: return "TYPE::TEXTURE::FACE_ID";

        case type::texture::VEHICLE_SLOT_ID: return "TYPE::TEXTURE::VEHICLE_SLOT_ID";
        case type::texture::ITEM_SLOT_ID: return "TYPE::TEXTURE::ITEM_SLOT_ID";
        case type::texture::TURREL_ID: return "TYPE::TEXTURE::TURREL_ID";

        case type::texture::SPACESTATION_ID: return "TYPE::TEXTURE::SPACESTATION_ID";
        case type::texture::SATELLITE_ID: return "TYPE::TEXTURE::SATELLITE_ID";
        case type::texture::SHIP_ID: return "TYPE::TEXTURE::SHIP_ID";
        case type::texture::STAR_ID: return "TYPE::TEXTURE::STAR_ID";
        case type::texture::PLANET_ID: return "TYPE::TEXTURE::PLANET_ID";

        case type::texture::ATMOSPHERE_ID: return "TYPE::TEXTURE::ATMOSPHERE_ID";
        case type::texture::RING_ID: return "TYPE::TEXTURE::RING_ID";

        case type::texture::ASTEROID_ID: return "TYPE::TEXTURE::ASTEROID_ID";
        case type::texture::MINERAL_ID: return "TYPE::TEXTURE::MINERAL_ID";
        case type::texture::CONTAINER_ID: return "TYPE::TEXTURE::CONTAINER_ID";
        case type::texture::BOMB_ID: return "TYPE::TEXTURE::BOMB_ID";
        case type::texture::BLACKHOLE_ID: return "TYPE::TEXTURE::BLACKHOLE_ID";

        case type::texture::PARTICLE_EFFECT_ID: return "TYPE::TEXTURE::PARTICLE_EFFECT_ID";
        case type::texture::LAZER_EFFECT_ID: return "TYPE::TEXTURE::LAZER_EFFECT_ID";
        case type::texture::SHIELD_EFFECT_ID: return "TYPE::TEXTURE::SHIELD_EFFECT_ID";

        case type::texture::DRIVE_EQUIPMENT_ID: return "TYPE::TEXTURE::DRIVE_EQUIPMENT_ID";
        case type::texture::LAZER_EQUIPMENT_ID: return "TYPE::TEXTURE::LAZER_EQUIPMENT_ID";
        case type::texture::ROCKET_EQUIPMENT_ID: return "TYPE::TEXTURE::ROCKET_EQUIPMENT_ID";
        case type::texture::PROTECTOR_EQUIPMENT_ID: return "TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID";
        case type::texture::DROID_EQUIPMENT_ID: return "TYPE::TEXTURE::DROID_EQUIPMENT_ID";
        case type::texture::GRAPPLE_EQUIPMENT_ID: return "TYPE::TEXTURE::GRAPPLE_EQUIPMENT_ID";
        case type::texture::BAK_EQUIPMENT_ID: return "TYPE::TEXTURE::BAK_EQUIPMENT_ID";
        case type::texture::ENERGIZER_EQUIPMENT_ID: return "TYPE::TEXTURE::ENERGIZER_EQUIPMENT_ID";
        case type::texture::FREEZER_EQUIPMENT_ID: return "TYPE::TEXTURE::FREEZER_EQUIPMENT_ID";
        case type::texture::RADAR_EQUIPMENT_ID: return "TYPE::TEXTURE::RADAR_EQUIPMENT_ID";
        case type::texture::SCANER_EQUIPMENT_ID: return "TYPE::TEXTURE::SCANER_EQUIPMENT_ID";

        case type::texture::MODULE_ID: return "TYPE::TEXTURE::MODULE_ID";

        case type::texture::ROCKET_BULLET_ID: return "TYPE::TEXTURE::ROCKET_BULLET_ID";
    }
    assert(false);
}

} // namespace type
