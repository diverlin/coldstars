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
    setRadius(GLOBAL_LIGHT_RADIUS);

    m_ambient = glm::vec4(ambient_factor*color.r, ambient_factor*color.b, ambient_factor*color.g, 1.0f);
    m_diffuse = color;
//    m_specular    = glm::vec4(1.5f); // visual artefact
    m_specular    = glm::vec4(0.0f);
    m_attenuation = glm::vec3(0.1f);
}

void Light::setRadius(float radius)
{
    radius = std::min(radius, GLOBAL_LIGHT_RADIUS);
    m_radiusOrigin = radius;
    m_radius = radius;
}

float Light::attenuationFactor(float distance) const
{
    float attenuation = 1.0f-float(std::pow(distance/radius(), 2));
    attenuation = std::max(attenuation, 0.0f);
    return attenuation;
}

void Light::setPosition(const glm::vec3& position)
{
    m_positionOrig = position;
    m_position = position;
    m_type = Type::STATIC;
}

void Light::useVariadicRadius(float min, float max, float speed)
{
    m_radius = min;
    m_radiusMin = min;
    m_radiusMax = max;
    m_radiusSpeed = speed;
    m_useVariadicRadius = true;
}

void Light::moveLinear(float radius, float speed, const glm::vec3& dir)
{
    m_type = Type::MOVE_LINEAR;
    m_amplitude = radius;
    m_speed = speed;
    m_moveDir = dir;
}

void Light::moveCircular(float amplitude, float speed)
{
    m_type = Type::MOVE_CIRCULAR;
    m_amplitude = amplitude;
    m_speed = speed;
}

void Light::update(float time)
{
    switch(m_type) {
    case Type::MOVE_LINEAR:
        m_position += m_speed*m_moveDir;
        if (glm::length(m_position - m_positionOrig) > m_amplitude) {
            m_moveDir *= -1;
        }
        break;
    case Type::MOVE_CIRCULAR:
        m_position.x = m_positionOrig.x + m_amplitude*glm::sin(m_speed*time);
        m_position.y = m_positionOrig.y + m_amplitude*glm::cos(m_speed*time);
        break;
    case Type::STATIC:
        break;
    }

    if (m_useVariadicRadius) {
        float factor = (1.0f + glm::cos(time*m_radiusSpeed)); //[0.0, 2.0]
        factor /= 2.0f; //[0.0, 1.0]
        m_radius = m_radiusMin+factor*m_radiusMax;
    }
    //std::cout<<m_radius<<std::endl;
}

} // namespace jeti

