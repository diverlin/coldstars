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

#include "LazerModule.hpp"
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>

LazerModule::LazerModule(int id)
:
damage_add(0),
radius_add(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::MODULE_ID);
    setSubTypeId(TYPE::ENTITY::LAZER_MODULE_ID);  
}

/* virtual */
LazerModule::~LazerModule()
{}

/* virtual */
void LazerModule::AddUniqueInfo()
{
//        info.addTitleStr("lazer module");
//        if (damage_add != 0)
//        {
//            info.addNameStr("damage_add:");   info.addValueStr(std::to_string(damage_add));
//        }
//        if (radius_add != 0)
//        {
//            info.addNameStr("radius_add:");   info.addValueStr(std::to_string(radius_add));
//        }
}

/*virtual*/
void LazerModule::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "lazer_module." + std::to_string(id()) + ".";
    
    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseModule::SaveData(save_ptree, root);
    LazerModule::SaveData(save_ptree, root);
}

/*virtual*/        
void LazerModule::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseModule::LoadData(load_ptree);
    LazerModule::LoadData(load_ptree);
}
    
/*virtual*/    
void LazerModule::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseModule::ResolveData();
    LazerModule::ResolveData();
}

void LazerModule::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    LOG(" LazerModule::SaveData()  id=" + std::to_string(id()) + " START");
    
    save_ptree.put(root+"damage_add", damage_add);
    save_ptree.put(root+"radius_add", radius_add);
}

void LazerModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
    LOG(" LazerModule::LoadData()  id=" + std::to_string(id()) + " START");
    
    damage_add = load_ptree.get<int>("damage_add");
    radius_add = load_ptree.get<int>("radius_add");
}

void LazerModule::ResolveData()
{
    LOG(" LazerModule::ResolveData()  id=" + std::to_string(id()) + " START");
}
