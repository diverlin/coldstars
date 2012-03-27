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



TrailEffect :: TrailEffect(vec2f* _pTo_start_pos, 
			   vec2f* _pTo_target_pos)
{
    	pTo_start_pos  = _pTo_start_pos;      //ob.points.midLeft
     	pTo_target_pos = _pTo_target_pos;     //ob.points.midFarLeft
}


TrailEffect :: ~TrailEffect()
{}

void TrailEffect :: createParticles()
{
     	for (unsigned int i = 0; i < num_particles; i++)
     	{
         	Particle* particle = new Particle(data_particle);  
                particle->setPosition(*pTo_start_pos);
         	particle->setVelocity(velocity);
         	particles_vec.push_back(particle);
     	}
}


void TrailEffect :: updateVelocity()
{
     	float xl = (pTo_target_pos->x - pTo_start_pos->x);
     	float yl = (pTo_target_pos->y - pTo_start_pos->y);
     	float l = sqrt(xl*xl + yl*yl);

     	float d_xn = xl / l;
     	float d_yn = yl / l;

     	velocity.x = d_xn * data_particle.velocity_start;
     	velocity.y = d_yn * data_particle.velocity_start;
}


void TrailEffect :: putParticlesToInitPos()
{
        float particle_offset = (data_particle.color_start.a - data_particle.color_end.a) / num_particles; 
        
     	for (unsigned int i = 0; i < particles_vec.size(); i++) 
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
                        particles_vec[i]->setPosition(*pTo_start_pos);
                        particles_vec[i]->setVelocity(velocity);
            		particles_vec[i]->reborn();
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
   	ParticleData data_particle;        
                       
   	data_particle.size_start = 15.0 + size_id;
   	data_particle.size_end   = 0.1;
   	data_particle.d_size     = 0.0;
   	   	
   	data_particle.velocity_start = 1.2;
   	data_particle.velocity_end   = 1.2;   	
   	data_particle.d_velocity     = 0.0; 
        
        data_particle.color_start.r    = 1.0;
	data_particle.color_start.g    = 1.0;
	data_particle.color_start.b    = 1.0;
        data_particle.color_start.a    = 0.9;

	data_particle.color_end.r    = 0.0;
	data_particle.color_end.g    = 0.0;
	data_particle.color_end.b    = 0.0;
        data_particle.color_end.a    = 0.1;

	data_particle.color_delta.r    = 0.0;
	data_particle.color_delta.g    = 0.0;
	data_particle.color_delta.b    = 0.0;
        data_particle.color_delta.a    = 0.1;
        
   	   	
   	int particles_num = 5;
                        
                       
        TextureOb* texOb_particle = g_TEXTURE_MANAGER.getTexObByColorId(TEXTURE::PARTICLE_EFFECT_ID, COLOR::RED_ID);
   	TrailEffect* drive_trail = new TrailEffect(pTo_pos, pTo_target_pos);
        
        drive_trail->setTextureOb(texOb_particle);                                 
        drive_trail->setParticleData(data_particle);
        drive_trail->setParticlesNum(particles_num);
        
        drive_trail->updateVelocity();
     	drive_trail->createParticles();
     	drive_trail->putParticlesToInitPos();
                
  	return drive_trail;
}


