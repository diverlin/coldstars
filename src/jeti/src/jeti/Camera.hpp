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

#pragma once

#include <ceti/NonCopyable.hpp>
#include <glm/glm.hpp>

namespace jeti {

class Camera : public NonCopyable
{
    const float CAMERA_SPEED_MAX = 10.0f;
    const float CAMERA_INERTIA = 0.95f;

public:
    Camera();
    ~Camera();

    const glm::vec3& lookTo() const { return m_lookTo; }
    const glm::vec3& lookFrom() const { return m_lookFrom; }
    float lookRadius() const { return m_lookRadius; }
    const glm::mat4& viewMatrix() const { return m_viewMatrix; }

    void appendSpeed(const glm::vec3&);

    void update(int, int);

private:
    float m_lookRadius = 500.0;

    glm::vec3 m_lookFrom = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 m_lookTo = glm::vec3(0.0f, 0.0f, 499.0f);
    glm::vec3 m_direction = glm::vec3(0.0f, 0.0f, -11.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);

    float m_inertiaFactor = CAMERA_INERTIA;
    glm::vec3 m_moveSpeed;
    float m_speedMax = CAMERA_SPEED_MAX;

    glm::mat4 m_viewMatrix;
};

} // namespace jeti


