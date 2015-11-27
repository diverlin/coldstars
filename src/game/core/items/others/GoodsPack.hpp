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

#include <items/BaseItem.hpp>
#include <common/constants.hpp>

class GoodsPack : public BaseItem
{
    public:                  
        GoodsPack(int, TYPE::ENTITY);
        virtual ~GoodsPack();
        
        void Increase(unsigned int amount) { m_data_item.mass += amount; }
        void Decrease(unsigned int amount) { m_data_item.mass -= amount; }

        virtual void UpdateOwnerAbilities();
        
        virtual void Save(boost::property_tree::ptree&) const;
        virtual void Load(const boost::property_tree::ptree&);
        virtual void Resolve();
        
    private:
        virtual void AddCommonInfo();
         virtual void AddUniqueInfo();   
         
         void SaveData(boost::property_tree::ptree&, const std::string&) const;
         void LoadData(const boost::property_tree::ptree& load_ptree);
         void ResolveData();
         
};

GoodsPack* GetNewGoodsPack(TYPE::ENTITY, const id_type& id = NONE_ID);

