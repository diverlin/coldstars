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

#include "DriveEffect.hpp"
#include <particlesystem/Particle.hpp>

namespace jeti {
namespace particlesystem {

Linear::Linear()
{}

Linear::~Linear()
{}

void Linear::createParticles()
{
    for (unsigned int i=0; i<_particlesNum(); i++) {
        Particle* particle = new Particle(_particleData());
        particle->setPosition(center());
        particle->setDirection(_direction());
        particle->setVelocity(velocity());
        _particles().push_back(particle);
    }
}

void Linear::update(const glm::vec3& offset)
{
    setCenter(center()+offset);
    for (Particle* particle: _particles()) {
        if (particle->isAlive()) {
            particle->update();
        } else {
            particle->reborn();
        }
    }
}

Linear* genLinearParticleSystem(control::Material* material, int size_id)
{
    ParticleData data_particle;
                   
    data_particle.size_start = 15.0f + 2*size_id;
    data_particle.size_end   = 2.0f;
    data_particle.d_size     = 0.0f;
    
    data_particle.velocity_start = 1.2f;
    data_particle.velocity_end   = 1.2f;
    data_particle.d_velocity     = 0.0f;
    
    data_particle.color_start.r = 1.0f;
    data_particle.color_start.g = 1.0f;
    data_particle.color_start.b = 1.0f;
    data_particle.color_start.a = 0.9f;
    
    data_particle.color_end.r = 0.0f;
    data_particle.color_end.g = 0.0f;
    data_particle.color_end.b = 0.0f;
    data_particle.color_end.a = 0.1f;
    
    data_particle.color_delta.r = 0.0f;
    data_particle.color_delta.g = 0.0f;
    data_particle.color_delta.b = 0.0f;
    data_particle.color_delta.a = 0.1f;
        
    int particles_num = 5;

    //control::Material* material = utils::createMaterialByDescriptorType(texture::Type::DISTANTSTAR);
    Linear* ps = new Linear();
    
    ps->setMaterial(material);
    ps->setParticleData(data_particle);
    ps->setParticlesNum(particles_num);
    
    ps->createParticles();
            
    return ps;
}

} // namespace aprticlesystem
} // namespace jeti

