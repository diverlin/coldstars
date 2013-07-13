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

#include "DroidModule.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"

DroidModule::DroidModule(int id)
:
repair_add(0)        
{
	SetId(id);
	SetTypeId(ENTITY::TYPE::MODULE_ID);
	SetSubTypeId(ENTITY::TYPE::DROID_MODULE_ID);
}

/* virtual */
DroidModule::~DroidModule() 
{}
	
/* virtual */	
void DroidModule::AddUniqueInfo()
{
    	info.addTitleStr("droid module");
    	info.addNameStr("repair_add:");   info.addValueStr( int2str(repair_add) );
}

/*virtual*/
void DroidModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "droid_module." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseModule(save_ptree, root);
	SaveDataUniqueDroidModule(save_ptree, root);
}

/*virtual*/		
void DroidModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseModule(load_ptree);
	LoadDataUniqueDroidModule(load_ptree);
}
	
/*virtual*/	
void DroidModule::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseModule();
	ResolveDataUniqueDroidModule();
}

void DroidModule::SaveDataUniqueDroidModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" SaveDataUniqueDroidModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
	save_ptree.put(root+"repair_add", repair_add);
}

void DroidModule::LoadDataUniqueDroidModule(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" LoadDataUniqueDroidModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
	repair_add = load_ptree.get<int>("repair_add");
}

void DroidModule::ResolveDataUniqueDroidModule()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" ResolveDataUniqueDroidModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
}


