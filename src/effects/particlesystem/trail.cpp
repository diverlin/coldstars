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



TrailEffect :: TrailEffect(TextureOb* _texOb, 
			   vec2f* _pTo_start_pos, 
			   vec2f* _pTo_target_pos, 
			   ParticleData _data_particle,
			   int _num_particles)
{
     	texOb = _texOb;
     	data_particle = _data_particle;
 
     	pTo_start_pos_x = &_pTo_start_pos->x;       //ob.points.midLeft
     	pTo_start_pos_y = &_pTo_start_pos->y;

     	pTo_target_pos_x = &_pTo_target_pos->x;     //ob.points.midFarLeft
     	pTo_target_pos_y = &_pTo_target_pos->y;  

     	particle_offset = (_data_particle.alpha_start - _data_particle.alpha_end) / _num_particles; 


     	updateVelocity();
     	
	bool _variation = false;
     	for (unsigned int i = 0; i < _num_particles; i++)
     	{
         	Particle* particle = new Particle(*_pTo_start_pos, _data_particle, _variation);  
         				   
         	particle->setVelocity(velocity);
         	particles_vec.push_back(particle);
     	}

     	putParticlesToInitPos();
}


TrailEffect :: ~TrailEffect()
{
	for (int i = 0; i < particles_vec.size(); i++) 
     	{
  		delete particles_vec[i];
     	}
}


void TrailEffect :: updateVelocity()
{
     	float xl = ((*pTo_target_pos_x) - (*pTo_start_pos_x));
     	float yl = ((*pTo_target_pos_y) - (*pTo_start_pos_y));
     	float l = sqrt(xl*xl + yl*yl);

     	float d_xn = xl / l;
     	float d_yn = yl / l;

     	velocity.x = d_xn * data_particle.velocity_start;
     	velocity.y = d_yn * data_particle.velocity_start;
}


void TrailEffect :: putParticlesToInitPos()
{
     	for (int i = 0; i < particles_vec.size(); i++) 
     	{
         	while ( particles_vec[i]->getAlpha() > ( particles_vec[i]->getAlphaStart() - i * particle_offset) ) 
         	{
            		particles_vec[i]->update();
         	}     
     	}
}


void TrailEffect :: update()
{
     	updateVelocity();

     	for (unsigned int i = 0; i < particles_vec.size(); i++) 
     	{
     		if (particles_vec[i]->getAlive() == true)
     		{
            		particles_vec[i]->update();
            	}
            	else
            	{
            		particles_vec[i]->reborn(vec2f(*pTo_start_pos_x, *pTo_start_pos_y), velocity);
            	}
	}
}



void TrailEffect :: render()
{
       	enable_POINTSPRITE();
       	
     		glBindTexture(GL_TEXTURE_2D, texOb->texture);
     		for (unsigned int i = 0; i < particles_vec.size(); i++) 
     		{
         		particles_vec[i]->render();
     		}
	disable_POINTSPRITE();
}





TrailEffect* createTrailEffect(int size_id, vec2f* pTo_pos, vec2f* pTo_target_pos)
{
	TextureOb* texOb_particle = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);

   	ParticleData data_particle;
   	data_particle.size_start = 15.0 + size_id;
   	data_particle.size_end   = 0.1;
   	data_particle.d_size     = 0.0;
   	   	
   	data_particle.velocity_start = 1.2;
   	data_particle.velocity_end   = 1.2;   	
   	data_particle.d_velocity     = 0.0; 
   	
   	data_particle.alpha_start = 0.6;
   	data_particle.alpha_end   = 0.0;
   	data_particle.d_alpha     = 0.05;  	
   	   	
   	int particles_num = 5;
   	   	
   	TrailEffect* drive_trail = new TrailEffect(texOb_particle, 
   					 	   pTo_pos,  
   					 	   pTo_target_pos, 
   					 	   data_particle,
   					 	   particles_num);
  	return drive_trail;   	
}


