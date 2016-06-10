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


#ifndef WEAPONCOMPLEX_HPP
#define WEAPONCOMPLEX_HPP

#include <vector>
#include <types/EntityTypes.hpp>

class Vehicle;
class ItemSlot;
namespace item {
class Base;
}
class SpaceObject;
class TextureOb;


class WeaponComplex
{
    public:
        WeaponComplex(Vehicle* owner_vehicle);
        ~WeaponComplex();

        int GetRadiusMin() const { return radius_min; }
        int GetTotalRadius() const { return total_radius; }
        int GetTotalDamage() const { return total_damage; }
       
        bool AddSlot(ItemSlot*);
        ItemSlot* GetEmptyWeaponSlot() const;
        ItemSlot* GetEquipedWeakestWeaponSlot() const;
    
        void PrepareWeapons();
             
        void SetTarget(SpaceObject*, ItemSlot* item_slot = nullptr);     
                   
        void Fire(int, float, bool);
        
        void ActivateAllWeapons();
        void DeactivateAllWeapons();
        void ActivateWeaponsBySubTypeId(type::ENTITY);
        void DeactivateWeaponsBySubTypeId(type::ENTITY);

        bool IsAnyWeaponSelected() const; 
        
        void UpdateFireAbility();
        
        void RenderWeaponIcons() const;
        void RenderWeaponsRange();
        
        void RenderTurrels() const;
            
    private:
        int total_damage = 0;
        int total_radius = 0;
        int radius_min = 0;
        
        Vehicle* owner_vehicle = nullptr;
        
        int fire_delay = 0, d_fire_delay = 0;
        std::vector<ItemSlot*> slot_weapon_vec;
        std::vector<ItemSlot*> slot_weapon_reloaded_vec;

        void ReloadAllWeapons();  
        void ValidateAllWeaponsTarget();              
};


#endif
