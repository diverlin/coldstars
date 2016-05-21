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

#include <types/IdType.hpp>

class BaseEquipment;

struct UnresolvedDataBaseModule {
    id_type equipment_owner_id;
};

class BaseModule : public BaseItem {
public:
    BaseModule();
    virtual ~BaseModule();

    void SetEquipmentOwner(BaseEquipment* equipment_owner) { this->equipment_owner = equipment_owner; }

protected:
    BaseEquipment* equipment_owner;

    UnresolvedDataBaseModule data_unresolved_BaseModule;

    void AddCommonInfo();

    void SaveData(boost::property_tree::ptree&, const std::string&) const;
    void LoadData(const boost::property_tree::ptree&);
    void ResolveData();
};

