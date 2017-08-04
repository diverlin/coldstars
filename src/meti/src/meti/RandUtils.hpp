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
#include <stdexcept>

#include <glm/glm.hpp>

namespace meti {

float getRandFloat(float);
float getRandFloat(float, float);
int getRandInt(int);
int getRandInt(int, int);
int getRandSign();
bool getRandBool();

glm::vec2 getRandVec2f(int radius_min, int radius_max);
glm::vec3 getRandXYVec3f(int radius_min, int radius_max, float z);
glm::vec3 getRandXYVec3Unit();
glm::vec3 getXYVec3(float radius, float angle);

bool isActionShouldHappen(int);

template<typename T>
const T& getRand(const std::vector<T>& v)
{
    if (v.empty()) {
        throw std::runtime_error("ERROR: std::vector is empty, not ably to get random element from it");
    }
    return v[getRandInt(v.size()-1)];
}

} // namespace meti
