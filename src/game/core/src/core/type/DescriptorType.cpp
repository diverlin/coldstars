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

#include "DescriptorType.hpp"

#include <cassert>

namespace core {

std::string to_string(Type type)
{
    switch(type)
    {
        case Type::NONE: { return "Type::NONE"; }

        // world
        case Type::GALAXY:         { return "Type::GALAXY";  }
        case Type::STARSYSTEM:     { return "Type::STARSYSTEM"; }

        // pilots
        case Type::NPC:             { return "Type::NPC"; }

        // space object
        case Type::STAR:         { return "Type::STAR"; }
        case Type::ASTEROID:     { return "Type::ASTEROID"; }
        case Type::PLANET:         { return "Type::PLANET"; }
        case Type::WORMHOLE:     { return "Type::BLACKHOLE"; }
        case Type::SHIP:         { return "Type::SHIP"; }
        case Type::SPACESTATION: { return "Type::SPACESTATION"; }
        case Type::SATELLITE:     { return "Type::SATELLITE"; }
        case Type::CONTAINER:     { return "Type::CONTAINER"; }
        case Type::BULLET:     { return "Type::BULLET"; }

        // equipment
        case Type::LAZER_EQUIPMENT:     { return "Type::LAZER_EQUIPMENT"; }
        case Type::ROCKET_EQUIPMENT: { return "Type::ROCKET_EQUIPMENT"; }
        case Type::DRIVE_EQUIPMENT:     { return "Type::DRIVE_EQUIPMENT"; }
        case Type::RADAR_EQUIPMENT:     { return "Type::RADAR_EQUIPMENT"; }
        case Type::BAK_EQUIPMENT:     { return "Type::BAK_EQUIPMENT"; }
        case Type::ENERGIZER_EQUIPMENT:     { return "Type::ENERGIZER_EQUIPMENT"; }
        case Type::PROTECTOR_EQUIPMENT:     { return "Type::PROTECTOR_EQUIPMENT"; }
        case Type::DROID_EQUIPMENT:         { return "Type::DROID_EQUIPMENT"; }
        case Type::FREEZER_EQUIPMENT:     { return "Type::FREEZER_EQUIPMENT"; }
        case Type::GRAPPLE_EQUIPMENT:     { return "Type::GRAPPLE_EQUIPMENT"; }
        case Type::SCANER_EQUIPMENT:     { return "Type::SCANER_EQUIPMENT"; }

        // module
        case Type::LAZER_MODULE:     { return "Type::LAZER_MODULE"; }
        case Type::ROCKET_MODULE:     { return "Type::ROCKET_MODULE"; }
        case Type::DRIVE_MODULE:     { return "Type::DRIVE_MODULE"; }
        case Type::RADAR_MODULE:     { return "Type::RADAR_MODULE"; }
        case Type::BAK_MODULE:         { return "Type::BAK_MODULE"; }
        case Type::ENERGIZER_MODULE: { return "Type::ENERGIZER_MODULE"; }
        case Type::PROTECTOR_MODULE: { return "Type::PROTECTOR_MODULE"; }
        case Type::DROID_MODULE:     { return "Type::DROID_MODULE"; }
        case Type::FREEZER_MODULE:     { return "Type::FREEZER_MODULE"; }
        case Type::GRAPPLE_MODULE:     { return "Type::GRAPPLE_MODULE"; }
        case Type::SCANER_MODULE:     { return "Type::SCANER_MODULE"; }

//        case Type::GOODS:     { return "Type::GOODS"; }

        // artefact
        case Type::GRAVITY_ARTEFACT:     { return "Type::GRAVITY_ARTEFACT"; }
        case Type::PROTECTOR_ARTEFACT:     { return "Type::PROTECTOR_ARTEFACT"; }

        // other
        case Type::HIT:     { return "Type::HIT"; }

        default: {
        assert(false);
        return "Type is unknown, fixme"; }
    }
}

} // namespace core
