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


#ifndef RADAREQUIPMENT_H
#define RADAREQUIPMENT_H


class RadarEquipment : public CommonForEquipment
{
   public:
      int radius_orig;
      int radius_add;
      int radius;

      VEC_pRadarModule_type modules_pList;

      // INFO 
      std::string info_title_0;
      std::string info_title_1;   std::string info_value_1;
      std::string info_title_2;   std::string info_value_2; 
      std::string info_title_3;   std::string info_value_3;
      std::string info_title_4;   std::string info_value_4;
      std::string info_title_5;   std::string info_value_5;


      RadarEquipment();
      RadarEquipment(TextureOb* pTo_itemTexOb, int _radius_orig, int _modules_num_max, int _mass, int _condition_max, int _deterioration_rate);
      ~RadarEquipment();

      void updatePropetries();
      void countPrice();
      void updateOwnerPropetries();

      void updateInfo();
           std::string returnRadiusStr();
        
      bool insertModule(RadarModule* pTo_radarModule);
};

RadarEquipment* radarEquipmentGenerator(int race_id, int revision_id = -1);

#endif 








         
