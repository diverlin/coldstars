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
#include <core/manager/EntityManager.hpp>

#include <core/model/world/starsystem.hpp>
#include <core/world/starsystem.hpp>

#include <core/builder/world/StarSystemBuilder.hpp>
#include <core/builder/spaceobject/ALL>
#include <core/builder/item/equipment/ALL>

#include <core/spaceobject/ALL>
#include <core/item/equipment/ALL>
#include <core/model/spaceobject/ALL>

#include <ceti/Pack.hpp>

#include <gtest/gtest.h>

namespace test {

TEST(starsystem, add_remove_star)
{
    /* create opbjects */
    core::control::StarSystem* starsystem = core::StarSystemBuilder::gen();

    ceti::pack<int_t> star_ids = starsystem->model()->stars();

    /* pre-add check */
    EXPECT_EQ(starsystem->stars().size(), star_ids.size());

    int iterations = 5;
    for(int i=1; i<iterations; ++i) {
        core::control::Star* star = core::StarBuilder::gen();

        /* pre-add check */
        EXPECT_EQ(place::Type::NONE, star->place());

        /* add objects */
        starsystem->add(star);
        star_ids.add(star->id());

        /* post-add check */
        EXPECT_EQ(place::Type::SPACE, star->place());
        EXPECT_EQ(starsystem->stars().size(), star_ids.size());
        EXPECT_EQ(starsystem->model()->stars(), star_ids);
    }

    for(core::control::Star* star: starsystem->stars()) {
        /* pre-remove check */
        EXPECT_EQ(place::Type::SPACE, star->place());

        starsystem->remove(star);
        star_ids.remove(star->id());

        /* post-remove check */
        EXPECT_EQ(place::Type::NONE, star->place());
        EXPECT_EQ(starsystem->stars().size(), star_ids.size());
        EXPECT_EQ(starsystem->model()->stars(), star_ids);
    }
}

TEST(starsystem, add_remove_planet)
{
    /* create opbjects */
    core::control::StarSystem* starsystem = core::StarSystemBuilder::gen();

    ceti::pack<int_t> planet_ids = starsystem->model()->planets();

    /* pre-add check */
    EXPECT_EQ(starsystem->planets().size(), planet_ids.size());

    int iterations = 5;
    for(int i=1; i<iterations; ++i) {
        core::control::Planet* planet = core::PlanetBuilder::gen();

        /* pre-add check */
        EXPECT_EQ(place::Type::NONE, planet->place());

        /* add objects */
        starsystem->add(planet);
        planet_ids.add(planet->id());

        /* post-add check */
        EXPECT_EQ(place::Type::SPACE, planet->place());
        EXPECT_EQ(starsystem->planets().size(), planet_ids.size());
        EXPECT_EQ(starsystem->model()->planets(), planet_ids);
    }

    for(core::control::Planet* planet: starsystem->planets()) {
        /* pre-remove check */
        EXPECT_EQ(place::Type::SPACE, planet->place());

        starsystem->remove(planet);
        planet_ids.remove(planet->id());

        /* post-remove check */
        EXPECT_EQ(place::Type::NONE, planet->place());
        EXPECT_EQ(starsystem->planets().size(), planet_ids.size());
        EXPECT_EQ(starsystem->model()->planets(), planet_ids);
    }
}

TEST(starsystem, add_remove_asteroid)
{
    /* create opbjects */
    core::control::StarSystem* starsystem = core::StarSystemBuilder::gen();

    ceti::pack<int_t> asteroid_ids = starsystem->model()->asteroids();

    /* pre-add check */
    EXPECT_EQ(starsystem->asteroids().size(), asteroid_ids.size());

    int iterations = 5;
    for(int i=1; i<iterations; ++i) {
        core::control::Asteroid* asteroid = core::AsteroidBuilder::gen();

        /* pre-add check */
        EXPECT_EQ(place::Type::NONE, asteroid->place());

        /* add objects */
        starsystem->add(asteroid);
        asteroid_ids.add(asteroid->id());

        /* post-add check */
        EXPECT_EQ(place::Type::SPACE, asteroid->place());
        EXPECT_EQ(starsystem->asteroids().size(), asteroid_ids.size());
        EXPECT_EQ(starsystem->model()->asteroids(), asteroid_ids);
    }

    for(core::control::Asteroid* asteroid: starsystem->asteroids()) {
        /* pre-remove check */
        EXPECT_EQ(place::Type::SPACE, asteroid->place());

        starsystem->remove(asteroid);
        asteroid_ids.remove(asteroid->id());

        /* post-remove check */
        EXPECT_EQ(place::Type::NONE, asteroid->place());
        EXPECT_EQ(starsystem->asteroids().size(), asteroid_ids.size());
        EXPECT_EQ(starsystem->model()->asteroids(), asteroid_ids);
    }
}

TEST(starsystem, add_remove_wormhole)
{
    /* create opbjects */
    core::control::StarSystem* starsystem = core::StarSystemBuilder::gen();

    ceti::pack<int_t> wormhole_ids = starsystem->model()->wormholes();

    /* pre-add check */
    EXPECT_EQ(starsystem->wormholes().size(), wormhole_ids.size());

    int iterations = 5;
    for(int i=1; i<iterations; ++i) {
        core::control::WormHole* wormhole = core::WormHoleBuilder::gen();

        /* pre-add check */
        EXPECT_EQ(place::Type::NONE, wormhole->place());

        /* add objects */
        starsystem->add(wormhole, glm::vec3(0.0f));
        wormhole_ids.add(wormhole->id());

        /* post-add check */
        EXPECT_EQ(place::Type::SPACE, wormhole->place());
        EXPECT_EQ(starsystem->wormholes().size(), wormhole_ids.size());
        EXPECT_EQ(starsystem->model()->wormholes(), wormhole_ids);
    }

    for(core::control::WormHole* wormhole: starsystem->wormholes()) {
        /* pre-remove check */
        EXPECT_EQ(place::Type::SPACE, wormhole->place());

        starsystem->remove(wormhole);
        wormhole_ids.remove(wormhole->id());

        /* post-remove check */
        EXPECT_EQ(place::Type::NONE, wormhole->place());
        EXPECT_EQ(starsystem->wormholes().size(), wormhole_ids.size());
        EXPECT_EQ(starsystem->model()->wormholes(), wormhole_ids);
    }
}

TEST(starsystem, add_remove_spacestation)
{
    /* create opbjects */
    core::control::StarSystem* starsystem = core::StarSystemBuilder::gen();

    ceti::pack<int_t> spacestation_ids = starsystem->model()->spacestations();

    /* pre-add check */
    EXPECT_EQ(starsystem->spacestations().size(), spacestation_ids.size());

    int iterations = 5;
    for(int i=1; i<iterations; ++i) {
        core::control::SpaceStation* spacestation = core::SpaceStationBuilder::gen();

        /* pre-add check */
        EXPECT_EQ(place::Type::NONE, spacestation->place());

        /* add objects */
        starsystem->add(spacestation);
        spacestation_ids.add(spacestation->id());

        /* post-add check */
        EXPECT_EQ(place::Type::SPACE, spacestation->place());
        EXPECT_EQ(starsystem->spacestations().size(), spacestation_ids.size());
        EXPECT_EQ(starsystem->model()->spacestations(), spacestation_ids);
    }

    for(core::control::SpaceStation* spacestation: starsystem->spacestations()) {
        /* pre-remove check */
        EXPECT_EQ(place::Type::SPACE, spacestation->place());

        starsystem->remove(spacestation);
        spacestation_ids.remove(spacestation->id());

        /* post-remove check */
        EXPECT_EQ(place::Type::NONE, spacestation->place());
        EXPECT_EQ(starsystem->spacestations().size(), spacestation_ids.size());
        EXPECT_EQ(starsystem->model()->spacestations(), spacestation_ids);
    }
}

TEST(starsystem, add_remove_ship)
{
    /* create opbjects */
    core::control::StarSystem* starsystem = core::StarSystemBuilder::gen();

    ceti::pack<int_t> ship_ids = starsystem->model()->ships();

    /* pre-add check */
    EXPECT_EQ(starsystem->ships().size(), ship_ids.size());

    int iterations = 5;
    for(int i=1; i<iterations; ++i) {
        core::control::Ship* ship = core::ShipBuilder::gen();

        /* pre-add check */
        EXPECT_EQ(place::Type::NONE, ship->place());

        /* add objects */
        starsystem->add(ship);
        ship_ids.add(ship->id());

        /* post-add check */
        EXPECT_EQ(place::Type::SPACE, ship->place());
        EXPECT_EQ(starsystem->ships().size(), ship_ids.size());
        EXPECT_EQ(starsystem->model()->ships(), ship_ids);
    }

    for(core::control::Ship* ship: starsystem->ships()) {
        /* pre-remove check */
        EXPECT_EQ(place::Type::SPACE, ship->place());

        starsystem->remove(ship);
        ship_ids.remove(ship->id());

        /* post-remove check */
        EXPECT_EQ(place::Type::NONE, ship->place());
        EXPECT_EQ(starsystem->ships().size(), ship_ids.size());
        EXPECT_EQ(starsystem->model()->ships(), ship_ids);
    }
}

TEST(starsystem, add_remove_satellite)
{
    /* create opbjects */
    core::control::StarSystem* starsystem = core::StarSystemBuilder::gen();

    ceti::pack<int_t> satellite_ids = starsystem->model()->satellites();

    /* pre-add check */
    EXPECT_EQ(starsystem->satellites().size(), satellite_ids.size());

    int iterations = 5;
    for(int i=1; i<iterations; ++i) {
        core::control::Satellite* satellite = core::SatelliteBuilder::gen();

        /* pre-add check */
        EXPECT_EQ(place::Type::NONE, satellite->place());

        /* add objects */
        starsystem->add(satellite);
        satellite_ids.add(satellite->id());

        /* post-add check */
        EXPECT_EQ(place::Type::SPACE, satellite->place());
        EXPECT_EQ(starsystem->satellites().size(), satellite_ids.size());
        EXPECT_EQ(starsystem->model()->satellites(), satellite_ids);
    }

    for(core::control::Satellite* satellite: starsystem->satellites()) {
        /* pre-remove check */
        EXPECT_EQ(place::Type::SPACE, satellite->place());

        starsystem->remove(satellite);
        satellite_ids.remove(satellite->id());

        /* post-remove check */
        EXPECT_EQ(place::Type::NONE, satellite->place());
        EXPECT_EQ(starsystem->satellites().size(), satellite_ids.size());
        EXPECT_EQ(starsystem->model()->satellites(), satellite_ids);
    }
}

TEST(starsystem, add_remove_container)
{
    /* create opbjects */
    core::control::StarSystem* starsystem = core::StarSystemBuilder::gen();

    ceti::pack<int_t> container_ids = starsystem->model()->containers();

    /* pre-add check */
    EXPECT_EQ(starsystem->containers().size(), container_ids.size());

    int iterations = 5;
    for(int i=1; i<iterations; ++i) {
        core::control::Container* container = core::ContainerBuilder::gen();

        /* pre-add check */
        EXPECT_EQ(place::Type::NONE, container->place());

        /* add objects */
        starsystem->add(container, glm::vec3(0.0f));
        container_ids.add(container->id());

        /* post-add check */
        EXPECT_EQ(place::Type::SPACE, container->place());
        EXPECT_EQ(starsystem->containers().size(), container_ids.size());
        EXPECT_EQ(starsystem->model()->containers(), container_ids);
    }

    for(core::control::Container* container: starsystem->containers()) {
        /* pre-remove check */
        EXPECT_EQ(place::Type::SPACE, container->place());

        starsystem->remove(container);
        container_ids.remove(container->id());

        /* post-remove check */
        EXPECT_EQ(place::Type::NONE, container->place());
        EXPECT_EQ(starsystem->containers().size(), container_ids.size());
        EXPECT_EQ(starsystem->model()->containers(), container_ids);
    }
}

TEST(starsystem, add_remove_bullet)
{
    /* create opbjects */
    core::control::StarSystem* starsystem = core::StarSystemBuilder::gen();

    ceti::pack<int_t> bullet_ids = starsystem->model()->bullets();

    /* pre-add check */
    EXPECT_EQ(starsystem->bullets().size(), bullet_ids.size());

    int iterations = 5;
    for(int i=1; i<iterations; ++i) {
        core::control::Bullet* bullet = core::BulletBuilder::gen(1);

        /* pre-add check */
        EXPECT_EQ(place::Type::NONE, bullet->place());

        /* add objects */
        starsystem->add(bullet, glm::vec3(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        bullet_ids.add(bullet->id());

        /* post-add check */
        EXPECT_EQ(place::Type::SPACE, bullet->place());
        EXPECT_EQ(starsystem->containers().size(), bullet_ids.size());
        EXPECT_EQ(starsystem->model()->containers(), bullet_ids);
    }

    for(core::control::Bullet* bullet: starsystem->bullets()) {
        /* pre-remove check */
        EXPECT_EQ(place::Type::SPACE, bullet->place());

        starsystem->remove(bullet);
        bullet_ids.remove(bullet->id());

        /* post-remove check */
        EXPECT_EQ(place::Type::NONE, bullet->place());
        EXPECT_EQ(starsystem->bullets().size(), bullet_ids.size());
        EXPECT_EQ(starsystem->model()->bullets(), bullet_ids);
    }
}

} // namespace test
