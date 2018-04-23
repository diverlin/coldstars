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

#include <string>

namespace telegram {

enum class Type : int
{
    NONE,
    /** CREATE */
    CREATE_GALAXY,
    CREATE_SECTOR,
    CREATE_STARSYSTEM,
    CREATE_PLAYER,
    CREATE_NPC,
    // spaceobjects
    CREATE_STAR,
    CREATE_PLANET,
    CREATE_ASTEROID,
    CREATE_SHIP,
    CREATE_BOMB,
    CREATE_GOODS,
    CREATE_CONTAINER,
    CREATE_BULLET,
    // items
    CREATE_BAK,
    CREATE_DRIVE,
    CREATE_DROID,
    CREATE_GRAPPLE,
    CREATE_SCANER,
    CREATE_RADAR,
    CREATE_PROTECTOR,
    CREATE_LAZER,
    CREATE_ROCKET,
    // effects
    CREATE_EXPLOSION_EFFECT,
    /** */

    /** DOCK */
    DOCK_SHIP,
    LAUNCH_SHIP,

    /** JUMP */
    JUMP_IN,
    JUMP_OUT,

    /** DROP_GRAB */
    DROP_ITEM,
    TAKE_CONTAINER,
    LOAD_ITEM,
    MOUNT_ITEM,

    /** TRANSITION */
    ADD_SECTOR_TO_GALAXY,
    ADD_STARSYSTEM_TO_SECTOR,
    ADD_STAR_TO_STARSYSTEM,
    ADD_PLANET_TO_STARSYSTEM,
    ADD_ASTEROID_TO_STARSYSTEM,
    ADD_SHIP_TO_STARSYSTEM,
    ADD_CONTAINER_TO_STARSYSTEM,
    ADD_NPC_TO_SHIP,
    INSERT,
    REMOVE_SPACEOBJECT_FROM_STARSYSTEM,
    REMOVE,
    DELETE,
    /** */

    HIT,

    ADD_SPACEOBJECT_TO_GARBAGE,


    // MOVE
    MOVE_VEHICLE,

    // shoot
    VEHICLE_TARGET_SPACEOBJECT,

    // GAME STATE
    END_TURN,

    // CLIENT
    PLAYER_REQUEST_MOVE,
    PLAYER_REQUEST_END_TURN,
    PLAYER_REQUEST_TARGET_SPACE_OBJECT,
    PLAYER_REQUEST_CREATE_NPC,
    PLAYER_REQUEST_BIND_NPC,
    PLAYER_REQUEST_BIND_NPC_AND_SHIP
};

std::string to_string(Type);

} // namespace telegram
