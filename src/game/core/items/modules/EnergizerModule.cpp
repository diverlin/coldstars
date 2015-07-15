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

#include "EnergizerModule.hpp"
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>
#include "../../items/equipment/BaseEquipment.hpp"

EnergizerModule::EnergizerModule(int id)
:
energy_max_add(0),
restoration_add(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::MODULE_ID);
    setSubTypeId(TYPE::ENTITY::ENERGIZER_MODULE_ID);
}

/* virtual */
EnergizerModule::~EnergizerModule()
{}

/* virtual */
void EnergizerModule::AddUniqueInfo()
{
//    info.addTitleStr("energizer module");
//    if (energy_max_add != 0)
//    {
//        info.addNameStr("energy_max_add:");  info.addValueStr( std::to_string(energy_max_add) );
//    }
//    if (restoration_add != 0)
//    {
//        info.addNameStr("restoration_add:"); info.addValueStr( std::to_string(restoration_add) );
//    }
}

/*virtual*/
void EnergizerModule::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "energizer_module." + std::to_string(id()) + ".";
    
    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseModule::SaveData(save_ptree, root);
    EnergizerModule::SaveData(save_ptree, root);
}

/*virtual*/        
void EnergizerModule::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseModule::LoadData(load_ptree);
    EnergizerModule::LoadData(load_ptree);
}
    
/*virtual*/    
void EnergizerModule::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseModule::ResolveData();
    EnergizerModule::ResolveData();
}

void EnergizerModule::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" EnergizerModule::SaveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"energy_max_add", energy_max_add);
    save_ptree.put(root+"restoration_add", restoration_add);
}

void EnergizerModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" EnergizerModule::LoadData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    energy_max_add = load_ptree.get<int>("energy_max_add");
    restoration_add = load_ptree.get<int>("restoration_add");
}

void EnergizerModule::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" EnergizerModule::ResolveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
}



