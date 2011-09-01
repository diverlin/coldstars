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


#include "effects.h"


DamageEffect :: DamageEffect(TextureOb* _pTo_texOb, 
			     StarSystem* _pTo_starsystem, 
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

    pTo_starsystem = _pTo_starsystem;
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
            if (particles_pList[pi]->is_alive == true)
            {
                particles_pList[pi]->updateLast();
                is_alive = true;
            }
     }
}

void DamageEffect :: render()
{
     glBindTexture(GL_TEXTURE_2D, texture);
     glPointSize(pSize);

     glBegin(GL_POINTS);
     for (unsigned int pi=0; pi < particles_pList.size(); pi++)
         if (particles_pList[pi]->is_alive == true)
             particles_pList[pi]->render();
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

void ParticleForDamageEffect :: fastCalcVelocityVector()
{
    float dx_n = randIntInRange(0, 10)*randomInverse()*0.1;
    float dy_n = randIntInRange(0, 10)*randomInverse()*0.1;

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
         is_alive = false;
}

void ParticleForDamageEffect :: render()
{
     glColor4f(1.0, 1.0, 1.0, alpha);
     glVertex3f(pos_x, pos_y, -2);
}









           
ExplosionEffect :: ExplosionEffect(TextureOb* _pTo_texOb, vec2f _center_pos, ParticleSystemData _psData)
{  
    is_alive = true;
    alreadyInRemoveQueue = false;
            
    pTo_texOb = _pTo_texOb;
    starsystem = NULL;

    texture = pTo_texOb->texture;

    center_x = _center_pos.x;
    center_y = _center_pos.y;

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


void ExplosionEffect :: setStarSystem(StarSystem* _starsystem) { starsystem = _starsystem; }



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
    glBindTexture(GL_TEXTURE_2D, texture);
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
    float animation_speed_rate = 0.5; //???? 

    center_x_start = _center_pos.x;
    center_y_start = _center_pos.y;
          
    size_start = _psData.particleSize_start;
    d_size = _psData.d_particleSize * animation_speed_rate;
          
    velocity_start = _psData.velocity_start * animation_speed_rate;
    d_velocity = _psData.d_velocity;
          
    alpha_start = _psData.alpha_start;
    alpha_end = _psData.alpha_end;
    d_alpha = _psData.d_alpha * animation_speed_rate;


    center_x = center_x_start;
    center_y = center_y_start;  

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
    float dx_n = randIntInRange(0, 10)*randomInverse()*0.1;
    float dy_n = randIntInRange(0, 10)*randomInverse()*0.1;

    velocity_x = dx_n * velocity_start;
    velocity_y = dy_n * velocity_start;
}


void ParticleForExplosionEffect :: accurateCalcVelocityVector()
{
    float _len   = randIntInRange(50, 100);
    float _angle = randIntInRange(0, 360)/57.0;

    float target_x = center_x + sin(_angle) * _len;
    float target_y = center_y + cos(_angle) * _len;

    float xl = (target_x - center_x);
    float yl = (target_y - center_y);

    float dx_n = xl/_len;
    float dy_n = yl/_len;

    velocity_x = dx_n * velocity_start;
    velocity_y = dy_n * velocity_start;
}  
          

void ParticleForExplosionEffect :: update()
{
    //printf("size = %f\n", size); 
    center_x += velocity_x;
    center_y += velocity_y; 

    alpha -= d_alpha;
    size -= d_size;

    if ((alpha <= alpha_end) or (size < 1))
    {   //printf("SOMETHING WRONG WITH PARTICLES, %f, %f\n", alpha, size);
        //alpha = 0.1;          // hack
        //size = 100;           // hack
        is_alive = false;
    }
}
    
       
void ParticleForExplosionEffect :: render()
{ 
    glColor4f(1.0f, 1.0f, 1.0f, alpha);
    glVertex3f(center_x, center_y , -2);
}            
                  









DriveTrailEffect :: DriveTrailEffect(TextureOb* _pTo_texOb, 
				     float* _pTo_OB_angle_inD, 
				     vec2f* _pTo_start_pos, 
				     vec2f* _pTo_target_pos, 
				     int _num_particles, 
				     float _size, 
				     float _velocity_orig, 
				     float _alpha_start, 
				     float _alpha_end, 
				     float _d_alpha)
{
     pTo_texOb = _pTo_texOb;
 
     texture = (*pTo_texOb).texture;

     pTo_OB_angle_inD = _pTo_OB_angle_inD;

     pTo_start_pos_x = &_pTo_start_pos->x;       //ob.points.midLeft
     pTo_start_pos_y = &_pTo_start_pos->y;

     pTo_target_pos_x = &_pTo_target_pos->x;     //ob.points.midFarLeft
     pTo_target_pos_y = &_pTo_target_pos->y;  

     num_particles = _num_particles;

     size = _size;

     velocity_orig = _velocity_orig;               

     particle_offset = (_alpha_start - _alpha_end) / num_particles; 

     for (unsigned int i = 0; i < num_particles; i++)
     {
         particleForDriveTrailEffect* pTo_particle = new particleForDriveTrailEffect(pTo_start_pos_x, 
         									     pTo_start_pos_y, 
         									     _alpha_start, 
         									     _alpha_end, 
         									     _d_alpha, 
         									     i);  
         particles_pList.push_back(pTo_particle);
     }

     updateVelocity();
     putParticlesToInitPos();
}

void DriveTrailEffect :: updateVelocity()
{
     float xl = ((*pTo_target_pos_x) - (*pTo_start_pos_x));
     float yl = ((*pTo_target_pos_y) - (*pTo_start_pos_y));
     float l = sqrt(xl*xl + yl*yl);

     float d_xn = xl / l;
     float d_yn = yl / l;

     velocity_x = d_xn * velocity_orig;
     velocity_y = d_yn * velocity_orig;
}


void DriveTrailEffect :: putParticlesToInitPos()
{
     for (int i = 0; i < num_particles; i++) 
     {
         while ( (*particles_pList[i]).alpha > ( particles_pList[i]->alpha_start - i * particle_offset) ) 
         {
            particles_pList[i]->update(velocity_x, velocity_y);
         }     
     }
}


void DriveTrailEffect :: update()
{
     //if self.ob.points.angle != self.last_angle:
     updateVelocity();
     //self.last_angle = self.ob.points.angle

     for (unsigned int i = 0; i < particles_pList.size(); i++) 
         (*particles_pList[i]).update(velocity_x, velocity_y);
}



void DriveTrailEffect :: render()
{
     glBindTexture(GL_TEXTURE_2D, texture);

     glPointSize(size);

     glBegin(GL_POINTS);
     for (unsigned int i = 0; i < particles_pList.size(); i++) 
         (*particles_pList[i]).render();
     glEnd();
}








particleForDriveTrailEffect :: particleForDriveTrailEffect(float* _pTo_start_pos_x, 
							   float* _pTo_start_pos_y, 
							   float _alpha_start, 
							   float _alpha_end, 
							   float _d_alpha, 
							   int _num)
{
          num = _num;
          pTo_start_pos_x = _pTo_start_pos_x;
          pTo_start_pos_y = _pTo_start_pos_y;

          pos_x = (*pTo_start_pos_x);
          pos_y = (*pTo_start_pos_y);

          alpha_start = _alpha_start;
          alpha_end   = _alpha_end;
          d_alpha     = _d_alpha;

          alpha = alpha_start;
}

void particleForDriveTrailEffect :: update(float dx, float dy)
{
     pos_x += dx;
     pos_y += dy; 
     alpha -= d_alpha;

     if (alpha < alpha_end)
     {
         pos_x = (*pTo_start_pos_x);
         pos_y = (*pTo_start_pos_y);
         alpha = alpha_start;
     }
}

void particleForDriveTrailEffect :: render()
{
     glColor4f(1.0, 1.0, 1.0, alpha);
     glVertex3f(pos_x, pos_y , -2);
}








