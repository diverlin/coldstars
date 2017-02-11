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

enum class TELEGRAM : int 
{
    NONE,
    /** CREATE */
    CREATE_STARSYSTEM,
    CREATE_SHIP,
    CREATE_BOMB,
    CREATE_CONTAINER,
    // equipment
    CREATE_BAK,
    CREATE_DRIVE,
    CREATE_DROID,
    CREATE_GRAPPLE,
    CREATE_SCANER,
    CREATE_RADAR,
    CREATE_PROTECTOR,
    /** */

    /** TRANSITION */
    STARSYSTEM_ADD_SHIP,
    STARSYSTEM_ADD_CONTAINER,
    INSERT,
    REMOVE,
    DELETE,
    /** */

    HIT,
    EXPLOSION
};

std::string to_string(const TELEGRAM&);


