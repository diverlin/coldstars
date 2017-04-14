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

#include "EntityType.hpp"

std::string to_string(entity::Type type_id)
{
    switch(type_id)
    {
        case entity::Type::NONE: { return "entity::Type::NONE"; break; }
            
        case entity::Type::VEHICLE:         { return "entity::Type::VEHICLE"; break; }
        case entity::Type::SHIP:         { return "entity::Type::SHIP"; break; }
        case entity::Type::SPACESTATION: { return "entity::Type::SPACESTATION"; break; }
        case entity::Type::SATELLITE:     { return "entity::Type::SATELLITE"; break; }
        case entity::Type::NPC:             { return "entity::Type::NPC"; break; }
        case entity::Type::BULLET:         { return "entity::Type::BULLET"; break; }
        case entity::Type::ROCKETBULLET: { return "entity::Type::ROCKETBULLET"; break; }
        case entity::Type::MINERALS:     { return "entity::Type::MINERALS"; break; }
        case entity::Type::FOOD:         { return "entity::Type::FOOD"; break; }
        case entity::Type::MEDICINE:     { return "entity::Type::MEDICINE"; break; }
        case entity::Type::MILITARY:     { return "entity::Type::MILITARY"; break; }
        case entity::Type::DRUG:         { return "entity::Type::DRUG"; break; }
        case entity::Type::EXCLUSIVE:     { return "entity::Type::EXCLUSIVE"; break; }
        case entity::Type::CONTAINER:     { return "entity::Type::CONTAINER"; break; }
        case entity::Type::GALAXY:         { return "entity::Type::GALAXY"; break; }
        case entity::Type::STARSYSTEM:     { return "entity::Type::STARSYSTEM"; break; }
        case entity::Type::STAR:         { return "entity::Type::STAR"; break; }
        case entity::Type::ASTEROID:     { return "entity::Type::ASTEROID"; break; }
        case entity::Type::PLANET:         { return "entity::Type::PLANET"; break; }
        case entity::Type::BLACKHOLE:     { return "entity::Type::BLACKHOLE"; break; }
        case entity::Type::BOMB:         { return "entity::Type::BOMB"; break; }
        case entity::Type::GOODS:         { return "entity::Type::GOODS"; break; }
        case entity::Type::PLAYER:         { return "entity::Type::PLAYER"; break; }
        case entity::Type::KOSMOPORT:     { return "entity::Type::KOSMOPORT"; break; }
        case entity::Type::NATURELAND:     { return "entity::Type::NATURELAND"; break; }

        case entity::Type::GOVERMENT:     { return "entity::Type::GOVERMENT"; break; }
        case entity::Type::STORE:         { return "entity::Type::STORE"; break; }
        case entity::Type::SHOP:         { return "entity::Type::SHOP"; break; }
        case entity::Type::ANGAR:         { return "entity::Type::ANGAR"; break; }
        
        case entity::Type::VEHICLE_SLOT:             { return "entity::Type::VEHICLE_SLOT"; break; }
        case entity::Type::VEHICLE_MILITARY_SLOT:     { return "entity::Type::VEHICLE_MILITARY_SLOT"; break; }
        case entity::Type::VEHICLE_VISITORS_SLOT:     { return "entity::Type::VEHICLE_VISITORS_SLOT"; break; }
        case entity::Type::ITEM_SLOT:         { return "entity::Type::ITEM_SLOT"; break; }
        
        case entity::Type::CARGO_SLOT:         { return "entity::Type::CARGO_SLOT"; break; }
        case entity::Type::GATE_SLOT:         { return "entity::Type::GATE_SLOT"; break; }
        case entity::Type::REPAIR_SLOT:         { return "entity::Type::REPAIR_SLOT"; break; }
        case entity::Type::WEAPON_SLOT:         { return "entity::Type::WEAPON_SLOT"; break; }
        case entity::Type::WEAPON_SLOT1:     { return "entity::Type::WEAPON_SLOT1"; break; }
        case entity::Type::WEAPON_SLOT2:     { return "entity::Type::WEAPON_SLOT2"; break; }
        case entity::Type::WEAPON_SLOT3:     { return "entity::Type::WEAPON_SLOT3"; break; }
        case entity::Type::WEAPON_SLOT4:     { return "entity::Type::WEAPON_SLOT4"; break; }
        case entity::Type::WEAPON_SLOT5:     { return "entity::Type::WEAPON_SLOT5"; break; }
        case entity::Type::WEAPON_SLOT6:     { return "entity::Type::WEAPON_SLOT6"; break; }
        case entity::Type::WEAPON_SLOT7:     { return "entity::Type::WEAPON_SLOT7"; break; }
        case entity::Type::WEAPON_SLOT8:     { return "entity::Type::WEAPON_SLOT8"; break; }
        case entity::Type::WEAPON_SLOT9:     { return "entity::Type::WEAPON_SLOT9"; break; }
        
        case entity::Type::DRIVE_SLOT:         { return "entity::Type::DRIVE_SLOT"; break; }
        case entity::Type::RADAR_SLOT:         { return "entity::Type::RADAR_SLOT"; break; }
        case entity::Type::BAK_SLOT:         { return "entity::Type::BAK_SLOT"; break; }
        case entity::Type::ENERGIZER_SLOT:     { return "entity::Type::ENERGIZER_SLOT"; break; }
        case entity::Type::PROTECTOR_SLOT:     { return "entity::Type::PROTECTOR_SLOT"; break; }
        case entity::Type::DROID_SLOT:         { return "entity::Type::DROID_SLOT"; break; }
        case entity::Type::FREEZER_SLOT:     { return "entity::Type::FREEZER_SLOT"; break; }
        case entity::Type::GRAPPLE_SLOT:     { return "entity::Type::GRAPPLE_SLOT"; break; }
        case entity::Type::SCANER_SLOT:         { return "entity::Type::SCANER_SLOT"; break; }
        case entity::Type::ARTEFACT_SLOT:     { return "entity::Type::ARTEFACT_SLOT"; break; }

        case entity::Type::EQUIPMENT:         { return "entity::Type::EQUIPMENT"; break; }
        case entity::Type::MODULE:             { return "entity::Type::MODULE"; break; }
        case entity::Type::ARTEFACT:         { return "entity::Type::ARTEFACT"; break; }
                                                                                                
        case entity::Type::LAZER_EQUIPMENT:     { return "entity::Type::LAZER_EQUIPMENT"; break; }
        case entity::Type::ROCKET_EQUIPMENT: { return "entity::Type::ROCKET_EQUIPMENT"; break; }
        case entity::Type::DRIVE_EQUIPMENT:     { return "entity::Type::DRIVE_EQUIPMENT"; break; }
        case entity::Type::RADAR_EQUIPMENT:     { return "entity::Type::RADAR_EQUIPMENT"; break; }
        case entity::Type::BAK_EQUIPMENT:     { return "entity::Type::BAK_EQUIPMENT"; break; }
        case entity::Type::ENERGIZER_EQUIPMENT:     { return "entity::Type::ENERGIZER_EQUIPMENT"; break; }
        case entity::Type::PROTECTOR_EQUIPMENT:     { return "entity::Type::PROTECTOR_EQUIPMENT"; break; }
        case entity::Type::DROID_EQUIPMENT:         { return "entity::Type::DROID_EQUIPMENT"; break; }
        case entity::Type::FREEZER_EQUIPMENT:     { return "entity::Type::FREEZER_EQUIPMENT"; break; }
        case entity::Type::GRAPPLE_EQUIPMENT:     { return "entity::Type::GRAPPLE_EQUIPMENT"; break; }
        case entity::Type::SCANER_EQUIPMENT:     { return "entity::Type::SCANER_EQUIPMENT"; break; }

        case entity::Type::LAZER_MODULE:     { return "entity::Type::LAZER_MODULE"; break; }
        case entity::Type::ROCKET_MODULE:     { return "entity::Type::ROCKET_MODULE"; break; }
        case entity::Type::DRIVE_MODULE:     { return "entity::Type::DRIVE_MODULE"; break; }
        case entity::Type::RADAR_MODULE:     { return "entity::Type::RADAR_MODULE"; break; }
        case entity::Type::BAK_MODULE:         { return "entity::Type::BAK_MODULE"; break; }
        case entity::Type::ENERGIZER_MODULE: { return "entity::Type::ENERGIZER_MODULE"; break; }
        case entity::Type::PROTECTOR_MODULE: { return "entity::Type::PROTECTOR_MODULE"; break; }
        case entity::Type::DROID_MODULE:     { return "entity::Type::DROID_MODULE"; break; }
        case entity::Type::FREEZER_MODULE:     { return "entity::Type::FREEZER_MODULE"; break; }
        case entity::Type::GRAPPLE_MODULE:     { return "entity::Type::GRAPPLE_MODULE"; break; }
        case entity::Type::SCANER_MODULE:     { return "entity::Type::SCANER_MODULE"; break; }
        
        case entity::Type::GRAVITY_ARTEFACT:     { return "entity::Type::GRAVITY_ARTEFACT"; break; }
        case entity::Type::PROTECTOR_ARTEFACT:     { return "entity::Type::PROTECTOR_ARTEFACT"; break; }

        case entity::Type::RANGER:     { return "entity::Type::RANGER"; break; }
        case entity::Type::WARRIOR:     { return "entity::Type::WARRIOR"; break; }
        case entity::Type::PIRAT:     { return "entity::Type::PIRAT"; break; }
        case entity::Type::TRADER:     { return "entity::Type::TRADER"; break; }
        case entity::Type::DIPLOMAT: { return "entity::Type::DIPLOMAT"; break; }

        default: { return "entity::Type::UNKNOWN id_type"; break; }
    }
}
