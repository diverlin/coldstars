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

class Vehicle;
#include "../spaceobjects/ItemSlot.hpp"

class WeaponComplex
{
	public:
      		WeaponComplex(Vehicle*);
      		~WeaponComplex();
               
               	TextureOb* GetItemTextureOb(int) const; // used for gui, additional icons
               
                bool AddSlot(ItemSlot*);
                bool AddItem(BaseItem*);
        	
               	void PrepareWeapons();
                     
                void SetTarget(BaseGameEntity*);     
                void SetPreciseFireTarget(BaseGameEntity*, ItemSlot*);     
                       
        	void Fire(int, int, bool);
        	
     		void ActivateAllWeapons();
     		void DeactivateAllWeapons();
		void ActivateWeaponsBySubTypeId(int);
		void DeactivateWeaponsBySubTypeId(int);

        	bool IsAnyWeaponSelected() const; 
        	//bool IsAllPreciseWeaponsSelected() const;
        	
        	bool UpdateFireAbility();
        	
        	void RenderWeaponIcons() const;
        	void RenderWeaponsRange();
        	
        	void RenderTurrels() const;
        	
      	private:
      		Vehicle* owner_vehicle;
      		
      		int fire_delay, d_fire_delay;
        	std::vector<ItemSlot*> slot_weapon_vec;
        	std::vector<ItemSlot*> slot_weapon_equiped_vec;
        	std::vector<ItemSlot*> slot_weapon_reloaded_vec;

        	void ResetDeselectedWeaponTargets(); 
   	
        	void ReloadAllWeapons();  
        	void ValidateAllWeaponsTarget();
      		
};


#endif
