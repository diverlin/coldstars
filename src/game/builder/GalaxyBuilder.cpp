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
#include "../world/galaxy.hpp"
#include "../world/starsystem.hpp"

#include "../config/config.hpp"

#include "../common/IdGenerator.hpp"
#include "../common/Logger.hpp"
#include "../world/EntityManager.hpp"
#include "../common/rand.hpp"
#include "../common/common.hpp"

#include "../world/GalaxyDescription.hpp"

GalaxyBuilder& GalaxyBuilder::Instance()
{
	static GalaxyBuilder instance;
	return instance;
}

GalaxyBuilder::~GalaxyBuilder()
{}

Galaxy* GalaxyBuilder::GetNewGalaxyTemplate(unsigned long int id) const
{
	Galaxy* galaxy = NULL;
	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
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

Galaxy* GalaxyBuilder::GetNewGalaxy(const GalaxyDescription& galaxy_description) const
{
	Galaxy* galaxy = GetNewGalaxyTemplate();
        CreateNewInternals(galaxy, galaxy_description);
        
	return galaxy;
} 


        	
void GalaxyBuilder::CreateNewInternals(Galaxy* galaxy, const GalaxyDescription& galaxy_description) const
{     
        float h_div_w_rate = ENTITY::GALAXY::STARSYSTEM_SEGMENTS_NUM_INHEIGHT/(float)ENTITY::GALAXY::STARSYSTEM_SEGMENTS_NUM_INWIDTH;
        int segment_w = ENTITY::GALAXY::PARSEC /((float)ENTITY::GALAXY::STARSYSTEM_SEGMENTS_NUM_INWIDTH + 1);
	int segment_h = ENTITY::GALAXY::PARSEC * h_div_w_rate/((float)ENTITY::GALAXY::STARSYSTEM_SEGMENTS_NUM_INHEIGHT + 1);
		
	std::vector<vec2f> starsystem_segment_vec;
	for (int i=1; i<=ENTITY::GALAXY::STARSYSTEM_SEGMENTS_NUM_INWIDTH; i++)
	{
		for (int j=1; j<=ENTITY::GALAXY::STARSYSTEM_SEGMENTS_NUM_INHEIGHT; j++)
		{
			starsystem_segment_vec.push_back(vec2f(i*segment_w/2, j*segment_h/2));
		}		
	}
	
	int starsystem_counter = 0;
    	for(int i=0; (i<starsystem_segment_vec.size()) and (starsystem_counter<galaxy_description.starsystem_num); i++)
    	{  
    		int starsystem_insegment_num = getRandInt(ENTITY::GALAXY::STARSYSTEM_INSEGMENT_NUM_MIN, ENTITY::GALAXY::STARSYSTEM_INSEGMENT_NUM_MAX);
                for (int j=0; (j<starsystem_insegment_num) and (starsystem_counter<galaxy_description.starsystem_num); j++)
                {
                	vec2f center = starsystem_segment_vec[i] + getRandVec2f(getMax(segment_w, segment_h)/7, getMax(segment_w, segment_h)/3);
                	                
        		StarSystem* starsystem = StarSystemBuilder::Instance().GetNewStarSystem();
        		galaxy->Add(starsystem, center); 
        		
        		starsystem_counter++;
 		}
 	}
}

                


                


