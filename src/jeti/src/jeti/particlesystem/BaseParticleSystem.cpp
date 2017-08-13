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

#include "BaseParticleSystem.hpp"
#include <particlesystem/Particle.hpp>

#include <jeti/Material.hpp>
#include <jeti/Mesh.hpp>
#include <jeti/Render.hpp>

#include <meti/RandUtils.hpp>

#include <glm/gtx/transform.hpp>


namespace jeti {
namespace particlesystem {

Base::Base(const ParticleSystemConfig& config)
    :
    m_config(config)
{
    m_mesh = new Mesh();
    m_direction = glm::vec3(1.0f, 0.0f, 0.0f);
}

Base::~Base()
{
    //delete m_mesh; FIXME cause bug

    for (Particle* particle: m_particles) {
        delete particle;
    }
    m_particles.clear();
}

void Base::_checkAlive() {
    if (m_particles.size() != m_config.particles_num) {
        return;
    }

    for (Particle* particle: _particles()) {
        if (particle->isAlive()) {
            m_isAlive = true;
            return;
        }
    }

    m_isAlive = false;
}

void Base::_emitNewParticle() {
    if (m_particles.size() >= m_config.particles_num) {
        return;
    }

    const auto now_time = std::chrono::steady_clock::now();
    float msec_diff = std::chrono::duration_cast<std::chrono::milliseconds>(now_time-m_lastTime).count();
    if (msec_diff > m_config.creation_delay_msec) {
        m_particles.push_back(_genParticle());
        m_lastTime = now_time;
    }
}

Particle* Base::_genParticle() const
{
    Particle* particle = new Particle(m_config.particle);
    particle->setPosition(m_center);
    if (m_config.use_rand_dir) {
        particle->randomizeDirection();
    } else {
        particle->setDirection(m_direction);
    }
    if (m_config.use_rand_color_delta) {
        glm::vec4 delta_color;
        delta_color.r = meti::addRandPercent(m_config.particle.color_delta.r, m_config.rand_color_delta);
        delta_color.g = meti::addRandPercent(m_config.particle.color_delta.g, m_config.rand_color_delta);
        delta_color.b = meti::addRandPercent(m_config.particle.color_delta.b, m_config.rand_color_delta);
        delta_color.a = meti::addRandPercent(m_config.particle.color_delta.a, m_config.rand_color_delta);
        particle->setColorDelta(delta_color);
    }
    if (m_config.use_rand_size_delta) {
        float size_delta = meti::addRandPercent(m_config.particle.size_delta, m_config.rand_size_delta);
        particle->setSizeDelta(size_delta);
    }

    return particle;
}

void Base::validateResources() const
{
    assert(m_material);
    if (!m_material->isLoaded()) {
        m_material->load();
    }
}

void Base::_updateToGPU()
{  
    std::vector<glm::vec3> positions;
    std::vector<glm::vec4> colors;
    std::vector<float> sizes;

    for (Particle* particle: m_particles) {
        positions.push_back(particle->position());
        colors.push_back(particle->color());
        sizes.push_back(particle->size());
    }

    m_mesh->fillPointVerticesFast(positions, colors, sizes);
}

void
Base::_updateModelMatrix()
{ 
    m_Tm = glm::translate(center());
    m_Mm = m_Tm;
}

void Base::draw(const jeti::Render& render) const
{
    if (!m_isAlive) {
        return;
    }
    render.drawParticles(*m_mesh, *m_material, m_Mm);
}

} // namespace particlesystem
} // namespace jeti
