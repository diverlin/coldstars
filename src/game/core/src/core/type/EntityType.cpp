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
        case entity::Type::NONE: { return "entity::type::NONE"; break; }
            
        case entity::Type::VEHICLE:         { return "entity::type::VEHICLE"; break; }
        case entity::Type::SHIP:         { return "entity::type::SHIP"; break; }
        case entity::Type::SPACESTATION: { return "entity::type::SPACESTATION"; break; }
        case entity::Type::SATELLITE:     { return "entity::type::SATELLITE"; break; }
        case entity::Type::NPC:             { return "entity::type::NPC"; break; }
        case entity::Type::BULLET:         { return "entity::type::BULLET"; break; }
        case entity::Type::ROCKETBULLET: { return "entity::type::ROCKETBULLET"; break; }
        case entity::Type::MINERALS:     { return "entity::type::MINERALS"; break; }
        case entity::Type::FOOD:         { return "entity::type::FOOD"; break; }
        case entity::Type::MEDICINE:     { return "entity::type::MEDICINE"; break; }
        case entity::Type::MILITARY:     { return "entity::type::MILITARY"; break; }
        case entity::Type::DRUG:         { return "entity::type::DRUG"; break; }
        case entity::Type::EXCLUSIVE:     { return "entity::type::EXCLUSIVE"; break; }
        case entity::Type::CONTAINER:     { return "entity::type::CONTAINER"; break; }
        case entity::Type::GALAXY:         { return "entity::type::GALAXY"; break; }
        case entity::Type::STARSYSTEM:     { return "entity::type::STARSYSTEM"; break; }
        case entity::Type::STAR:         { return "entity::type::STAR"; break; }
        case entity::Type::ASTEROID:     { return "entity::type::ASTEROID"; break; }
        case entity::Type::PLANET:         { return "entity::type::PLANET"; break; }
        case entity::Type::BLACKHOLE:     { return "entity::type::BLACKHOLE"; break; }
        case entity::Type::BOMB:         { return "entity::type::BOMB"; break; }
        case entity::Type::GOODS:         { return "entity::type::GOODS"; break; }
        case entity::Type::PLAYER:         { return "entity::type::PLAYER"; break; }
        case entity::Type::KOSMOPORT:     { return "entity::type::KOSMOPORT"; break; }
        case entity::Type::NATURELAND:     { return "entity::type::NATURELAND"; break; }

        case entity::Type::GOVERMENT:     { return "entity::type::GOVERMENT"; break; }
        case entity::Type::STORE:         { return "entity::type::STORE"; break; }
        case entity::Type::SHOP:         { return "entity::type::SHOP"; break; }
        case entity::Type::ANGAR:         { return "entity::type::ANGAR"; break; }
        
        case entity::Type::VEHICLE_SLOT:             { return "entity::type::VEHICLE_SLOT"; break; }
        case entity::Type::VEHICLE_MILITARY_SLOT:     { return "entity::type::VEHICLE_MILITARY_SLOT"; break; }
        case entity::Type::VEHICLE_VISITORS_SLOT:     { return "entity::type::VEHICLE_VISITORS_SLOT"; break; }
        case entity::Type::ITEM_SLOT:         { return "entity::type::ITEM_SLOT"; break; }
        
        case entity::Type::CARGO_SLOT:         { return "entity::type::CARGO_SLOT"; break; }
        case entity::Type::GATE_SLOT:         { return "entity::type::GATE_SLOT"; break; }
        case entity::Type::REPAIR_SLOT:         { return "entity::type::REPAIR_SLOT"; break; }
        case entity::Type::WEAPON_SLOT:         { return "entity::type::WEAPON_SLOT"; break; }
        case entity::Type::WEAPON_SLOT1:     { return "entity::type::WEAPON_SLOT1"; break; }
        case entity::Type::WEAPON_SLOT2:     { return "entity::type::WEAPON_SLOT2"; break; }
        case entity::Type::WEAPON_SLOT3:     { return "entity::type::WEAPON_SLOT3"; break; }
        case entity::Type::WEAPON_SLOT4:     { return "entity::type::WEAPON_SLOT4"; break; }
        case entity::Type::WEAPON_SLOT5:     { return "entity::type::WEAPON_SLOT5"; break; }
        case entity::Type::WEAPON_SLOT6:     { return "entity::type::WEAPON_SLOT6"; break; }
        case entity::Type::WEAPON_SLOT7:     { return "entity::type::WEAPON_SLOT7"; break; }
        case entity::Type::WEAPON_SLOT8:     { return "entity::type::WEAPON_SLOT8"; break; }
        case entity::Type::WEAPON_SLOT9:     { return "entity::type::WEAPON_SLOT9"; break; }
        
        case entity::Type::DRIVE_SLOT:         { return "entity::type::DRIVE_SLOT"; break; }
        case entity::Type::RADAR_SLOT:         { return "entity::type::RADAR_SLOT"; break; }
        case entity::Type::BAK_SLOT:         { return "entity::type::BAK_SLOT"; break; }
        case entity::Type::ENERGIZER_SLOT:     { return "entity::type::ENERGIZER_SLOT"; break; }
        case entity::Type::PROTECTOR_SLOT:     { return "entity::type::PROTECTOR_SLOT"; break; }
        case entity::Type::DROID_SLOT:         { return "entity::type::DROID_SLOT"; break; }
        case entity::Type::FREEZER_SLOT:     { return "entity::type::FREEZER_SLOT"; break; }
        case entity::Type::GRAPPLE_SLOT:     { return "entity::type::GRAPPLE_SLOT"; break; }
        case entity::Type::SCANER_SLOT:         { return "entity::type::SCANER_SLOT"; break; }
        case entity::Type::ARTEFACT_SLOT:     { return "entity::type::ARTEFACT_SLOT"; break; }

        case entity::Type::EQUIPMENT:         { return "entity::type::EQUIPMENT"; break; }
        case entity::Type::MODULE:             { return "entity::type::MODULE"; break; }
        case entity::Type::ARTEFACT:         { return "entity::type::ARTEFACT"; break; }
                                                                                                
        case entity::Type::LAZER_EQUIPMENT:     { return "entity::type::LAZER_EQUIPMENT"; break; }
        case entity::Type::ROCKET_EQUIPMENT: { return "entity::type::ROCKET_EQUIPMENT"; break; }
        case entity::Type::DRIVE_EQUIPMENT:     { return "entity::type::DRIVE_EQUIPMENT"; break; }
        case entity::Type::RADAR_EQUIPMENT:     { return "entity::type::RADAR_EQUIPMENT"; break; }
        case entity::Type::BAK_EQUIPMENT:     { return "entity::type::BAK_EQUIPMENT"; break; }
        case entity::Type::ENERGIZER_EQUIPMENT:     { return "entity::type::ENERGIZER_EQUIPMENT"; break; }
        case entity::Type::PROTECTOR_EQUIPMENT:     { return "entity::type::PROTECTOR_EQUIPMENT"; break; }
        case entity::Type::DROID_EQUIPMENT:         { return "entity::type::DROID_EQUIPMENT"; break; }
        case entity::Type::FREEZER_EQUIPMENT:     { return "entity::type::FREEZER_EQUIPMENT"; break; }
        case entity::Type::GRAPPLE_EQUIPMENT:     { return "entity::type::GRAPPLE_EQUIPMENT"; break; }
        case entity::Type::SCANER_EQUIPMENT:     { return "entity::type::SCANER_EQUIPMENT"; break; }

        case entity::Type::LAZER_MODULE:     { return "entity::type::LAZER_MODULE"; break; }
        case entity::Type::ROCKET_MODULE:     { return "entity::type::ROCKET_MODULE"; break; }
        case entity::Type::DRIVE_MODULE:     { return "entity::type::DRIVE_MODULE"; break; }
        case entity::Type::RADAR_MODULE:     { return "entity::type::RADAR_MODULE"; break; }
        case entity::Type::BAK_MODULE:         { return "entity::type::BAK_MODULE"; break; }
        case entity::Type::ENERGIZER_MODULE: { return "entity::type::ENERGIZER_MODULE"; break; }
        case entity::Type::PROTECTOR_MODULE: { return "entity::type::PROTECTOR_MODULE"; break; }
        case entity::Type::DROID_MODULE:     { return "entity::type::DROID_MODULE"; break; }
        case entity::Type::FREEZER_MODULE:     { return "entity::type::FREEZER_MODULE"; break; }
        case entity::Type::GRAPPLE_MODULE:     { return "entity::type::GRAPPLE_MODULE"; break; }
        case entity::Type::SCANER_MODULE:     { return "entity::type::SCANER_MODULE"; break; }
        
        case entity::Type::GRAVITY_ARTEFACT:     { return "entity::type::GRAVITY_ARTEFACT"; break; }
        case entity::Type::PROTECTOR_ARTEFACT:     { return "entity::type::PROTECTOR_ARTEFACT"; break; }

        case entity::Type::RANGER:     { return "entity::type::RANGER"; break; }
        case entity::Type::WARRIOR:     { return "entity::type::WARRIOR"; break; }
        case entity::Type::PIRAT:     { return "entity::type::PIRAT"; break; }
        case entity::Type::TRADER:     { return "entity::type::TRADER"; break; }
        case entity::Type::DIPLOMAT: { return "entity::type::DIPLOMAT"; break; }

        default: { return "entity::type::UNKNOWN id_type"; break; }
    }
}
