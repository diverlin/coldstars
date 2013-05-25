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
#include "../../resources/TextureManager.hpp"
#include "../../common/constants.hpp"

DamageEffect::DamageEffect()
{
	//subtype_id = DAMAGE_EFFECT_ID;
}

DamageEffect::~DamageEffect()
{}


void DamageEffect::CreateParticles()
{
	for(int i=0; i<num_particles; i++)
    	{  
       		Particle* particle = new Particle(data_particle);
       		particle->Randomize_d_alpha(0.003, 0.006); //   ??
       		particle->CalcRandomVelocity();
       		particles_vec.push_back(particle);
    	}
}

void DamageEffect::Update()
{
     	is_alive = false;
        for (unsigned int i=0; i<num_particles; i++)
        {
                if (particles_vec[i]->GetAlive() == true)
        	{
            		particles_vec[i]->Update();
            		is_alive = true;
            	}
            	else
            	{
            		if (is_dying == false)
            		{
            			particles_vec[i]->Reborn();
            		}
            	}
        }
}

void DamageEffect::Render()
{
	glPushMatrix();
		glTranslatef(parent->GetCenter().x, parent->GetCenter().y, 0.0);
	     	glBindTexture(GL_TEXTURE_2D, textureOb->texture);
		for (unsigned int i=0; i<num_particles; i++)
		{
	       		particles_vec[i]->Render();
	       	}
	glPopMatrix(); 
}





DamageEffect* getNewDamageEffect(int color_id, BaseSpaceEntity* parent)
{
	int particles_num = 10;
   
    	ParticleData data_particle;
        data_particle.size_start = 25;
        data_particle.size_end = 0.1;
        data_particle.d_size = 0.01; 
        
        data_particle.velocity_start = 1.3;
        data_particle.velocity_end   = 1.3;        
        data_particle.d_velocity   = 0.0;
                
        data_particle.color_start.r    = 1.0;
	data_particle.color_start.g    = 1.0;
	data_particle.color_start.b    = 1.0;
        data_particle.color_start.a    = 1.0;

	data_particle.color_end.r    = 0.0;
	data_particle.color_end.g    = 0.0;
	data_particle.color_end.b    = 0.0;
        data_particle.color_end.a    = 0.1;

	data_particle.color_delta.r    = 0.0;
	data_particle.color_delta.g    = 0.0;
	data_particle.color_delta.b    = 0.0;
        data_particle.color_delta.a    = 0.0; // is modifed iduvidually for each particle  
        
        TextureOb* texOb_particle = TextureManager::Instance().GetTexObByColorId(TEXTURE::PARTICLE_EFFECT_ID, color_id);
                
	DamageEffect* damage = new DamageEffect();
        
        damage->SetTextureOb(texOb_particle);        
        damage->SetParticleData(data_particle);
        damage->SetParticlesNum(particles_num);
                
        damage->SetParent(parent);
        damage->SetCenter(parent->GetCenter());
                
        damage->CreateParticles();
                
	return damage;
}

