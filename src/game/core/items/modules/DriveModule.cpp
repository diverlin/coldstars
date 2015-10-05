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

#include "DriveModule.hpp"
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

DriveModule::DriveModule(int id)
:
speed_add(0),
hyper_add(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::MODULE_ID);
    setSubTypeId(TYPE::ENTITY::DRIVE_MODULE_ID);
}

/* virtual */
DriveModule::~DriveModule()
{}
        
/* virtual */
void DriveModule::AddUniqueInfo()
{ 
//    info.addTitleStr("drive module");
//    if (speed_add != 0)
//    {
//        info.addNameStr("speed_add:");       info.addValueStr( std::to_string(speed_add) );
//    }
    
//    if (hyper_add != 0)
//    {
//        info.addNameStr("hyper_add:");       info.addValueStr( std::to_string(hyper_add) );
//    }
}


/*virtual*/
void DriveModule::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "drive_module." + std::to_string(id()) + ".";
    
    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseModule::SaveData(save_ptree, root);
    DriveModule::SaveData(save_ptree, root);
}

/*virtual*/        
void DriveModule::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseModule::LoadData(load_ptree);
    DriveModule::LoadData(load_ptree);
}
    
/*virtual*/    
void DriveModule::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseModule::ResolveData();
    DriveModule::ResolveData();
}

void DriveModule::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    Logger::Instance().Log(" DriveModule::SaveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    
    save_ptree.put(root+"speed_add", speed_add);
    save_ptree.put(root+"hyper_add", hyper_add);
}

void DriveModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
    Logger::Instance().Log(" DriveModule::LoadData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    
    speed_add = load_ptree.get<int>("speed_add");
    hyper_add = load_ptree.get<int>("hyper_add");
}

void DriveModule::ResolveData()
{
    Logger::Instance().Log(" DriveModule::ResolveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
}



