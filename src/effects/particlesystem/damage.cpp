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


#include "damage.hpp"


DamageEffect :: DamageEffect(TextureOb* _texOb, 
			     float* _pTo_center_x,
			     float* _pTo_center_y, 
			     ParticleData _data_particle,
			     int _num_particles)
{
    	is_alive = true;
    	is_dying = false;

    	pTo_center_x = _pTo_center_x;
    	pTo_center_y = _pTo_center_y;

    	texOb = _texOb;
    	
    	data_particle = _data_particle;


	bool _variation = true;
   	for (unsigned int i = 0; i < _num_particles; i++)
   	{
        	Particle* particle = new Particle(vec2f(*pTo_center_x, *pTo_center_y), _data_particle, _variation);  
        	particle->randomize_d_alpha(0.003, 0.006);    					  
        	particles_vec.push_back(particle);
    	} 
}

DamageEffect :: ~DamageEffect()
{
	for (int i = 0; i < particles_vec.size(); i++) 
     	{
  		delete particles_vec[i];
     	}
}


bool DamageEffect :: getAlive() const { return is_alive; }
bool DamageEffect :: setDying() { is_dying = true; }


void DamageEffect :: update()
{
     	is_alive = false;

        for (unsigned int pi=0; pi < particles_vec.size(); pi++)
        {
                if (particles_vec[pi]->getAlive() == true)
        	{
            		particles_vec[pi]->update();
            		is_alive = true;
            	}
            	else
            	{
            		if (is_dying == false)
            		{
            			particles_vec[pi]->reborn(vec2f(*pTo_center_x, *pTo_center_y));
            		}
            	}
        }
}

void DamageEffect :: render()
{
     	glBindTexture(GL_TEXTURE_2D, texOb->texture);
	for (unsigned int pi=0; pi < particles_vec.size(); pi++)
	{
       		particles_vec[pi]->render();
       	}
}





DamageEffect* createDamageEffect( TextureOb* _texOb, float* pTo_center_x, float* pTo_center_y)
{
	int particles_num = 5;
   
    	ParticleData data_particle;
        data_particle.size_start = 30;
        data_particle.size_end = 0.1;
        data_particle.d_size = 0.001; 
        
        data_particle.velocity_start = 1.3;
        data_particle.velocity_end   = 1.3;        
        data_particle.d_velocity   = 0.0;
                
	data_particle.alpha_start = 1.0; 
	data_particle.alpha_end = 0.1; 
	data_particle.d_alpha = 0;   // is modifed iduvidually for each particle                       

	DamageEffect* damage = new DamageEffect(_texOb, pTo_center_x, pTo_center_y, data_particle, particles_num);
	return damage;
}

