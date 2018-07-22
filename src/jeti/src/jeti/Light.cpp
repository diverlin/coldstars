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

namespace jeti {


Light::Light(const glm::vec4& color, float ambient_factor)
{
    m_ambient = glm::vec4(ambient_factor*color.r, ambient_factor*color.b, ambient_factor*color.g, 1.0f);
    m_diffuse = color;
//    m_specular    = glm::vec4(1.5f); // visual artefact
    m_specular    = glm::vec4(0.0f);
    m_attenuation = glm::vec3(0.1f);
}

void Light::setPosition(const glm::vec3& position)
{
    m_center = position;
    m_position = position;
    m_type = Type::STATIC;
}

void Light::moveLinear(float radius, float speed, const glm::vec3& dir)
{
    m_type = Type::MOVE_LINEAR;
    m_radius = radius;
    m_speed = speed;
    m_moveDir = dir;
}

void Light::moveCircular(float radius, float speed)
{
    m_type = Type::MOVE_CIRCULAR;
    m_radius = radius;
    m_speed = speed;
    m_moveDir = m_moveDir;
}

void Light::update(float time)
{
    switch(m_type) {
    case Type::MOVE_LINEAR:
        m_position += m_speed*m_moveDir;
        if (glm::length(m_position - m_center) > m_radius) {
            m_moveDir *= -1;
        }
        break;
    case Type::MOVE_CIRCULAR:
        m_position.x = m_radius*glm::sin(m_speed*time);
        m_position.y = m_radius*glm::cos(m_speed*time);
        break;
    case Type::STATIC:
        break;
    }
}

} // namespace jeti

