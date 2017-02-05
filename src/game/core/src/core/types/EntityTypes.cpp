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

#include "EntityTypes.hpp"

std::string to_string(entity::type type_id)
{
    switch(type_id)
    {
        case entity::type::NONE_ID: { return "entity::type::NONE_ID"; break; }
            
        case entity::type::VEHICLE_ID:         { return "entity::type::VEHICLE_ID"; break; }
        case entity::type::SHIP_ID:         { return "entity::type::SHIP_ID"; break; }
        case entity::type::SPACESTATION_ID: { return "entity::type::SPACESTATION_ID"; break; }
        case entity::type::SATELLITE_ID:     { return "entity::type::SATELLITE_ID"; break; }
        case entity::type::NPC_ID:             { return "entity::type::NPC_ID"; break; }
        case entity::type::BULLET_ID:         { return "entity::type::BULLET_ID"; break; }
        case entity::type::ROCKETBULLET_ID: { return "entity::type::ROCKETBULLET_ID"; break; }
        case entity::type::MINERALS_ID:     { return "entity::type::MINERALS_ID"; break; }
        case entity::type::FOOD_ID:         { return "entity::type::FOOD_ID"; break; }
        case entity::type::MEDICINE_ID:     { return "entity::type::MEDICINE_ID"; break; }
        case entity::type::MILITARY_ID:     { return "entity::type::MILITARY_ID"; break; }
        case entity::type::DRUG_ID:         { return "entity::type::DRUG_ID"; break; }
        case entity::type::EXCLUSIVE_ID:     { return "entity::type::EXCLUSIVE_ID"; break; }
        case entity::type::CONTAINER_ID:     { return "entity::type::CONTAINER_ID"; break; }
        case entity::type::GALAXY_ID:         { return "entity::type::GALAXY_ID"; break; }
        case entity::type::STARSYSTEM_ID:     { return "entity::type::STARSYSTEM_ID"; break; }
        case entity::type::STAR_ID:         { return "entity::type::STAR_ID"; break; }
        case entity::type::ASTEROID_ID:     { return "entity::type::ASTEROID_ID"; break; }
        case entity::type::PLANET_ID:         { return "entity::type::PLANET_ID"; break; }
        case entity::type::BLACKHOLE_ID:     { return "entity::type::BLACKHOLE_ID"; break; }
        case entity::type::BOMB_ID:         { return "entity::type::BOMB_ID"; break; }
        case entity::type::GOODS_ID:         { return "entity::type::GOODS_ID"; break; }
        case entity::type::PLAYER_ID:         { return "entity::type::PLAYER_ID"; break; }
        case entity::type::KOSMOPORT_ID:     { return "entity::type::KOSMOPORT_ID"; break; }
        case entity::type::NATURELAND_ID:     { return "entity::type::NATURELAND_ID"; break; }

        case entity::type::GOVERMENT_ID:     { return "entity::type::GOVERMENT_ID"; break; }
        case entity::type::STORE_ID:         { return "entity::type::STORE_ID"; break; }
        case entity::type::SHOP_ID:         { return "entity::type::SHOP_ID"; break; }
        case entity::type::ANGAR_ID:         { return "entity::type::ANGAR_ID"; break; }
        
        case entity::type::VEHICLE_SLOT_ID:             { return "entity::type::VEHICLE_SLOT_ID"; break; }
        case entity::type::VEHICLE_MILITARY_SLOT_ID:     { return "entity::type::VEHICLE_MILITARY_SLOT_ID"; break; }
        case entity::type::VEHICLE_VISITORS_SLOT_ID:     { return "entity::type::VEHICLE_VISITORS_SLOT_ID"; break; }
        case entity::type::ITEM_SLOT_ID:         { return "entity::type::ITEM_SLOT_ID"; break; }
        
        case entity::type::CARGO_SLOT_ID:         { return "entity::type::CARGO_SLOT_ID"; break; }
        case entity::type::GATE_SLOT_ID:         { return "entity::type::GATE_SLOT_ID"; break; }
        case entity::type::REPAIR_SLOT_ID:         { return "entity::type::REPAIR_SLOT_ID"; break; }
        case entity::type::WEAPON_SLOT_ID:         { return "entity::type::WEAPON_SLOT_ID"; break; }
        case entity::type::WEAPON_SLOT1_ID:     { return "entity::type::WEAPON_SLOT1_ID"; break; }
        case entity::type::WEAPON_SLOT2_ID:     { return "entity::type::WEAPON_SLOT2_ID"; break; }
        case entity::type::WEAPON_SLOT3_ID:     { return "entity::type::WEAPON_SLOT3_ID"; break; }
        case entity::type::WEAPON_SLOT4_ID:     { return "entity::type::WEAPON_SLOT4_ID"; break; }
        case entity::type::WEAPON_SLOT5_ID:     { return "entity::type::WEAPON_SLOT5_ID"; break; }
        case entity::type::WEAPON_SLOT6_ID:     { return "entity::type::WEAPON_SLOT6_ID"; break; }
        case entity::type::WEAPON_SLOT7_ID:     { return "entity::type::WEAPON_SLOT7_ID"; break; }
        case entity::type::WEAPON_SLOT8_ID:     { return "entity::type::WEAPON_SLOT8_ID"; break; }
        case entity::type::WEAPON_SLOT9_ID:     { return "entity::type::WEAPON_SLOT9_ID"; break; }
        
        case entity::type::DRIVE_SLOT_ID:         { return "entity::type::DRIVE_SLOT_ID"; break; }
        case entity::type::RADAR_SLOT_ID:         { return "entity::type::RADAR_SLOT_ID"; break; }
        case entity::type::BAK_SLOT_ID:         { return "entity::type::BAK_SLOT_ID"; break; }
        case entity::type::ENERGIZER_SLOT_ID:     { return "entity::type::ENERGIZER_SLOT_ID"; break; }
        case entity::type::PROTECTOR_SLOT_ID:     { return "entity::type::PROTECTOR_SLOT_ID"; break; }
        case entity::type::DROID_SLOT_ID:         { return "entity::type::DROID_SLOT_ID"; break; }
        case entity::type::FREEZER_SLOT_ID:     { return "entity::type::FREEZER_SLOT_ID"; break; }
        case entity::type::GRAPPLE_SLOT_ID:     { return "entity::type::GRAPPLE_SLOT_ID"; break; }
        case entity::type::SCANER_SLOT_ID:         { return "entity::type::SCANER_SLOT_ID"; break; }
        case entity::type::ARTEFACT_SLOT_ID:     { return "entity::type::ARTEFACT_SLOT_ID"; break; }

        case entity::type::EQUIPMENT_ID:         { return "entity::type::EQUIPMENT_ID"; break; }
        case entity::type::MODULE_ID:             { return "entity::type::MODULE_ID"; break; }
        case entity::type::ARTEFACT_ID:         { return "entity::type::ARTEFACT_ID"; break; }
                                                                                                
        case entity::type::LAZER_EQUIPMENT_ID:     { return "entity::type::LAZER_EQUIPMENT_ID"; break; }
        case entity::type::ROCKET_EQUIPMENT_ID: { return "entity::type::ROCKET_EQUIPMENT_ID"; break; }
        case entity::type::DRIVE_EQUIPMENT_ID:     { return "entity::type::DRIVE_EQUIPMENT_ID"; break; }
        case entity::type::RADAR_EQUIPMENT_ID:     { return "entity::type::RADAR_EQUIPMENT_ID"; break; }
        case entity::type::BAK_EQUIPMENT_ID:     { return "entity::type::BAK_EQUIPMENT_ID"; break; }
        case entity::type::ENERGIZER_EQUIPMENT_ID:     { return "entity::type::ENERGIZER_EQUIPMENT_ID"; break; }
        case entity::type::PROTECTOR_EQUIPMENT_ID:     { return "entity::type::PROTECTOR_EQUIPMENT_ID"; break; }
        case entity::type::DROID_EQUIPMENT_ID:         { return "entity::type::DROID_EQUIPMENT_ID"; break; }
        case entity::type::FREEZER_EQUIPMENT_ID:     { return "entity::type::FREEZER_EQUIPMENT_ID"; break; }
        case entity::type::GRAPPLE_EQUIPMENT_ID:     { return "entity::type::GRAPPLE_EQUIPMENT_ID"; break; }
        case entity::type::SCANER_EQUIPMENT_ID:     { return "entity::type::SCANER_EQUIPMENT_ID"; break; }

        case entity::type::LAZER_MODULE_ID:     { return "entity::type::LAZER_MODULE_ID"; break; }
        case entity::type::ROCKET_MODULE_ID:     { return "entity::type::ROCKET_MODULE_ID"; break; }
        case entity::type::DRIVE_MODULE_ID:     { return "entity::type::DRIVE_MODULE_ID"; break; }
        case entity::type::RADAR_MODULE_ID:     { return "entity::type::RADAR_MODULE_ID"; break; }
        case entity::type::BAK_MODULE_ID:         { return "entity::type::BAK_MODULE_ID"; break; }
        case entity::type::ENERGIZER_MODULE_ID: { return "entity::type::ENERGIZER_MODULE_ID"; break; }
        case entity::type::PROTECTOR_MODULE_ID: { return "entity::type::PROTECTOR_MODULE_ID"; break; }
        case entity::type::DROID_MODULE_ID:     { return "entity::type::DROID_MODULE_ID"; break; }
        case entity::type::FREEZER_MODULE_ID:     { return "entity::type::FREEZER_MODULE_ID"; break; }
        case entity::type::GRAPPLE_MODULE_ID:     { return "entity::type::GRAPPLE_MODULE_ID"; break; }
        case entity::type::SCANER_MODULE_ID:     { return "entity::type::SCANER_MODULE_ID"; break; }
        
        case entity::type::GRAVITY_ARTEFACT_ID:     { return "entity::type::GRAVITY_ARTEFACT_ID"; break; }
        case entity::type::PROTECTOR_ARTEFACT_ID:     { return "entity::type::PROTECTOR_ARTEFACT_ID"; break; }

        case entity::type::RANGER_ID:     { return "entity::type::RANGER_ID"; break; }
        case entity::type::WARRIOR_ID:     { return "entity::type::WARRIOR_ID"; break; }
        case entity::type::PIRAT_ID:     { return "entity::type::PIRAT_ID"; break; }
        case entity::type::TRADER_ID:     { return "entity::type::TRADER_ID"; break; }
        case entity::type::DIPLOMAT_ID: { return "entity::type::DIPLOMAT_ID"; break; }

        default: { return "entity::type::UNKNOWN id_type"; break; }
    }
}
