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

#include <cassert>

namespace core {

std::string to_string(SlotType type)
{
    switch(type)
    {
    case SlotType::NONE:     { return "slot::Type::NONE"; }
    case SlotType::WEAPON:   { return "slot::Type::WEAPON"; }
    case SlotType::CARGO:    { return "slot::Type::CARGO"; }
    case SlotType::ARTEFACT: { return "slot::Type::ARTEFACT"; }

    case SlotType::DRIVE:     { return "slot::Type::DRIVE"; }
    case SlotType::RADAR:     { return "slot::Type::RADAR"; }
    case SlotType::BAK:       { return "slot::Type::BAK"; }
    case SlotType::ENERGIZER: { return "slot::Type::ENERGIZER"; }
    case SlotType::PROTECTOR: { return "slot::Type::PROTECTOR"; }
    case SlotType::DROID:     { return "slot::Type::DROID"; }
    case SlotType::FREEZER:   { return "slot::Type::FREEZER"; }
    case SlotType::GRAPPLE:   { return "slot::Type::GRAPPLE"; }
    case SlotType::SCANER:    { return "slot::Type::SCANER"; }
    case SlotType::GATE:      { return "slot::Type::GATE"; }
    }

    assert(false);
    return "UNDEFINED";
}

} // namespace core

namespace entity {

std::string to_string(Type type)
{
    switch(type)
    {
        case Type::NONE: { return "NONE"; }
            
        case Type::VEHICLE:         { return "VEHICLE"; }
        case Type::SHIP:         { return "SHIP"; }
        case Type::SPACESTATION: { return "SPACESTATION"; }
        case Type::SATELLITE:     { return "SATELLITE"; }
        case Type::NPC:             { return "NPC"; }
        case Type::BULLET:         { return "BULLET"; }
        case Type::Bullet: { return "Bullet"; }
        case Type::MINERALS:     { return "MINERALS"; }
        case Type::FOOD:         { return "FOOD"; }
        case Type::MEDICINE:     { return "MEDICINE"; }
        case Type::MILITARY:     { return "MILITARY"; }
        case Type::DRUG:         { return "DRUG"; }
        case Type::EXCLUSIVE:     { return "EXCLUSIVE"; }
        case Type::CONTAINER:     { return "CONTAINER"; }
        case Type::GALAXY:         { return "GALAXY"; }
        case Type::STARSYSTEM:     { return "STARSYSTEM"; }
        case Type::STAR:         { return "STAR"; }
        case Type::ASTEROID:     { return "ASTEROID"; }
        case Type::PLANET:         { return "PLANET"; }
        case Type::WORMHOLE:     { return "WORMHOLE"; }
        case Type::BOMB:         { return "BOMB"; }
        case Type::GOODS:         { return "GOODS"; }
        case Type::PLAYER:         { return "PLAYER"; }
        case Type::KOSMOPORT:     { return "KOSMOPORT"; }
        case Type::NATURELAND:     { return "NATURELAND"; }

        case Type::GOVERMENT:     { return "GOVERMENT"; }
        case Type::STORE:         { return "STORE"; }
        case Type::SHOP:         { return "SHOP"; }
        case Type::ANGAR:         { return "ANGAR"; }
        
        case Type::VEHICLE_SLOT:             { return "VEHICLE_SLOT"; }
        case Type::VEHICLE_MILITARY_SLOT:     { return "VEHICLE_MILITARY_SLOT"; }
        case Type::VEHICLE_VISITORS_SLOT:     { return "VEHICLE_VISITORS_SLOT"; }
        
        case Type::GATE_SLOT:         { return "GATE_SLOT"; }
        case Type::REPAIR_SLOT:         { return "REPAIR_SLOT"; }

//        case Type::WEAPON1_SLOT:     { return "WEAPON1_SLOT"; }
//        case Type::WEAPON2_SLOT:     { return "WEAPON2_SLOT"; }
//        case Type::WEAPON3_SLOT:     { return "WEAPON3_SLOT"; }
//        case Type::WEAPON4_SLOT:     { return "WEAPON4_SLOT"; }
//        case Type::WEAPON5_SLOT:     { return "WEAPON5_SLOT"; }
//        case Type::WEAPON6_SLOT:     { return "WEAPON6_SLOT"; }
//        case Type::WEAPON7_SLOT:     { return "WEAPON7_SLOT"; }
//        case Type::WEAPON8_SLOT:     { return "WEAPON8_SLOT"; }
//        case Type::WEAPON9_SLOT:     { return "WEAPON9_SLOT"; }
        

        case Type::EQUIPMENT:         { return "EQUIPMENT"; }
        case Type::MODULE:             { return "MODULE"; }
        case Type::ARTEFACT:         { return "ARTEFACT"; }
                                                                                                
        case Type::LAZER_EQUIPMENT:     { return "LAZER_EQUIPMENT"; }
        case Type::ROCKET_EQUIPMENT: { return "ROCKET_EQUIPMENT"; }
        case Type::DRIVE_EQUIPMENT:     { return "DRIVE_EQUIPMENT"; }
        case Type::RADAR_EQUIPMENT:     { return "RADAR_EQUIPMENT"; }
        case Type::BAK_EQUIPMENT:     { return "BAK_EQUIPMENT"; }
        case Type::ENERGIZER_EQUIPMENT:     { return "ENERGIZER_EQUIPMENT"; }
        case Type::PROTECTOR_EQUIPMENT:     { return "PROTECTOR_EQUIPMENT"; }
        case Type::DROID_EQUIPMENT:         { return "DROID_EQUIPMENT"; }
        case Type::FREEZER_EQUIPMENT:     { return "FREEZER_EQUIPMENT"; }
        case Type::GRAPPLE_EQUIPMENT:     { return "GRAPPLE_EQUIPMENT"; }
        case Type::SCANER_EQUIPMENT:     { return "SCANER_EQUIPMENT"; }

        case Type::LAZER_MODULE:     { return "LAZER_MODULE"; }
        case Type::ROCKET_MODULE:     { return "ROCKET_MODULE"; }
        case Type::DRIVE_MODULE:     { return "DRIVE_MODULE"; }
        case Type::RADAR_MODULE:     { return "RADAR_MODULE"; }
        case Type::BAK_MODULE:         { return "BAK_MODULE"; }
        case Type::ENERGIZER_MODULE: { return "ENERGIZER_MODULE"; }
        case Type::PROTECTOR_MODULE: { return "PROTECTOR_MODULE"; }
        case Type::DROID_MODULE:     { return "DROID_MODULE"; }
        case Type::FREEZER_MODULE:     { return "FREEZER_MODULE"; }
        case Type::GRAPPLE_MODULE:     { return "GRAPPLE_MODULE"; }
        case Type::SCANER_MODULE:     { return "SCANER_MODULE"; }
        
        case Type::GRAVITY_ARTEFACT:     { return "GRAVITY_ARTEFACT"; }
        case Type::PROTECTOR_ARTEFACT:     { return "PROTECTOR_ARTEFACT"; }

        case Type::RANGER:     { return "RANGER"; }
        case Type::WARRIOR:     { return "WARRIOR"; }
        case Type::PIRAT:     { return "PIRAT"; }
        case Type::TRADER:     { return "TRADER"; }
        case Type::DIPLOMAT: { return "DIPLOMAT"; }

        case Type::SECTOR: { return "SECTOR"; }
    }

    assert(false);
    return "UNDEFINED";
}

} // namespace entity
