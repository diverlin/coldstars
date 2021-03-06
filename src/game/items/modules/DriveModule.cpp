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
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"

DriveModule::DriveModule(int id)
:
speed_add(0),
hyper_add(0)
{
    SetId(id);
    SetTypeId(TYPE::ENTITY::MODULE_ID);
    SetSubTypeId(TYPE::ENTITY::DRIVE_MODULE_ID);
}

/* virtual */
DriveModule::~DriveModule()
{}
        
/* virtual */
void DriveModule::AddUniqueInfo()
{ 
    info.addTitleStr("drive module"); 
    if (speed_add != 0)
    { 
        info.addNameStr("speed_add:");       info.addValueStr( int2str(speed_add) );
    } 
    
    if (hyper_add != 0)
    { 
        info.addNameStr("hyper_add:");       info.addValueStr( int2str(hyper_add) );
    }
}


/*virtual*/
void DriveModule::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "drive_module." + int2str(GetId()) + ".";
    
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
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" DriveModule::SaveData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"speed_add", speed_add);
    save_ptree.put(root+"hyper_add", hyper_add);
}

void DriveModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" DriveModule::LoadData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    speed_add = load_ptree.get<int>("speed_add");
    hyper_add = load_ptree.get<int>("hyper_add");
}

void DriveModule::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" DriveModule::ResolveData()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}



