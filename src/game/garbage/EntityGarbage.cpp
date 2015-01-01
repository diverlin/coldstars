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
#include <ceti/myStr.hpp>
#include "../common/Logger.hpp"
#include "../common/Base.hpp"
#include "../world/EntityManager.hpp"
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
    Logger::Instance().Log("________EntityGarbage::Add entity " + getTypeStr(entity->GetTypeId()) + "(" +ceti::int2str(entity->GetTypeId()) +") " + getTypeStr(entity->GetSubTypeId()) + "(" + ceti::int2str(entity->GetSubTypeId()) + ") id=" + ceti::int2str(entity->GetId()));
    for (unsigned int i=0; i<entities_vec.size(); i++)
    {
        if (entities_vec[i]->GetId() == entity->GetId())
        {
            Logger::Instance().Log("________EntityGarbage::Add dublicated entity found(fix that) " + getTypeStr(entities_vec[i]->GetTypeId()) + "(" +ceti::int2str(entities_vec[i]->GetTypeId()) +") " + getTypeStr(entities_vec[i]->GetSubTypeId()) + "(" + ceti::int2str(entities_vec[i]->GetSubTypeId()) + ") id=" + ceti::int2str(entities_vec[i]->GetId()));
            exit(0);
        }
    }
    #endif
        
    entities_vec.push_back(entity);
    entity->PutChildsToGarbage();
}

void EntityGarbage::Clear()
{  
       for(unsigned int i=0; i<entities_vec.size(); i++)
    { 
        EntityManager::Instance().RemoveEntity(entities_vec[i]);
        #if CREATEDESTROY_LOG_ENABLED == 1
        Logger::Instance().Log("________EntityGarbage::Clear delete entity " + getTypeStr(entities_vec[i]->GetTypeId()) + "(" +ceti::int2str(entities_vec[i]->GetTypeId()) +") " + getTypeStr(entities_vec[i]->GetSubTypeId()) + "(" + ceti::int2str(entities_vec[i]->GetSubTypeId()) + ") id=" + ceti::int2str(entities_vec[i]->GetId()));
        #endif
        EntityIdGenerator::Instance().AddFreeId(entities_vec[i]->GetId());
        delete entities_vec[i];
    }
    entities_vec.clear();
}

