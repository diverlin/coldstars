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
    SetTypeId(TYPE::ENTITY::MODULE_ID);
    SetSubTypeId(TYPE::ENTITY::DROID_MODULE_ID);
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
void DroidModule::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "droid_module." + int2str(GetId()) + ".";
    
    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseModule::SaveData(save_ptree, root);
    DroidModule::SaveData(save_ptree, root);
}

/*virtual*/        
void DroidModule::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseModule::LoadData(load_ptree);
    DroidModule::LoadData(load_ptree);
}
    
/*virtual*/    
void DroidModule::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseModule::ResolveData();
    DroidModule::ResolveData();
}

void DroidModule::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" DroidModule::SaveData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"repair_add", repair_add);
}

void DroidModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" DroidModule::LoadData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    repair_add = load_ptree.get<int>("repair_add");
}

void DroidModule::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" DroidModule::ResolveData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}


