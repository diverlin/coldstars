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

#include "Explosion.hpp"

#include <particlesystem/Particle.hpp>

#include <meti/RandUtils.hpp>

namespace jeti {
namespace particlesystem {

Explosion::Explosion(const ParticleSystemConfig& config)
    :
      Base(config)
{}

void Explosion::update()
{
    for (Particle* particle: _particles()) {
        if (particle->isAlive()) {
            particle->update();
        }
    }

    _updateToGPU();
    _updateModelMatrix();
    _emitNewParticle();
    _checkAlive();
}


Explosion* genExplosion(control::Material* material, float size)
{
    const float SIZE_RATIO = 1.2f;
    const float NUM_RATIO = 0.5f;

    ParticleSystemConfig config;

    config.particles_num = int(NUM_RATIO*size);
    config.creation_delay_msec = 10;

    config.use_rand_dir = true;
    config.use_rand_color_delta = true;
    config.rand_color_delta = 0.5f;

    config.use_rand_size_delta = true;
    config.rand_size_delta = 0.9f;

    ParticleConfig& particle = config.particle;
    particle.size_start = SIZE_RATIO*size;
    particle.size_end   = 5.5f;
    particle.size_delta = 0.5f;

    particle.velocity_start = 1.5f;
    particle.velocity_end   = 1.5f;
    particle.velocity_delta = 0.0f;

    particle.color_start.r = 1.0f;
    particle.color_start.g = 1.0f;
    particle.color_start.b = 1.0f;
    particle.color_start.a = 1.0f;

    particle.color_end = 0.0f;

    particle.color_delta.r = 0.01f;
    particle.color_delta.g = 0.02f;
    particle.color_delta.b = 0.03f;
    particle.color_delta.a = 0.01f;
    particle.color_delta *= 0.5f;

    Explosion* ps = new Explosion(config);
    ps->setMaterial(material);
    return ps;
}

} // namespace particlesystem
} // namespace jeti
