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

#include "Base.hpp"

class SpaceObject;
class ItemSlot;

namespace item {

class Lazer : public control::item::BaseEquipment
{
    public:
        Lazer(int_t id);
        virtual ~Lazer();

        void SetDamageOrig(int damage_orig) { m_damage_orig = damage_orig; }
        void SetRadiusOrig(int radius_orig) { m_radius_orig = radius_orig; }

        int damage() const override final { return m_damage; }
        int radius() const override final { return m_radius; }
        
        void FireEvent(SpaceObject*, ItemSlot*, float, bool);

        virtual void updateProperties();

        void CountPrice();

        virtual void Save(boost::property_tree::ptree&) const;
        virtual void Load(const boost::property_tree::ptree&);
        virtual void Resolve();
        
    private:
        int m_damage_orig;
        int m_damage_add;
        int m_damage;

        int m_radius_orig;
        int m_radius_add;
        int m_radius;

        //              jeti::control::TextureOb* texOb_turrel;
        //              jeti::control::TextureOb* texOb_lazerEffect;

        void virtual addUniqueInfo();
        std::string GetDamageStr();
        std::string GetRadiusStr();

        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
};

} // namespace item
