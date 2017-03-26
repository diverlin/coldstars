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

std::string to_string(descriptor::Type type)
{
    switch(type)
    {
        case descriptor::Type::NONE: { return "descriptor::Type::NONE"; break; }

        // world
        case descriptor::Type::GALAXY:         { return "descriptor::Type::GALAXY"; break; }
        case descriptor::Type::STARSYSTEM:     { return "descriptor::Type::STARSYSTEM"; break; }
        case descriptor::Type::SECTOR:     { return "descriptor::Type::SECTOR"; break; }

        // pilots
        case descriptor::Type::NPC:             { return "descriptor::Type::NPC"; break; }

        // space object
        case descriptor::Type::STAR:         { return "descriptor::Type::STAR"; break; }
        case descriptor::Type::ASTEROID:     { return "descriptor::Type::ASTEROID"; break; }
        case descriptor::Type::PLANET:         { return "descriptor::Type::PLANET"; break; }
        case descriptor::Type::WORMHOLE:     { return "descriptor::Type::BLACKHOLE"; break; }
        case descriptor::Type::SHIP:         { return "descriptor::Type::SHIP"; break; }
        case descriptor::Type::SPACESTATION: { return "descriptor::Type::SPACESTATION"; break; }
        case descriptor::Type::SATELLITE:     { return "descriptor::Type::SATELLITE"; break; }
        case descriptor::Type::CONTAINER:     { return "descriptor::Type::CONTAINER"; break; }

        // equipment
        case descriptor::Type::LAZER_EQUIPMENT:     { return "descriptor::Type::LAZER_EQUIPMENT"; break; }
        case descriptor::Type::ROCKET_EQUIPMENT: { return "descriptor::Type::ROCKET_EQUIPMENT"; break; }
        case descriptor::Type::DRIVE_EQUIPMENT:     { return "descriptor::Type::DRIVE_EQUIPMENT"; break; }
        case descriptor::Type::RADAR_EQUIPMENT:     { return "descriptor::Type::RADAR_EQUIPMENT"; break; }
        case descriptor::Type::BAK_EQUIPMENT:     { return "descriptor::Type::BAK_EQUIPMENT"; break; }
        case descriptor::Type::ENERGIZER_EQUIPMENT:     { return "descriptor::Type::ENERGIZER_EQUIPMENT"; break; }
        case descriptor::Type::PROTECTOR_EQUIPMENT:     { return "descriptor::Type::PROTECTOR_EQUIPMENT"; break; }
        case descriptor::Type::DROID_EQUIPMENT:         { return "descriptor::Type::DROID_EQUIPMENT"; break; }
        case descriptor::Type::FREEZER_EQUIPMENT:     { return "descriptor::Type::FREEZER_EQUIPMENT"; break; }
        case descriptor::Type::GRAPPLE_EQUIPMENT:     { return "descriptor::Type::GRAPPLE_EQUIPMENT"; break; }
        case descriptor::Type::SCANER_EQUIPMENT:     { return "descriptor::Type::SCANER_EQUIPMENT"; break; }

        // module
        case descriptor::Type::LAZER_MODULE:     { return "descriptor::Type::LAZER_MODULE"; break; }
        case descriptor::Type::ROCKET_MODULE:     { return "descriptor::Type::ROCKET_MODULE"; break; }
        case descriptor::Type::DRIVE_MODULE:     { return "descriptor::Type::DRIVE_MODULE"; break; }
        case descriptor::Type::RADAR_MODULE:     { return "descriptor::Type::RADAR_MODULE"; break; }
        case descriptor::Type::BAK_MODULE:         { return "descriptor::Type::BAK_MODULE"; break; }
        case descriptor::Type::ENERGIZER_MODULE: { return "descriptor::Type::ENERGIZER_MODULE"; break; }
        case descriptor::Type::PROTECTOR_MODULE: { return "descriptor::Type::PROTECTOR_MODULE"; break; }
        case descriptor::Type::DROID_MODULE:     { return "descriptor::Type::DROID_MODULE"; break; }
        case descriptor::Type::FREEZER_MODULE:     { return "descriptor::Type::FREEZER_MODULE"; break; }
        case descriptor::Type::GRAPPLE_MODULE:     { return "descriptor::Type::GRAPPLE_MODULE"; break; }
        case descriptor::Type::SCANER_MODULE:     { return "descriptor::Type::SCANER_MODULE"; break; }
        
        // artefact
        case descriptor::Type::GRAVITY_ARTEFACT:     { return "descriptor::Type::GRAVITY_ARTEFACT"; break; }
        case descriptor::Type::PROTECTOR_ARTEFACT:     { return "descriptor::Type::PROTECTOR_ARTEFACT"; break; }

        // other
        case descriptor::Type::HIT:     { return "descriptor::Type::HIT"; break; }

        default: { return "descriptor::type is unknown, fixme"; break; }
    }
}
