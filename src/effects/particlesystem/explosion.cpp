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

           
ExplosionEffect :: ExplosionEffect(TextureOb* _texOb, vec2f _center_pos, ParticleSystemData _psData)
{  
    	is_alive = true;
    	alreadyInRemoveQueue = false;
            
    	texOb = _texOb;

    	center = _center_pos;

    	num_particles = _psData.particles_num;
    	pSize_start   = _psData.particleSize_start;

    
    	for(int i=0;i<num_particles;i++)
    	{  
       		//velocity_start = randIntInRange(50, 100)*0.005;
       		//printf("rand=%f, i=%i\n",d_velocity, i);
       		ParticleForExplosionEffect* _particle = new ParticleForExplosionEffect(_center_pos, _psData, i);
       		particles_pList.push_back(_particle);
    	}
}
 
ExplosionEffect :: ~ExplosionEffect()
{}



void ExplosionEffect :: update()
{
    	is_alive = false;
    	for(int i = 0; i<particles_pList.size(); i++)
    	{
        	if (particles_pList[i]->is_alive == true)
        	{
           		particles_pList[i]->update();
           		is_alive = true;
        	}
    	}  
      
    	if(is_alive == false)
    	{
        	if(alreadyInRemoveQueue == false)
        	{
            		//self.starsystem.effect_EXPLOSION_remove_queue.append(self)  
            		alreadyInRemoveQueue = true;
        	}      
    	}
}     

    

void ExplosionEffect :: render()
{
    	glBindTexture(GL_TEXTURE_2D, texOb->texture);
    	for(unsigned int i = 0; i<particles_pList.size(); i++)
    	{
        	if(particles_pList[i]->is_alive == true)
        	{
           		glPointSize(particles_pList[i]->size);
           		glBegin(GL_POINTS);
           			particles_pList[i]->render();
           		glEnd();
        	}
    	}            
}  








ParticleForExplosionEffect :: ParticleForExplosionEffect(vec2f _center_pos,  ParticleSystemData _psData, int _curnum)
{
    	is_alive = true;
    	float animation_speed_rate = randIntInRange(5,8) * 0.1; //???? 
          
    	size_start = _psData.particleSize_start;
    	d_size     = _psData.d_particleSize * animation_speed_rate;
          
    	velocity_start = _psData.velocity_start * animation_speed_rate;
    	d_velocity     = _psData.d_velocity;
          
    	alpha_start = _psData.alpha_start;
    	alpha_end   = _psData.alpha_end;
    	d_alpha     = _psData.d_alpha * animation_speed_rate;

    	center = _center_pos;
    	
    	size = size_start;
    	alpha = alpha_start;
          
    	curnum = _curnum;
          
    	if (randIntInRange(0,10) > 5)
      		accurateCalcVelocityVector();
    	else
      		fastCalcVelocityVector();
}         

ParticleForExplosionEffect :: ~ParticleForExplosionEffect()
{}


void ParticleForExplosionEffect :: fastCalcVelocityVector()
{
    	float dx_n = randIntInRange(0, 10)*getRandomSign()*0.1;
    	float dy_n = randIntInRange(0, 10)*getRandomSign()*0.1;

    	velocity.set(dx_n * velocity_start, dy_n * velocity_start);
}


void ParticleForExplosionEffect :: accurateCalcVelocityVector()
{
    	float _len   = randIntInRange(50, 100);
    	float _angle = randIntInRange(0, 360)/57.0;

    	float target_x = center.x + sin(_angle) * _len;
    	float target_y = center.y + cos(_angle) * _len;

    	float xl = (target_x - center.x);
    	float yl = (target_y - center.y);

    	float dx_n = xl/_len;
    	float dy_n = yl/_len;

    	velocity.set(dx_n * velocity_start, dy_n * velocity_start);
}  
          

void ParticleForExplosionEffect :: update()
{
    	center.x += velocity.x;
    	center.y += velocity.y; 

    	alpha -= d_alpha;
    	size -= d_size;

    	if ((alpha <= alpha_end) or (size < 1))
    	{   	//printf("SOMETHING WRONG WITH PARTICLES, %f, %f\n", alpha, size);
        	//alpha = 0.1;          // hack
        	//size = 100;           // hack
        	is_alive = false;
    	}
}
    
       
void ParticleForExplosionEffect :: render()
{ 
    	glColor4f(1.0f, 1.0f, 1.0f, alpha);
    	glVertex3f(center.x, center.y , -2);
}            
                 
                 
                 
                 


void  createExplosion(StarSystem* _starsystem, vec2f _center_pos, int obSize)
{
	//obSize = randIntInRange(1, 9);  	// DEBUG

	ExplosionEffect* _explosion;

	TextureOb* _particleTexOb; 
	ParticleSystemData  _psData;
   
	_psData.velocity_start = randIntInRange(13,17) * 0.1;
	_psData.velocity_end = _psData.velocity_start;

	_psData.alpha_start    = 1.0;
	_psData.alpha_end      = 0.1;
	
	_psData.d_velocity     = 0;
	_psData.d_alpha        = randIntInRange(5,8) * 0.001;
	_psData.d_particleSize = randIntInRange(60,80) * 0.01;
 
        
	if (obSize < 4)
	{
		_psData.particles_num = randIntInRange(10 * obSize, 15 * obSize);    
		_psData.particleSize_start  = 25 * obSize;                                 

		_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);

		_explosion = new ExplosionEffect(_particleTexOb, _center_pos, _psData);
		_starsystem->addExplosionEffect(_explosion);
	}
    	else    
	{
		_psData.particles_num = 40;
		_psData.particleSize_start  = 25 * obSize;

		_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);
		
		_explosion = new ExplosionEffect(_particleTexOb, _center_pos, _psData);
		_starsystem->addExplosionEffect(_explosion);
       

		_psData.particles_num = 50;
		_psData.particleSize_start  = 25 * (obSize-1);

		_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(YELLOW_COLOR_ID);
		
		_explosion = new ExplosionEffect(_particleTexOb, _center_pos, _psData);
		_starsystem->addExplosionEffect(_explosion);
       
		_psData.particles_num = 100;                              
		_psData.particleSize_start  = 25 * (obSize-2);

		_particleTexOb = g_TEXTURE_MANAGER.returnParticleTexObByColorId(RED_COLOR_ID);
		
		_explosion = new ExplosionEffect(_particleTexOb, _center_pos, _psData);
		_starsystem->addExplosionEffect(_explosion);
	} 	       
 
	createShockWave(_starsystem, _center_pos, obSize);
	//explosion.play()
} 
