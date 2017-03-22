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

#include "helper.hpp"

#include <core/common/Global.hpp>

#include <core/descriptor/Base.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <core/model/world/starsystem.hpp>
#include <core/world/starsystem.hpp>

#include <core/builder/world/StarSystemBuilder.hpp>
#include <core/builder/spaceobject/ALL>

#include <core/spaceobject/ALL>
#include <core/model/spaceobject/ALL>

#include <core/manager/EntityManager.hpp>

#include <ceti/Pack.hpp>

#include <gtest/gtest.h>

namespace test {

TEST(starsystem, add_remove_objects)
{
    /* create opbjects */
    StarSystem starsystem;

    ceti::pack<int_t> star_ids = starsystem.model()->stars();
    ceti::pack<int_t> planet_ids = starsystem.model()->planets();
    ceti::pack<int_t> spacestation_init = starsystem.model()->spacestations();
    ceti::pack<int_t> ship_ids = starsystem.model()->ships();
    ceti::pack<int_t> satellite_ids = starsystem.model()->satellites();

    /* pre-add check */
    EXPECT_EQ(starsystem.control()->stars().size(), star_ids.size());
    EXPECT_EQ(starsystem.control()->planets().size(), planet_ids.size());
    EXPECT_EQ(starsystem.control()->spacestations().size(), spacestation_init.size());
    EXPECT_EQ(starsystem.control()->ships().size(), ship_ids.size());
    EXPECT_EQ(starsystem.control()->satellites().size(), satellite_ids.size());

    for(int i=1; i<5; ++i) {
        Star star;
        Planet planet;
        //    test::SpaceStation spacestation;
        Ship ship;
        //    test::Satellite satellite;

        /* add objects */
        starsystem.control()->add(star.model());
        star_ids.add(star.model()->id());

        starsystem.control()->add(planet.model());
        planet_ids.add(planet.model()->id());

        //    starsystem.control()->add(spacestation.model());
        starsystem.control()->add(ship.model());
        ship_ids.add(ship.model()->id());
        //    starsystem.control()->add(satellite.model());

        /* post-add check */
        EXPECT_EQ(starsystem.control()->stars().size(), star_ids.size());
        EXPECT_EQ(starsystem.model()->stars(), star_ids);

        EXPECT_EQ(starsystem.control()->planets().size(), planet_ids.size());
        EXPECT_EQ(starsystem.model()->planets(), planet_ids);

        //    EXPECT_EQ(starsystem.control()->spacestations().size(), init_spacestations.size() + i);

        EXPECT_EQ(starsystem.control()->ships().size(), ship_ids.size());
        EXPECT_EQ(starsystem.model()->ships(), ship_ids);

        //    EXPECT_EQ(starsystem.control()->satellites().size(), init_satellites.size() + i);
    }

    for(control::Ship* ship: starsystem.control()->ships()) {
        starsystem.control()->remove(ship);
        ship_ids.remove(ship->model()->id());

        EXPECT_EQ(starsystem.control()->ships().size(), ship_ids.size());
        EXPECT_EQ(starsystem.model()->ships(), ship_ids);
    }
    for(control::Star* star: starsystem.control()->stars()) {
        starsystem.control()->remove(star);
        star_ids.remove(star->model()->id());

        EXPECT_EQ(starsystem.control()->stars().size(), star_ids.size());
        EXPECT_EQ(starsystem.model()->stars(), star_ids);
        return;
    }
    for(control::Planet* planet: starsystem.control()->planets()) {
        starsystem.control()->remove(planet);
        planet_ids.remove(planet->model()->id());

        EXPECT_EQ(starsystem.control()->planets().size(), planet_ids.size());
        EXPECT_EQ(starsystem.model()->planets(), planet_ids);
    }
//    for(control::Asteroid* asteroid: starsystem.control()->asteroids()) {
//        starsystem.control()->remove(asteroid);

//        asteroid_ids.remove(asteroid->model()->id());

//        EXPECT_EQ(starsystem.control()->asteroids().size(), asteroid_ids.size());
//        EXPECT_EQ(starsystem.model()->asteroids(), asteroid_ids);
//    }
}

} // namespace test
