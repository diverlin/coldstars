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


#ifndef DRIVEJET_H
#define DRIVEJET_H




class particleForDriveTrailEffect
{
   public:
       int num;

       float* pTo_start_pos_x;
       float* pTo_start_pos_y;             // self.pos_orig = ob.points.midLeft
       float pos_x, pos_y;                 // self.pos = [ob.points.midLeft[0], ob.points.midLeft[1]]

       float alpha_start;
       float alpha_end; 
       float d_alpha;
       float alpha;

     particleForDriveTrailEffect(float* _pTo_pos_orig_x, 
     				 float* _pTo_pos_orig_y, 
     				 float _alpha_start, 
     				 float _alpha_end, 
     				 float _d_alpha, 
     				 int _num);  // fake
     				 
     void update(float dx, float dy);
     void render();
};
typedef std::vector<particleForDriveTrailEffect*> VEC_pParticleForDriveTrailEffect_type; 









class DriveTrailEffect
{
   public:
       Ship* pTo_ship;
       TextureOb* pTo_texOb;

       GLuint texture;

       float* pTo_OB_angle_inD;

       float* pTo_start_pos_x;       //ob.points.midLeft
       float* pTo_start_pos_y;

       float* pTo_target_pos_x;     //ob.points.midFarLeft
       float* pTo_target_pos_y;  

       int num_particles;

       float size;

       float velocity_orig;             
       float velocity_x, velocity_y;

       float particle_offset;

       VEC_pParticleForDriveTrailEffect_type particles_pList;

       DriveTrailEffect(TextureOb* _pTo_texOb, 
       			float* _pTo_OB_angle_inD, 
       			vec2f* _pTo_start_pos, 
       			vec2f* _pTo_target_pos, 
       			int _num_particles, 
       			float _size, 
       			float _velocity_orig, 
       			float _alpha_start, 
       			float _alpha_end, 
       			float _d_alpha);

       ~DriveTrailEffect();
       void generateParticles(); 
       void updateVelocity();
       void putParticlesToInitPos();
       void update();
       void render();
};  
typedef std::vector<DriveTrailEffect*>  VEC_pDriveTrailEffect_type; 



#endif
