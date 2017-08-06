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

#include "DamageEffect.hpp"
#include <particlesystem/Particle.hpp>

namespace jeti {
namespace particlesystem {

DamageEffect::DamageEffect(const ParticleSystemConfig& config)
    :
      Base(config)
{
    //subtype_id = DAMAGE_EFFECT;
}

/* virtual override final */
DamageEffect::~DamageEffect()
{}


void DamageEffect::CreateParticles()
{
//    for(unsigned int i=0; i<_particlesNum(); i++) {
//        Particle* particle = new Particle(_particleData());
//        particle->randomizeDeltaAlpha(0.003, 0.006); //   ??
//        particle->randomDirection();

//        _particles().push_back(particle);
//    }
}

void DamageEffect::update(const glm::vec3& offset)
{
    _setIsAlive(false);
    for (Particle* particle: _particles()) {
        if (particle->isAlive()) {
            particle->update();
            _setIsAlive(true);
        } else {
            if (!_isDying()) {
                particle->restart(_direction());
            }
        }
    }
}

//DamageEffect* getNewDamageEffect(int color_id, SpaceObject* parent)
//{
//    int particles_num = 10;
    
//    ParticleData data_particle;
//    data_particle.size_start = 25;
//    data_particle.size_end = 2.0;
//    data_particle.d_size = 0.02;
    
//    data_particle.velocity_start = 1.3;
//    data_particle.velocity_end   = 1.3;
//    data_particle.d_velocity   = 0.0;
    
//    data_particle.color_start.r    = 1.0;
//    data_particle.color_start.g    = 1.0;
//    data_particle.color_start.b    = 1.0;
//    data_particle.color_start.a    = 1.0;
    
//    data_particle.color_end.r    = 0.0;
//    data_particle.color_end.g    = 0.0;
//    data_particle.color_end.b    = 0.0;
//    data_particle.color_end.a    = 0.1;
    
//    data_particle.color_delta.r    = 0.0;
//    data_particle.color_delta.g    = 0.0;
//    data_particle.color_delta.b    = 0.0;
//    data_particle.color_delta.a    = 0.0; // is modifed iduvidually for each particle
    
//    TextureOb* texOb_particle = TextureCollector::Instance().GetTexObByColorId(TYPE::TEXTURE::PARTICLE_EFFECT, color_id);
    
//    DamageEffect* damage = new DamageEffect();
    
//    damage->SetTextureOb(texOb_particle);
//    damage->SetParticleData(data_particle);
//    damage->SetParticlesNum(particles_num);
    
//    damage->setParent(parent);
//    damage->setCenter(parent->center());
    
//    damage->CreateParticles();
    
//    return damage;
//}

} // namespace particlesystem
} // namespace jeti
