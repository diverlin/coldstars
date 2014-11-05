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
#include <MyGl.hpp>
#include <glm/glm.hpp>
 
#include <types/TextureTypes.hpp>
#include <types/RaceTypes.hpp>
#include <types/EntityTypes.hpp>
#include <types/TechLevelTypes.hpp>

struct TextureDescriptor
{
    TYPE::TEXTURE type;
    TYPE::ENTITY subtype;   //# warrior/trader and so on
    TYPE::RACE race;
    TYPE::TECHLEVEL tech_level;

    TextureDescriptor()
    :
    type(TYPE::TEXTURE::NONE_ID),
    subtype(TYPE::ENTITY::NONE_ID),
    race(TYPE::RACE::NONE_ID),
    tech_level(TYPE::TECHLEVEL::NONE_ID)
    {}
};

