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


#include <builder/world/StarSystemBuilder.hpp>
#include <builder/spaceobjects/IncludeSpaceObjectBuilders.hpp>
#include <builder/pilots/NpcBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <struct/StarSystemDescriptor.hpp>

#include <spaceobjects/IncludeSpaceObjects.hpp>

#include <world/starsystem.hpp>

//#include <effects/DistantNebulaEffect.hpp>
//#include <effects/DistantStarEffect.hpp>

#include <meti/RandUtils.hpp>

#include <managers/EntitiesManager.hpp>

StarSystemBuilder::StarSystemBuilder()
{}

StarSystemBuilder::~StarSystemBuilder()
{}

StarSystem* StarSystemBuilder::createTemplate(INTLONGEST id) const
{
    StarSystem* starsystem = nullptr;    
    if (id == NONE_ID) {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    try {
        starsystem = new StarSystem(id);
    } catch(std::bad_alloc) {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }    
    global::get().entitiesManager().RegisterEntity(starsystem);
    
    return starsystem;
} 

StarSystem* StarSystemBuilder::create(const StarSystemDescriptor& starsystem_descriptor) const
{
    StarSystem* starsystem = createTemplate();
    createInternals(starsystem, starsystem_descriptor);
    
    return starsystem;
} 
            
void StarSystemBuilder::createInternals(StarSystem* starsystem, const StarSystemDescriptor& starsystem_descriptor) const
{
    starsystem->GetAsteroidManager().Parameterize(starsystem_descriptor.asteroid_num);
    CreateStar(starsystem);
    
    int distNebula_num = meti::getRandInt(ENTITY::STARSYSTEM::DISTANT_NEBULA_MIN, ENTITY::STARSYSTEM::DISTANT_NEBULA_MAX);
    // alpitodorender CreateBackground(starsystem, distNebula_num, /*distStar_num*/1, starsystem->GetStar()->GetColorId());
      
    CreatePlanets(starsystem, starsystem_descriptor.planet_num);
}
 
void StarSystemBuilder::CreateBackground(StarSystem* starsystem, int distNebula_num, int distStar_num, int color_id) const
{
    for(int i=0; i<distNebula_num; i++)
    { 
//        DistantNebulaEffect* dn = GetNewDistantNebulaEffect();
//        starsystem->Add(dn);
    } 

    for(int i=0; i<distStar_num; i++)
    { 
//        DistantStarEffect* ds = GetNewDistantStarEffect();
//        starsystem->Add(ds);
    } 
}
                                            
void StarSystemBuilder::CreateStar(StarSystem* starsystem) const
{
    Star* star = global::get().starBuilder().create();
    starsystem->Add(star);
    //alpitodorender starsystem->SetColor(star->color());
}

void StarSystemBuilder::CreatePlanets(StarSystem* starsystem, int planet_per_system) const
{
    int orbit_radius = meti::getRandInt(2 * ENTITY::PLANET::DISTANCE_MIN, 2 * ENTITY::PLANET::DISTANCE_MAX);
    
    for(int i=0; i<planet_per_system; i++) {
        Planet* planet = global::get().planetBuilder().create(orbit_radius);
        starsystem->Add(planet, starsystem->GetStar());
        orbit_radius += meti::getRandInt(ENTITY::PLANET::DISTANCE_MIN, ENTITY::PLANET::DISTANCE_MAX);
    }
        
}
