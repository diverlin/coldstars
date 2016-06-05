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

#include <item/BaseItem.hpp>

class Bomb : public item::Base
{
    public:
        Bomb(const id_type& id);
        virtual ~Bomb();

        void setDamage(int damage) { this->m_damage = damage; }
        void setRadius(int radius) { this->m_radius = radius; }

        int damage() const override final { return m_damage; }
        int radius() const override final { return m_radius; }

        virtual void UpdateOwnerAbilities();

        virtual void Save(boost::property_tree::ptree&) const;
        virtual void Load(const boost::property_tree::ptree&);
        virtual void Resolve();
        
    private:
        int m_damage = 0;
        int m_radius = 0;

        virtual void AddCommonInfo();
        virtual void addUniqueInfo();

        void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();
};


