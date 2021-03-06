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

#include "ExplosionEffect.hpp"
#include "effects/particlesystem/Particle.hpp"
#include <common/constants.hpp>
#include <resources/TextureManager.hpp>

#include <math/rand.hpp>

ExplosionEffect::ExplosionEffect(float radius)
:
m_Radius(radius)
{
    m_TypeId = EFFECT::EXPLOSION_ID;
    
    m_TextureOb = TextureManager::Instance().GetTexObByColorId(TYPE::TEXTURE::PARTICLE_EFFECT_ID, COLOR::RED_ID); 
    m_ParticlesNum = 1000;
    
    int size_id = CONVERTER::SIZE2SIZEID.GetEquivalent(m_Radius);
     
    //data_particle.velocity_start = getRandInt(13,17) * 0.1;   
    m_DataParticle.velocity_start = (float)size_id*0.1f + getRandInt(40,90) * 0.01;
    m_DataParticle.velocity_end   = m_DataParticle.velocity_start;
    m_DataParticle.d_velocity     = 0;

    m_DataParticle.color_start.r    = 1.0;
    m_DataParticle.color_start.g    = 1.0;
    m_DataParticle.color_start.b    = 1.0;
    m_DataParticle.color_start.a    = 1.0;

    m_DataParticle.color_end.r    = 0.0;
    m_DataParticle.color_end.g    = 0.0;
    m_DataParticle.color_end.b    = 0.0;
    m_DataParticle.color_end.a    = 0.0;

    m_DataParticle.color_delta.r    = 0.0;
    m_DataParticle.color_delta.g    = 0.0;
    m_DataParticle.color_delta.b    = 0.0;
    m_DataParticle.color_delta.a    = getRandInt(20,30) * 0.0004;

    
    //data_particle.size_start
    m_DataParticle.size_end          = 2.0;        
    m_DataParticle.d_size          = (float)size_id*0.04f + getRandInt(30,50) * 0.002;  
        

    m_DataParticle.size_start  = 10 * size_id;                                         
        
    CreateParticles();
    //else    
    //{
        //{
        //particles_num = 40;
        //data_particle.size_start  = 50 * size_id;
        
        //texOb_particle = TextureManager::Instance().GetTexObByColorId(TYPE::TEXTURE::PARTICLE_EFFECT_ID, COLOR::RED_ID);
        
        //ExplosionEffect* explosion_slice = new ExplosionEffect();
        //explosion_slice->SetTextureOb(texOb_particle);
        //explosion_slice->SetParticleData(data_particle);
        //explosion_slice->SetParticlesNum(particles_num);
        
        //explosion_slice->CreateParticles();
        
        //Add(explosion_slice);
        //}

        //{
        //particles_num = 50;
        //data_particle.size_start  = 40 * size_id;
        
        //texOb_particle = TextureManager::Instance().GetTexObByColorId(TYPE::TEXTURE::PARTICLE_EFFECT_ID, COLOR::YELLOW_ID);
        
        //ExplosionEffect* explosion_slice = new ExplosionEffect();
        //explosion_slice->SetTextureOb(texOb_particle);
        //explosion_slice->SetParticleData(data_particle);
        //explosion_slice->SetParticlesNum(particles_num);
        
        //explosion_slice->CreateParticles();
        
        //Add(explosion_slice);
        //}
    
        //{
        //particles_num = 60;                              
        //data_particle.size_start  = 30 * size_id;
        
        //texOb_particle = TextureManager::Instance().GetTexObByColorId(TYPE::TEXTURE::PARTICLE_EFFECT_ID, COLOR::RED_ID);
        
        //ExplosionEffect* explosion_slice = new ExplosionEffect();
        //explosion_slice->SetTextureOb(texOb_particle);
        //explosion_slice->SetParticleData(data_particle);
        //explosion_slice->SetParticlesNum(particles_num);
        
        //explosion_slice->CreateParticles();
        
        //Add(explosion_slice);
        //}
    //} 
}
 
/* virtual override final */
ExplosionEffect::~ExplosionEffect()
{}

void ExplosionEffect::CreateParticles()
{
    for(unsigned int i=0; i<m_ParticlesNum; i++)
    {  
        Particle* particle = new Particle(m_DataParticle);
        particle->CalcRandomVelocity();
        m_Particles.push_back(particle);
    }
}

/* virtual override final */
void ExplosionEffect::Update()
{
    BaseParticleSystem::Update();

    m_IsAlive = false;
    for (unsigned int i=0; i<m_ParticlesNum; i++)
    {
        if (m_Particles[i]->GetIsAlive() == true)
        {
            m_Particles[i]->Update();
            m_IsAlive = true;
        }
    }  
}

   
ExplosionEffect* getNewExplosionEffect(float radius)
{
    //size_id = getRandInt(1,9); // DEBUG
    ExplosionEffect* explosion = new ExplosionEffect(radius);
    return explosion;
} 
