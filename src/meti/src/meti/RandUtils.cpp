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

namespace {
const float FLOAT_RATE = 100000.0f;
} // namespace

namespace meti {
namespace rand {

bool gen_probability(int val) {
    assert(val>0&&val<=100);
    return (gen_int(0, 100) < val);
}

float add_percent(float val, float percent)
{
    return val*(1+gen_float(percent));
}

float gen_float(float high)
{
    return float(gen_int(0, int(FLOAT_RATE*high))/FLOAT_RATE);
}

float gen_float(float low, float high)
{
    assert(low<=high);
    return float(gen_int(int(FLOAT_RATE*low), int(FLOAT_RATE*high))/FLOAT_RATE);
}

int gen_int(int low, int high)
{
    assert(low<=high);
    return (low != high) ? low + std::rand()%(high+1-low) : low;
}

int gen_int(int arg)
{
    assert(arg>=0);
    return std::rand()%(arg+1);
}

int gen_sign()
{
    return gen_bool()? 1: -1;
}

bool gen_bool()
{
    return gen_int(0,10) > 5 ? true : false;
}

float gen_angle()
{
    return gen_float(2*float(M_PI));
}

glm::vec2 gen_vec2(float radius_min, float radius_max)
{
    float alpha = gen_angle();
    float radius = gen_float(radius_min, radius_max);
    return glm::vec2(radius*std::sin(alpha), radius*std::cos(alpha));
}

glm::vec3 gen_vec3xy(float radius_min, float radius_max)
{
    float radius = gen_float(radius_min, radius_max);
    glm::vec3 result;
    fill_vec3xy_unit(result);
    result *= radius;
    return result;
}

glm::vec3 gen_vec3xy(float radius)
{
    glm::vec3 result;
    fill_vec3xy_unit(result);
    result *= radius;
    return result;
}

glm::vec3 gen_vec3xy_unit()
{
    float alpha = gen_angle();
    return glm::vec3(std::sin(alpha), std::cos(alpha), 0.0f);
}

glm::vec3 gen_vec3_unit()
{
    float x = gen_float(0.01f, 1.0f);
    float y = gen_float(0.01f, 1.0f);
    float z = gen_float(0.01f, 1.0f);
    return glm::normalize(glm::vec3(x,y,z));
}

void fill_vec3xy_unit(glm::vec3& direction)
{
    float alpha = gen_angle();
    direction.x = std::sin(alpha);
    direction.y = std::cos(alpha);
    direction.z = 0.0f;
}

} // namespace rand
} // namespace meti
