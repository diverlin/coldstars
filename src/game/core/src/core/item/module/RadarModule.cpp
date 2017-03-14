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

#include "RadarModule.hpp"
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

RadarModule::RadarModule(int id)
:
radius_add(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::MODULE_ID);
    setSubTypeId(TYPE::ENTITY::RADAR_MODULE_ID); 
}

/* virtual */
RadarModule::~RadarModule() 
{}

/* virtual */
void RadarModule::addUniqueInfo()
{
//    info.addTitleStr("radar module");
//    info.addNameStr("radius_add:");   info.addValueStr(std::to_string(radius_add));
}

/*virtual*/
void RadarModule::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "radar_module." + std::to_string(id()) + ".";
    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseModule::SaveData(save_ptree, root);
    RadarModule::SaveData(save_ptree, root);
}

/*virtual*/        
void RadarModule::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseModule::LoadData(load_ptree);
    RadarModule::LoadData(load_ptree);
}
    
/*virtual*/    
void RadarModule::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseModule::ResolveData();
    RadarModule::ResolveData();
}

void RadarModule::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    LOG(" RadarModule::SaveData()  id=" + std::to_string(id()) + " START");
    
    save_ptree.put(root+"radius_add", radius_add);
}

void RadarModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LOG(" RadarModule::LoadData()  id=" + std::to_string(id()) + " START");
    
    radius_add = load_ptree.get<int>("radius_add");
}

void RadarModule::ResolveData()
{
    LOG(" RadarModule::ResolveData()  id=" + std::to_string(id()) + " START");
}

