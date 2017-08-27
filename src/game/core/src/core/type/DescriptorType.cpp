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

namespace descriptor {

std::string to_string(Type type)
{
    switch(type)
    {
        case Type::NONE: { return "descriptor::Type::NONE"; }

        // world
        case Type::GALAXY:         { return "descriptor::Type::GALAXY";  }
        case Type::STARSYSTEM:     { return "descriptor::Type::STARSYSTEM"; }
        case Type::SECTOR:     { return "descriptor::Type::SECTOR"; }

        // pilots
        case Type::NPC:             { return "descriptor::Type::NPC"; }

        // space object
        case Type::STAR:         { return "descriptor::Type::STAR"; }
        case Type::ASTEROID:     { return "descriptor::Type::ASTEROID"; }
        case Type::PLANET:         { return "descriptor::Type::PLANET"; }
        case Type::WORMHOLE:     { return "descriptor::Type::BLACKHOLE"; }
        case Type::SHIP:         { return "descriptor::Type::SHIP"; }
        case Type::SPACESTATION: { return "descriptor::Type::SPACESTATION"; }
        case Type::SATELLITE:     { return "descriptor::Type::SATELLITE"; }
        case Type::CONTAINER:     { return "descriptor::Type::CONTAINER"; }
        case Type::BULLET:     { return "descriptor::Type::BULLET"; }

        // equipment
        case Type::LAZER_EQUIPMENT:     { return "descriptor::Type::LAZER_EQUIPMENT"; }
        case Type::ROCKET_EQUIPMENT: { return "descriptor::Type::ROCKET_EQUIPMENT"; }
        case Type::DRIVE_EQUIPMENT:     { return "descriptor::Type::DRIVE_EQUIPMENT"; }
        case Type::RADAR_EQUIPMENT:     { return "descriptor::Type::RADAR_EQUIPMENT"; }
        case Type::BAK_EQUIPMENT:     { return "descriptor::Type::BAK_EQUIPMENT"; }
        case Type::ENERGIZER_EQUIPMENT:     { return "descriptor::Type::ENERGIZER_EQUIPMENT"; }
        case Type::PROTECTOR_EQUIPMENT:     { return "descriptor::Type::PROTECTOR_EQUIPMENT"; }
        case Type::DROID_EQUIPMENT:         { return "descriptor::Type::DROID_EQUIPMENT"; }
        case Type::FREEZER_EQUIPMENT:     { return "descriptor::Type::FREEZER_EQUIPMENT"; }
        case Type::GRAPPLE_EQUIPMENT:     { return "descriptor::Type::GRAPPLE_EQUIPMENT"; }
        case Type::SCANER_EQUIPMENT:     { return "descriptor::Type::SCANER_EQUIPMENT"; }

        // module
        case Type::LAZER_MODULE:     { return "descriptor::Type::LAZER_MODULE"; }
        case Type::ROCKET_MODULE:     { return "descriptor::Type::ROCKET_MODULE"; }
        case Type::DRIVE_MODULE:     { return "descriptor::Type::DRIVE_MODULE"; }
        case Type::RADAR_MODULE:     { return "descriptor::Type::RADAR_MODULE"; }
        case Type::BAK_MODULE:         { return "descriptor::Type::BAK_MODULE"; }
        case Type::ENERGIZER_MODULE: { return "descriptor::Type::ENERGIZER_MODULE"; }
        case Type::PROTECTOR_MODULE: { return "descriptor::Type::PROTECTOR_MODULE"; }
        case Type::DROID_MODULE:     { return "descriptor::Type::DROID_MODULE"; }
        case Type::FREEZER_MODULE:     { return "descriptor::Type::FREEZER_MODULE"; }
        case Type::GRAPPLE_MODULE:     { return "descriptor::Type::GRAPPLE_MODULE"; }
        case Type::SCANER_MODULE:     { return "descriptor::Type::SCANER_MODULE"; }
        
        // artefact
        case Type::GRAVITY_ARTEFACT:     { return "descriptor::Type::GRAVITY_ARTEFACT"; }
        case Type::PROTECTOR_ARTEFACT:     { return "descriptor::Type::PROTECTOR_ARTEFACT"; }

        // other
        case Type::HIT:     { return "descriptor::Type::HIT"; }

        default: {
        assert(false);
        return "descriptor::Type is unknown, fixme"; }
    }
}

} // namespace descriptor
