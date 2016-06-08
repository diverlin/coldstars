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

//#include <effects/DistantNebulaEffect.hpp>
//#include <effects/DistantStarEffect.hpp>

#include <meti/RandUtils.hpp>

#include <managers/EntityManager.hpp>

StarsystemBuilder::StarsystemBuilder()
{}

StarsystemBuilder::~StarsystemBuilder()
{}

Starsystem* StarsystemBuilder::getNew(const descriptor::Base& descriptor) const
{
    Starsystem* starsystem = new Starsystem(descriptor.id());
    assert(starsystem);
    global::get().entityManager().reg(starsystem);
    __createInternals(starsystem, descriptor);
    return starsystem;
} 

Starsystem* StarsystemBuilder::getNew(const std::string& data) const
{
    return getNew(descriptor::Base(data));
}

void StarsystemBuilder::__createInternals(Starsystem* starsystem, const descriptor::Base& starsystem_descriptor) const
{
    //    starsystem->asteroidManager().Parameterize(starsystem_descriptor.asteroid_num);
    //    CreateStar(starsystem);
    
    //    int distNebula_num = meti::getRandInt(ENTITY::STARSYSTEM::DISTANT_NEBULA_MIN, ENTITY::STARSYSTEM::DISTANT_NEBULA_MAX);
    //    // alpitodorender CreateBackground(starsystem, distNebula_num, /*distStar_num*/1, starsystem->GetStar()->GetColorId());

    //    CreatePlanets(starsystem, starsystem_descriptor.planet_num);
}

void StarsystemBuilder::__createBackground(Starsystem* starsystem, int distNebula_num, int distStar_num, int color_id) const
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

void StarsystemBuilder::__createStar(Starsystem* starsystem) const
{
    Star* star = global::get().starBuilder().getNew();
    starsystem->add(star);
    //alpitodorender starsystem->SetColor(star->color());
}

void StarsystemBuilder::__createPlanets(Starsystem* starsystem, int planet_per_system) const
{
    int orbit_radius = meti::getRandInt(2 * ENTITY::PLANET::DISTANCE_MIN, 2 * ENTITY::PLANET::DISTANCE_MAX);
    
    for(int i=0; i<planet_per_system; i++) {
        Planet* planet = global::get().planetBuilder().create(orbit_radius);
        starsystem->add(planet, starsystem->star());
        orbit_radius += meti::getRandInt(ENTITY::PLANET::DISTANCE_MIN, ENTITY::PLANET::DISTANCE_MAX);
    }

}
