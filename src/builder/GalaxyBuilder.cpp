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
#include "../world/starsystem.hpp"

#include "../config/config.hpp"

#include "../common/id.hpp"
#include "../common/Logger.hpp"
#include "../common/EntityManager.hpp"
#include "../common/rand.hpp"
#include "../common/common.hpp"

#include "God.hpp"

GalaxyBuilder& GalaxyBuilder::Instance()
{
	static GalaxyBuilder instance;
	return instance;
}

GalaxyBuilder::~GalaxyBuilder()
{}

Galaxy* GalaxyBuilder::GetNewGalaxyTemplate(int id) const
{
	Galaxy* galaxy = NULL;
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
        
        return galaxy;
} 

Galaxy* GalaxyBuilder::GetNewGalaxy() const
{
	Galaxy* galaxy = GetNewGalaxyTemplate();
	
	switch(Config::Instance().GetGameMode())
        {
        	case GAME_MODE::NORMAL_RUN:
        	{
        	        CreateNewInternals(galaxy);
        		break;
        	}

        	case GAME_MODE::SIMPLE_RUN:
        	{
        	        CreateNewInternals_SIMPLE_RUN(galaxy);
        		break;
        	}
        }
        
	return galaxy;
} 


        	
void GalaxyBuilder::CreateNewInternals(Galaxy* galaxy) const
{     
        float h_div_w_rate = ENTITY::GALAXY::STARSYSTEM_SEGMENT_HEIGHT_NUM/(float)ENTITY::GALAXY::STARSYSTEM_SEGMENT_WIDTH_NUM;
        int segment_w = ENTITY::GALAXY::PARSEC /((float)ENTITY::GALAXY::STARSYSTEM_SEGMENT_WIDTH_NUM + 1);
	int segment_h = ENTITY::GALAXY::PARSEC * h_div_w_rate/((float)ENTITY::GALAXY::STARSYSTEM_SEGMENT_HEIGHT_NUM + 1);
		
	std::vector<vec2f> starsystem_segment_vec;
	for (int i=1; i<=ENTITY::GALAXY::STARSYSTEM_SEGMENT_WIDTH_NUM; i++)
	{
		for (int j=1; j<=ENTITY::GALAXY::STARSYSTEM_SEGMENT_HEIGHT_NUM; j++)
		{
			starsystem_segment_vec.push_back(vec2f(i*segment_w/2, j*segment_h/2));
		}		
	}
	
    	for(int i=0; i<starsystem_segment_vec.size(); i++)
    	{  
    		int starsystem_insegment_num = getRandInt(ENTITY::GALAXY::STARSYSTEM_INSEGMENT_NUM_MIN, ENTITY::GALAXY::STARSYSTEM_INSEGMENT_NUM_MAX);
                for (int j=0; j<starsystem_insegment_num; j++)
                {
                	vec2f center = starsystem_segment_vec[i] + getRandVec2f(getMax(segment_w, segment_h)/7, getMax(segment_w, segment_h)/3);
                	                
        		StarSystem* starsystem = StarSystemBuilder::Instance().GetNewStarSystem();
        		galaxy->Add(starsystem, center);
        		
        		God::Instance().CreateLifeInStarSystem(starsystem);
 		}
 	}
}

       	
void GalaxyBuilder::CreateNewInternals_SIMPLE_RUN(Galaxy* galaxy) const
{     
	vec2f center(getRandInt(200, 400), getRandInt(200, 400));
			
	StarSystem* starsystem = StarSystemBuilder::Instance().GetNewStarSystem();
	galaxy->Add(starsystem, center);
	
	//God::Instance().CreateLifeInStarSystem(starsystem);
}

                


                


