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

#include <particlesystem/ParticleData.hpp>

#include <glm/glm.hpp>

namespace jeti {
namespace particlesystem {

class Particle
{
public:
    Particle(const Config&);
    ~Particle();

    void setPosition(const glm::vec3& position) { m_position = position; }
    void setDirection(const glm::vec3& direction) { m_direction = direction; }
    void setVelocity(float velocity) { m_velocity = velocity; }
    void setColorDelta(const glm::vec4& color_delta) { m_config.color_delta = color_delta; }
    void setSizeDelta(float size_delta) { m_config.size_delta = size_delta; }

    bool isAlive() const { return m_isAlive; }
    float alpha() const { return m_color.a; }

    const glm::vec3& position() const { return m_position; }
    const glm::vec4& color() const { return m_color; }

    float size() const { return m_size; }

    void restart(const glm::vec3&);

    void randomizeLifeTime(float, float);
    void randomizeDeltaAlpha(float, float);

    void randomDirection();

    void update();

private:
    bool m_isAlive = true;

    glm::vec3 m_position;
    glm::vec3 m_direction;
    float m_velocity = 0.0f;

    glm::vec4 m_color;

    float m_size = 1.0f;

    Config m_config;
};

} // namespace particlesystem
} // namespace jeti
