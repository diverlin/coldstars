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

#include "ScanerModule.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"

ScanerModule::ScanerModule(int id)
:
scan_add(0)
{
	SetId(id);
	SetTypeId(ENTITY::TYPE::MODULE_ID);
    SetSubTypeId(ENTITY::TYPE::SCANER_MODULE_ID);   
}

/* virtual */
ScanerModule::~ScanerModule() 
{}

/* virtual */		
void ScanerModule::AddUniqueInfo()
{
    	info.addTitleStr("scaner module");
    	info.addNameStr("scan_add:");      info.addValueStr( int2str(scan_add) );
}

/*virtual*/
void ScanerModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "scaner_module." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseModule(save_ptree, root);
	SaveDataUniqueScanerModule(save_ptree, root);
}

/*virtual*/		
void ScanerModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseModule(load_ptree);
	LoadDataUniqueScanerModule(load_ptree);
}
	
/*virtual*/	
void ScanerModule::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseModule();
	ResolveDataUniqueScanerModule();
}

void ScanerModule::SaveDataUniqueScanerModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" SaveDataUniqueScanerModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
	save_ptree.put(root+"scan_add", scan_add);
}

void ScanerModule::LoadDataUniqueScanerModule(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" LoadDataUniqueScanerModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
	scan_add = load_ptree.get<int>("scan_add");
}

void ScanerModule::ResolveDataUniqueScanerModule()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" ResolveDataUniqueScanerModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
}
