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


#ifndef WEAPONCOMPLEX_H
#define WEAPONCOMPLEX_H

#include <vector>
class Vehicle;
class ItemSlot;
class BaseItem;
class BaseSpaceEntity;
class TextureOb;
#include "../common/constants.hpp"

class WeaponComplex
{
	public:
      		WeaponComplex();
      		~WeaponComplex();
               
               	void SetOwnerVehicle(Vehicle* owner_vehicle) { this->owner_vehicle = owner_vehicle; };
               	TextureOb* GetItemTextureOb(int) const; // used for gui, additional icons
               
               	int GetRadiusMin() const { return radius_min; };
                int GetTotalRadius() const { return total_radius; };
                int GetTotalDamage() const { return total_damage; };
               
                bool AddSlot(ItemSlot*);
                ItemSlot* GetEmptyWeaponSlot() const;
                ItemSlot* GetEquipedWeakestWeaponSlot() const;
        	
               	void PrepareWeapons();
                     
                void SetTarget(BaseSpaceEntity*, ItemSlot* item_slot = nullptr);     
                       
        	void Fire(int, float, bool);
        	
     		void ActivateAllWeapons();
     		void DeactivateAllWeapons();
		void ActivateWeaponsBySubTypeId(ENTITY::eTYPE);
		void DeactivateWeaponsBySubTypeId(ENTITY::eTYPE);

        	bool IsAnyWeaponSelected() const; 
        	
        	void UpdateFireAbility();
        	
        	void RenderWeaponIcons() const;
        	void RenderWeaponsRange();
        	
        	void RenderTurrels() const;
        	
      	private:
      		int total_damage;
      		int total_radius;
      		int radius_min;
      		
      		Vehicle* owner_vehicle;
      		
      		int fire_delay, d_fire_delay;
        	std::vector<ItemSlot*> slot_weapon_vec;
        	std::vector<ItemSlot*> slot_weapon_reloaded_vec;
   	
        	void ReloadAllWeapons();  
        	void ValidateAllWeaponsTarget();      		
};


#endif
