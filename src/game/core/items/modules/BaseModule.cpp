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

#include "BaseModule.hpp"
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

#include <common/Global.hpp>
#include <managers/EntityManager.hpp>

#include "../../items/equipment/BaseEquipment.hpp"

BaseModule::BaseModule():
equipment_owner(nullptr)
{}

/* virtual */
BaseModule::~BaseModule ()
{}

void BaseModule::AddCommonInfo()
{
    //info.addNameStr("mass:");      info.addValueStr( std::to_string(data_item.mass) );
}

void BaseModule::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    Logger::Instance().Log(" BaseModule::SaveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    
    if (equipment_owner)     { save_ptree.put(root+"unresolved.equipment_owner_id", equipment_owner->id()); }
    else                   { save_ptree.put(root+"unresolved.equipment_owner_id", NONE_ID); }
}

void BaseModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
    Logger::Instance().Log(" BaseModule::LoadData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);

    data_unresolved_BaseModule.equipment_owner_id = load_ptree.get<int>("unresolved.equipment_owner_id");
}

void BaseModule::ResolveData()
{
    Logger::Instance().Log(" BaseModule::ResolveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    
    if(data_unresolved_BaseModule.equipment_owner_id != NONE_ID) {
        ((BaseEquipment*)global::get().entitiesManager().entity(data_unresolved_BaseModule.equipment_owner_id))->InsertModule(this);
    }
}
