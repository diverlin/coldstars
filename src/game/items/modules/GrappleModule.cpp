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
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"

GrappleModule::GrappleModule(int id)
:
strength_add(0),
radius_add(0),    
speed_add(0),     
maxNumItem_add(0)
{
    SetId(id);
    SetTypeId(TYPE::ENTITY::MODULE_ID);
    SetSubTypeId(TYPE::ENTITY::GRAPPLE_MODULE_ID);  
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
            info.addNameStr("strength_add:");    info.addValueStr( int2str(strength_add) );
        }
        if (radius_add != 0)
        { 
            info.addNameStr("radius_add:");      info.addValueStr( int2str(radius_add) );
        } 
        if (speed_add != 0)
        {
            info.addNameStr("speed_add:");       info.addValueStr( int2str(speed_add) );
        }
        if (maxNumItem_add != 0)
        {
            info.addNameStr("maxNumItem_add:");  info.addValueStr( int2str(maxNumItem_add) ); 
        }
}

/*virtual*/
void GrappleModule::SaveData(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "grapple_module." + int2str(GetId()) + ".";
    Base::Save(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
    SaveDataUniqueBaseModule(save_ptree, root);
    SaveDataUniqueGrappleModule(save_ptree, root);
}

/*virtual*/        
void GrappleModule::LoadData(const boost::property_tree::ptree& load_ptree)
{
    Base::Load(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
    LoadDataUniqueBaseModule(load_ptree);
    LoadDataUniqueGrappleModule(load_ptree);
}
    
/*virtual*/    
void GrappleModule::ResolveData()
{
    Base::Resolve();
        ResolveDataUniqueBaseItem();
    ResolveDataUniqueBaseModule();
    ResolveDataUniqueGrappleModule();
}

void GrappleModule::SaveDataUniqueGrappleModule(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" SaveDataUniqueGrappleModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    save_ptree.put(root+"strength_add", strength_add);
    save_ptree.put(root+"radius_add", radius_add);
    save_ptree.put(root+"speed_add", speed_add);
    save_ptree.put(root+"maxNumItem_add", maxNumItem_add);
}

void GrappleModule::LoadDataUniqueGrappleModule(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" LoadDataUniqueGrappleModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
    
    strength_add = load_ptree.get<int>("strength_add");
    radius_add = load_ptree.get<int>("radius_add");
    speed_add = load_ptree.get<int>("speed_add");
    maxNumItem_add = load_ptree.get<int>("maxNumItem_add");
}

void GrappleModule::ResolveDataUniqueGrappleModule()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" ResolveDataUniqueGrappleModule()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
    #endif
}







