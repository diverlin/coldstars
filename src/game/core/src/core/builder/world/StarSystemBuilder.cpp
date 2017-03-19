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

#include <core/generator/DescriptorGenerator.hpp>

//#include <client/effects/DistantNebulaEffect.hpp>
//#include <client/effects/DistantStarEffect.hpp>

#include <meti/RandUtils.hpp>

#include <core/manager/EntityManager.hpp>

namespace builder {

model::StarSystem*
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

model::StarSystem*
StarSystem::gen(descriptor::StarSystem* descr)
{
    model::StarSystem* model = new model::StarSystem;
    assert(model);
    core::global::get().entityManager().reg(model);
    __createInternals(model, descr);
    return model;
} 

model::StarSystem*
StarSystem::gen(const std::string& data)
{
    //return gen(descriptor::Base(data));
}

void StarSystem::__createInternals(model::StarSystem* model, descriptor::StarSystem* descr)
{
    //    starsystem->asteroidManager().Parameterize(starsystem_descriptor.asteroid_num);
    __createStar(model);
    
    //    int distNebula_num = meti::getRandInt(ENTITY::STARSYSTEM::DISTANT_NEBULA_MIN, ENTITY::STARSYSTEM::DISTANT_NEBULA_MAX);
    //    // alpitodorender CreateBackground(starsystem, distNebula_num, /*distStar_num*/1, starsystem->GetStar()->GetColorId());

    __createPlanets(model, meti::getRandInt(2,5));
}

void StarSystem::__createBackground(model::StarSystem* starsystem, int distNebula_num, int distStar_num, int color_id)
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

void StarSystem::__createStar(model::StarSystem* model)
{
    control::StarSystem starsystem(model);
    model::Star* model_star = builder::Star::gen();
    starsystem.add(model_star);
    //alpitodorender starsystem->SetColor(star->color());
}

void StarSystem::__createPlanets(model::StarSystem* model, int planet_per_system)
{
    //int orbit_radius = meti::getRandInt(2 * model::Planet::DISTANCE_MIN, 2 * model::Planet::DISTANCE_MAX);
    control::StarSystem starsystem(model);

    for(int i=0; i<planet_per_system; i++) {
        model::Planet* planet = builder::Planet::gen();
        starsystem.add(planet, starsystem.star());
        //orbit_radius += meti::getRandInt(ENTITY::PLANET::DISTANCE_MIN, ENTITY::PLANET::DISTANCE_MAX);
    }

}

} // namespace builder
