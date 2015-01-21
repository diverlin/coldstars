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

#include "EntityGarbage.hpp"
//#include <ceti/StringUtils.hpp>
#include "../common/Logger.hpp"
#include "../common/Base.hpp"
#include "../common/Global.hpp"
#include "../world/EntitiesManager.hpp"
#include "../common/IdGenerator.hpp"

EntityGarbage& EntityGarbage::Instance()
{
    static EntityGarbage instance;
    return instance;
}

EntityGarbage::~EntityGarbage()
{}
                  
void EntityGarbage::Add(Base* entity) 
{
    #if CREATEDESTROY_LOG_ENABLED == 1
    Logger::Instance().Log("________EntityGarbage::Add entity " + getTypeStr(entity->typeId()) + "(" +std::to_string(entity->typeId()) +") " + getTypeStr(entity->subTypeId()) + "(" + std::to_string(entity->subTypeId()) + ") id=" + std::to_string(entity->id()));
    for (unsigned int i=0; i<entities_vec.size(); i++)
    {
        if (entities_vec[i]->id() == entity->id())
        {
            Logger::Instance().Log("________EntityGarbage::Add dublicated entity found(fix that) " + getTypeStr(entities_vec[i]->typeId()) + "(" +std::to_string(entities_vec[i]->typeId()) +") " + getTypeStr(entities_vec[i]->subTypeId()) + "(" + std::to_string(entities_vec[i]->subTypeId()) + ") id=" + std::to_string(entities_vec[i]->id()));
            exit(0);
        }
    }
    #endif
        
    entities_vec.push_back(entity);
    entity->putChildrenToGarbage();
}

void EntityGarbage::Clear()
{  
       for(unsigned int i=0; i<entities_vec.size(); i++)
    { 
        global::instance().entitiesManager().RemoveEntity(entities_vec[i]);
        #if CREATEDESTROY_LOG_ENABLED == 1
        Logger::Instance().Log("________EntityGarbage::Clear delete entity " + getTypeStr(entities_vec[i]->typeId()) + "(" +std::to_string(entities_vec[i]->typeId()) +") " + getTypeStr(entities_vec[i]->subTypeId()) + "(" + std::to_string(entities_vec[i]->subTypeId()) + ") id=" + std::to_string(entities_vec[i]->id()));
        #endif
        EntityIdGenerator::Instance().AddFreeId(entities_vec[i]->id());
        delete entities_vec[i];
    }
    entities_vec.clear();
}

