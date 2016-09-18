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


#pragma once

#include <ceti/type/IdType.hpp>
#include <item/equipment/Base.hpp>
#include <common/BulletData.hpp>

namespace item {
namespace equipment {

class Rocket : public Base
{ 
       public:
        Rocket(const int_t& id);
        virtual ~Rocket();
        
        void SetAmmoMaxOrig(int ammo_max_orig) { m_ammo_max_orig = ammo_max_orig; }
        void SetDamageOrig(int damage_orig)    { m_damage_orig   = damage_orig; }
        void SetRadiusOrig(int radius_orig)    { m_radius_orig   = radius_orig; }
        void SetBulletData(BulletData data_bullet) { data_bullet = data_bullet; }
        
        void SetAmmo(int ammo) { m_ammo = ammo; }
        
        int GetAmmoMax() const { return m_ammo_max; }
        int GetAmmo()   const { return m_ammo; }
        int damage() const override final { return m_damage; }
        int radius() const override final { return m_radius; }
        
        void FireEvent(float);
        
        virtual void updateProperties();
        
        void CountPrice();
        
        virtual void Save(boost::property_tree::ptree&) const;
        virtual void Load(const boost::property_tree::ptree&);
        virtual void Resolve();
              
    private:
        int m_ammo_max_orig;
        int m_ammo_max_add;
        int m_ammo;
        int m_ammo_max;
        
        int m_damage_orig;
        int m_damage_add;
        int m_damage;
        
        int m_radius_orig;
        int m_radius_add;
        int m_radius;     
        
        int fire_atOnce;
        
        BulletData data_bullet;
        
        void virtual addUniqueInfo();
        std::string GetAmmoStr();
        std::string GetDamageStr();
        std::string GetRadiusStr();
        
        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();  
};

} // namespace equipment
} // namespace item
