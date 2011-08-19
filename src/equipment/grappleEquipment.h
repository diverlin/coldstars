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


#ifndef GRAPPLEEQUIPMENT_H
#define GRAPPLEEQUIPMENT_H


class GrappleEquipment : public CommonForEquipment
{
   public:
      //grapple_list = []
      //grapple_remove_queue = []

      int strength_orig;
      int strength_add;
      int strength;

      int radius_orig;
      int radius_add;
      int radius;

      int speed_orig;
      int speed_add;
      int speed; 

      int maxNumItem_orig;
      int maxNumItem_add;
      int maxNumItem;

      VEC_pGrappleModule_type modules_pList; 

      // INFO 
      std::string info_title_0;
      std::string info_title_1;   std::string info_value_1;
      std::string info_title_2;   std::string info_value_2; 
      std::string info_title_3;   std::string info_value_3;
      std::string info_title_4;   std::string info_value_4;
      std::string info_title_5;   std::string info_value_5;
      std::string info_title_6;   std::string info_value_6;
      std::string info_title_7;   std::string info_value_7;
      std::string info_title_8;   std::string info_value_8;


      GrappleEquipment();
      GrappleEquipment(TextureOb* _pTo_itemTexOb, int _strength_orig, int _radius_orig, int _speed_orig, int _maxNumItem_orig, int _modules_num_max, int _mass, int _condition_max, int _deterioration_rate);   // joun strength and speed attributes into one
      ~GrappleEquipment();

      void countPrice();
      void updatePropetries();
      void updateOwnerPropetries();

      void updateInfo();
           std::string returnStrengthStr();
           std::string returnRadiusStr();
           std::string returnSpeedStr();
           std::string returnMaxNumItemStr();
           
      bool insertModule(GrappleModule* pTo_grappleModule);
};

#endif 
