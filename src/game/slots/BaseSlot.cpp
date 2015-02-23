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

#include "BaseSlot.hpp"
#include "../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include "../common/Logger.hpp"

#include <common/Global.hpp>
#include <world/EntitiesManager.hpp>

#include "../spaceobjects/Vehicle.hpp"

BaseSlot::BaseSlot()
:
selected(false),
textureOb(nullptr),
owner(nullptr)
{}

/* virtual */
BaseSlot::~BaseSlot()
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("___::~BaseSlot("+std::to_string(id())+")");
    #endif
}
                
void BaseSlot::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{   
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BaseSlot("+std::to_string(id())+")::SaveData", SAVELOAD_LOG_DIP);
    #endif
        
    if (owner) { save_ptree.put(root+"unresolved.owner_id", owner->id()); }
    else       { save_ptree.put(root+"unresolved.owner_id", NONE_ID); }
    
    save_ptree.put(root+"position.x", position.x);
    save_ptree.put(root+"position.y", position.y);
}

void BaseSlot::LoadData(const boost::property_tree::ptree& load_ptree)
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BaseSlot("+std::to_string(id())+")::LoadData", SAVELOAD_LOG_DIP);
    #endif
       
    unresolved_BaseSlot.owner_id = load_ptree.get<int>("unresolved.owner_id"); 
    position = glm::vec2(load_ptree.get<int>("position.x"), load_ptree.get<int>("position.y"));

}

void BaseSlot::ResolveData()
{
    #if SAVELOAD_LOG_ENABLED == 1
    Logger::Instance().Log(" BaseSlot("+std::to_string(id())+")::ResolveData", SAVELOAD_LOG_DIP);
    #endif
    
    if (unresolved_BaseSlot.owner_id != NONE_ID)
    {
        owner = global::get().entitiesManager().GetEntityById(unresolved_BaseSlot.owner_id);
    }
}


