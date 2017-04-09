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
#include <core/builder/spaceobject/ALL>
#include <core/builder/pilot/NpcBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <core/spaceobject/ALL>

#include <world/starsystem.hpp>

#include <descriptor/Base.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/model/world/starsystem.hpp>

#include <core/generator/DescriptorGenerator.hpp>

//#include <client/effects/DistantNebulaEffect.hpp>
//#include <client/effects/DistantStarEffect.hpp>

#include <meti/RandUtils.hpp>

#include <core/manager/EntityManager.hpp>
#include <core/descriptor/comm/Creation.hpp>

namespace builder {

control::StarSystem*
StarSystem::gen()
{
    descriptor::StarSystem* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::STARSYSTEM)) {
        descr = descriptor::genStarSystem();
    } else {
        descr = descriptor::Manager::get().randStarSystem();
    }
    assert(descr);
    return gen(descr);
}

control::StarSystem*
StarSystem::gen(descriptor::StarSystem* descr)
{
    control::StarSystem* starsystem = __genTemplate(descr);
    __createInternals(starsystem, descr);
    return starsystem;
} 

control::StarSystem*
StarSystem::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::StarSystem* descr = descriptor::Manager::get().starSystem(descriptor_id);
    control::StarSystem* starsystem = __genTemplate(descr, ob_id);
    __createInternals(starsystem, descr);
    return starsystem;
}

control::StarSystem*
StarSystem::__genTemplate(descriptor::StarSystem* descr, int_t ob_id)
{
    model::StarSystem* model = new model::StarSystem(descr->id(), ob_id);
    assert(model);

    control::StarSystem* starsystem = new control::StarSystem(descr, model);
    assert(starsystem);

    EntityManager::get().add(starsystem);
    return starsystem;
}


void StarSystem::__createInternals(control::StarSystem* starsystem, descriptor::StarSystem* descr)
{
    //    starsystem->asteroidManager().Parameterize(starsystem_descriptor.asteroid_num);
    //__createStar(starsystem);
    
    //    int distNebula_num = meti::getRandInt(ENTITY::STARSYSTEM::DISTANT_NEBULA_MIN, ENTITY::STARSYSTEM::DISTANT_NEBULA_MAX);
    //    // alpitodorender CreateBackground(starsystem, distNebula_num, /*distStar_num*/1, starsystem->GetStar()->GetColorId());

    //__createPlanets(starsystem, meti::getRandInt(2,5));
}

void StarSystem::__createBackground(control::StarSystem& starsystem, int distNebula_num, int distStar_num, int color_id)
{
    for(int i=0; i<distNebula_num; i++) {
        //        DistantNebulaEffect* dn = GetNewDistantNebulaEffect();
        //        starsystem->Add(dn);
    }

    for(int i=0; i<distStar_num; i++) {
        //        DistantStarEffect* ds = GetNewDistantStarEffect();
        //        starsystem->Add(ds);
    }
}

void StarSystem::__createStar(control::StarSystem& starsystem)
{
    control::Star* model_star = builder::Star::gen();
    starsystem.add(model_star);
    //alpitodorender starsystem->SetColor(star->color());
}

void StarSystem::__createPlanets(control::StarSystem& starsystem, int planet_per_system)
{
    //int orbit_radius = meti::getRandInt(2 * model::Planet::DISTANCE_MIN, 2 * model::Planet::DISTANCE_MAX);
    for(int i=0; i<planet_per_system; i++) {
        control::Planet* planet = builder::Planet::gen();
        starsystem.add(planet);
        //orbit_radius += meti::getRandInt(ENTITY::PLANET::DISTANCE_MIN, ENTITY::PLANET::DISTANCE_MAX);
    }
}

} // namespace builder
