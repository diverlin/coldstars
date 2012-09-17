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

#include "GalaxyBuilder.hpp"
#include "StarSystemBuilder.hpp"

#include "../common/id.hpp"
#include "../common/Logger.hpp"
#include "../common/EntityManager.hpp"
#include "../common/rand.hpp"

GalaxyBuilder& GalaxyBuilder::Instance()
{
	static GalaxyBuilder instance;
	return instance;
}

GalaxyBuilder::~GalaxyBuilder()
{}

void GalaxyBuilder::CreateNewGalaxy(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	galaxy = new Galaxy(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        EntityManager::Instance().RegisterEntity(galaxy);
} 
        	
void GalaxyBuilder::CreateNewInternals()
{     	
    	int starsystem_num = getRandInt(ENTITY::GALAXY::STARSYSTEM_NUM_MIN, ENTITY::GALAXY::STARSYSTEM_NUM_MAX);
    	for(int i=0; i<starsystem_num; i++)
    	{  
                StarSystemBuilder::Instance().CreateNewStarSystem();
                StarSystemBuilder::Instance().CreateNewInternals();
                
        	StarSystem* starsystem = StarSystemBuilder::Instance().GetStarSystem();
        	starsystem->SetGalaxy(galaxy);
        	galaxy->Add(starsystem);
 	}
}

void GalaxyBuilder::CreateNewInternals_TEST()
{     	
    	int starsystem_num = 1;
    	for(int i=0; i<starsystem_num; i++)
    	{  
                StarSystemBuilder::Instance().CreateNewStarSystem();
                StarSystemBuilder::Instance().CreateNewInternals_TEST();
                
        	StarSystem* starsystem = StarSystemBuilder::Instance().GetStarSystem();
        	starsystem->SetGalaxy(galaxy);
        	galaxy->Add(starsystem);
 	}
}

                


