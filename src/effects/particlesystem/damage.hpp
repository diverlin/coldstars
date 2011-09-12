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


#ifndef DAMAGE_H
#define DAMAGE_H



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

      ParticleForDamageEffect(float* pTo_center_x, 
      			      float* pTo_center_y, 
      			      float _velocity_start, 
      			      float _alpha_start, 
      			      float _alpha_end, 
      			      float _d_alpha);
      			      
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

       float* pTo_center_x;
       float* pTo_center_y;

       GLuint texture;
       int num_particles;
       float pSize;

       float velocity_start;
       float alpha_start;
       float alpha_end;

       std::vector<ParticleForDamageEffect*> particles_pList;

       DamageEffect(TextureOb* _pTo_texOb, 
       		    float* _pTo_center_x, 
       		    float* _pTo_center_y, 
       		    int _num_particles, 
       		    float _pSize, 
       		    float _velocity_start, 
       		    float _alpha_start, 
       		    float _alpha_end, 
       		    float _d_alpha);
       		    
       ~DamageEffect();

       void update();
       void render();
};



#endif 
