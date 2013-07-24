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

#include "../../common/constants.hpp"
#include "../../resources/TextureManager.hpp"
#include "../../common/rand.hpp"

ExplosionSlice::ExplosionSlice()
{}
 
/* virtual override final */
ExplosionSlice::~ExplosionSlice()
{}

void ExplosionSlice::CreateParticles()
{
	for(int i=0; i<num_particles; i++)
	{  
		Particle* particle = new Particle(data_particle);
		particle->CalcRandomVelocity();
		particles_vec.push_back(particle);
	}
}

/* virtual override final */
void ExplosionSlice::Update()
{
	is_alive = false;
	for (unsigned int i=0; i<num_particles; i++)
	{
		if (particles_vec[i]->GetAlive() == true)
		{
			particles_vec[i]->Update();
			is_alive = true;
		}
	}  
}     

/* virtual override final */
void ExplosionSlice::Render(float scale)
{
	glBindTexture(GL_TEXTURE_2D, textureOb->texture);
	for(unsigned int i=0; i<num_particles; i++)
	{
		particles_vec[i]->Render(scale);
	}  
}  
     



ExplosionEffect::ExplosionEffect(float radius):
radius(radius)
{
	type_id = EFFECT::EXPLOSION_ID;
	
	TextureOb* texOb_particle; 
	ParticleData  data_particle;
	int particles_num;
	
	this->radius = radius;
	
	int size_id = CONVERTER::SIZE2SIZEID.GetEquivalent(this->radius);
	 
	//data_particle.velocity_start = getRandInt(13,17) * 0.1;   
	data_particle.velocity_start = (float)size_id*0.1f + getRandInt(40,90) * 0.01;
	data_particle.velocity_end   = data_particle.velocity_start;
	data_particle.d_velocity     = 0;

	data_particle.color_start.r    = 1.0;
	data_particle.color_start.g    = 1.0;
	data_particle.color_start.b    = 1.0;
	data_particle.color_start.a    = 1.0;

	data_particle.color_end.r    = 0.0;
	data_particle.color_end.g    = 0.0;
	data_particle.color_end.b    = 0.0;
	data_particle.color_end.a    = 0.0;

	data_particle.color_delta.r    = 0.0;
	data_particle.color_delta.g    = 0.0;
	data_particle.color_delta.b    = 0.0;
	data_particle.color_delta.a    = getRandInt(20,30) * 0.0004;

	
	//data_particle.size_start
	data_particle.size_end 	     = 2.0;		
	data_particle.d_size 	     = (float)size_id*0.4f + getRandInt(30,50) * 0.02;  
        
	if (size_id == 1)
	{
		particles_num = 30;    
		data_particle.size_start  = 50 * size_id;                                         

		texOb_particle = TextureManager::Instance().GetTexObByColorId(TEXTURE::PARTICLE_EFFECT_ID, COLOR::RED_ID);
		
		ExplosionSlice* explosion_slice = new ExplosionSlice();
		explosion_slice->SetTextureOb(texOb_particle);
		explosion_slice->SetParticleData(data_particle);
		explosion_slice->SetParticlesNum(particles_num);
		
		explosion_slice->CreateParticles();
		
		Add(explosion_slice);
	}
    	else    
	{
		{
		particles_num = 40;
		data_particle.size_start  = 50 * size_id;
		
		texOb_particle = TextureManager::Instance().GetTexObByColorId(TEXTURE::PARTICLE_EFFECT_ID, COLOR::RED_ID);
		
		ExplosionSlice* explosion_slice = new ExplosionSlice();
		explosion_slice->SetTextureOb(texOb_particle);
		explosion_slice->SetParticleData(data_particle);
		explosion_slice->SetParticlesNum(particles_num);
		
		explosion_slice->CreateParticles();
		
		Add(explosion_slice);
		}

		{
		particles_num = 50;
		data_particle.size_start  = 40 * size_id;
		
		texOb_particle = TextureManager::Instance().GetTexObByColorId(TEXTURE::PARTICLE_EFFECT_ID, COLOR::YELLOW_ID);
		
		ExplosionSlice* explosion_slice = new ExplosionSlice();
		explosion_slice->SetTextureOb(texOb_particle);
		explosion_slice->SetParticleData(data_particle);
		explosion_slice->SetParticlesNum(particles_num);
		
		explosion_slice->CreateParticles();
		
		Add(explosion_slice);
		}
	
		{
		particles_num = 60;                              
		data_particle.size_start  = 30 * size_id;
		
		texOb_particle = TextureManager::Instance().GetTexObByColorId(TEXTURE::PARTICLE_EFFECT_ID, COLOR::RED_ID);
		
		ExplosionSlice* explosion_slice = new ExplosionSlice();
		explosion_slice->SetTextureOb(texOb_particle);
		explosion_slice->SetParticleData(data_particle);
		explosion_slice->SetParticlesNum(particles_num);
		
		explosion_slice->CreateParticles();
		
		Add(explosion_slice);
		}
	} 	   


}
 
/* virtual override final */
ExplosionEffect::~ExplosionEffect()
{
	for (unsigned int i=0; i<slice_vec.size(); i++)
	{
		delete slice_vec[i];
	}
}

/* virtual override final */
void ExplosionEffect::Update()
{
	is_alive = false;
	for (unsigned int i=0; i<slice_vec.size(); i++)
	{
		if (slice_vec[i]->GetAlive() == true)
		{
			slice_vec[i]->Update();
			is_alive = true;
		}        	
	}  
}     
    
/* virtual override final */
void ExplosionEffect::Render(float scale)
{
	glPushMatrix();
	{
		glTranslatef(center.x, center.y, 0.0);	
	   	for (unsigned int i=0; i<slice_vec.size(); i++)
	   	{
	   		slice_vec[i]->Render(scale);
	   	}         
	}
	glPopMatrix();  
}  

ExplosionEffect* getNewExplosionEffect(float radius)
{
	//size_id = getRandInt(1,9); // DEBUG
	ExplosionEffect* explosion = new ExplosionEffect(radius);
	return explosion;
} 
