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

#include <vector>
#include <string>

namespace entity
{
    enum class type
    {
        NONE=0,
        /** */

        GALAXY_ID, SECTOR_ID, STARSYSTEM_ID, STAR_ID, ASTEROID_ID, 
        
        PLANET_ID, 
        PLANET_MIXED_ID, PLANET_WATER_ID, PLANET_VULCANIC_ID, PLANET_ICE_ID, PLANET_GAS_ID, PLANET_ROCK_ID,    
        
        BLACKHOLE_ID, 
                        
        VEHICLE_ID, 
        
        NPC_ID, SHIP_ID,
        RANGER_ID, WARRIOR_ID, PIRAT_ID, TRADER_ID, DIPLOMAT_ID,
        
        SPACESTATION_ID,
        SPACESTATION_MILITARY_ID, SPACESTATION_RESEARCH_ID, SPACESTATION_PIRAT_ID,

        SATELLITE_ID,
         
        CONTAINER_ID,
        MINERALS_ID, FOOD_ID, MEDICINE_ID, MILITARY_ID, DRUG_ID, EXCLUSIVE_ID, 
        
        BULLET_ID, ROCKETBULLET_ID,
        
        BOMB_ID, GOODS_ID, PLAYER_ID, KOSMOPORT_ID, NATURELAND_ID,

        GOVERMENT_ID, STORE_ID, SHOP_ID, ANGAR_ID,
        
        VEHICLE_SLOT_ID, VEHICLE_MILITARY_SLOT_ID, VEHICLE_VISITORS_SLOT_ID, 
        
        ITEM_SLOT_ID, 
        
        CARGO_SLOT_ID, 
        CARGO_SLOT1_ID, CARGO_SLOT2_ID, CARGO_SLOT3_ID, CARGO_SLOT4_ID, CARGO_SLOT5_ID, CARGO_SLOT6_ID, CARGO_SLOT7_ID, CARGO_SLOT8_ID, CARGO_SLOT9_ID,  
        CARGO_SLOT10_ID, CARGO_SLOT11_ID, CARGO_SLOT12_ID, CARGO_SLOT13_ID, CARGO_SLOT14_ID, CARGO_SLOT15_ID, CARGO_SLOT16_ID, CARGO_SLOT17_ID, CARGO_SLOT18_ID,
                
        WEAPON_SLOT_ID, 
        WEAPON_SLOT1_ID, WEAPON_SLOT2_ID, WEAPON_SLOT3_ID, WEAPON_SLOT4_ID, WEAPON_SLOT5_ID, WEAPON_SLOT6_ID, WEAPON_SLOT7_ID, WEAPON_SLOT8_ID, WEAPON_SLOT9_ID,
        
        GATE_SLOT_ID, REPAIR_SLOT_ID, CHARGE_SLOT_ID,
        
        DRIVE_SLOT_ID, RADAR_SLOT_ID, BAK_SLOT_ID, ENERGIZER_SLOT_ID, PROTECTOR_SLOT_ID, DROID_SLOT_ID, FREEZER_SLOT_ID, GRAPPLE_SLOT_ID, SCANER_SLOT_ID, 
        
        ARTEFACT_SLOT_ID, 
        ARTEFACT_SLOT1_ID, ARTEFACT_SLOT2_ID, ARTEFACT_SLOT3_ID, ARTEFACT_SLOT4_ID,
        
        EQUIPMENT_ID, MODULE_ID, ARTEFACT_ID,
                
        LAZER_EQUIPMENT_ID, ROCKET_EQUIPMENT_ID, DRIVE_EQUIPMENT_ID, RADAR_EQUIPMENT_ID, BAK_EQUIPMENT_ID, ENERGIZER_EQUIPMENT_ID, PROTECTOR_EQUIPMENT_ID, DROID_EQUIPMENT_ID, FREEZER_EQUIPMENT_ID, GRAPPLE_EQUIPMENT_ID, SCANER_EQUIPMENT_ID,  
        LAZER_MODULE_ID, ROCKET_MODULE_ID, DRIVE_MODULE_ID, RADAR_MODULE_ID, BAK_MODULE_ID, ENERGIZER_MODULE_ID, PROTECTOR_MODULE_ID, DROID_MODULE_ID, FREEZER_MODULE_ID, GRAPPLE_MODULE_ID, SCANER_MODULE_ID,
    
