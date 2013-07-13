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
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"
#include "../../world/EntityManager.hpp"
#include "../../items/equipment/BaseEquipment.hpp"

BaseModule::BaseModule():
equipment_owner(nullptr)
{}

/* virtual */
BaseModule::~BaseModule ()
{}

void BaseModule::AddCommonInfo()
{
    	info.addNameStr("mass:");      info.addValueStr( int2str(data_item.mass) );
}

void BaseModule::SaveDataUniqueBaseModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" SaveDataUniqueBaseModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
        if (equipment_owner) 	{ save_ptree.put(root+"unresolved.equipment_owner_id", equipment_owner->GetId()); }
	else           		{ save_ptree.put(root+"unresolved.equipment_owner_id", NONE_ID); }
}

void BaseModule::LoadDataUniqueBaseModule(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" LoadDataUniqueBaseModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
	data_unresolved_BaseModule.equipment_owner_id = load_ptree.get<int>("unresolved.equipment_owner_id");
}

void BaseModule::ResolveDataUniqueBaseModule()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" ResolveDataUniqueBaseModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
	if(data_unresolved_BaseModule.equipment_owner_id != NONE_ID) 
	{
		((BaseEquipment*)EntityManager::Instance().GetEntityById(data_unresolved_BaseModule.equipment_owner_id))->InsertModule(this);
	}
}
