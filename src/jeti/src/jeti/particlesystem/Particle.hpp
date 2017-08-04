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
    Particle(const ParticleData&);
    ~Particle();

    void setPosition(const glm::vec3& position) { m_position = position; }
    void setVelocity(const glm::vec3& velocity) { m_velocity = velocity; }

    bool isAlive() const { return m_isAlive; }
    float alpha() const { return m_color.a; }

    const glm::vec3& position() const { return m_position; }
    const glm::vec4& color() const { return m_color; }

    float size() const { return m_size; }

    void reborn();

    void randomizeLifeTime(float, float);
    void randomizeDeltaAlpha(float, float);

    void randomVelocity();
    void randAccurateVelocity();
    void randDirtyVelocity();

    void update();

private:
    bool m_isAlive = true;

    glm::vec3 m_position;
    glm::vec3 m_velocity;
    glm::vec3 m_force;

    glm::vec4 m_color;

    float m_size;

    ParticleData m_dataParticle;
};

} // namespace particlesystem
} // namespace jeti
