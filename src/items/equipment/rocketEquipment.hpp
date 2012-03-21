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

struct BulletData
{
	TextureOb* texOb;
	
	int damage; 
        int armor; 
        int live_time;
                
        float speed_init;
        float speed_max;
        float d_speed; 
        float angular_speed; 
};



class RocketEquipment : public EquipmentBase
{ 
   	public:
      		RocketEquipment(int ammo_max_orig, 
      				int damage_orig, 
      				int radius_orig);
      		virtual ~RocketEquipment();

		int getAmmo()   const;
		int getDamage() const;
		int getRadius() const;
		
      		void fireEvent();
      		      
      		void virtual updateOwnerAbilities();
      		
      	      	void countPrice();
      		virtual void updatePropetries();
      		
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
     	      	
      	      	BulletData data_bullet;
      		
     		void virtual addUniqueInfo();
           	std::string getAmmoStr();
           	std::string getDamageStr();
           	std::string getRadiusStr();
};

RocketEquipment* getNewRocketEquipment(int race_id, int revision_id = -1);

#endif 
