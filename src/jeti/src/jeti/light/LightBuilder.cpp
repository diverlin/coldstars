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

#include "LightBuilder.hpp"

#include "Light.hpp"

#include <meti/RandUtils.hpp>

namespace jeti {

LightBuilder::LightBuilder(int w, int h)
    : m_width(w)
    , m_height(h)
{
}

LightBuilder::~LightBuilder()
{
    delete m_light;
}

LightBuilder& LightBuilder::genGlobal()
{
    assert(m_light==nullptr);
    m_light = new Light;
    m_light->__makeGlobal();
    return *this;
}

LightBuilder& LightBuilder::genLocal(float radius)
{
    assert(m_light==nullptr);
    m_light = new Light;
    m_light->__makeLocal();
    m_light->__setRadius(radius);
    return *this;
}

LightBuilder& LightBuilder::genEffect()
{
    assert(m_light==nullptr);
    m_light = new Light;
    m_light->__makeEffect();
    return *this;
}

LightBuilder& LightBuilder::position()
{
    glm::vec3 pos(0.0f, 0.0f, LIGHT_DEFAULT_ZPOZ);
    float max = __getScreenWorldSize();
    pos.x = max * meti::rand::gen_float(-0.5f, 0.5f);
    pos.y = max * meti::rand::gen_float(-0.5f, 0.5f);
    return position(pos);
}

LightBuilder& LightBuilder::position(const glm::vec3& position)
{
    assert(m_light);
    m_light->__setPosition(position);
    return *this;
}

LightBuilder& LightBuilder::radius()
{
    float max = __getScreenWorldSize();
    float r = max * meti::rand::gen_float(0.3f, 0.6f);
    return radius(r);
}

LightBuilder& LightBuilder::radius(float radius)
{
    assert(m_light);
    assert(!m_light->isGlobal()); // we don't want change the radius for global light
    assert(radius >= 1.08f && "radius less is not visible");
    m_light->__setRadius(radius);
    return *this;
}

LightBuilder& LightBuilder::radiusVar()
{
    float max = __getScreenWorldSize();
    float radius_min = max * meti::rand::gen_float(0.1f, 0.2f);
    float radius_max = max * meti::rand::gen_float(0.3f, 0.6f);
    float radius_step = max * meti::rand::gen_float(0.01f, 0.03f);
    return radiusVar(radius_min, radius_max, radius_step);
}

LightBuilder& LightBuilder::radiusVar(float radius_min, float radius_max, float radius_step)
{
    assert(m_light);
    m_light->__useVariadicRadius(radius_min, radius_max, radius_step);
    return *this;
}

LightBuilder& LightBuilder::color()
{
    glm::vec4 c(1.0f);
    int choice = meti::rand::gen_int(0,2);
    if (choice == 0)
        c.r = meti::rand::gen_float(0.5f, 1.0f);
    if (choice == 1)
        c.g = meti::rand::gen_float(0.5f, 1.0f);
    if (choice == 2)
        c.b = meti::rand::gen_float(0.5f, 1.0f);
    return color(c);
}

LightBuilder& LightBuilder::color(const glm::vec4& color)
{
    assert(m_light);
    m_light->__setColor(color);
    return *this;
}

LightBuilder& LightBuilder::moveCircular()
{
    float max = __getScreenWorldSize();
    float radius = max * meti::rand::gen_float(0.05f, 0.4f);
    float speed = max * meti::rand::gen_float(0.001f, 0.005f);
    return moveCircular(radius, speed);
}

LightBuilder& LightBuilder::moveCircular(float radius, float speed)
{
    assert(m_light);
    m_light->__moveCircular(radius, speed);
    return *this;
}

LightBuilder& LightBuilder::moveLinear()
{
    float max = __getScreenWorldSize();
    float speed = max * meti::rand::gen_float(0.003f, 0.01f);
    glm::vec3 dir = meti::rand::gen_vec3xy_unit();

    return moveLinear(dir, speed);
}

LightBuilder& LightBuilder::moveLinear(const glm::vec3& dir, float speed)
{
    assert(m_light);
    m_light->__moveLinear(dir, speed);
    return *this;
}

LightBuilder& LightBuilder::moveLinearCyclic()
{
    float max = __getScreenWorldSize();
    float speed = max * meti::rand::gen_float(0.001f, 0.005f);
    glm::vec3 dir = meti::rand::gen_vec3xy_unit();
    float distance = max * meti::rand::gen_float(0.2f, 0.8f);

    return moveLinearCyclic(distance, dir, speed);
}

LightBuilder& LightBuilder::moveLinearCyclic(float distance, const glm::vec3& dir, float speed)
{
    assert(m_light);
    m_light->__moveLinearCyclic(distance, dir, speed);
    return *this;
}

Light* LightBuilder::take()
{
    assert(m_light);
    Light* light = m_light;
    m_light = nullptr;
    return light;
}

float LightBuilder::__getScreenWorldSize() const
{
    assert(m_width);
    assert(m_height);
    return std::max(m_width, m_height);
}

} // namespace jeti

