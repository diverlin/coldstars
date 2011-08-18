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


#ifndef ROCKETEQUIPMENT_H
#define ROCKETEQUIPMENT_H


class RocketBullet
{
    public:
        int type_id;
       
        bool is_alive;
        bool is_explosed;

        TextureOb* pTo_texOb;
        GLuint texture;
        int w, h;

        StarSystem* pTo_starsystem;

        //CommonInstance.__init__(self, texOb.texture, (texOb.w, texOb.h))
        //if self.animated == True:
        //   self.render = self.renderInSpace
        //else:
        //   self.render = self.renderInSpace

        int owner_id;
        //int target_type_id;

    
        //Ship*      pTo_shipTarget;
        //Asteroid*  pTo_asteroidTarget;
        //Mineral*   pTo_mineralTarget;
        //Container* pTo_containerTarget; 
        
        float* pTo_target_pos_x;
        float* pTo_target_pos_y;
        bool target_is_alive;    
        bool* pTo_target_is_alive;

        int damage;

        int size;
        int armor;

        float speed_init;
        float speed_max;
        float d_speed;  
        float angular_speed;
        float speed;
        float step;

        int live_time;

        Points points;

        RocketBullet(StarSystem* _pTo_starsystem, TextureOb* _pTo_texOb, float _start_pos_x, float _start_pos_y, float _angle_inD, float* _pTo_target_pos_x, float* _pTo_target_pos_y, bool* _pTo_target_is_alive, int _owner_id, int _damage, int _size, int _armor, float _speed_init, float _speed_max, float _d_speed, float _angular_speed, int _live_time);
        ~RocketBullet();
        
        //void setShipAsTarget(Ship* _pTo_ship);
        //void setAsteroidAsTarget(Asteroid* _pTo_asteroid);
        //void setMineralAsTarget(Mineral* _pTo_mineral);
        //void setContainerAsTarget(Container* _pTo_container);

        void update_inSpace_inDynamic();
        void updateDebugWay(int _timer);   // DEBUG
        void stepCalculation();
        void hit(int _damage);
        void death();

        float dx, dy;
        float angle_inD;

        void renderDriveJet();
        void renderInSpace();
};




class RocketEquipment : public CommonForEquipment
{ 
   public:
      int type_id;
      int subtype_id;

      int ammo_max_orig;
      int ammo_max_add;
      int ammo;
      int ammo_max;
      
      int damage_orig;
      int damage_add;
      int damage;

      int radius_orig;
      int radius_add;
      int radius; 

      TextureOb* pTo_bulletTexOb;
      int bullet_size; 
      int bullet_armor;
      float bullet_speed_init;
      float bullet_speed_max;
      float bullet_d_speed;
      int bullet_live_time;
      float bullet_angular_speed;

      TextureOb* pTo_turrelTexOb;
      Turrel* pTo_turrel;
      WeaponSlot* pTo_wslot;
      
      VEC_pRocketModule_type modules_pList;
      
      // INFO 
      std::string info_title_0;
      std::string info_title_1;   std::string info_value_1;
      std::string info_title_2;   std::string info_value_2; 
      std::string info_title_3;   std::string info_value_3;
      std::string info_title_4;   std::string info_value_4;
      std::string info_title_5;   std::string info_value_5;
      std::string info_title_6;   std::string info_value_6;
      std::string info_title_7;   std::string info_value_7;

      RocketEquipment();
      RocketEquipment(TextureOb* pTo_itemTexOb, int _ammo_max_orig, int _damage_orig, int _radius_orig, int _modules_num_max, int _mass, int _condition_max, int _deterioration_rate);
      ~RocketEquipment();

      void countPrice();
      void updatePropetries();
      void updateOwnerPropetries();

      void updateInfo();
           std::string returnAmmoStr();
           std::string returnDamageStr();
           std::string returnRadiusStr();

      void fireEvent();
      
      bool insertModule(RocketModule* pTo_rocketModule);
};

#endif 
