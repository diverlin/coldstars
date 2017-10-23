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

#include "TelegramType.hpp"

#include <cassert>

namespace telegram {

std::string to_string(Type type)
{
    switch(type) {
    case Type::NONE: { return "telegramm::Type::NONE"; }

        /** CREATE */
    case Type::CREATE_GALAXY: { return "telegramm::Type::CREATE_GALAXY"; }
    case Type::CREATE_SECTOR: { return "telegramm::Type::CREATE_SECTOR"; }
    case Type::CREATE_STARSYSTEM: { return "telegramm::Type::CREATE_STARSYSTEM"; }
    case Type::CREATE_PLAYER: { return "telegramm::Type::CREATE_PLAYER"; }
    case Type::CREATE_NPC: { return "telegramm::Type::CREATE_NPC"; }

        // spaceobjects
    case Type::CREATE_STAR: { return "telegramm::Type::CREATE_STAR"; }
    case Type::CREATE_PLANET: { return "telegramm::Type::CREATE_PLANET"; }
    case Type::CREATE_ASTEROID: { return "telegramm::Type::CREATE_ASTEROID"; }
    case Type::CREATE_SHIP: { return "telegramm::Type::CREATE_SHIP"; }
    case Type::CREATE_BOMB: { return "telegramm::Type::CREATE_BOMB"; }
    case Type::CREATE_GOODS: { return "telegramm::Type::CREATE_GOODS"; }
    case Type::CREATE_CONTAINER: { return "telegramm::Type::CREATE_CONTAINER"; }
    case Type::CREATE_BULLET: { return "telegramm::Type::CREATE_BULLET"; }

        // items
    case Type::CREATE_BAK: { return "telegramm::Type::CREATE_BAK"; }
    case Type::CREATE_DRIVE: { return "telegramm::Type::CREATE_DRIVE"; }
    case Type::CREATE_DROID: { return "telegramm::Type::CREATE_DROID"; }
    case Type::CREATE_GRAPPLE: { return "telegramm::Type::CREATE_GRAPPLE"; }
    case Type::CREATE_SCANER: { return "telegramm::Type::CREATE_SCANER"; }
    case Type::CREATE_RADAR: { return "telegramm::Type::CREATE_RADAR"; }
    case Type::CREATE_PROTECTOR: { return "telegramm::Type::CREATE_PROTECTOR"; }
    case Type::CREATE_LAZER: { return "telegramm::Type::CREATE_LAZER"; }
    case Type::CREATE_ROCKET: { return "telegramm::Type::CREATE_ROCKET"; }

        // effects
    case Type::CREATE_EXPLOSION_EFFECT: { return "telegramm::Type::CREATE_EXPLOSION_EFFECT"; }
        /** */

        /** DOCK */
    case Type::DOCK_SHIP: { return "telegramm::Type::DOCK_SHIP"; }
    case Type::LAUNCH_SHIP: { return "telegramm::Type::LAUNCH_SHIP"; }

        /** JUMP */
    case Type::JUMP_IN: { return "telegramm::Type::JUMP_IN"; }
    case Type::JUMP_OUT: { return "telegramm::Type::JUMP_OUT"; }

        /** DROP_GRAB */
    case Type::DROP_ITEM: { return "telegramm::Type::DROP_ITEM"; }
    case Type::TAKE_CONTAINER: { return "telegramm::Type::TAKE_CONTAINER"; }
    case Type::LOAD_ITEM: { return "telegramm::Type::LOAD_ITEM"; }
    case Type::MOUNT_ITEM: { return "telegramm::Type::MOUNT_ITEM"; }

        /** TRANSITION */
    case Type::ADD_SECTOR_TO_GALAXY: { return "telegramm::Type::ADD_SECTOR_TO_GALAXY"; }
    case Type::ADD_STARSYSTEM_TO_SECTOR: { return "telegramm::Type::ADD_STARSYSTEM_TO_SECTOR"; }
    case Type::ADD_STAR_TO_STARSYSTEM: { return "telegramm::Type::ADD_STAR_TO_STARSYSTEM"; }
    case Type::ADD_PLANET_TO_STARSYSTEM: { return "telegramm::Type::ADD_PLANET_TO_STARSYSTEM"; }
    case Type::ADD_ASTEROID_TO_STARSYSTEM: { return "telegramm::Type::ADD_ASTEROID_TO_STARSYSTEM"; }
    case Type::ADD_SHIP_TO_STARSYSTEM: { return "telegramm::Type::ADD_SHIP_TO_STARSYSTEM"; }
    case Type::ADD_CONTAINER_TO_STARSYSTEM: { return "telegramm::Type::ADD_CONTAINER_TO_STARSYSTEM"; }
    case Type::ADD_NPC_TO_SHIP: { return "telegramm::Type::ADD_NPC_TO_SHIP"; }
    case Type::INSERT: { return "telegramm::Type::INSERT"; }
    case Type::REMOVE_SPACEOBJECT_FROM_STARSYSTEM: { return "telegramm::Type::REMOVE_SPACEOBJECT_FROM_STARSYSTEM"; }
    case Type::REMOVE: { return "telegramm::Type::REMOVE"; }
    case Type::DELETE: { return "telegramm::Type::DELETE"; }
        /** */

    case Type::HIT: { return "telegramm::Type::HIT"; }

    case Type::ADD_SPACEOBJECT_TO_GARBAGE: { return "telegramm::Type::ADD_SPACEOBJECT_TO_GARBAGE"; }


    default: {
        assert(false);
        return "entity::Type::UNKNOWN type"; }
    }
}

} // namespace telegramm
