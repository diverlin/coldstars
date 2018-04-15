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
        case Type::NONE: { return "entity::Type::NONE"; }
            
        case Type::VEHICLE:         { return "entity::Type::VEHICLE"; }
        case Type::SHIP:         { return "entity::Type::SHIP"; }
        case Type::SPACESTATION: { return "entity::Type::SPACESTATION"; }
        case Type::SATELLITE:     { return "entity::Type::SATELLITE"; }
        case Type::NPC:             { return "entity::Type::NPC"; }
        case Type::BULLET:         { return "entity::Type::BULLET"; }
        case Type::Bullet: { return "entity::Type::Bullet"; }
        case Type::MINERALS:     { return "entity::Type::MINERALS"; }
        case Type::FOOD:         { return "entity::Type::FOOD"; }
        case Type::MEDICINE:     { return "entity::Type::MEDICINE"; }
        case Type::MILITARY:     { return "entity::Type::MILITARY"; }
        case Type::DRUG:         { return "entity::Type::DRUG"; }
        case Type::EXCLUSIVE:     { return "entity::Type::EXCLUSIVE"; }
        case Type::CONTAINER:     { return "entity::Type::CONTAINER"; }
        case Type::GALAXY:         { return "entity::Type::GALAXY"; }
        case Type::STARSYSTEM:     { return "entity::Type::STARSYSTEM"; }
        case Type::STAR:         { return "entity::Type::STAR"; }
        case Type::ASTEROID:     { return "entity::Type::ASTEROID"; }
        case Type::PLANET:         { return "entity::Type::PLANET"; }
        case Type::WORMHOLE:     { return "entity::Type::WORMHOLE"; }
        case Type::BOMB:         { return "entity::Type::BOMB"; }
        case Type::GOODS:         { return "entity::Type::GOODS"; }
        case Type::PLAYER:         { return "entity::Type::PLAYER"; }
        case Type::KOSMOPORT:     { return "entity::Type::KOSMOPORT"; }
        case Type::NATURELAND:     { return "entity::Type::NATURELAND"; }

        case Type::GOVERMENT:     { return "entity::Type::GOVERMENT"; }
        case Type::STORE:         { return "entity::Type::STORE"; }
        case Type::SHOP:         { return "entity::Type::SHOP"; }
        case Type::ANGAR:         { return "entity::Type::ANGAR"; }
        
        case Type::VEHICLE_SLOT:             { return "entity::Type::VEHICLE_SLOT"; }
        case Type::VEHICLE_MILITARY_SLOT:     { return "entity::Type::VEHICLE_MILITARY_SLOT"; }
        case Type::VEHICLE_VISITORS_SLOT:     { return "entity::Type::VEHICLE_VISITORS_SLOT"; }
        
        case Type::GATE_SLOT:         { return "entity::Type::GATE_SLOT"; }
        case Type::REPAIR_SLOT:         { return "entity::Type::REPAIR_SLOT"; }

//        case Type::WEAPON1_SLOT:     { return "entity::Type::WEAPON1_SLOT"; }
//        case Type::WEAPON2_SLOT:     { return "entity::Type::WEAPON2_SLOT"; }
//        case Type::WEAPON3_SLOT:     { return "entity::Type::WEAPON3_SLOT"; }
//        case Type::WEAPON4_SLOT:     { return "entity::Type::WEAPON4_SLOT"; }
//        case Type::WEAPON5_SLOT:     { return "entity::Type::WEAPON5_SLOT"; }
//        case Type::WEAPON6_SLOT:     { return "entity::Type::WEAPON6_SLOT"; }
//        case Type::WEAPON7_SLOT:     { return "entity::Type::WEAPON7_SLOT"; }
//        case Type::WEAPON8_SLOT:     { return "entity::Type::WEAPON8_SLOT"; }
//        case Type::WEAPON9_SLOT:     { return "entity::Type::WEAPON9_SLOT"; }
        

        case Type::EQUIPMENT:         { return "entity::Type::EQUIPMENT"; }
        case Type::MODULE:             { return "entity::Type::MODULE"; }
        case Type::ARTEFACT:         { return "entity::Type::ARTEFACT"; }
                                                                                                
        case Type::LAZER_EQUIPMENT:     { return "entity::Type::LAZER_EQUIPMENT"; }
        case Type::ROCKET_EQUIPMENT: { return "entity::Type::ROCKET_EQUIPMENT"; }
        case Type::DRIVE_EQUIPMENT:     { return "entity::Type::DRIVE_EQUIPMENT"; }
        case Type::RADAR_EQUIPMENT:     { return "entity::Type::RADAR_EQUIPMENT"; }
        case Type::BAK_EQUIPMENT:     { return "entity::Type::BAK_EQUIPMENT"; }
        case Type::ENERGIZER_EQUIPMENT:     { return "entity::Type::ENERGIZER_EQUIPMENT"; }
        case Type::PROTECTOR_EQUIPMENT:     { return "entity::Type::PROTECTOR_EQUIPMENT"; }
        case Type::DROID_EQUIPMENT:         { return "entity::Type::DROID_EQUIPMENT"; }
        case Type::FREEZER_EQUIPMENT:     { return "entity::Type::FREEZER_EQUIPMENT"; }
        case Type::GRAPPLE_EQUIPMENT:     { return "entity::Type::GRAPPLE_EQUIPMENT"; }
        case Type::SCANER_EQUIPMENT:     { return "entity::Type::SCANER_EQUIPMENT"; }

        case Type::LAZER_MODULE:     { return "entity::Type::LAZER_MODULE"; }
        case Type::ROCKET_MODULE:     { return "entity::Type::ROCKET_MODULE"; }
        case Type::DRIVE_MODULE:     { return "entity::Type::DRIVE_MODULE"; }
        case Type::RADAR_MODULE:     { return "entity::Type::RADAR_MODULE"; }
        case Type::BAK_MODULE:         { return "entity::Type::BAK_MODULE"; }
        case Type::ENERGIZER_MODULE: { return "entity::Type::ENERGIZER_MODULE"; }
        case Type::PROTECTOR_MODULE: { return "entity::Type::PROTECTOR_MODULE"; }
        case Type::DROID_MODULE:     { return "entity::Type::DROID_MODULE"; }
        case Type::FREEZER_MODULE:     { return "entity::Type::FREEZER_MODULE"; }
        case Type::GRAPPLE_MODULE:     { return "entity::Type::GRAPPLE_MODULE"; }
        case Type::SCANER_MODULE:     { return "entity::Type::SCANER_MODULE"; }
        
        case Type::GRAVITY_ARTEFACT:     { return "entity::Type::GRAVITY_ARTEFACT"; }
        case Type::PROTECTOR_ARTEFACT:     { return "entity::Type::PROTECTOR_ARTEFACT"; }

        case Type::RANGER:     { return "entity::Type::RANGER"; }
        case Type::WARRIOR:     { return "entity::Type::WARRIOR"; }
        case Type::PIRAT:     { return "entity::Type::PIRAT"; }
        case Type::TRADER:     { return "entity::Type::TRADER"; }
        case Type::DIPLOMAT: { return "entity::Type::DIPLOMAT"; }
    }

    assert(false);
    return "UNDEFINED";
}

} // namespace entity
