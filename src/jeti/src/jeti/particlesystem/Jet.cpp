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

#include "Jet.hpp"
#include "Particle.hpp"

#include <cmath>

namespace jeti {
namespace particlesystem {

Jet::Jet(const ParticleSystemConfig& config)
    : Base(config)
{}

void Jet::update(const glm::vec3& center, const:: glm::vec3& dir)
{
    setDirection(dir);
    update(center);
}

void Jet::update(const glm::vec3& center)
{    
    setCenter(center);

    for (Particle* particle: _particles()) {
        if (particle->isAlive()) {
            particle->update();
        } else {
            particle->restart(_direction());
        }
    }

    _updateToGPU();
    _updateModelMatrix();
    _emitNewParticle();
}

Jet* genJet(control::Material* material, int size_id)
{
    ParticleSystemConfig config;

    config.particles_num = 10;
    config.creation_delay_msec = 50;
    config.use_rand_dir = false;

    config.use_rand_color_delta = true;
    config.rand_color_delta = 0.2f;

    config.use_rand_size_delta = true;
    config.rand_size_delta = 0.1f;

    ParticleConfig& particle = config.particle;
    particle.size_start = 15.0f + 2*size_id;
    particle.size_end   = 2.0f;
    particle.size_delta = 0.9f;
    
    particle.velocity_start = 0.05f;
    particle.velocity_end   = 0.05f;
    particle.velocity_delta = 0.0f;
    
    particle.color_start.r = 1.0f;
    particle.color_start.g = 1.0f;
    particle.color_start.b = 1.0f;
    particle.color_start.a = 0.9f;
    
    particle.color_end = 0.0f;
    
    particle.color_delta.r = 0.0f;
    particle.color_delta.g = 0.1f;
    particle.color_delta.b = 0.0f;
    particle.color_delta.a = 0.05f;
        
    //control::Material* material = utils::createMaterialByDescriptorType(texture::Type::DISTANTSTAR);
    Jet* ps = new Jet(config);
    ps->setMaterial(material);

    return ps;
}

} // namespace aprticlesystem
} // namespace jeti

