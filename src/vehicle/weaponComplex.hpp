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


class WeaponComplex
{
	public:
      		WeaponComplex();
      		~WeaponComplex();
      		
      		void postCreateInit(int, Rect, VehicleCommon*, bool, TextureOb*);
      
      		ItemSlot weapon_slot1;
        	ItemSlot weapon_slot2;
        	ItemSlot weapon_slot3;
        	ItemSlot weapon_slot4;
        	ItemSlot weapon_slot5;

        	WeaponSelector weapon_selector; 
        	
               	void prepareWeapons();
                     
                template <typename TARGET_TYPE>      
                void setWeaponsTarget(TARGET_TYPE*);     
       
        	void weaponsFire_TRUE(int timer);
        	void weaponsFire_FALSE(int timer);

     		void selectWeapons();  
        	void resetDeselectedWeaponTargets();   
        	bool isAnyWeaponSelected() const; 
        	
        	bool updateFireAbility();
        	
        	void renderWeaponIcons() const;
        	void renderWeaponsRange();
        	
        	void renderTurrels() const;
        	
      	private:
      		int weapon_num;
      		Points* owner_points;
      		
      		int fire_delay, d_fire_delay;
        	std::vector<ItemSlot*> slot_weapon_vec;
        	std::vector<ItemSlot*> slot_weapon_equiped_vec;
        	std::vector<ItemSlot*> slot_weapon_reloaded_vec;
        	
        	Turrel* turrel1;
        	Turrel* turrel2;
        	Turrel* turrel3;
        	Turrel* turrel4;
        	Turrel* turrel5;
        	
        	void reloadAllWeapons();  
        	void validateAllReloadedWeaponsTarget();
      		
};


#endif
