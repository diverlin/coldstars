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
    ceti::pack<int_t> asteroid_ids = starsystem.model()->asteroids();
    ceti::pack<int_t> wormhole_ids = starsystem.model()->wormholes();
    ceti::pack<int_t> spacestation_ids= starsystem.model()->spacestations();
    ceti::pack<int_t> ship_ids = starsystem.model()->ships();
    ceti::pack<int_t> satellite_ids = starsystem.model()->satellites();
    ceti::pack<int_t> container_ids = starsystem.model()->containers();

    /* pre-add check */
    EXPECT_EQ(starsystem.control()->stars().size(), star_ids.size());
    EXPECT_EQ(starsystem.control()->planets().size(), planet_ids.size());
    EXPECT_EQ(starsystem.control()->asteroids().size(), asteroid_ids.size());
    EXPECT_EQ(starsystem.control()->wormholes().size(), wormhole_ids.size());
    EXPECT_EQ(starsystem.control()->spacestations().size(), spacestation_ids.size());
    EXPECT_EQ(starsystem.control()->ships().size(), ship_ids.size());
    EXPECT_EQ(starsystem.control()->satellites().size(), satellite_ids.size());
    EXPECT_EQ(starsystem.control()->containers().size(), container_ids.size());

    int iterations = 5;
    for(int i=1; i<iterations; ++i) {
        control::Star* star = genStar();
        control::Planet* planet = genPlanet();
        control::Asteroid* asteroid = genAsteroid();
        control::WormHole* wormhole = genWormHole();
        SpaceStation spacestation;
        Ship ship;
        Satellite satellite;
        control::Container* container = genContainer();

        /* add objects */
        starsystem.control()->add(star->model());
        star_ids.add(star->model()->id());

        starsystem.control()->add(planet->model());
        planet_ids.add(planet->model()->id());

        starsystem.control()->add(asteroid->model());
        asteroid_ids.add(asteroid->model()->id());

        starsystem.control()->add(spacestation.model());
        spacestation_ids.add(spacestation.model()->id());

        starsystem.control()->add(ship.model());
        ship_ids.add(ship.model()->id());

        starsystem.control()->add(satellite.model());
        satellite_ids.add(satellite.model()->id());

        starsystem.control()->add(container->model());
        container_ids.add(container->model()->id());

        /* post-add check */
        EXPECT_EQ(starsystem.control()->stars().size(), star_ids.size());
        EXPECT_EQ(starsystem.model()->stars(), star_ids);

        EXPECT_EQ(starsystem.control()->planets().size(), planet_ids.size());
        EXPECT_EQ(starsystem.model()->planets(), planet_ids);

        EXPECT_EQ(starsystem.control()->asteroids().size(), asteroid_ids.size());
        EXPECT_EQ(starsystem.model()->asteroids(), asteroid_ids);

        EXPECT_EQ(starsystem.control()->wormholes().size(), wormhole_ids.size());
        EXPECT_EQ(starsystem.model()->wormholes(), wormhole_ids);

        EXPECT_EQ(starsystem.control()->spacestations().size(), spacestation_ids.size());
        EXPECT_EQ(starsystem.model()->spacestations(), spacestation_ids);

        EXPECT_EQ(starsystem.control()->ships().size(), ship_ids.size());
        EXPECT_EQ(starsystem.model()->ships(), ship_ids);

        EXPECT_EQ(starsystem.control()->containers().size(), container_ids.size());
        EXPECT_EQ(starsystem.model()->containers(), container_ids);
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
    for(control::Asteroid* asteroid: starsystem.control()->asteroids()) {
        starsystem.control()->remove(asteroid);
        asteroid_ids.remove(asteroid->model()->id());

        EXPECT_EQ(starsystem.control()->asteroids().size(), asteroid_ids.size());
        EXPECT_EQ(starsystem.model()->asteroids(), asteroid_ids);
    }
    for(control::WormHole* wormhole: starsystem.control()->wormholes()) {
        starsystem.control()->remove(wormhole);
        asteroid_ids.remove(wormhole->model()->id());

        EXPECT_EQ(starsystem.control()->wormholes().size(), wormhole_ids.size());
        EXPECT_EQ(starsystem.model()->wormholes(), wormhole_ids);
    }
    for(control::SpaceStation* spacestation: starsystem.control()->spacestations()) {
        starsystem.control()->remove(spacestation);
        spacestation_ids.remove(spacestation->model()->id());

        EXPECT_EQ(starsystem.control()->spacestations().size(), spacestation_ids.size());
        EXPECT_EQ(starsystem.model()->spacestations(), spacestation_ids);
    }
    for(control::Ship* ship: starsystem.control()->ships()) {
        starsystem.control()->remove(ship);
        ship_ids.remove(ship->model()->id());

        EXPECT_EQ(starsystem.control()->ships().size(), ship_ids.size());
        EXPECT_EQ(starsystem.model()->ships(), ship_ids);
    }
    for(control::Satellite* satellite: starsystem.control()->satellites()) {
        starsystem.control()->remove(satellite);
        satellite_ids.remove(satellite->model()->id());

        EXPECT_EQ(starsystem.control()->satellites().size(), satellite_ids.size());
        EXPECT_EQ(starsystem.model()->satellites(), satellite_ids);
    }
    for(control::Container* container: starsystem.control()->containers()) {
        starsystem.control()->remove(container);
        satellite_ids.remove(container->model()->id());

        EXPECT_EQ(starsystem.control()->containers().size(), container_ids.size());
        EXPECT_EQ(starsystem.model()->containers(), container_ids);
    }
}

} // namespace test
