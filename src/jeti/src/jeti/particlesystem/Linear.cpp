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

#include <cmath>

#include "Linear.hpp"
#include "Particle.hpp"

namespace jeti {
namespace particlesystem {

Linear::Linear(const ParticleSystemData& particleData)
    : Base(particleData)
{}

void Linear::update(const glm::vec3& offset, const:: glm::vec3& dir)
{
    setDirection(dir);
    update(offset);
}

void Linear::update(const glm::vec3& offset)
{
    for (Particle* particle: _particles()) {
        if (particle->isAlive()) {
            particle->update();
        } else {
            particle->reborn();
        }
    }

    _updateToGPU();
    _updateModelMatrix();
    _emitNewParticle();
}

Linear* genLinearParticleSystem(control::Material* material, int size_id)
{
    ParticleSystemData config;

    config.particles_num = 5;
    config.creation_delay = 0.1f;

    config.size_start = 15.0f + 2*size_id;
    config.size_end   = 2.0f;
    config.size_delta = 0.0f;
    
    config.velocity_start = 0.05f;
    config.velocity_end   = 0.05f;
    config.velocity_delta = config.velocity_start;
    
    config.color_start.r = 1.0f;
    config.color_start.g = 1.0f;
    config.color_start.b = 1.0f;
    config.color_start.a = 0.9f;
    
    config.color_end.r = 0.0f;
    config.color_end.g = 0.0f;
    config.color_end.b = 0.0f;
    config.color_end.a = 0.1f;
    
    config.color_delta.r = 0.0f;
    config.color_delta.g = 0.0f;
    config.color_delta.b = 0.0f;
    config.color_delta.a = 0.1f;
        
    //control::Material* material = utils::createMaterialByDescriptorType(texture::Type::DISTANTSTAR);
    Linear* ps = new Linear(config);
    ps->setMaterial(material);

    return ps;
}

} // namespace aprticlesystem
} // namespace jeti

