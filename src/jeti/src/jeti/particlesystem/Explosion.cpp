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

#include <iostream>

namespace jeti {
namespace particlesystem {

Explosion::Explosion(const Config& config, float radius)
    :
      Base(config)
    , m_radius(radius)
{}

void Explosion::update(const glm::vec3& center)
{
    setCenter(center);

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


Explosion* genExplosion(control::Material* material)
{
    float radius = 100;
    int size_id = 1;

    Config config;

    config.particles_num = 50;
    config.creation_delay_msec =10;

    config.size_start = 25.0f + 2*size_id;
    config.size_end   = 2.0f;
    config.size_delta = 0.2f;

    config.velocity_start = 0.015f;
    config.velocity_end   = 0.015f;
    config.velocity_delta = 0.0f;

    config.color_start.r = 1.0f;
    config.color_start.g = 1.0f;
    config.color_start.b = 1.0f;
    config.color_start.a = 1.0f;

    config.color_end.r = 0.0f;
    config.color_end.g = 0.0f;
    config.color_end.b = 0.0f;
    config.color_end.a = 0.0f;

    config.color_delta.r = 0.01f;
    config.color_delta.g = 0.02f;
    config.color_delta.b = 0.03f;
    config.color_delta.a = 0.01f;
    config.color_delta *= 0.5f;

    config.use_rand_dir = true;
    config.use_rand_color_delta = true;
    config.rand_color_delta = 0.5f;

    config.use_rand_size_delta = true;
    config.rand_size_delta = 0.9f;

    //size_id = getRandInt(1,9); // DEBUG
    Explosion* ps = new Explosion(config, radius);
    ps->setMaterial(material);
    return ps;
}

} // namespace particlesystem
} // namespace jeti
