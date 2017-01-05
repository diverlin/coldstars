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

StarsystemBuilder::StarsystemBuilder()
{}

StarsystemBuilder::~StarsystemBuilder()
{}

Starsystem* StarsystemBuilder::create()
{
    const descriptor::Starsystem& descriptor = core::global::get().descriptors().starsystem().random();
    return create(descriptor);
}

Starsystem* StarsystemBuilder::create(const descriptor::Starsystem& descriptor)
{
    Starsystem* starsystem = new Starsystem;
    assert(starsystem);
   core::global::get().entityManager().reg(starsystem);
    __createInternals(starsystem, descriptor);
    return starsystem;
} 

Starsystem* StarsystemBuilder::create(const std::string& data)
{
    //return getNew(descriptor::Base(data));
}

void StarsystemBuilder::__createInternals(Starsystem* starsystem, const descriptor::Starsystem& descriptor)
{
    //    starsystem->asteroidManager().Parameterize(starsystem_descriptor.asteroid_num);
    __createStar(starsystem);
    
    //    int distNebula_num = meti::getRandInt(ENTITY::STARSYSTEM::DISTANT_NEBULA_MIN, ENTITY::STARSYSTEM::DISTANT_NEBULA_MAX);
    //    // alpitodorender CreateBackground(starsystem, distNebula_num, /*distStar_num*/1, starsystem->GetStar()->GetColorId());

    __createPlanets(starsystem, meti::getRandInt(2,5));
}

void StarsystemBuilder::__createBackground(Starsystem* starsystem, int distNebula_num, int distStar_num, int color_id)
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

void StarsystemBuilder::__createStar(Starsystem* starsystem)
{
    model::Star* star = builder::Star::getNew();
    starsystem->add(star);
    //alpitodorender starsystem->SetColor(star->color());
}

void StarsystemBuilder::__createPlanets(Starsystem* starsystem, int planet_per_system)
{
    //int orbit_radius = meti::getRandInt(2 * model::Planet::DISTANCE_MIN, 2 * model::Planet::DISTANCE_MAX);
    
    for(int i=0; i<planet_per_system; i++) {
        model::Planet* planet = builder::Planet::getNew();
        //starsystem->add(planet, starsystem->star());
        starsystem->add(planet);
        //orbit_radius += meti::getRandInt(ENTITY::PLANET::DISTANCE_MIN, ENTITY::PLANET::DISTANCE_MAX);
    }

}
