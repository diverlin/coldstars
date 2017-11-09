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


#include "Camera.hpp"

#include <meti/common.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <ceti/StringUtils.hpp>
#include <iostream>

namespace jeti {

void Camera::setTargetPosition(const glm::vec3& position)
{
    if (m_position == position) {
        return;
    }
    __resetSpeed();

    glm::vec3 diff(position-m_position);
    glm::vec3 dir(glm::normalize(diff));
    float dist = glm::length(diff);

    int num = 60;
    float step = dist/num;
    glm::vec3 pos = m_position;
    for (int i=0; i<num; ++i) {
        pos += step*dir;
        m_positions.push_back(pos);
    }

    m_it = 0;
    m_autoMove = true;
}

void Camera::addSpeed(const glm::vec3& speed)
{ 
    if (glm::length(speed) == 0) {
        return;
    }
    if (__speedAboveMax()) {
        return;
    }
    m_speed += speed;
    m_speed.z = 0;

    m_autoMove = false;
}

void Camera::update()
{
    if (m_autoMove) {
        if (m_it < m_positions.size()) {
            m_position = m_positions[m_it];
            m_it++;
        } else {
            m_autoMove = false;
            m_positions.clear();
            m_it = -1;
        }
    } else {
        m_position += m_speed;
        m_speed *= m_inertiaFactor;
    }

    m_target = m_position + m_radius*m_direction;
    std::cout<<"pos="<<ceti::to_string(m_position)<<" target="<<ceti::to_string(m_target)<<" r="<<m_radius<<std::endl;
    m_viewMatrix = glm::lookAt(m_position, m_target, m_up);
}

bool Camera::__speedAboveMax() const
{
    return (glm::length(m_speed) > m_speedMax);
}

void Camera::__resetSpeed() {
    m_speed = glm::vec3(0.0f);
}
} // namespace jeti
