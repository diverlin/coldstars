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


class RocketEquipment : public BaseEquipment
{ 
   	public:
      		RocketEquipment(int);
      		virtual ~RocketEquipment();

		void SetAmmoMaxOrig(int ammo_max_orig) { this->ammo_max_orig = ammo_max_orig; };
		void SetDamageOrig(int damage_orig)    { this->damage_orig   = damage_orig; };
		void SetRadiusOrig(int radius_orig)    { this->radius_orig   = radius_orig; };
                void SetBulletData(BulletData data_bullet) { this->data_bullet = data_bullet; };
                
    		void SetAmmo(int ammo) { this->ammo = ammo; };
                            
		int GetAmmo()   const { return ammo; };
		int GetDamage() const { return damage; };
		int GetRadius() const { return radius; };
		
      		void FireEvent();
      		
      	      	void CountPrice();
      		virtual void UpdatePropetries();
      		
      		virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(boost::property_tree::ptree&);
		virtual void ResolveData();
      		
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
      		
     		void virtual AddUniqueInfo();
           	std::string GetAmmoStr();
           	std::string GetDamageStr();
           	std::string GetRadiusStr();
                
                void SaveDataUniqueRocketEquipment(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueRocketEquipment(const boost::property_tree::ptree&);
		void ResolveDataUniqueRocketEquipment();  
};

#endif 
