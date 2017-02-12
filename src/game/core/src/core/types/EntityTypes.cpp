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
        case entity::type::NONE: { return "entity::type::NONE"; break; }
            
        case entity::type::VEHICLE:         { return "entity::type::VEHICLE"; break; }
        case entity::type::SHIP:         { return "entity::type::SHIP"; break; }
        case entity::type::SPACESTATION: { return "entity::type::SPACESTATION"; break; }
        case entity::type::SATELLITE:     { return "entity::type::SATELLITE"; break; }
        case entity::type::NPC:             { return "entity::type::NPC"; break; }
        case entity::type::BULLET:         { return "entity::type::BULLET"; break; }
        case entity::type::ROCKETBULLET: { return "entity::type::ROCKETBULLET"; break; }
        case entity::type::MINERALS:     { return "entity::type::MINERALS"; break; }
        case entity::type::FOOD:         { return "entity::type::FOOD"; break; }
        case entity::type::MEDICINE:     { return "entity::type::MEDICINE"; break; }
        case entity::type::MILITARY:     { return "entity::type::MILITARY"; break; }
        case entity::type::DRUG:         { return "entity::type::DRUG"; break; }
        case entity::type::EXCLUSIVE:     { return "entity::type::EXCLUSIVE"; break; }
        case entity::type::CONTAINER:     { return "entity::type::CONTAINER"; break; }
        case entity::type::GALAXY:         { return "entity::type::GALAXY"; break; }
        case entity::type::STARSYSTEM:     { return "entity::type::STARSYSTEM"; break; }
        case entity::type::STAR:         { return "entity::type::STAR"; break; }
        case entity::type::ASTEROID:     { return "entity::type::ASTEROID"; break; }
        case entity::type::PLANET:         { return "entity::type::PLANET"; break; }
        case entity::type::BLACKHOLE:     { return "entity::type::BLACKHOLE"; break; }
        case entity::type::BOMB:         { return "entity::type::BOMB"; break; }
        case entity::type::GOODS:         { return "entity::type::GOODS"; break; }
        case entity::type::PLAYER:         { return "entity::type::PLAYER"; break; }
        case entity::type::KOSMOPORT:     { return "entity::type::KOSMOPORT"; break; }
        case entity::type::NATURELAND:     { return "entity::type::NATURELAND"; break; }

        case entity::type::GOVERMENT:     { return "entity::type::GOVERMENT"; break; }
        case entity::type::STORE:         { return "entity::type::STORE"; break; }
        case entity::type::SHOP:         { return "entity::type::SHOP"; break; }
        case entity::type::ANGAR:         { return "entity::type::ANGAR"; break; }
        
        case entity::type::VEHICLE_SLOT:             { return "entity::type::VEHICLE_SLOT"; break; }
        case entity::type::VEHICLE_MILITARY_SLOT:     { return "entity::type::VEHICLE_MILITARY_SLOT"; break; }
        case entity::type::VEHICLE_VISITORS_SLOT:     { return "entity::type::VEHICLE_VISITORS_SLOT"; break; }
        case entity::type::ITEM_SLOT:         { return "entity::type::ITEM_SLOT"; break; }
        
        case entity::type::CARGO_SLOT:         { return "entity::type::CARGO_SLOT"; break; }
        case entity::type::GATE_SLOT:         { return "entity::type::GATE_SLOT"; break; }
        case entity::type::REPAIR_SLOT:         { return "entity::type::REPAIR_SLOT"; break; }
        case entity::type::WEAPON_SLOT:         { return "entity::type::WEAPON_SLOT"; break; }
        case entity::type::WEAPON_SLOT1:     { return "entity::type::WEAPON_SLOT1"; break; }
        case entity::type::WEAPON_SLOT2:     { return "entity::type::WEAPON_SLOT2"; break; }
        case entity::type::WEAPON_SLOT3:     { return "entity::type::WEAPON_SLOT3"; break; }
        case entity::type::WEAPON_SLOT4:     { return "entity::type::WEAPON_SLOT4"; break; }
        case entity::type::WEAPON_SLOT5:     { return "entity::type::WEAPON_SLOT5"; break; }
        case entity::type::WEAPON_SLOT6:     { return "entity::type::WEAPON_SLOT6"; break; }
        case entity::type::WEAPON_SLOT7:     { return "entity::type::WEAPON_SLOT7"; break; }
        case entity::type::WEAPON_SLOT8:     { return "entity::type::WEAPON_SLOT8"; break; }
        case entity::type::WEAPON_SLOT9:     { return "entity::type::WEAPON_SLOT9"; break; }
        
        case entity::type::DRIVE_SLOT:         { return "entity::type::DRIVE_SLOT"; break; }
        case entity::type::RADAR_SLOT:         { return "entity::type::RADAR_SLOT"; break; }
        case entity::type::BAK_SLOT:         { return "entity::type::BAK_SLOT"; break; }
        case entity::type::ENERGIZER_SLOT:     { return "entity::type::ENERGIZER_SLOT"; break; }
        case entity::type::PROTECTOR_SLOT:     { return "entity::type::PROTECTOR_SLOT"; break; }
        case entity::type::DROID_SLOT:         { return "entity::type::DROID_SLOT"; break; }
        case entity::type::FREEZER_SLOT:     { return "entity::type::FREEZER_SLOT"; break; }
        case entity::type::GRAPPLE_SLOT:     { return "entity::type::GRAPPLE_SLOT"; break; }
        case entity::type::SCANER_SLOT:         { return "entity::type::SCANER_SLOT"; break; }
        case entity::type::ARTEFACT_SLOT:     { return "entity::type::ARTEFACT_SLOT"; break; }

        case entity::type::EQUIPMENT:         { return "entity::type::EQUIPMENT"; break; }
        case entity::type::MODULE:             { return "entity::type::MODULE"; break; }
        case entity::type::ARTEFACT:         { return "entity::type::ARTEFACT"; break; }
                                                                                                
        case entity::type::LAZER_EQUIPMENT:     { return "entity::type::LAZER_EQUIPMENT"; break; }
        case entity::type::ROCKET_EQUIPMENT: { return "entity::type::ROCKET_EQUIPMENT"; break; }
        case entity::type::DRIVE_EQUIPMENT:     { return "entity::type::DRIVE_EQUIPMENT"; break; }
        case entity::type::RADAR_EQUIPMENT:     { return "entity::type::RADAR_EQUIPMENT"; break; }
        case entity::type::BAK_EQUIPMENT:     { return "entity::type::BAK_EQUIPMENT"; break; }
        case entity::type::ENERGIZER_EQUIPMENT:     { return "entity::type::ENERGIZER_EQUIPMENT"; break; }
        case entity::type::PROTECTOR_EQUIPMENT:     { return "entity::type::PROTECTOR_EQUIPMENT"; break; }
        case entity::type::DROID_EQUIPMENT:         { return "entity::type::DROID_EQUIPMENT"; break; }
        case entity::type::FREEZER_EQUIPMENT:     { return "entity::type::FREEZER_EQUIPMENT"; break; }
        case entity::type::GRAPPLE_EQUIPMENT:     { return "entity::type::GRAPPLE_EQUIPMENT"; break; }
        case entity::type::SCANER_EQUIPMENT:     { return "entity::type::SCANER_EQUIPMENT"; break; }

        case entity::type::LAZER_MODULE:     { return "entity::type::LAZER_MODULE"; break; }
        case entity::type::ROCKET_MODULE:     { return "entity::type::ROCKET_MODULE"; break; }
        case entity::type::DRIVE_MODULE:     { return "entity::type::DRIVE_MODULE"; break; }
        case entity::type::RADAR_MODULE:     { return "entity::type::RADAR_MODULE"; break; }
        case entity::type::BAK_MODULE:         { return "entity::type::BAK_MODULE"; break; }
        case entity::type::ENERGIZER_MODULE: { return "entity::type::ENERGIZER_MODULE"; break; }
        case entity::type::PROTECTOR_MODULE: { return "entity::type::PROTECTOR_MODULE"; break; }
        case entity::type::DROID_MODULE:     { return "entity::type::DROID_MODULE"; break; }
        case entity::type::FREEZER_MODULE:     { return "entity::type::FREEZER_MODULE"; break; }
        case entity::type::GRAPPLE_MODULE:     { return "entity::type::GRAPPLE_MODULE"; break; }
        case entity::type::SCANER_MODULE:     { return "entity::type::SCANER_MODULE"; break; }
        
        case entity::type::GRAVITY_ARTEFACT:     { return "entity::type::GRAVITY_ARTEFACT"; break; }
        case entity::type::PROTECTOR_ARTEFACT:     { return "entity::type::PROTECTOR_ARTEFACT"; break; }

        case entity::type::RANGER:     { return "entity::type::RANGER"; break; }
        case entity::type::WARRIOR:     { return "entity::type::WARRIOR"; break; }
        case entity::type::PIRAT:     { return "entity::type::PIRAT"; break; }
        case entity::type::TRADER:     { return "entity::type::TRADER"; break; }
        case entity::type::DIPLOMAT: { return "entity::type::DIPLOMAT"; break; }

        default: { return "entity::type::UNKNOWN id_type"; break; }
    }
}
