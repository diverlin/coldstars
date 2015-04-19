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


#include "RandUtils.hpp"
#include <stdlib.h>
#include <cmath>

namespace meti {

int getRandIntFromVec(const std::vector<int>& vec)
{
    assert(!vec.empty());
    return vec[getRandInt(0, vec.size()-1)];
}

float getRandFloat(float low, float high)
{
    assert(low<=high);
    float precision = 100000.0;
    return (float)getRandInt((int)precision*low, (int)precision*high)/precision;
}

int getRandInt(int low, int high)
{
    assert(low<=high);
    return (low != high) ? low + rand()%(high+1-low) : low;
}

int getRandSign()
{
    return getRandInt(0,10) > 5 ? 1: -1;
}

bool getRandBool()
{
    return getRandInt(0,10) > 5 ? true : false;
}

bool isActionShouldHappen(int percent)
{
    return percent > getRandInt(1, 100)? true : false;
}

glm::vec2 getRandVec2f(int radius_min, int radius_max)
{
    float alpha = glm::radians((float)getRandInt(0, 360));
    int len = getRandInt(radius_min, radius_max);
    return glm::vec2(sin(alpha) * len, cos(alpha) * len);
}

glm::vec3 getRandXYVec3f(int radius_min, int radius_max, float z)
{
    float alpha = glm::radians((float)getRandInt(0, 360));
    int len = getRandInt(radius_min, radius_max);
    return glm::vec3(sin(alpha)*len, cos(alpha)*len, z);
}

glm::vec3 getRandXYVec3Unit()
{
    float alpha = glm::radians((float)getRandInt(0, 360));
    return glm::vec3(sin(alpha), cos(alpha), 0.0);
}

glm::vec3 getXYVec3Unit(float alpha)
{
    alpha = glm::radians(alpha); //ugly
    return glm::vec3(sin(alpha), cos(alpha), 0.0);
}

} // namespace meti
