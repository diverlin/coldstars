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

#include "LazerModule.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"

LazerModule::LazerModule(int id)
:
damage_add(0),
radius_add(0)
{
	SetId(id);
	SetTypeId(ENTITY::TYPE::MODULE_ID);
    SetSubTypeId(ENTITY::TYPE::LAZER_MODULE_ID);  
}

/* virtual */
LazerModule::~LazerModule()
{}

/* virtual */
void LazerModule::AddUniqueInfo()
{
    	info.addTitleStr("lazer module");
    	if (damage_add != 0) 
    	{
    		info.addNameStr("damage_add:");   info.addValueStr(int2str(damage_add));
    	}
    	if (radius_add != 0)
    	{ 
    		info.addNameStr("radius_add:");   info.addValueStr(int2str(radius_add));
    	}
}

/*virtual*/
void LazerModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "lazer_module." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseModule(save_ptree, root);
	SaveDataUniqueLazerModule(save_ptree, root);
}

/*virtual*/		
void LazerModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseModule(load_ptree);
	LoadDataUniqueLazerModule(load_ptree);
}
	
/*virtual*/	
void LazerModule::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseModule();
	ResolveDataUniqueLazerModule();
}

void LazerModule::SaveDataUniqueLazerModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" SaveDataUniqueLazerModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
	save_ptree.put(root+"damage_add", damage_add);
	save_ptree.put(root+"radius_add", radius_add);
}

void LazerModule::LoadDataUniqueLazerModule(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" LoadDataUniqueLazerModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
	damage_add = load_ptree.get<int>("damage_add");
	radius_add = load_ptree.get<int>("radius_add");
}

void LazerModule::ResolveDataUniqueLazerModule()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" ResolveDataUniqueLazerModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
}
