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


#include "explosion.hpp"

           
ExplosionEffect :: ExplosionEffect(TextureOb* _texOb, vec2f _center_pos, ParticleData _data_particle, int _num_particles)
{  
    	is_alive = true;
            
    	texOb = _texOb;

	bool _variation = true;
    	for(int i=0;i<_num_particles;i++)
    	{  
       		Particle* _particle = new Particle(_center_pos, _data_particle, _variation);
       		particles_vec.push_back(_particle);
    	}
}
 
ExplosionEffect :: ~ExplosionEffect()
{
	for (int i = 0; i < particles_vec.size(); i++) 
     	{
  		delete particles_vec[i];
     	}
}


bool ExplosionEffect :: getAlive() const { return is_alive; }


void ExplosionEffect :: update()
{
    	is_alive = false;
    	for(int i = 0; i<particles_vec.size(); i++)
    	{
        	if (particles_vec[i]->getAlive() == true)
        	{
           		particles_vec[i]->update();
           		is_alive = true;
        	}
    	}  
}     
    

void ExplosionEffect :: render()
{
    	glBindTexture(GL_TEXTURE_2D, texOb->texture);
    	for(unsigned int i = 0; i<particles_vec.size(); i++)
    	{
		particles_vec[i]->render();
    	}            
}  



                 


void  createExplosion(StarSystem* _starsystem, vec2f _center_pos, int obSize)
{
	//obSize = getRandInt(1, 9);  	// DEBUG
	ExplosionEffect* explosion;
	
	TextureOb* texOb_particle; 
	ParticleData  data_particle;
	int particles_num;
   
	data_particle.velocity_start = getRandInt(13,17) * 0.1;
	data_particle.velocity_end   = data_particle.velocity_start;
	data_particle.d_velocity     = 0;

	data_particle.alpha_start    = 1.0;
	data_particle.alpha_end      = 0.1;
	data_particle.d_alpha        = getRandInt(5,8) * 0.001;
	
	//data_particle.size_start
	data_particle.size_end 	     = 0.1;
	data_particle.d_size 	     = getRandInt(60,80) * 0.01; 
        
	if (obSize < 4)
	{
		particles_num = getRandInt(10 * obSize, 15 * obSize);    
		data_particle.size_start  = 25 * obSize;                                 

		texOb_particle = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);

		explosion = new ExplosionEffect(texOb_particle, _center_pos, data_particle, particles_num);
		_starsystem->addExplosionEffect(explosion);
	}
    	else    
	{
		particles_num = 40;
		data_particle.size_start  = 25 * obSize;

		texOb_particle = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);
		
		explosion = new ExplosionEffect(texOb_particle, _center_pos, data_particle, particles_num);
		_starsystem->addExplosionEffect(explosion);
       

		particles_num = 50;
		data_particle.size_start  = 25 * (obSize-1);

		texOb_particle = g_TEXTURE_MANAGER.returnParticleTexObByColorId(YELLOW_COLOR_ID);
		
		explosion = new ExplosionEffect(texOb_particle, _center_pos, data_particle, particles_num);
		_starsystem->addExplosionEffect(explosion);
       
		particles_num = 100;                              
		data_particle.size_start  = 25 * (obSize-2);

		texOb_particle = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);
		
		explosion = new ExplosionEffect(texOb_particle, _center_pos, data_particle, particles_num);
		_starsystem->addExplosionEffect(explosion);
	} 	       
 
 	if ( (obSize > 3) && (_starsystem->getShockWaveNum() < 10) )
	{
		createShockWave(_starsystem, _center_pos, obSize);
	}
	//explosion.play()
} 
