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

#include "FreezerModule.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"

FreezerModule::FreezerModule(int id)
{
        data_id.type_id    = id;
        data_id.subtype_id = ENTITY::FREEZER_MODULE_ID; 
        
     	freeze_add = 0;
}

/* virtual */
FreezerModule::~FreezerModule() 
{}

/* virtual */
void FreezerModule::AddUniqueInfo()
{
    	info.addTitleStr("freezer module");
    	info.addNameStr("freeze_add:");     info.addValueStr( int2str(freeze_add) );
}

/*virtual*/
void FreezerModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "freezer_module." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseModule(save_ptree, root);
	SaveDataUniqueFreezerModule(save_ptree, root);
}

/*virtual*/		
void FreezerModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseModule(load_ptree);
	LoadDataUniqueFreezerModule(load_ptree);
}
	
/*virtual*/	
void FreezerModule::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseModule();
	ResolveDataUniqueFreezerModule();
}

void FreezerModule::SaveDataUniqueFreezerModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"freeze_add", freeze_add);
}

void FreezerModule::LoadDataUniqueFreezerModule(const boost::property_tree::ptree& load_ptree)
{
	freeze_add = load_ptree.get<int>("freeze_add");
}

void FreezerModule::ResolveDataUniqueFreezerModule()
{}