        GRAVITY_ARTEFACT_ID, PROTECTOR_ARTEFACT_ID,


        /** */
        ANY_ID
    };
}
 
const std::vector<entity::type> SLOT_WEAPON_TYPES =
{ 
entity::type::WEAPON_SLOT1_ID,
entity::type::WEAPON_SLOT2_ID,
entity::type::WEAPON_SLOT3_ID,
entity::type::WEAPON_SLOT4_ID,
entity::type::WEAPON_SLOT5_ID,
entity::type::WEAPON_SLOT6_ID,
entity::type::WEAPON_SLOT7_ID,
entity::type::WEAPON_SLOT8_ID,
entity::type::WEAPON_SLOT9_ID
};
   
const std::vector<entity::type> SLOT_CARGO_TYPES =
{ 
entity::type::CARGO_SLOT1_ID,
entity::type::CARGO_SLOT2_ID,
entity::type::CARGO_SLOT3_ID,
entity::type::CARGO_SLOT4_ID,
entity::type::CARGO_SLOT5_ID,
entity::type::CARGO_SLOT6_ID,
entity::type::CARGO_SLOT7_ID,
entity::type::CARGO_SLOT8_ID,
entity::type::CARGO_SLOT9_ID,
entity::type::CARGO_SLOT10_ID,
//entity::Type::CARGO_SLOT11_ID,
//entity::Type::CARGO_SLOT12_ID,
//entity::Type::CARGO_SLOT13_ID,
//entity::Type::CARGO_SLOT14_ID,
//entity::Type::CARGO_SLOT15_ID,
//entity::Type::CARGO_SLOT16_ID,
//entity::Type::CARGO_SLOT17_ID,
//entity::Type::CARGO_SLOT18_ID
};

const std::vector<entity::type> SLOT_ARTEFACT_TYPES =
{ 
entity::type::ARTEFACT_SLOT1_ID,
entity::type::ARTEFACT_SLOT2_ID,
entity::type::ARTEFACT_SLOT3_ID,
entity::type::ARTEFACT_SLOT4_ID,
};

const std::vector<entity::type> EQUIPMENT_TYPES =
{ 
entity::type::LAZER_EQUIPMENT_ID,
entity::type::ROCKET_EQUIPMENT_ID,
entity::type::DRIVE_EQUIPMENT_ID,
entity::type::RADAR_EQUIPMENT_ID,
entity::type::BAK_EQUIPMENT_ID,
entity::type::ENERGIZER_EQUIPMENT_ID,
entity::type::PROTECTOR_EQUIPMENT_ID,
entity::type::DROID_EQUIPMENT_ID,
entity::type::FREEZER_EQUIPMENT_ID,
entity::type::GRAPPLE_EQUIPMENT_ID,
entity::type::SCANER_EQUIPMENT_ID
};

const std::vector<entity::type> MODULE_TYPES =
{ 
entity::type::LAZER_MODULE_ID,
entity::type::ROCKET_MODULE_ID,
entity::type::DRIVE_MODULE_ID,
entity::type::RADAR_MODULE_ID,
entity::type::BAK_MODULE_ID,
entity::type::ENERGIZER_MODULE_ID,
entity::type::PROTECTOR_MODULE_ID,
entity::type::DROID_MODULE_ID,
entity::type::FREEZER_MODULE_ID,
entity::type::GRAPPLE_MODULE_ID,
entity::type::SCANER_MODULE_ID
};    

std::string to_string(entity::type);

