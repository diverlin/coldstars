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
      		WeaponComplex(Vehicle*);
      		~WeaponComplex();

                void SetWeaponSlot1(ItemSlot* weapon_slot1) { this->weapon_slot1 = weapon_slot1; };
                void SetWeaponSlot2(ItemSlot* weapon_slot2) { this->weapon_slot2 = weapon_slot2; };
                void SetWeaponSlot3(ItemSlot* weapon_slot3) { this->weapon_slot3 = weapon_slot3; };
                void SetWeaponSlot4(ItemSlot* weapon_slot4) { this->weapon_slot4 = weapon_slot4; };
                void SetWeaponSlot5(ItemSlot* weapon_slot5) { this->weapon_slot5 = weapon_slot5; };
                
                ItemSlot* GetWeaponSlot1() { return weapon_slot1; };
                ItemSlot* GetWeaponSlot2() { return weapon_slot2; };
                ItemSlot* GetWeaponSlot3() { return weapon_slot3; };
                ItemSlot* GetWeaponSlot4() { return weapon_slot4; };
                ItemSlot* GetWeaponSlot5() { return weapon_slot5; };
        	
      		void PostCreateInit(int, bool);

        	WeaponSelector weapon_selector; 
        	
               	void PrepareWeapons();
                     
                void SetTarget(BaseGameEntity*);     
       
        	void Fire(int timer, bool);

     		void SelectWeapons();  
        	void ResetDeselectedWeaponTargets();   
        	bool IsAnyWeaponSelected() const; 
        	
        	bool UpdateFireAbility();
        	
        	void RenderWeaponIcons() const;
        	void RenderWeaponsRange();
        	
        	void RenderTurrels() const;
        	
      	private:
      		int weapon_num;
      		Vehicle* owner_vehicle;
                //Points points;
      		
      		int fire_delay, d_fire_delay;
        	std::vector<ItemSlot*> slot_weapon_vec;
        	std::vector<ItemSlot*> slot_weapon_equiped_vec;
        	std::vector<ItemSlot*> slot_weapon_reloaded_vec;
        	
        	ItemSlot* weapon_slot1;
        	ItemSlot* weapon_slot2;
        	ItemSlot* weapon_slot3;
        	ItemSlot* weapon_slot4;
        	ItemSlot* weapon_slot5;
        	
        	Turrel* turrel1;
        	Turrel* turrel2;
        	Turrel* turrel3;
        	Turrel* turrel4;
        	Turrel* turrel5;
        	
        	void ReloadAllWeapons();  
        	void ValidateAllReloadedWeaponsTarget();
      		
};


#endif
