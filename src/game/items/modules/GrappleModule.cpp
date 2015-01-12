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

#include "GrappleModule.hpp"
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include "../../common/Logger.hpp"

GrappleModule::GrappleModule(int id)
:
strength_add(0),
radius_add(0),    
speed_add(0),     
maxNumItem_add(0)
{
    setId(id);
    setTypeId(TYPE::ENTITY::MODULE_ID);
    setSubTypeId(TYPE::ENTITY::GRAPPLE_MODULE_ID);  
}

/* virtual */
GrappleModule::~GrappleModule() 
{}

/* virtual */
void GrappleModule::AddUniqueInfo()
{
        info.addTitleStr("grapple module");
        if (strength_add != 0)
        {
            info.addNameStr("strength_add:");    info.addValueStr( std::to_string(strength_add) );
        }
        if (radius_add != 0)
        { 
            info.addNameStr("radius_add:");      info.addValueStr( std::to_string(radius_add) );
        } 
        if (speed_add != 0)
        {
            info.addNameStr("speed_add:");       info.addValueStr( std::to_string(speed_add) );
        }
        if (maxNumItem_add != 0)
        {
            info.addNameStr("maxNumItem_add:");  info.addValueStr( std::to_string(maxNumItem_add) );
        }
}

/*virtual*/
void GrappleModule::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "grapple_module." + std::to_string(id()) + ".";

    Base::SaveData(save_ptree, root);
    BaseItem::SaveData(save_ptree, root);
    BaseModule::SaveData(save_ptree, root);
    GrappleModule::SaveData(save_ptree, root);
}

/*virtual*/        
void GrappleModule::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    BaseItem::LoadData(load_ptree);
    BaseModule::LoadData(load_ptree);
    GrappleModule::LoadData(load_ptree);
}
    
/*virtual*/    
void GrappleModule::Resolve()
{
    Base::ResolveData();
    BaseItem::ResolveData();
    BaseModule::ResolveData();
    GrappleModule::ResolveData();
}

void GrappleModule::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" GrappleModule::SaveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"strength_add", strength_add);
    save_ptree.put(root+"radius_add", radius_add);
    save_ptree.put(root+"speed_add", speed_add);
    save_ptree.put(root+"maxNumItem_add", maxNumItem_add);
}

void GrappleModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" GrappleModule::LoadData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    strength_add = load_ptree.get<int>("strength_add");
    radius_add = load_ptree.get<int>("radius_add");
    speed_add = load_ptree.get<int>("speed_add");
    maxNumItem_add = load_ptree.get<int>("maxNumItem_add");
}

void GrappleModule::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" GrappleModule::ResolveData()  id=" + std::to_string(id()) + " START", SAVELOAD_LOG_DIP);
    #endif
}







