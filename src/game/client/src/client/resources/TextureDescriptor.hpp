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
#include <vector>
//#include <MyGl.hpp>
#include <glm/glm.hpp>
 
#include <types/TextureTypes.hpp>
#include <types/RaceTypes.hpp>
#include <types/EntityTypes.hpp>
#include <types/TechLevelTypes.hpp>

struct TextureDescriptor
{
    texture::type type_id;
    entity::type subtype_id;   //# warrior/trader and so on
    race::type race_id;
    tech::type tech_level_id;

    TextureDescriptor()
    :
    type_id(texture::type::FAILBACK),
    subtype_id(entity::type::NONE_ID),
    race_id(race::type::NONE_ID),
    tech_level_id(tech::type::NONE)
    {}

    bool operator==(const TextureDescriptor& rhs) const
    {
        if (type_id != rhs.type_id)
            return false;
        if (subtype_id != rhs.subtype_id)
            return false;
        if (race_id != rhs.race_id)
            return false;
        if (tech_level_id != rhs.tech_level_id)
            return false;

        return true;
    }
};

