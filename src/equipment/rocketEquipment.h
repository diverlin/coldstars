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

class RocketEquipment : public CommonForEquipment
{ 
   	public:
      		RocketEquipment();
      		RocketEquipment(TextureOb* pTo_itemTexOb, 
      				int _ammo_max_orig, 
      				int _damage_orig, 
      				int _radius_orig, 
      				int _modules_num_max, 
      				int _mass, 
      				int _condition_max, 
      				int _deterioration_rate);
      				
      		~RocketEquipment();

		int getAmmo()   const;
		int getDamage() const;
		int getRadius() const;
		
      		void countPrice();
      		void updatePropetries();
      		void updateOwnerPropetries();

      		void updateInfo();
           		std::string returnAmmoStr();
           		std::string returnDamageStr();
           		std::string returnRadiusStr();

      		void fireEvent();
      
      		bool insertModule(RocketModule* pTo_rocketModule);
      		
      	private:
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
      		
      	      	TextureOb* turrelTexOb;
      	      	
      		TextureOb* pTo_bulletTexOb;
      		int bullet_size; 
      		int bullet_armor;
      		float bullet_speed_init;
      		float bullet_speed_max;
      		float bullet_d_speed;
      		int bullet_live_time;
      		float bullet_angular_speed;
      		
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
      	
};

RocketEquipment* rocketEquipmentGenerator(int race_id, int revision_id = -1);

#endif 
