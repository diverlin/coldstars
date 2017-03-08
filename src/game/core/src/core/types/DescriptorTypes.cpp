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

#include "DescriptorTypes.hpp"

std::string to_string(descriptor::Type type)
{
    switch(type)
    {
        case descriptor::Type::NONE: { return "descriptor::type::NONE"; break; }

        // world
        case descriptor::Type::GALAXY:         { return "descriptor::type::GALAXY"; break; }
        case descriptor::Type::STARSYSTEM:     { return "descriptor::type::STARSYSTEM"; break; }
        case descriptor::Type::SECTOR:     { return "descriptor::type::SECTOR"; break; }

        // pilots
        case descriptor::Type::NPC:             { return "descriptor::type::NPC"; break; }

        // space object
        case descriptor::Type::STAR:         { return "descriptor::type::STAR"; break; }
        case descriptor::Type::ASTEROID:     { return "descriptor::type::ASTEROID"; break; }
        case descriptor::Type::PLANET:         { return "descriptor::type::PLANET"; break; }
        case descriptor::Type::BLACKHOLE:     { return "descriptor::type::BLACKHOLE"; break; }
        case descriptor::Type::SHIP:         { return "descriptor::type::SHIP"; break; }
        case descriptor::Type::SPACESTATION: { return "descriptor::type::SPACESTATION"; break; }
        case descriptor::Type::SATELLITE:     { return "descriptor::type::SATELLITE"; break; }
        case descriptor::Type::CONTAINER:     { return "descriptor::type::CONTAINER"; break; }

        // equipment
        case descriptor::Type::LAZER_EQUIPMENT:     { return "descriptor::type::LAZER_EQUIPMENT"; break; }
        case descriptor::Type::ROCKET_EQUIPMENT: { return "descriptor::type::ROCKET_EQUIPMENT"; break; }
        case descriptor::Type::DRIVE_EQUIPMENT:     { return "descriptor::type::DRIVE_EQUIPMENT"; break; }
        case descriptor::Type::RADAR_EQUIPMENT:     { return "descriptor::type::RADAR_EQUIPMENT"; break; }
        case descriptor::Type::BAK_EQUIPMENT:     { return "descriptor::type::BAK_EQUIPMENT"; break; }
        case descriptor::Type::ENERGIZER_EQUIPMENT:     { return "descriptor::type::ENERGIZER_EQUIPMENT"; break; }
        case descriptor::Type::PROTECTOR_EQUIPMENT:     { return "descriptor::type::PROTECTOR_EQUIPMENT"; break; }
        case descriptor::Type::DROID_EQUIPMENT:         { return "descriptor::type::DROID_EQUIPMENT"; break; }
        case descriptor::Type::FREEZER_EQUIPMENT:     { return "descriptor::type::FREEZER_EQUIPMENT"; break; }
        case descriptor::Type::GRAPPLE_EQUIPMENT:     { return "descriptor::type::GRAPPLE_EQUIPMENT"; break; }
        case descriptor::Type::SCANER_EQUIPMENT:     { return "descriptor::type::SCANER_EQUIPMENT"; break; }

        // module
        case descriptor::Type::LAZER_MODULE:     { return "descriptor::type::LAZER_MODULE"; break; }
        case descriptor::Type::ROCKET_MODULE:     { return "descriptor::type::ROCKET_MODULE"; break; }
        case descriptor::Type::DRIVE_MODULE:     { return "descriptor::type::DRIVE_MODULE"; break; }
        case descriptor::Type::RADAR_MODULE:     { return "descriptor::type::RADAR_MODULE"; break; }
        case descriptor::Type::BAK_MODULE:         { return "descriptor::type::BAK_MODULE"; break; }
        case descriptor::Type::ENERGIZER_MODULE: { return "descriptor::type::ENERGIZER_MODULE"; break; }
        case descriptor::Type::PROTECTOR_MODULE: { return "descriptor::type::PROTECTOR_MODULE"; break; }
        case descriptor::Type::DROID_MODULE:     { return "descriptor::type::DROID_MODULE"; break; }
        case descriptor::Type::FREEZER_MODULE:     { return "descriptor::type::FREEZER_MODULE"; break; }
        case descriptor::Type::GRAPPLE_MODULE:     { return "descriptor::type::GRAPPLE_MODULE"; break; }
        case descriptor::Type::SCANER_MODULE:     { return "descriptor::type::SCANER_MODULE"; break; }
        
        // artefact
        case descriptor::Type::GRAVITY_ARTEFACT:     { return "descriptor::type::GRAVITY_ARTEFACT"; break; }
        case descriptor::Type::PROTECTOR_ARTEFACT:     { return "descriptor::type::PROTECTOR_ARTEFACT"; break; }

        default: { return "descriptor::type is unknown, fixme"; break; }
    }
}
