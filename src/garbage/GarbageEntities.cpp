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

#include "GarbageEntities.hpp"
#include "../common/myStr.hpp"
#include "../common/Logger.hpp"
#include "../common/Base.hpp"

GarbageEntities::GarbageEntities()
{}

GarbageEntities::~GarbageEntities()
{}
                  
void GarbageEntities::Add(Base* entitiy) 
{
	entities_vec.push_back(entitiy);
}

void GarbageEntities::Clear()
{  
   	for(unsigned int i=0; i<entities_vec.size(); i++)
    	{ 
    		#if CREATEDESTROY_LOG_ENABLED == 1
    		Logger::Instance().Log("________GarbageEntities delete " + getEntityStr(entities_vec[i]->GetTypeId()) + "(" +int2str(entities_vec[i]->GetTypeId()) +") " + getEntityStr(entities_vec[i]->GetSubTypeId()) + "(" + int2str(entities_vec[i]->GetSubTypeId()) + ") id=" + int2str(entities_vec[i]->GetId()));
		#endif
		delete entities_vec[i];
	}
    	entities_vec.clear();
}

