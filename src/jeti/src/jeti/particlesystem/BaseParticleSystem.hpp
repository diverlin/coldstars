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

#include <vector>
#include <chrono>

namespace jeti {

class Render;
class Mesh;
namespace control {
class Material;
}

namespace particlesystem {

class Particle;

class Base
{
public:
    Base(const Config&);
    virtual ~Base();

    [[deprecated("depr")]]
    void validateResources() const;

    void setDying() { m_isDying = true; }
    void setMaterial(control::Material* material) { m_material = material; }

    void setCenter(const glm::vec3& center) { m_center = center; }
    void setDirection(const glm::vec3& dir) { m_direction = dir; }

    int typeId() const { return m_type; }
    bool isAlive() const { return m_isAlive; }
    const glm::vec3& center() const { return m_center; }
    float velocity() const { return m_velocity; }

    const Mesh& mesh() const { return *m_mesh; }
    const control::Material& material() const { return *m_material; }

    const glm::mat4& modelMatrix() const { return m_Mm; }

    virtual void update(const glm::vec3&) = 0;
    void draw(const jeti::Render&) const;

protected:
    void _emitNewParticle();
    Particle* _genParticle() const;

    void _updateModelMatrix();

    void _setIsAlive(bool isAlive) { m_isAlive = isAlive; }

    bool _isDying() const { return m_isDying; }

    const glm::vec3& _direction() const { return m_direction; }

    Config& _particleData() { return m_config; }
    std::vector<Particle*>& _particles() { return m_particles; }

    void _updateToGPU();

private:
    int m_type = -1;
    std::chrono::steady_clock::time_point m_lastTime;

    control::Material* m_material = nullptr;
    Mesh* m_mesh = nullptr;
    Config m_config;

    glm::vec3 m_center;
    glm::vec3 m_direction;
    float m_velocity = 0.0f;

    glm::mat4 m_Tm;
    glm::mat4 m_Sm;
    glm::mat4 m_Mm;

    bool m_isAlive = true;
    bool m_isDying = false;

    std::vector<Particle*> m_particles;
};

} // namespace particlesystem
} // namespace jeti
