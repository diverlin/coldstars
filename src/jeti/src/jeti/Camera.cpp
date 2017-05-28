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

#include <glm/gtc/matrix_transform.hpp>

namespace jeti {

void Camera::appendSpeed(const glm::vec3& speed) 
{ 
    if (glm::length(m_moveSpeed) < m_speedMax) {
        m_moveSpeed += speed; 
    }
}

void Camera::update()
{
    m_moveSpeed *= m_inertiaFactor;
    m_position += m_moveSpeed;
    m_target = m_position + m_direction;

    m_viewMatrix = glm::lookAt(m_position, m_target, m_up);
}

} // namespace jeti
