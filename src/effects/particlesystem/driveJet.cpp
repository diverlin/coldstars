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


#include "driveJet.hpp"




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








