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

Jet::Jet(const Config& particleData)
    : Base(particleData)
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

Jet* genLinearParticleSystem(control::Material* material, int size_id)
{
    Config config;

    config.particles_num = 10;
    config.creation_delay_msec = 50;

    config.size_start = 15.0f + 2*size_id;
    config.size_end   = 2.0f;
    config.size_delta = 0.9f;
    
    config.velocity_start = 0.05f;
    config.velocity_end   = 0.05f;
    config.velocity_delta = 0.0f;
    
    config.color_start.r = 1.0f;
    config.color_start.g = 1.0f;
    config.color_start.b = 1.0f;
    config.color_start.a = 0.9f;
    
    config.color_end.r = 0.0f;
    config.color_end.g = 0.0f;
    config.color_end.b = 0.0f;
    config.color_end.a = 0.1f;
    
    config.color_delta.r = 0.0f;
    config.color_delta.g = 0.1f;
    config.color_delta.b = 0.0f;
    config.color_delta.a = 0.05f;
        
    //control::Material* material = utils::createMaterialByDescriptorType(texture::Type::DISTANTSTAR);
    Jet* ps = new Jet(config);
    ps->setMaterial(material);

    return ps;
}

} // namespace aprticlesystem
} // namespace jeti

