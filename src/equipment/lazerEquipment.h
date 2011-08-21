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


#ifndef LAZEREQUIPMENT_H
#define LAZEREQUIPMENT_H


class LazerEquipment : public CommonForEquipment
{
    public:
      int damage_orig;
      int damage_add;
      int damage;

      int radius_orig;
      int radius_add;
      int radius;

      TextureOb* pTo_lazerEffectTexOb;
      TextureOb* pTo_particleTexOb;
      
      int particle_Size;

      TextureOb* turrelTexOb;
      //Turrel* turrel;
      
      VEC_pLazerModule_type modules_pList;

      // INFO 
      std::string info_title_0;
      std::string info_title_1;   std::string info_value_1;
      std::string info_title_2;   std::string info_value_2; 
      std::string info_title_3;   std::string info_value_3;
      std::string info_title_4;   std::string info_value_4;
      std::string info_title_5;   std::string info_value_5;
      std::string info_title_6;   std::string info_value_6;


      LazerEquipment(TextureOb* _pTo_itemTexOb, int _damage_orig, int _radius_orig, int _modules_num_max, int _mass, int _condition_max, int _deterioration_rate);
      ~LazerEquipment();

      void updatePropetries();
      void countPrice();
      void updateOwnerPropetries();
      void updateInfo();
           std::string returnDamageStr();
           std::string returnRadiusStr();
      void fireEvent(Turrel* _turrel);
      
      bool insertModule(LazerModule* pTo_lazerModule);
};



class LazerTraceEffect
{ 
    public:
       bool is_alive;
       bool is_alreadyInRemoveQueue; 

       StarSystem* pTo_starsystem;

       TextureOb* pTo_texOb;
       GLuint texture;
       int w,h;

       TextureOb* pTo_particleTexOb;

       float particle_size;

       int existance_time;

       DamageEffect* pTo_damageEffect;

       float* pTo_start_pos_x;
       float* pTo_start_pos_y;
       float* pTo_end_pos_x;
       float* pTo_end_pos_y;


       float len; 
       float angle_inR;
       float d_angle_inR;
       float additional_angle_inR;
       float angle_inD; 

       // NEW!!!
       //damage_effect = None
       // NEW!!!
        

       LazerTraceEffect(TextureOb* pTo_texOb, TextureOb* pTo_particleTexOb, float _particle_size, float* _pTo_start_pos_x, float* _pTo_start_pos_y, float* _pTo_end_pos_x, float* _pTo_end_pos_y);
       ~LazerTraceEffect();

       void update();
       void updateAngleAndLen();

       void render();
            void (LazerTraceEffect::*pToFunc_render)();
            void _renderFrame();
            void _renderFrames();
};

#endif 
