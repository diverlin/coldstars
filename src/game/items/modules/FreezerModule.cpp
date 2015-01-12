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
//#include <ceti/StringUtils.hpp>
#include "../../common/Logger.hpp"

FreezerModule::FreezerModule(int id)
:
freeze_add(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::MODULE_ID);
    setSubTypeId(TYPE::ENTITY::FREEZER_MODULE_ID); 
}

/* virtual */
FreezerModule::~FreezerModule() 
{}

/* virtual */
void FreezerModule::AddUniqueInfo()
{
    info.addTitleStr("freezer module");
    info.addNameStr("freeze_add:");     info.addValueStr( std::to_string(freeze_add) );
}

/*virtual*/
void FreezerModule::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "freezer_module." + std::to_string(id()) + ".";

    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseModule::SaveData(save_ptree, root);
    FreezerModule::SaveData(save_ptree, root);
}

/*virtual*/        
void FreezerModule::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseModule::LoadData(load_ptree);
    FreezerModule::LoadData(load_ptree);
}
    
/*virtual*/    
void FreezerModule::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseModule::ResolveData();
    FreezerModule::ResolveData();
}

void FreezerModule::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" FreezerModule::SaveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"freeze_add", freeze_add);
}

void FreezerModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" FreezerModule::LoadData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    freeze_add = load_ptree.get<int>("freeze_add");
}

void FreezerModule::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" FreezerModule::ResolveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
}


