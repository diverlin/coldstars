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

    enum class Category {
        NONE=0,
        /** */

        /** */
        ANY
    };

    enum class Type
    {
        NONE=0,
        /** */

        GALAXY, SECTOR, STARSYSTEM, STAR, ASTEROID, 
        
        PLANET, 
        PLANET_MIXED, PLANET_WATER, PLANET_VULCANIC, PLANET_ICE, PLANET_GAS, PLANET_ROCK,    
        
        BLACKHOLE, 
                        
        VEHICLE, 
        
        NPC, SHIP,
        RANGER, WARRIOR, PIRAT, TRADER, DIPLOMAT,
        
        SPACESTATION,
        SPACESTATION_MILITARY, SPACESTATION_RESEARCH, SPACESTATION_PIRAT,

        SATELLITE,
         
        CONTAINER,
        MINERALS, FOOD, MEDICINE, MILITARY, DRUG, EXCLUSIVE, 
        
        BULLET, ROCKETBULLET,
        
        BOMB, GOODS, PLAYER, KOSMOPORT, NATURELAND,

        GOVERMENT, STORE, SHOP, ANGAR,
        
        VEHICLE_SLOT, VEHICLE_MILITARY_SLOT, VEHICLE_VISITORS_SLOT, 
        
        ITEM_SLOT, 
        
        CARGO_SLOT, 
        CARGO_SLOT1, CARGO_SLOT2, CARGO_SLOT3, CARGO_SLOT4, CARGO_SLOT5, CARGO_SLOT6, CARGO_SLOT7, CARGO_SLOT8, CARGO_SLOT9,  
        CARGO_SLOT10, CARGO_SLOT11, CARGO_SLOT12, CARGO_SLOT13, CARGO_SLOT14, CARGO_SLOT15, CARGO_SLOT16, CARGO_SLOT17, CARGO_SLOT18,
                
        WEAPON_SLOT, 
        WEAPON_SLOT1, WEAPON_SLOT2, WEAPON_SLOT3, WEAPON_SLOT4, WEAPON_SLOT5, WEAPON_SLOT6, WEAPON_SLOT7, WEAPON_SLOT8, WEAPON_SLOT9,
        
        GATE_SLOT, REPAIR_SLOT, CHARGE_SLOT,
        
        DRIVE_SLOT, RADAR_SLOT, BAK_SLOT, ENERGIZER_SLOT, PROTECTOR_SLOT, DROID_SLOT, FREEZER_SLOT, GRAPPLE_SLOT, SCANER_SLOT, 
        
        ARTEFACT_SLOT, 
        ARTEFACT_SLOT1, ARTEFACT_SLOT2, ARTEFACT_SLOT3, ARTEFACT_SLOT4,
        
        EQUIPMENT, MODULE, ARTEFACT,
                
        LAZER_EQUIPMENT, ROCKET_EQUIPMENT, DRIVE_EQUIPMENT, RADAR_EQUIPMENT, BAK_EQUIPMENT, ENERGIZER_EQUIPMENT, PROTECTOR_EQUIPMENT, DROID_EQUIPMENT, FREEZER_EQUIPMENT, GRAPPLE_EQUIPMENT, SCANER_EQUIPMENT,  
        LAZER_MODULE, ROCKET_MODULE, DRIVE_MODULE, RADAR_MODULE, BAK_MODULE, ENERGIZER_MODULE, PROTECTOR_MODULE, DROID_MODULE, FREEZER_MODULE, GRAPPLE_MODULE, SCANER_MODULE,
    
        GRAVITY_ARTEFACT, PROTECTOR_ARTEFACT,


        /** */
        ANY
    };
}
 
const std::vector<entity::Type> SLOT_WEAPON_TYPES =
{ 
entity::Type::WEAPON_SLOT1,
entity::Type::WEAPON_SLOT2,
entity::Type::WEAPON_SLOT3,
entity::Type::WEAPON_SLOT4,
entity::Type::WEAPON_SLOT5,
entity::Type::WEAPON_SLOT6,
entity::Type::WEAPON_SLOT7,
entity::Type::WEAPON_SLOT8,
entity::Type::WEAPON_SLOT9
};
   
const std::vector<entity::Type> SLOT_CARGO_TYPES =
{ 
entity::Type::CARGO_SLOT1,
entity::Type::CARGO_SLOT2,
entity::Type::CARGO_SLOT3,
entity::Type::CARGO_SLOT4,
entity::Type::CARGO_SLOT5,
entity::Type::CARGO_SLOT6,
entity::Type::CARGO_SLOT7,
entity::Type::CARGO_SLOT8,
entity::Type::CARGO_SLOT9,
entity::Type::CARGO_SLOT10,
//entity::Type::CARGO_SLOT11,
//entity::Type::CARGO_SLOT12,
//entity::Type::CARGO_SLOT13,
//entity::Type::CARGO_SLOT14,
//entity::Type::CARGO_SLOT15,
//entity::Type::CARGO_SLOT16,
//entity::Type::CARGO_SLOT17,
//entity::Type::CARGO_SLOT18
};

const std::vector<entity::Type> SLOT_ARTEFACT_TYPES =
{ 
entity::Type::ARTEFACT_SLOT1,
entity::Type::ARTEFACT_SLOT2,
entity::Type::ARTEFACT_SLOT3,
entity::Type::ARTEFACT_SLOT4,
};

const std::vector<entity::Type> EQUIPMENT_TYPES =
{ 
entity::Type::LAZER_EQUIPMENT,
entity::Type::ROCKET_EQUIPMENT,
entity::Type::DRIVE_EQUIPMENT,
entity::Type::RADAR_EQUIPMENT,
entity::Type::BAK_EQUIPMENT,
entity::Type::ENERGIZER_EQUIPMENT,
entity::Type::PROTECTOR_EQUIPMENT,
entity::Type::DROID_EQUIPMENT,
entity::Type::FREEZER_EQUIPMENT,
entity::Type::GRAPPLE_EQUIPMENT,
entity::Type::SCANER_EQUIPMENT
};

const std::vector<entity::Type> MODULE_TYPES =
{ 
entity::Type::LAZER_MODULE,
entity::Type::ROCKET_MODULE,
entity::Type::DRIVE_MODULE,
entity::Type::RADAR_MODULE,
entity::Type::BAK_MODULE,
entity::Type::ENERGIZER_MODULE,
entity::Type::PROTECTOR_MODULE,
entity::Type::DROID_MODULE,
entity::Type::FREEZER_MODULE,
entity::Type::GRAPPLE_MODULE,
entity::Type::SCANER_MODULE
};    

std::string to_string(entity::Type);

