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


DamageEffect :: DamageEffect(TextureOb* _pTo_texOb, 
			     float* _pTo_center_x, 
			     float* _pTo_center_y, 
			     int _num_particles, 
			     float _pSize, 
			     float _velocity_start, 
			     float _alpha_start, 
			     float _alpha_end, 
			     float _d_alpha)
{
    	is_alive = true;
    	is_dying = false;

    	pTo_center_x = _pTo_center_x;
    	pTo_center_y = _pTo_center_y;

    	texture = _pTo_texOb->texture;
    	num_particles = _num_particles;
    	pSize = _pSize;

    	velocity_start = _velocity_start;
    	alpha_start = _alpha_start;
    	alpha_end = _alpha_end;

   	for (unsigned int i = 0; i < num_particles; i++)
   	{
        	ParticleForDamageEffect* pTo_particle = new ParticleForDamageEffect(pTo_center_x, 
        								    	    pTo_center_y, 
        								            velocity_start, 
        								            alpha_start, 
        								            alpha_end, 
        								            randIntInRange(3,6)*0.01);
        	particles_pList.push_back(pTo_particle);
    	} 
}

DamageEffect :: ~DamageEffect()
{}


bool DamageEffect :: getAlive() const { return is_alive; }
bool DamageEffect :: setDying() { is_dying = true; }


void DamageEffect :: update()
{
     	is_alive = false;

     	if (is_dying == false)
     	{
        	for (unsigned int pi=0; pi < particles_pList.size(); pi++)
        	{
            		particles_pList[pi]->updateLoop();
            		is_alive = true;
        	}	 
     	} 
     	else
     	{
        	for (unsigned int pi=0; pi < particles_pList.size(); pi++)
        	{
            		if (particles_pList[pi]->getAlive() == true)
            		{
                		particles_pList[pi]->updateLast();
                		is_alive = true;
            		}
            	}
     	}
}

void DamageEffect :: render()
{
     	glBindTexture(GL_TEXTURE_2D, texture);
     	glPointSize(pSize);

     	glBegin(GL_POINTS);
     		for (unsigned int pi=0; pi < particles_pList.size(); pi++)
     		{
         		if (particles_pList[pi]->getAlive() == true)
         		{
             			particles_pList[pi]->render();
             		}
        	}
     	glEnd();
}













ParticleForDamageEffect :: ParticleForDamageEffect(float* _pTo_center_x, 
						   float* _pTo_center_y, 
						   float _velocity_start, 
						   float _alpha_start, 
						   float _alpha_end, 
						   float _d_alpha)
{
     	is_alive = true;

     	pTo_center_x = _pTo_center_x;
     	pTo_center_y = _pTo_center_y;
  

     	alpha_start = _alpha_start;
     	alpha_end   = _alpha_end;
     	d_alpha     = _d_alpha;
     	alpha       = _alpha_start;


    	velocity_start = _velocity_start;

     	if (randIntInRange(1,2) == 1)
        	fastCalcVelocityVector();
     	else
        	accurateCalcVelocityVector();
}


bool ParticleForDamageEffect :: getAlive() const  { return is_alive; }   
   		
      		
void ParticleForDamageEffect :: fastCalcVelocityVector()
{
    	float dx_n = randIntInRange(0, 10)*getRandomSign()*0.1;
    	float dy_n = randIntInRange(0, 10)*getRandomSign()*0.1;

    	velocity_x = dx_n * velocity_start;
    	velocity_y = dy_n * velocity_start;
}


void ParticleForDamageEffect :: accurateCalcVelocityVector()
{
    	float _len   = randIntInRange(50, 100);
    	float _angle = randIntInRange(0, 360)/57.0;

    	float target_x = pos_x + sin(_angle) * _len;
    	float target_y = pos_y + cos(_angle) * _len;

    	float xl = (target_x - pos_x);
    	float yl = (target_y - pos_y);

    	float dx_n = xl/_len;
    	float dy_n = yl/_len;

    	velocity_x = dx_n * velocity_start;
    	velocity_y = dy_n * velocity_start;
}  


void ParticleForDamageEffect :: updateLoop()
{
    	pos_x += velocity_x;
    	pos_y += velocity_y; 
    	alpha  -= d_alpha;
          
    	if (alpha < alpha_end)
    	{
       		alpha = alpha_start;
       		pos_x = (*pTo_center_x);
       		pos_y = (*pTo_center_y);

       		if (randIntInRange(1,2) == 1)
          		fastCalcVelocityVector();
       		else
          		accurateCalcVelocityVector();
    	}
}

void ParticleForDamageEffect :: updateLast()
{
     	pos_x += velocity_x;
     	pos_y += velocity_y;
     	alpha -= d_alpha;
          
     	if (alpha < alpha_end)
     	{
         	is_alive = false;
        }
}

void ParticleForDamageEffect :: render()
{
     	glColor4f(1.0, 1.0, 1.0, alpha);
     	glVertex3f(pos_x, pos_y, -2);
}












