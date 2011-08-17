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


#ifndef EFFECTS_H
#define EFFECTS_H

class ParticleForDamageEffect
{
   public:
      bool is_alive;
 
      float* pTo_center_x;
      float* pTo_center_y;  

      float pos_x;
      float pos_y;  

      float alpha_start;
      float alpha_end;
      float d_alpha;
      float alpha;

      float velocity_start;
      float velocity_x;
      float velocity_y;

      ParticleForDamageEffect(float* pTo_center_x, float* pTo_center_y, float _velocity_start, float _alpha_start, float _alpha_end, float _d_alpha);
      ~ParticleForDamageEffect();
      
      void fastCalcVelocityVector();
      void accurateCalcVelocityVector();
      void updateLoop();
      void updateLast();
      void render();
};


class DamageEffect
{
   public: 
       bool is_alive;
       bool is_dying;

       StarSystem* pTo_starsystem;
       float* pTo_center_x;
       float* pTo_center_y;

       GLuint texture;
       int num_particles;
       float pSize;

       float velocity_start;
       float alpha_start;
       float alpha_end;

       VEC_pParticleForDamageEffect_type particles_pList;

       DamageEffect(TextureOb* _pTo_texOb, StarSystem* _pTo_starsystem, float* _pTo_center_x, float* _pTo_center_y, int _num_particles, float _pSize, float _velocity_start, float _alpha_start, float _alpha_end, float _d_alpha);
       ~DamageEffect();

       void update();
       void render();
};


class ParticleForExplosionEffect
{ 
    public:
        bool is_alive;
        int curnum;
        
        float center_x_start;
        float center_y_start;   
        float center_x;
        float center_y;  
   
        float alpha_start;
        float alpha_end;
        float d_alpha;
        float alpha;
   
        float size_start;
        float d_size;
        float size;
 
        float velocity_start;
        float d_velocity; 

        float velocity_x;
        float velocity_y;  
        
        
      ParticleForExplosionEffect(float _center_x_start, float _center_y_start, float _size_start, float _d_size, float _velocity_start, float _d_velocity, float _alpha_start, float _alpha_end, float _d_alpha, float _curnum);
      ~ParticleForExplosionEffect();

      void fastCalcVelocityVector();
      void accurateCalcVelocityVector();
      void update();
      void render();
};



class ExplosionEffect
{ 
    public:
          TextureOb* pTo_texOb;
          StarSystem* pTo_starsystem;
          bool is_alive;
          bool alreadyInRemoveQueue;
  
          //type of starsystem;
          GLuint texture;

          float center_x;
          float center_y;
   
          int num_particles;
          VEC_pParticleForExplosionEffect_type particles_pList;
           
          float pSize_start;
           
       ExplosionEffect(TextureOb* _pTo_texOb, StarSystem* _pTo_starsystem, float _center_x, float _center_y, int _num_particles, float _pSize_start, float _d_pSize,  float _velocity_start, float _alpha_start, float _alpha_end, float _d_alpha);
       ~ExplosionEffect();

       void update();
       void render();
};















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

     particleForDriveTrailEffect(float* _pTo_pos_orig_x, float* _pTo_pos_orig_y, float _alpha_start, float _alpha_end, float _d_alpha, int _num);  // fake
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

       DriveTrailEffect(TextureOb* _pTo_texOb, float* _pTo_OB_angle_inD, float* _pTo_start_pos_x, float* _pTo_start_pos_y, float* _pTo_target_pos_x, float* _pTo_target_pos_y, int _num_particles, float _size, float _velocity_orig, float _alpha_start, float _alpha_end, float _d_alpha);

       ~DriveTrailEffect();
       void generateParticles(); 
       void updateVelocity();
       void putParticlesToInitPos();
       void update();
       void render();
};  
typedef std::vector<DriveTrailEffect*>  VEC_pDriveTrailEffect_type; 













#endif /* EFFECTS_H */
