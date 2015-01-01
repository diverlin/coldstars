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
#include <glm/glm.hpp>

namespace meti {

int getRandIntFromVec(const std::vector<int>&);

float getRandFloat(float, float);
int getRandInt(int, int);
int getRandSign();
bool getRandBool();

glm::vec2 getRandVec2f(int radius_min, int radius_max);
glm::vec3 getRandXYVec3f(int radius_min, int radius_max, float z);
glm::vec3 getRandXYVec3Unit();

bool isActionShouldHappen(int);

template<typename TYPE> 
TYPE getRand(const std::vector<TYPE>& vec)
{
    if (vec.size()>0) { return vec[getRandInt(0, vec.size()-1)]; }
    else              { return TYPE::NONE_ID; }
}

template<typename TYPE>
TYPE getRandomElement(const std::vector<TYPE>& vec)
{
    assert(vec.size());
    return vec[getRandInt(0, vec.size()-1)];
}

} // namespace meti
