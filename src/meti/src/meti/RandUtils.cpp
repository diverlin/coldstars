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
namespace rand {

bool get_probability(int val) {
    assert(val>0&&val<=100);
    return (get_int(0, 100) > val);
}

float add_percent(float val, float percent)
{
    return val*(1+get_float(percent));
}

float get_float(float high)
{
    float precision = 100000.0;
    return (float)get_int(0, (int)precision*high)/precision;
}

float get_float(float low, float high)
{
    assert(low<=high);
    float precision = 100000.0;
    return (float)get_int((int)precision*low, (int)precision*high)/precision;
}

int get_int(int low, int high)
{
    assert(low<=high);
    return (low != high) ? low + std::rand()%(high+1-low) : low;
}

int get_int(int arg)
{
    //assert(arg != 0);
    return std::rand()%(arg+1);
}

int get_sing()
{
    return get_bool()? 1: -1;
}

bool get_bool()
{
    return get_int(0,10) > 5 ? true : false;
}

float get_angle()
{
    return get_float(2*M_PI);
}

glm::vec2 get_vec2(int radius_min, int radius_max)
{
    float alpha = get_angle();
    int radius = get_int(radius_min, radius_max);
    return glm::vec2(radius*sin(alpha), radius*cos(alpha));
}

glm::vec3 get_vec3xy(int radius_min, int radius_max)
{
    float radius = get_int(radius_min, radius_max);
    glm::vec3 result;
    get_vec3xy_unit(result);
    result *= radius;
    return result;
}

glm::vec3 get_vec3xy(float radius)
{
    glm::vec3 result;
    get_vec3xy_unit(result);
    result *= radius;
    return result;
}

glm::vec3 get_vec3xy_unit()
{
    float alpha = get_angle();
    return glm::vec3(sin(alpha), cos(alpha), 0.0f);
}

void get_vec3xy_unit(glm::vec3& direction)
{
    float alpha = get_angle();
    direction.x = std::sin(alpha);
    direction.y = std::cos(alpha);
    direction.z = 0.0f;
}

} // namespace rand
} // namespace meti
