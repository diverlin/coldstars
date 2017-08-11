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

//#include <MyGl.hpp>
 
#include <type/TextureType.hpp>
#include <type/RaceType.hpp>
#include <type/EntityType.hpp>
#include <type/TechLevelType.hpp>

#include <glm/glm.hpp>

#include <string>
#include <vector>

struct TextureDescriptor
{
    texture::Type type_id;
    entity::Type group;   //# warrior/trader and so on
    race::Type race_id;
    tech::Type tech_level_id;

    TextureDescriptor()
    :
    type_id(texture::Type::FAILBACK),
    group(entity::Type::NONE),
    race_id(race::Type::NONE),
    tech_level_id(tech::Type::NONE)
    {}

    bool operator==(const TextureDescriptor& rhs) const
    {
        if (type_id != rhs.type_id)
            return false;
        if (group != rhs.group)
            return false;
        if (race_id != rhs.race_id)
            return false;
        if (tech_level_id != rhs.tech_level_id)
            return false;

        return true;
    }
};

