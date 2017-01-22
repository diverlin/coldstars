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

#include <spaceobjects/ALL>

#include <world/starsystem.hpp>

#include <descriptors/Base.hpp>
#include <descriptors/DescriptorManager.hpp>

//#include <client/effects/DistantNebulaEffect.hpp>
//#include <client/effects/DistantStarEffect.hpp>

#include <meti/RandUtils.hpp>

#include <managers/EntityManager.hpp>

namespace builder {

Starsystem::Starsystem()
{}

Starsystem::~Starsystem()
{}

model::Starsystem*
Starsystem::create()
{
    const descriptor::Starsystem& descriptor = core::global::get().descriptors().starsystem().random();
    return create(descriptor);
}

model::Starsystem*
Starsystem::create(const descriptor::Starsystem& descriptor)
{
    model::Starsystem* starsystem = new model::Starsystem;
    assert(starsystem);
    core::global::get().entityManager().reg(starsystem);
    __createInternals(starsystem, descriptor);
    return starsystem;
} 

model::Starsystem*
Starsystem::create(const std::string& data)
{
    //return getNew(descriptor::Base(data));
}

void Starsystem::__createInternals(model::Starsystem* starsystem, const descriptor::Starsystem& descriptor)
{
    //    starsystem->asteroidManager().Parameterize(starsystem_descriptor.asteroid_num);
    __createStar(starsystem);
    
    //    int distNebula_num = meti::getRandInt(ENTITY::STARSYSTEM::DISTANT_NEBULA_MIN, ENTITY::STARSYSTEM::DISTANT_NEBULA_MAX);
    //    // alpitodorender CreateBackground(starsystem, distNebula_num, /*distStar_num*/1, starsystem->GetStar()->GetColorId());

    __createPlanets(starsystem, meti::getRandInt(2,5));
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
    model::Star* star = builder::Star::create();
    assert(false);
//    starsystem->add(star);
    //alpitodorender starsystem->SetColor(star->color());
}

void Starsystem::__createPlanets(model::Starsystem* starsystem, int planet_per_system)
{
    //int orbit_radius = meti::getRandInt(2 * model::Planet::DISTANCE_MIN, 2 * model::Planet::DISTANCE_MAX);
    
    for(int i=0; i<planet_per_system; i++) {
        model::Planet* planet = builder::Planet::create();
        //starsystem->add(planet, starsystem->star());
        assert(false);
//        starsystem->add(planet);
        //orbit_radius += meti::getRandInt(ENTITY::PLANET::DISTANCE_MIN, ENTITY::PLANET::DISTANCE_MAX);
    }

}

} // namespace builder
