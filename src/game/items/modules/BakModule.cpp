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

#include "BakModule.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"

BakModule::BakModule(int id)
:
fuel_max_add(0)
{
	SetId(id);
	SetTypeId(ENTITY::TYPE::MODULE_ID);
	SetSubTypeId(ENTITY::TYPE::BAK_MODULE_ID);
}

/* virtual */
BakModule::~BakModule() 
{}

/* virtual */
void BakModule::AddUniqueInfo()
{
    	info.addTitleStr("bak module");
    	info.addNameStr("fuel_max_add:"); info.addValueStr( int2str(fuel_max_add) );
}

/*virtual*/
void BakModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
	const std::string root = "bak_module." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseModule(save_ptree, root);
	SaveDataUniqueBakModule(save_ptree, root);
}

/*virtual*/		
void BakModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
        LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseModule(load_ptree);
	LoadDataUniqueBakModule(load_ptree);
}
	
/*virtual*/	
void BakModule::ResolveData()
{
        ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseModule();
	ResolveDataUniqueBakModule();
}

void BakModule::SaveDataUniqueBakModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" SaveDataUniqueBakModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
	save_ptree.put(root+"fuel_max_add", fuel_max_add);
}

void BakModule::LoadDataUniqueBakModule(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" LoadDataUniqueBakModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
	fuel_max_add = load_ptree.get<int>("fuel_max_add");
}

void BakModule::ResolveDataUniqueBakModule()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" ResolveDataUniqueBakModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
}
