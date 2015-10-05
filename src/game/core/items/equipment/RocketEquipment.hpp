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


#ifndef ROCKETEQUIPMENT_HPP
#define ROCKETEQUIPMENT_HPP

#include <types/MyInt.hpp>
#include <items/equipment/BaseEquipment.hpp>
#include <common/BulletData.hpp>


class RocketEquipment : public BaseEquipment
{ 
       public:
        RocketEquipment(INTLONGEST);
        virtual ~RocketEquipment();
        
        void SetAmmoMaxOrig(int ammo_max_orig) { this->ammo_max_orig = ammo_max_orig; };
        void SetDamageOrig(int damage_orig)    { this->damage_orig   = damage_orig; };
        void SetRadiusOrig(int radius_orig)    { this->radius_orig   = radius_orig; };
        void SetBulletData(BulletData data_bullet) { this->data_bullet = data_bullet; };
        
        void SetAmmo(int ammo) { this->ammo = ammo; };
        
        int GetAmmoMax() const { return ammo_max; };                            
        int GetAmmo()   const { return ammo; };
        int GetDamage() const { return damage; };
        int GetRadius() const { return radius; };
        
        void FireEvent(float);
        
        virtual void updateProperties();
        
        void CountPrice();
        
        virtual void Save(boost::property_tree::ptree&) const;
        virtual void Load(const boost::property_tree::ptree&);
        virtual void Resolve();
              
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
        
        int fire_atOnce;
        
        BulletData data_bullet;
        
        void virtual AddUniqueInfo();
        std::string GetAmmoStr();
        std::string GetDamageStr();
        std::string GetRadiusStr();
        
        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();  
};

#endif 
