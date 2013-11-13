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


Camera::Camera()
:
m_InertiaFactor(CAMERA_INERTIA),
m_SpeedMax(CAMERA_SPEED_MAX)
{
    m_Pos  = glm::vec3(0.0f, 0.0f, 499.0f);
    m_Dir  = glm::vec3(0.0f, 0.0f, -1.0f); 
    m_Up   = glm::vec3(0.0f, 1.0f, 0.0f);
}
        
Camera::~Camera()
{}

void Camera::AddMoveSpeed(const glm::vec3& speed) 
{ 
    if (glm::length(m_MoveSpeed) < m_SpeedMax)
    {
        m_MoveSpeed += speed; 
    }
}

void Camera::Update()
{
    m_MoveSpeed *= m_InertiaFactor;
    m_Pos += m_MoveSpeed; 
    
    m_Vm = glm::lookAt(m_Pos, m_Pos+m_Dir, m_Up);
}
