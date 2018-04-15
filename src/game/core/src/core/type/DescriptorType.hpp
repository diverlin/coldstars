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

namespace core {

enum class Type {
    NONE=0,
    /** */

    // world
    GALAXY,
    SECTOR,
    STARSYSTEM,
    HYPERSPACE,

    // pilot
    NPC,

    // space object
    STAR,
    ASTEROID,
    PLANET,
    WORMHOLE,
    SHIP,
    SPACESTATION,
    SATELLITE,
    CONTAINER,
    BULLET,

    /// items
    // other
    GOODS,

    // equipment
    LAZER_EQUIPMENT,
    ROCKET_EQUIPMENT,
    DRIVE_EQUIPMENT,
    RADAR_EQUIPMENT,
    BAK_EQUIPMENT,
    ENERGIZER_EQUIPMENT,
    PROTECTOR_EQUIPMENT,
    DROID_EQUIPMENT,
    FREEZER_EQUIPMENT,
    GRAPPLE_EQUIPMENT,
    SCANER_EQUIPMENT,

    // module
    LAZER_MODULE,
    ROCKET_MODULE,
    DRIVE_MODULE,
    RADAR_MODULE,
    BAK_MODULE,
    ENERGIZER_MODULE,
    PROTECTOR_MODULE,
    DROID_MODULE,
    FREEZER_MODULE,
    GRAPPLE_MODULE,
    SCANER_MODULE,
    
    // dock
    KOSMOPORT,
    NATURELAND,
    ANGAR,
    SHOP,
    STORE,
    GOVERMENT,

    // artefact
    GRAVITY_ARTEFACT,
    PROTECTOR_ARTEFACT,

    // other
    HIT,

    // resources
    MESH,
    MATERIAL,

    // parts
    TURREL,

    /** */
    ANY
};

std::string to_string(Type);

} // namespace core


