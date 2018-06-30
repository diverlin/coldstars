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
    case Type::NONE: { return "telegram::Type::NONE"; }

        /** CREATE */
    case Type::CREATE_GALAXY: { return "telegram::Type::CREATE_GALAXY"; }
    case Type::CREATE_SECTOR: { return "telegram::Type::CREATE_SECTOR"; }
    case Type::CREATE_STARSYSTEM: { return "telegram::Type::CREATE_STARSYSTEM"; }
//    case Type::CREATE_PLAYER: { return "telegram::Type::CREATE_PLAYER"; }
    case Type::CREATE_NPC: { return "telegram::Type::CREATE_NPC"; }

        // spaceobjects
    case Type::CREATE_STAR: { return "telegram::Type::CREATE_STAR"; }
    case Type::CREATE_PLANET: { return "telegram::Type::CREATE_PLANET"; }
    case Type::CREATE_ASTEROID: { return "telegram::Type::CREATE_ASTEROID"; }
    case Type::CREATE_SHIP: { return "telegram::Type::CREATE_SHIP"; }
    case Type::CREATE_BOMB: { return "telegram::Type::CREATE_BOMB"; }
    case Type::CREATE_GOODS: { return "telegram::Type::CREATE_GOODS"; }
    case Type::CREATE_CONTAINER: { return "telegram::Type::CREATE_CONTAINER"; }
    case Type::CREATE_BULLET: { return "telegram::Type::CREATE_BULLET"; }

        // items
    case Type::CREATE_BAK: { return "telegram::Type::CREATE_BAK"; }
    case Type::CREATE_DRIVE: { return "telegram::Type::CREATE_DRIVE"; }
    case Type::CREATE_DROID: { return "telegram::Type::CREATE_DROID"; }
    case Type::CREATE_GRAPPLE: { return "telegram::Type::CREATE_GRAPPLE"; }
    case Type::CREATE_SCANER: { return "telegram::Type::CREATE_SCANER"; }
    case Type::CREATE_RADAR: { return "telegram::Type::CREATE_RADAR"; }
    case Type::CREATE_PROTECTOR: { return "telegram::Type::CREATE_PROTECTOR"; }
    case Type::CREATE_LAZER: { return "telegram::Type::CREATE_LAZER"; }
    case Type::CREATE_ROCKET: { return "telegram::Type::CREATE_ROCKET"; }

        // effects
    case Type::CREATE_EXPLOSION_EFFECT: { return "telegram::Type::CREATE_EXPLOSION_EFFECT"; }
        /** */

        /** DOCK */
    case Type::DOCK_SHIP: { return "telegram::Type::DOCK_SHIP"; }
    case Type::LAUNCH_SHIP: { return "telegram::Type::LAUNCH_SHIP"; }

        /** JUMP */
    case Type::JUMP_IN: { return "telegram::Type::JUMP_IN"; }
    case Type::JUMP_OUT: { return "telegram::Type::JUMP_OUT"; }

        /** DROP_GRAB */
    case Type::DROP_ITEM: { return "telegram::Type::DROP_ITEM"; }
    case Type::TAKE_CONTAINER: { return "telegram::Type::TAKE_CONTAINER"; }
    case Type::LOAD_ITEM: { return "telegram::Type::LOAD_ITEM"; }
    case Type::MOUNT_ITEM: { return "telegram::Type::MOUNT_ITEM"; }

        /** TRANSITION */
    case Type::ADD_SECTOR_TO_GALAXY: { return "telegram::Type::ADD_SECTOR_TO_GALAXY"; }
    case Type::ADD_STARSYSTEM_TO_SECTOR: { return "telegram::Type::ADD_STARSYSTEM_TO_SECTOR"; }
    case Type::ADD_STAR_TO_STARSYSTEM: { return "telegram::Type::ADD_STAR_TO_STARSYSTEM"; }
    case Type::ADD_PLANET_TO_STARSYSTEM: { return "telegram::Type::ADD_PLANET_TO_STARSYSTEM"; }
    case Type::ADD_ASTEROID_TO_STARSYSTEM: { return "telegram::Type::ADD_ASTEROID_TO_STARSYSTEM"; }
    case Type::ADD_SHIP_TO_STARSYSTEM: { return "telegram::Type::ADD_SHIP_TO_STARSYSTEM"; }
    case Type::ADD_CONTAINER_TO_STARSYSTEM: { return "telegram::Type::ADD_CONTAINER_TO_STARSYSTEM"; }
    case Type::ADD_NPC_TO_SHIP: { return "telegram::Type::ADD_NPC_TO_SHIP"; }
    case Type::INSERT: { return "telegram::Type::INSERT"; }
    case Type::REMOVE_SPACEOBJECT_FROM_STARSYSTEM: { return "telegram::Type::REMOVE_SPACEOBJECT_FROM_STARSYSTEM"; }
    case Type::REMOVE: { return "telegram::Type::REMOVE"; }
    case Type::DELETE: { return "telegram::Type::DELETE"; }
        /** */

    case Type::HIT: { return "telegram::Type::HIT"; }

    case Type::ADD_SPACEOBJECT_TO_GARBAGE: { return "telegram::Type::ADD_SPACEOBJECT_TO_GARBAGE"; }


        // MOVE
    case Type::MOVE_VEHICLE: { return "telegram::Type::MOVE_VEHICLE"; }

        // shoot
    case Type::VEHICLE_TARGET_SPACEOBJECT: { return "telegram::Type::TARGET_SPACEOBJECT"; }

        // GAME STATE
    case Type::END_TURN: { return "telegram::Type::END_TURN"; }

        // CLIENT
    case Type::PLAYER_REQUEST_MOVE: { return "telegram::Type::PLAYER_REQUEST_MOVE"; }
    case Type::PLAYER_REQUEST_END_TURN: { return "telegram::Type::PLAYER_REQUEST_END_TURN"; }
    case Type::PLAYER_REQUEST_TARGET_SPACE_OBJECT: { return "telegram::Type::PLAYER_REQUEST_TARGET_SPACE_OBJECT"; }
    case Type::PLAYER_REQUEST_CREATE_NPC: { return "telegram::Type::PLAYER_REQUEST_CREATE_NPC"; }
    case Type::PLAYER_REQUEST_CREATE_SHIP: { return "telegram::Type::PLAYER_REQUEST_CREATE_SHIP"; }
    case Type::PLAYER_REQUEST_BIND_NPC: { return "telegram::Type::PLAYER_REQUEST_BIND_NPC"; }
    case Type::PLAYER_REQUEST_INSERT_NPC_TO_SHIP: { return "telegram::Type::PLAYER_REQUEST_INSERT_NPC_TO_SHIP"; }

    case Type::REPLY_PLAYER_CREATE_NPC: { return "telegram::Type::REPLY_PLAYER_CREATE_NPC"; }
    case Type::REPLY_PLAYER_CREATE_SHIP: { return "telegram::Type::REPLY_PLAYER_CREATE_SHIP"; }
    case Type::REPLY_PLAYER_BIND_NPC: { return "telegram::Type::REPLY_PLAYER_BIND_NPC"; }
    case Type::REPLY_PLAYER_INSERT_NPC_TO_SHIP: { return "telegram::Type::REPLY_PLAYER_INSERT_NPC_TO_SHIP"; }

    default: {
        assert(false);
        return "entity::Type::UNKNOWN type"; }
    }
}

} // namespace telegram
