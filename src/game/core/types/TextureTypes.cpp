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


std::string str(type::TEXTURE type_id)
{
    switch(type_id)
    {
        case type::TEXTURE::NONE_ID: return "TYPE::TEXTURE::NONE_ID";

        case type::TEXTURE::ANGAR_BACKGROUND_ID: return "TYPE::TEXTURE::ANGAR_BACKGROUND_ID";
        case type::TEXTURE::STORE_BACKGROUND_ID: return "TYPE::TEXTURE::STORE_BACKGROUND_ID";
        case type::TEXTURE::SHOP_BACKGROUND_ID: return "TYPE::TEXTURE::SHOP_BACKGROUND_ID";
        case type::TEXTURE::GOVERMENT_BACKGROUND_ID: return "TYPE::TEXTURE::GOVERMENT_BACKGROUND_ID";

        case type::TEXTURE::NATURELAND_BACKGROUND_ID: return "TYPE::TEXTURE::NATURELAND_BACKGROUND_ID";

        case type::TEXTURE::NEBULA_BACKGROUND_ID: return "TYPE::TEXTURE::NEBULA_BACKGROUND_ID";
        case type::TEXTURE::DISTANTSTAR_ID: return "TYPE::TEXTURE::DISTANTSTAR_ID";

        case type::TEXTURE::FACE_ID: return "TYPE::TEXTURE::FACE_ID";

        case type::TEXTURE::VEHICLE_SLOT_ID: return "TYPE::TEXTURE::VEHICLE_SLOT_ID";
        case type::TEXTURE::ITEM_SLOT_ID: return "TYPE::TEXTURE::ITEM_SLOT_ID";
        case type::TEXTURE::TURREL_ID: return "TYPE::TEXTURE::TURREL_ID";

        case type::TEXTURE::SPACESTATION_ID: return "TYPE::TEXTURE::SPACESTATION_ID";
        case type::TEXTURE::SATELLITE_ID: return "TYPE::TEXTURE::SATELLITE_ID";
        case type::TEXTURE::SHIP_ID: return "TYPE::TEXTURE::SHIP_ID";
        case type::TEXTURE::STAR_ID: return "TYPE::TEXTURE::STAR_ID";
        case type::TEXTURE::PLANET_ID: return "TYPE::TEXTURE::PLANET_ID";

        case type::TEXTURE::ATMOSPHERE_ID: return "TYPE::TEXTURE::ATMOSPHERE_ID";
        case type::TEXTURE::RING_ID: return "TYPE::TEXTURE::RING_ID";

        case type::TEXTURE::ASTEROID_ID: return "TYPE::TEXTURE::ASTEROID_ID";
        case type::TEXTURE::MINERAL_ID: return "TYPE::TEXTURE::MINERAL_ID";
        case type::TEXTURE::CONTAINER_ID: return "TYPE::TEXTURE::CONTAINER_ID";
        case type::TEXTURE::BOMB_ID: return "TYPE::TEXTURE::BOMB_ID";
        case type::TEXTURE::BLACKHOLE_ID: return "TYPE::TEXTURE::BLACKHOLE_ID";

        case type::TEXTURE::PARTICLE_EFFECT_ID: return "TYPE::TEXTURE::PARTICLE_EFFECT_ID";
        case type::TEXTURE::LAZER_EFFECT_ID: return "TYPE::TEXTURE::LAZER_EFFECT_ID";
        case type::TEXTURE::SHIELD_EFFECT_ID: return "TYPE::TEXTURE::SHIELD_EFFECT_ID";

        case type::TEXTURE::DRIVE_EQUIPMENT_ID: return "TYPE::TEXTURE::DRIVE_EQUIPMENT_ID";
        case type::TEXTURE::LAZER_EQUIPMENT_ID: return "TYPE::TEXTURE::LAZER_EQUIPMENT_ID";
        case type::TEXTURE::ROCKET_EQUIPMENT_ID: return "TYPE::TEXTURE::ROCKET_EQUIPMENT_ID";
        case type::TEXTURE::PROTECTOR_EQUIPMENT_ID: return "TYPE::TEXTURE::PROTECTOR_EQUIPMENT_ID";
        case type::TEXTURE::DROID_EQUIPMENT_ID: return "TYPE::TEXTURE::DROID_EQUIPMENT_ID";
        case type::TEXTURE::GRAPPLE_EQUIPMENT_ID: return "TYPE::TEXTURE::GRAPPLE_EQUIPMENT_ID";
        case type::TEXTURE::BAK_EQUIPMENT_ID: return "TYPE::TEXTURE::BAK_EQUIPMENT_ID";
        case type::TEXTURE::ENERGIZER_EQUIPMENT_ID: return "TYPE::TEXTURE::ENERGIZER_EQUIPMENT_ID";
        case type::TEXTURE::FREEZER_EQUIPMENT_ID: return "TYPE::TEXTURE::FREEZER_EQUIPMENT_ID";
        case type::TEXTURE::RADAR_EQUIPMENT_ID: return "TYPE::TEXTURE::RADAR_EQUIPMENT_ID";
        case type::TEXTURE::SCANER_EQUIPMENT_ID: return "TYPE::TEXTURE::SCANER_EQUIPMENT_ID";

        case type::TEXTURE::MODULE_ID: return "TYPE::TEXTURE::MODULE_ID";

        case type::TEXTURE::ROCKET_BULLET_ID: return "TYPE::TEXTURE::ROCKET_BULLET_ID";

        default: return "TYPE::TEXTURE::UNKNOWN";
    }

}

