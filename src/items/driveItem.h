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


#ifndef DRIVEITEM_H
#define DRIVEITEM_H


class DriveItem :  public CommonForItems
{
public:
      int type_id;
      int subtype_id;

      int speed_orig;
      int speed_add;
      int speed;

      int hyper_orig;
      int hyper_add;
      int hyper;

      TextureOb* pTo_particleTexOb;
      int particle_num;
      float particle_size;
      float particle_velocity;
      float particle_alpha_start;
      float particle_alpha_end;
      float particle_d_alpha;

      VEC_pDriveModule_type modules_pList;
      
      // INFO 
      std::string info_title_0;
      std::string info_title_1;   std::string info_value_1;
      std::string info_title_2;   std::string info_value_2; 
      std::string info_title_3;   std::string info_value_3;
      std::string info_title_4;   std::string info_value_4;
      std::string info_title_5;   std::string info_value_5;
      std::string info_title_6;   std::string info_value_6;


      DriveItem();
      DriveItem(TextureOb* pTo_itemTexOb, int speed_orig, int hyper_orig, int modules_num_max, int mass, int condition_max, int deterioration_rate);
      ~DriveItem();

      void updatePropetries();
      void countPrice();
      void updateOwnerPropetries();

      void updateInfo();
           std::string returnSpeedStr();
           std::string returnHyperStr();
           
      bool insertModule(DriveModule* pTo_driveModule);
};

#endif 




