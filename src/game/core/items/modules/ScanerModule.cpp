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
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

ScanerModule::ScanerModule(int id)
:
scan_add(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::MODULE_ID);
    setSubTypeId(TYPE::ENTITY::SCANER_MODULE_ID);   
}

/* virtual */
ScanerModule::~ScanerModule() 
{}

/* virtual */        
void ScanerModule::AddUniqueInfo()
{
//    info.addTitleStr("scaner module");
//    info.addNameStr("scan_add:");      info.addValueStr( std::to_string(scan_add) );
}

/*virtual*/
void ScanerModule::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "scaner_module." + std::to_string(id()) + ".";
    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseModule::SaveData(save_ptree, root);
    ScanerModule::SaveData(save_ptree, root);
}

/*virtual*/        
void ScanerModule::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseModule::LoadData(load_ptree);
    ScanerModule::LoadData(load_ptree);
}
    
/*virtual*/    
void ScanerModule::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseModule::ResolveData();
    ScanerModule::ResolveData();
}

void ScanerModule::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" ScanerModule::SaveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"scan_add", scan_add);
}

void ScanerModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" ScanerModule::LoadData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    scan_add = load_ptree.get<int>("scan_add");
}

void ScanerModule::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" ScanerModule::ResolveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
}
