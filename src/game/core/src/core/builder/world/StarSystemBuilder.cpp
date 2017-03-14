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
#include <builder/spaceobjects/ALL>
#include <builder/pilots/NpcBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <core/spaceobject/ALL>

#include <world/starsystem.hpp>

#include <descriptor/Base.hpp>
#include <descriptor/DescriptorManager.hpp>

//#include <client/effects/DistantNebulaEffect.hpp>
//#include <client/effects/DistantStarEffect.hpp>

#include <meti/RandUtils.hpp>

#include <managers/EntityManager.hpp>

namespace builder {

model::Starsystem*
Starsystem::create()
{
    descriptor::Starsystem* descr = descriptor::Manager::get().starsystem().random();
    return create(descr);
}

model::Starsystem*
Starsystem::create(descriptor::Starsystem* descr)
{
    model::Starsystem* model = new model::Starsystem;
    assert(model);
    core::global::get().entityManager().reg(model);
    __createInternals(model, descr);
    return model;
} 

model::Starsystem*
Starsystem::create(const std::string& data)
{
    //return gen(descriptor::Base(data));
}

void Starsystem::__createInternals(model::Starsystem* model, descriptor::Starsystem* descr)
{
    //    starsystem->asteroidManager().Parameterize(starsystem_descriptor.asteroid_num);
    __createStar(model);
    
    //    int distNebula_num = meti::getRandInt(ENTITY::STARSYSTEM::DISTANT_NEBULA_MIN, ENTITY::STARSYSTEM::DISTANT_NEBULA_MAX);
    //    // alpitodorender CreateBackground(starsystem, distNebula_num, /*distStar_num*/1, starsystem->GetStar()->GetColorId());

    __createPlanets(model, meti::getRandInt(2,5));
}

void Starsystem::__createBackground(model::Starsystem* starsystem, int distNebula_num, int distStar_num, int color_id)
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

void Starsystem::__createStar(model::Starsystem* starsystem)
{
    model::Star* star = builder::Star::gen();
    assert(false);
//    starsystem->add(star);
    //alpitodorender starsystem->SetColor(star->color());
}

void Starsystem::__createPlanets(model::Starsystem* starsystem, int planet_per_system)
{
    //int orbit_radius = meti::getRandInt(2 * model::Planet::DISTANCE_MIN, 2 * model::Planet::DISTANCE_MAX);
    
    for(int i=0; i<planet_per_system; i++) {
        model::Planet* planet = builder::Planet::gen();
        //starsystem->add(planet, starsystem->star());
        assert(false);
//        starsystem->add(planet);
        //orbit_radius += meti::getRandInt(ENTITY::PLANET::DISTANCE_MIN, ENTITY::PLANET::DISTANCE_MAX);
    }

}

} // namespace builder
