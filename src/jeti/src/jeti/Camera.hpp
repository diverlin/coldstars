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

#include <meti/VectorUtils.hpp>

#include <glm/glm.hpp>

namespace jeti {

class Camera : public NonCopyable
{
    const float CAMERA_SPEED_MAX = 20.0f;
    const float CAMERA_INERTIA = 0.95f;
    const float LOOKTO_Z = -1000.0;
public:
    Camera() = default;
    ~Camera() = default;

    void setPosition(const glm::vec3& position) { m_position = position; }
    const glm::vec3& target() const { return m_target; }
    const glm::vec3& position() const { return m_position; }
    const glm::vec3& up() const { return m_up; }
    const glm::vec3& speed() const { return m_speed; }

    float radius() const { return m_radius; }
    const glm::mat4& viewMatrix() const { return m_viewMatrix; }

    void addSpeed(const glm::vec2&);
    void addSpeed(const glm::vec3&);

    void update();

private:
    float m_radius = 1000.0;

    glm::vec3 m_position;

    glm::vec3 m_target;
    glm::vec3 m_direction = glm::vec3(0.0f, 0.0f, LOOKTO_Z);
    glm::vec3 m_up = meti::OY;

    float m_inertiaFactor = CAMERA_INERTIA;
    glm::vec3 m_speed;
    float m_speedMax = CAMERA_SPEED_MAX;

    glm::mat4 m_viewMatrix;

    bool __speedAboveMax() const;
};

} // namespace jeti


