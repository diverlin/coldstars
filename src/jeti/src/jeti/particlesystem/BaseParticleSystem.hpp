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

namespace jeti {

class Mesh;
namespace control {
class Material;
}

namespace particlesystem {

class Particle;

class Base
{
public:
    Base();
    virtual ~Base();

    [[deprecated("depr")]]
    void validateResources() const;

    void setDying() { m_isDying = true; }
    void setMaterial(control::Material* material) { m_material = material; }

    void setCenter(const glm::vec3& center) { m_center = center; }
    void setParticlesNum(unsigned int particles_num)  { m_particlesNum = particles_num; }
    void setParticleData(const ParticleData& data_particle) { m_dataParticle = data_particle; }

    int typeId() const { return m_typeId; }
    bool isAlive() const { return m_isAlive; }
    const glm::vec3& center() const { return m_center; }
    const Mesh& mesh() const { return *m_mesh; }
    const control::Material& material() const { return *m_material; }

    const glm::mat4& actualModelMatrix();

    virtual void update() = 0;

protected:
    unsigned int _particlesNum() const { return m_particlesNum; }

    void _setIsAlive(bool isAlive) { m_isAlive = isAlive; }

    bool _isDying() const { return m_isDying; }

    ParticleData& _particleData() { return m_dataParticle; }
    std::vector<Particle*>& _particles() { return m_particles; }

private:
    int m_typeId;
    unsigned int m_particlesNum;

    control::Material* m_material = nullptr;
    Mesh* m_mesh = nullptr;
    ParticleData m_dataParticle;

    glm::vec3 m_center;
    glm::vec3 m_velocity;
    glm::vec3 m_dir;

    glm::mat4 m_matrixModel;

    bool m_isAlive;
    bool m_isDying;

    std::vector<Particle*> m_particles;
};

} // namespace particlesystem
} // namespace jeti
