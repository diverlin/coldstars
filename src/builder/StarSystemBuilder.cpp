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

#include "StarSystemBuilder.hpp"

#include "NpcBuilder.hpp"
#include "StarBuilder.hpp"
#include "PlanetBuilder.hpp"
#include "SpaceStationBuilder.hpp"
#include "SatelliteBuilder.hpp"
#include "ShipBuilder.hpp"
#include "../spaceobjects/BlackHole.hpp"
#include "../spaceobjects/Planet.hpp"
#include "../spaceobjects/Star.hpp"

#include "../common/id.hpp"
#include "../world/EntityManager.hpp"
#include "../common/Logger.hpp"
#include "../common/rand.hpp"

#include "../world/starsystem.hpp"

#include "../effects/DistantNebulaEffect.hpp"
#include "../effects/DistantStarEffect.hpp"

StarSystemBuilder& StarSystemBuilder::Instance()
{
	static StarSystemBuilder instance;
	return instance;
}

StarSystemBuilder::~StarSystemBuilder()
{}

StarSystem* StarSystemBuilder::GetNewStarSystemTemplate(unsigned long int id) const
{
	StarSystem* starsystem = NULL;
	
	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	starsystem = new StarSystem(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        EntityManager::Instance().RegisterEntity(starsystem);
        
        return starsystem;
} 

StarSystem* StarSystemBuilder::GetNewStarSystem() const
{
	StarSystem* starsystem = GetNewStarSystemTemplate();
	CreateNewInternals(starsystem);
        
        return starsystem;
} 
        	
void StarSystemBuilder::CreateNewInternals(StarSystem* starsystem) const
{
        CreateStar(starsystem);
        
        int distNebula_num = getRandInt(ENTITY::STARSYSTEM::DISTANT_NEBULA_MIN, ENTITY::STARSYSTEM::DISTANT_NEBULA_MAX);
        int distStar_num = getRandInt(ENTITY::STARSYSTEM::DISTANT_STAR_MIN, ENTITY::STARSYSTEM::DISTANT_STAR_MAX);
        CreateBackground(starsystem, distNebula_num, distStar_num, starsystem->GetStar()->GetColorId());
          
        int planet_num = getRandInt(ENTITY::STARSYSTEM::PLANET_NUM_MIN, ENTITY::STARSYSTEM::PLANET_NUM_MAX);
        CreatePlanets(starsystem, planet_num);
}
 
void StarSystemBuilder::CreateBackground(StarSystem* starsystem, int distNebula_num, int distStar_num, int color_id) const
{
        for(int i=0; i<distNebula_num; i++)
        { 
		DistantNebulaEffect* dn = GetNewDistantNebulaEffect();
                starsystem->Add(dn);
        } 

        for(int i=0; i<distStar_num; i++)
        { 
		DistantStarEffect* ds = GetNewDistantStarEffect();
                starsystem->Add(ds);
        } 
}
                        	                
void StarSystemBuilder::CreateStar(StarSystem* starsystem) const
{
        Star* star = StarBuilder::Instance().GetNewStar(); 
        starsystem->Add(star);
	starsystem->SetColor(star->GetColor());
}

void StarSystemBuilder::CreatePlanets(StarSystem* starsystem, int planet_per_system) const
{
        int orbit_radius = getRandInt(2 * ENTITY::PLANET::DISTANCE_MIN, 2 * ENTITY::PLANET::DISTANCE_MAX);

        for(int i=0; i<planet_per_system; i++)
        {             
                Planet* planet = PlanetBuilder::Instance().GetNewPlanet(orbit_radius);

                starsystem->Add(planet, starsystem->GetStar());
                
                orbit_radius += getRandInt(ENTITY::PLANET::DISTANCE_MIN, ENTITY::PLANET::DISTANCE_MAX);
        }
        
}
