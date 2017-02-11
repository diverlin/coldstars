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
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

DroidModule::DroidModule(int id)
:
repair_add(0)        
{
    setId(id);
    setTypeId(TYPE::ENTITY::MODULE_ID);
    setSubTypeId(TYPE::ENTITY::DROID_MODULE_ID);
}

/* virtual */
DroidModule::~DroidModule() 
{}
    
/* virtual */    
void DroidModule::addUniqueInfo()
{
//    info.addTitleStr("droid module");
//    info.addNameStr("repair_add:");   info.addValueStr( std::to_string(repair_add) );
}

/*virtual*/
void DroidModule::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "droid_module." + std::to_string(id()) + ".";
    
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
    LOG(" DroidModule::SaveData()  id=" + std::to_string(id()) + " START");
    
    save_ptree.put(root+"repair_add", repair_add);
}

void DroidModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LOG(" DroidModule::LoadData()  id=" + std::to_string(id()) + " START");
    
    repair_add = load_ptree.get<int>("repair_add");
}

void DroidModule::ResolveData()
{
    LOG(" DroidModule::ResolveData()  id=" + std::to_string(id()) + " START");
}

