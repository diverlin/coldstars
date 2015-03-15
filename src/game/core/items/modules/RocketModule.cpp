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

#include "RocketModule.hpp"
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include "../../common/Logger.hpp"

RocketModule::RocketModule(int id)
:
ammo_max_add(0),
damage_add(0),
radius_add(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::MODULE_ID);
    setSubTypeId(TYPE::ENTITY::ROCKET_MODULE_ID);  
}
       
/* virtual */
RocketModule::~RocketModule() 
{}

/* virtual */
void RocketModule::AddUniqueInfo()
{/*
    info.addTitleStr("rocket module"); 
    if (ammo_max_add != 0)
    {
        info.addNameStr("ammo_max_add:");   info.addValueStr(std::to_string(ammo_max_add));
    }
    if (damage_add != 0)
    {
        info.addNameStr("damage_add:");     info.addValueStr(std::to_string(damage_add));
    }
    if (radius_add != 0)
    {
        info.addNameStr("radius_add:");     info.addValueStr(std::to_string(radius_add));
    } */
}


/*virtual*/
void RocketModule::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "rocket_module." + std::to_string(id()) + ".";
    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseModule::SaveData(save_ptree, root);
    RocketModule::SaveData(save_ptree, root);
}

/*virtual*/        
void RocketModule::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseModule::LoadData(load_ptree);
    RocketModule::LoadData(load_ptree);
}
    
/*virtual*/    
void RocketModule::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseModule::ResolveData();
    RocketModule::ResolveData();
}

void RocketModule::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" RocketModule::SaveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"ammo_max_add", ammo_max_add);
    save_ptree.put(root+"damage_add", damage_add);
    save_ptree.put(root+"radius_add", radius_add);
}

void RocketModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" RocketModule::LoadData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    ammo_max_add = load_ptree.get<int>("ammo_max_add");
    damage_add = load_ptree.get<int>("damage_add");
    radius_add = load_ptree.get<int>("radius_add");
}

void RocketModule::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" RocketModule::ResolveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
}

