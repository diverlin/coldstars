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

bool rand_probability(int val) {
    assert(val>0&&val<=100);
    return (rand_int(0, 100) > val);
}

void rand_xy_vec3_unit(glm::vec3& direction)
{
    float angle = rand_float(2*M_PI);
    direction.x = cos(angle);
    direction.y = sin(angle);
    direction.z = 0.0f;
}

float addRandPercent(float val, float percent)
{
    return val*(1+rand_float(percent));
}

float rand_float(float high)
{
    float precision = 100000.0;
    return (float)rand_int(0, (int)precision*high)/precision;
}

float rand_float(float low, float high)
{
    assert(low<=high);
    float precision = 100000.0;
    return (float)rand_int((int)precision*low, (int)precision*high)/precision;
}

int rand_int(int low, int high)
{
    assert(low<=high);
    return (low != high) ? low + std::rand()%(high+1-low) : low;
}

int rand_int(int arg)
{
    //assert(arg != 0);
    return std::rand()%(arg+1);
}

int rand_sing()
{
    return rand_int(0,10) > 5 ? 1: -1;
}

bool rand_bool()
{
    return rand_int(0,10) > 5 ? true : false;
}

glm::vec2 rand_vec2f(int radius_min, int radius_max)
{
    float alpha = glm::radians((float)rand_int(0, 360));
    int len = rand_int(radius_min, radius_max);
    return glm::vec2(sin(alpha) * len, cos(alpha) * len);
}

glm::vec3 rand_xy_vec3f(int radius_min, int radius_max, float z)
{
    float alpha = glm::radians((float)rand_int(0, 360));
    int len = rand_int(radius_min, radius_max);
    return glm::vec3(sin(alpha)*len, cos(alpha)*len, z);
}

glm::vec3 rand_xy_vec3(float r)
{
    float alpha = glm::radians((float)rand_int(0, 360));
    return r*glm::vec3(sin(alpha), cos(alpha), 0.0);
}

glm::vec3 rand_xy_vec3_unit()
{
    float alpha = glm::radians((float)rand_int(0, 360));
    return glm::vec3(sin(alpha), cos(alpha), 0.0);
}

} // namespace meti
