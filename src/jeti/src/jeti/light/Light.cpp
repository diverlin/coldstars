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


#include "Light.hpp"

#include <iostream>

namespace jeti {

Light::Light(const glm::vec4& color, float ambient_factor)
{
    __setColor(color, ambient_factor);
}

void Light::__setColor(const glm::vec4& color, float ambient_factor)
{
    m_ambient = glm::vec4(ambient_factor*color.r, ambient_factor*color.b, ambient_factor*color.g, 1.0f);
    m_diffuse = color;
//    m_specular    = glm::vec4(1.5f); // visual artefact
    m_specular    = glm::vec4(0.0f);
    m_attenuation = glm::vec3(0.1f);
}

void Light::__makeGlobal()
{
    m_role = Role::GLOBAL;
    __setRadius(GLOBAL_LIGHT_RADIUS);
}

void Light::__makeLocal()
{
    m_role = Role::LOCAL;
}

void Light::__makeEffect()
{
    m_role = Role::EFFECT;
}

void Light::__setRadius(float radius)
{
    assert(radius>=0);
    m_radiusOrigin = radius;
    m_radius = radius;
}

float Light::attenuationFactor(float distance) const
{
    float attenuation = 1.0f-float(std::pow(distance/radius(), 2));
    attenuation = std::max(attenuation, 0.0f);
    return attenuation;
}

void Light::__setPosition(const glm::vec3& position)
{
    m_positionOrig = position;
    m_position = position;
    m_moveType = Move::STATIC;
}

void Light::__useVariadicRadius(float min, float max, float speed)
{
    m_radius = min;
    m_radiusMin = min;
    m_radiusMax = max;
    m_radiusSpeed = speed;
    m_useVariadicRadius = true;
}

void Light::__moveLinear(const glm::vec3& dir, float speed)
{
    m_moveType = Move::LINEAR;
    m_speed = speed;
    m_moveDir = dir;
}

void Light::__moveLinearCyclic(float distance, const glm::vec3& dir, float speed)
{
    m_moveType = Move::LINEARCYCLIC;
    m_distance = distance;
    m_speed = speed;
    m_moveDir = dir;
}

void Light::__moveCircular(float amplitude, float speed)
{
    m_moveType = Move::CIRCULAR;
    m_distance = amplitude;
    m_speed = speed;
}

void Light::__init(float time)
{
    if (m_isInitialized) {
        return;
    }

    m_bornTime = time;

    m_isInitialized = true;
}

void Light::__updateMovement(float time)
{
    switch(m_moveType) {
    case Move::LINEAR:
        m_position += m_speed*m_moveDir;
        break;
    case Move::LINEARCYCLIC:
        m_position += m_speed*m_moveDir;
        if (glm::length(m_position - m_positionOrig) > m_distance) {
            m_moveDir *= -1;
        }
        break;
    case Move::CIRCULAR:
        m_position.x = m_positionOrig.x + m_distance*glm::sin(m_speed*time);
        m_position.y = m_positionOrig.y + m_distance*glm::cos(m_speed*time);
        break;
    case Move::STATIC:
        break;
    }
}

void Light::__updateRadius(float time)
{
    if (m_useVariadicRadius) {
        float factor = (1.0f + glm::cos(time*m_radiusSpeed)); //[0.0, 2.0]
        factor /= 2.0f; //[0.0, 1.0]
        m_radius = m_radiusMin+factor*m_radiusMax;
        //std::cout<<m_radius<<std::endl;
    }
}

void Light::__updateLifeTime(float time)
{
    m_lifeTime = time - m_bornTime;

    if (m_isDying) {
        m_radius *= 0.95f;
        if (m_radius < 10) {
            m_isAlive = false;
        }
    }
}

void Light::update(float time)
{
    __init(time);
    __updateMovement(time);
    __updateRadius(time);
    __updateLifeTime(time);
}

} // namespace jeti

