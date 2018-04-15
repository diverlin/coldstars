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

#include <core/type/PlaceType.hpp>
#include <core/common/Global.hpp>
#include <core/descriptor/Base.hpp>

#include <core/manager/EntityManager.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/manager/Garbage.hpp>

#include <core/pilot/Npc.hpp>

#include <core/generator/DescriptorGenerator.hpp>

#include <core/builder/world/ALL>
#include <core/builder/spaceobject/ALL>
#include <core/builder/item/equipment/ALL>

#include <core/world/ALL>
#include <core/item/equipment/ALL>
#include <core/spaceobject/ALL>
#include <core/slot/ItemSlot.hpp>

#include <core/descriptor/spaceobject/Ship.hpp>

#include <core/model/spaceobject/Planet.hpp>
#include <core/model/spaceobject/Ship.hpp>
#include <core/model/spaceobject/Container.hpp>

#include <core/model/item/equipment/Drive.hpp>

#include <core/communication/Events.hpp>
#include <core/communication/TelegramHandler.hpp>

#include <ceti/Pack.hpp>

#include <gtest/gtest.h>

namespace test {

TEST(ship, create)
{
    core::control::Ship* ship = core::ShipBuilder::gen();

    EXPECT_EQ(ship->descriptor()->bakSlotNum(), ship->bakSlots().size());
    EXPECT_EQ(ship->descriptor()->driveSlotNum(), ship->driveSlots().size());
    EXPECT_EQ(ship->descriptor()->radarSlotNum(), ship->radarSlots().size());
    EXPECT_EQ(ship->descriptor()->scanerSlotNum(), ship->scanerSlots().size());
    EXPECT_EQ(ship->descriptor()->grappleSlotNum(), ship->grappleSlots().size());
    EXPECT_EQ(ship->descriptor()->droidSlotNum(), ship->droidSlots().size());
    EXPECT_EQ(ship->descriptor()->protectorSlotNum(), ship->protectorSlots().size());
    EXPECT_EQ(ship->descriptor()->weaponSlotNum(), ship->weaponSlots().size());
    EXPECT_EQ(ship->descriptor()->cargoSlotNum(), ship->cargoSlots().size());
}

TEST(ship, drop_item)
{
    /* create objects */
    core::control::StarSystem* starsystem = core::StarSystemBuilder::gen();
    core::control::Ship* ship = core::ShipBuilder::gen();

    /* equip ship */
    core::control::Drive* drive = core::DriveItemBuilder::gen();
    ship->mount(drive);

    /* add ship */
    starsystem->add(ship);
    EXPECT_EQ(0, starsystem->containers().size());
    EXPECT_TRUE(ship->properties().speed > 0);
    EXPECT_EQ(1, ship->model()->items().size());

    /* drop item to space */
    core::event::dropItem(ship->id(), drive->id());

    EXPECT_EQ(0, ship->model()->items().size());
    EXPECT_EQ(1, starsystem->containers().size());
    assert(starsystem->containers().front());

    core::control::Container* container = starsystem->containers().front();
    EXPECT_EQ(ship->position(), container->position());
    EXPECT_EQ(place::Type::SPACE, container->place());
    EXPECT_EQ(drive, container->item());

    EXPECT_EQ(0, ship->properties().speed);
}

TEST(ship, grab_container)
{
    /* create objects */
    core::control::StarSystem* starsystem = core::StarSystemBuilder::gen();
    core::control::Ship* ship = core::ShipBuilder::gen();
    core::control::Grapple* grapple = core::GrappleItemBuilder::gen();
    EXPECT_TRUE(ship->mount(grapple));

    core::control::Container* container = core::ContainerBuilder::gen();
    core::control::Lazer* lazer = core::LazerItemBuilder::gen();
    EXPECT_TRUE(container->insert(lazer));

    /* add to starsystem */
    starsystem->add(ship);
    starsystem->add(container, glm::vec3(0.0f));

    EXPECT_EQ(1, starsystem->containers().size());
    EXPECT_EQ(place::Type::SPACE, container->place());

    ship->grab(container);

    core::event::takeContainer(ship->id(), container->id());

    EXPECT_EQ(0, starsystem->containers().size());
    EXPECT_EQ(false, container->isAlive());
}


TEST(ship, move)
{
    /* create objects */
    core::control::StarSystem* starsystem = core::StarSystemBuilder::gen();
    core::control::Ship* ship = core::ShipBuilder::gen();
    core::control::Drive* drive = core::DriveItemBuilder::gen();
    core::control::Bak* bak = core::BakItemBuilder::gen();

    EXPECT_TRUE(ship->mount(drive));
    EXPECT_TRUE(ship->mount(bak));

    /* add to starsystem */
    starsystem->add(ship);
    EXPECT_EQ(ship->position(), meti::vec3());

    EXPECT_TRUE(ship->properties().speed > 0);

    float val = 400;
    meti::vec3 target_pos = meti::vec3(val,0,0);
    ship->navigate(target_pos);

    int ticks = 2*int(val);
    while(ticks) {
        ship->update();
        ticks--;
    }
    expect_eq(ship->position(), target_pos);
}


TEST(ship, shoot_ship)
{
    /* create objects */
    core::control::StarSystem* starsystem = core::StarSystemBuilder::gen();
    core::control::Ship* ship = core::ShipBuilder::gen();
    core::control::Lazer* lazer1 = core::LazerItemBuilder::gen();
    core::control::Lazer* lazer2 = core::LazerItemBuilder::gen();
    EXPECT_TRUE(ship->mount(lazer1));
    EXPECT_TRUE(ship->mount(lazer2));

    core::control::Ship* target = core::ShipBuilder::gen();
    core::control::Drive* drive = core::DriveItemBuilder::gen();
    EXPECT_TRUE(target->mount(drive));

    /* add to starsystem */
    starsystem->add(ship);
    starsystem->add(target);

    /* initiate shoot */
    ship->weapons().prepare();
    assert(false);
//    ship->weapons().select();

//    slot::Item* slot = target->__itemSlot(drive->model()->slot());

//    EXPECT_TRUE(ship->weapons().setTarget(target, slot));

//    EXPECT_EQ(target, lazer1->target());
//    EXPECT_EQ(target, lazer2->target());

//    int dist = (ship->position() - target->position()).length();
//    int actual_damage = ship->weapons().guessDamage(dist) * target->adjustDissipateFilter();
//    int armor_init = target->model()->armor();

//    EXPECT_EQ(false, drive->isLocked());

//    event::shoot(ship->id(), lazer1->id());
//    event::shoot(ship->id(), lazer2->id());

//    EXPECT_EQ(true, drive->isLocked());

//    //EXPECT_TRUE(target->npc()->isAgressor(ship->id()));

//    EXPECT_TRUE(actual_damage != 0);
//    EXPECT_TRUE((armor_init - actual_damage) - target->model()->armor() <= 1);

//    lazer1->reset();
//    EXPECT_EQ(nullptr, lazer1->target());
}

TEST(ship, shoot_ship_presize)
{
    /* create objects */
//    control::Ship* ship1 = builder::Ship::gen();
//    control::Ship* ship2 = builder::Ship::gen();

//    /* initiate shoot */
//    ship1->weapons().prepare();
//    ship1->weapons().select();
//    ship1->weapons().setTarget(ship2);

//    int dist = (ship1->position() - ship2->position()).length();
//    int actual_damage = ship1->weapons().guessDamage(dist) * ship2->adjustDissipateFilter();
//    int armor_init = ship2->model()->armor();

//    ship1->weapons().fire(/*timer=*/0, /*rate=*/1.0);

//    EXPECT_TRUE((armor_init - actual_damage) - ship2->model()->armor() <= 1);
}

TEST(ship, kill)
{
    /* create objects */
    core::control::Ship* ship = core::ShipBuilder::gen();

    ship->hit(100000);
    EXPECT_EQ(0, ship->model()->armor());
}

namespace {

void compareSpaceObjectModels(model::SpaceObjectModel* m1, model::SpaceObjectModel* m2)
{
    EXPECT_EQ(m1->armor(), m2->armor());
    EXPECT_EQ(m1->parent(), m2->parent());
    EXPECT_EQ(m1->starsystem(), m2->starsystem());
    EXPECT_EQ(m1->place(), m2->place());
    //EXPECT_EQ(m1->mass(), m2->mass());
    EXPECT_EQ(m1->givenExpirience(), m2->givenExpirience());

//    EXPECT_EQ(m1->properties(), m2->properties());
//    EXPECT_EQ(m1->needs(), m2->needs());
}

void compareVehileModels(model::VehicleModel* m1, model::VehicleModel* m2)
{
    EXPECT_EQ(m1->npc(), m2->npc());
    EXPECT_EQ(m1->dock(), m2->dock());
    EXPECT_EQ(m1->land(), m2->land());
    EXPECT_EQ(m1->items(), m2->items());

//    EXPECT_EQ(m1->properties(), m2->properties());
//    EXPECT_EQ(m1->needs(), m2->needs());

    compareSpaceObjectModels(m1, m2);
}

void compareShipModels(model::ShipModel* m1, model::ShipModel* m2)
{
    EXPECT_EQ(m1->data(), m2->data());

    compareVehileModels(m1, m2);
}

void compareVehicleProperties(const core::control::Vehicle::Propetries& origin, const core::control::Vehicle::Propetries& clone)
{
    EXPECT_EQ(origin.free_space, clone.free_space);
    EXPECT_EQ(origin.protection, clone.protection);
    EXPECT_EQ(origin.radar, clone.radar);
    EXPECT_EQ(origin.speed, clone.speed);
    EXPECT_EQ(origin.energy, clone.energy);
    EXPECT_EQ(origin.hyper, clone.hyper);
    EXPECT_EQ(origin.repair, clone.repair);
    EXPECT_EQ(origin.freeze, clone.freeze);
    EXPECT_EQ(origin.scan, clone.scan);
    EXPECT_EQ(origin.grab_strength, clone.grab_strength);
    EXPECT_EQ(origin.grab_radius, clone.grab_radius);
    EXPECT_EQ(origin.temperature, clone.temperature);
    EXPECT_EQ(origin.artefact_gravity, clone.artefact_gravity);
    EXPECT_EQ(origin.artefact_protection, clone.artefact_protection);
    EXPECT_EQ(origin.total_damage, clone.total_damage);
    EXPECT_EQ(origin.fire_radius_min, clone.fire_radius_min);
    EXPECT_EQ(origin.fire_radius_max, clone.fire_radius_max);
    EXPECT_EQ(origin.equipment_radar, clone.equipment_radar);
    EXPECT_EQ(origin.shield_effect_enabled, clone.shield_effect_enabled);
    EXPECT_EQ(origin.hibernate_mode_enabled, clone.hibernate_mode_enabled);
}

} // namespace


void testShipCloneScenario(core::control::Ship* ship)
{
    core::control::Vehicle::Propetries properties = ship->properties(); // we need copy, not reference

    model::ShipModel* model = new model::ShipModel(ship->model()->data());
    core::control::Ship* clone = new core::control::Ship(ship->descriptor(), model);

    compareShipModels(ship->model(), model);
    compareVehicleProperties(properties, clone->properties());
}

TEST(ship, equip_and_clone)
{
    core::control::Ship* ship = core::ShipBuilder::gen();
    ship->manage( core::BakItemBuilder::gen() );
    ship->manage( core::DriveItemBuilder::gen() );
    ship->manage( core::ScanerItemBuilder::gen() );
    ship->manage( core::DroidItemBuilder::gen() );
    ship->manage( core::RadarItemBuilder::gen() );
    ship->manage( core::ProtectorItemBuilder::gen() );
    ship->load( core::ProtectorItemBuilder::gen() );
    ship->load( core::LazerItemBuilder::gen() );
    ship->load( core::RocketItemBuilder::gen() );

    testShipCloneScenario(ship);
}

TEST(ship, dock)
{
    // create
    core::control::StarSystem* starsystem = core::StarSystemBuilder::gen();
    core::control::Star* star = core::StarBuilder::gen();
    core::control::Planet* planet = core::PlanetBuilder::gen();
    core::control::Ship* ship = core::ShipBuilder::gen();

    core::control::Bak* bak = core::BakItemBuilder::gen();
    core::control::Drive* drive = core::DriveItemBuilder::gen();
    EXPECT_TRUE(ship->mount(bak));
    EXPECT_TRUE(ship->mount(drive));

    starsystem->add(star);
    starsystem->add(planet);
    starsystem->add(ship, planet->position());

    // starsystem
    EXPECT_EQ(1, starsystem->ships().size());

    // ship
    EXPECT_EQ(planet->position(), ship->position());
    EXPECT_EQ(place::Type::SPACE, ship->place());
    EXPECT_EQ(nullptr, ship->land());

    int iterations = 10;
    for (int i=0; i<iterations; ++i) {
        /** docking */

        // drive complex
        EXPECT_EQ(nullptr, ship->navigator().target());
        EXPECT_EQ(core::complex::Drive::Action::NONE, ship->navigator().action());

        ship->dock(planet);

        // drive complex
        EXPECT_EQ(planet, ship->navigator().target());
        EXPECT_EQ(core::complex::Drive::Action::DOCKING, ship->navigator().action());

        core::event::dockShip(ship->id(), planet->land()->id());

        // starsystem
        EXPECT_EQ(0, starsystem->ships().size());

        // land
        EXPECT_EQ(1, planet->land()->shipsNum());

        // ship
        EXPECT_EQ(planet->position(), ship->position());
        EXPECT_EQ(place::Type::KOSMOPORT, ship->place());
        EXPECT_EQ(planet->land(), ship->land());

        /** launching */
        core::event::launchShip(ship->id(), planet->land()->id());

        // starsystem
        EXPECT_EQ(1, starsystem->ships().size());

        // land
        EXPECT_EQ(0, planet->land()->shipsNum());

        // ship
        EXPECT_EQ(planet->position(), ship->position());
        EXPECT_EQ(place::Type::SPACE, ship->place());
        EXPECT_EQ(nullptr, ship->land());
    }
}

TEST(ship, jump)
{
    // create
    core::control::HyperSpace* hyper = core::HyperSpaceBuilder::gen();
    core::control::StarSystem* starsystem_jumpFrom = core::StarSystemBuilder::gen();
    core::control::StarSystem* starsystem_jumpTo = core::StarSystemBuilder::gen();
    core::control::Ship* ship = core::ShipBuilder::gen();

    core::control::Bak* bak = core::BakItemBuilder::gen();
    core::control::Drive* drive = core::DriveItemBuilder::gen();
    EXPECT_TRUE(ship->mount(bak));
    EXPECT_TRUE(ship->mount(drive));

    starsystem_jumpFrom->add(ship);

    int iterations = 10;
    for (int i=0; i<iterations; ++i) {
        // ping pong logic
        if (starsystem_jumpTo == ship->starsystem()) {
            std::swap(starsystem_jumpTo, starsystem_jumpFrom);
        }

        /** jump in */
        // starsystem
        EXPECT_EQ(1, starsystem_jumpFrom->ships().size());
        EXPECT_EQ(0, starsystem_jumpTo->ships().size());

        // hyper
        EXPECT_EQ(0, hyper->vehicles().size());

        // ship
        EXPECT_EQ(place::Type::SPACE, ship->place());

        core::event::jumpIn(ship->id());

        // starsystem
        EXPECT_EQ(0, starsystem_jumpFrom->ships().size());
        EXPECT_EQ(0, starsystem_jumpTo->ships().size());

        // hyper
        EXPECT_EQ(1, hyper->vehicles().size());

        // ship
        EXPECT_EQ(place::Type::HYPERSPACE, ship->place());
        EXPECT_EQ(nullptr, ship->starsystem());

        /** jump out */
        core::event::jumpOut(ship->id(), starsystem_jumpTo->id());

        // starsystem
        EXPECT_EQ(0, starsystem_jumpFrom->ships().size());
        EXPECT_EQ(1, starsystem_jumpTo->ships().size());

        // hyper
        EXPECT_EQ(0, hyper->vehicles().size());

        // ship
        EXPECT_EQ(place::Type::SPACE, ship->place());
        EXPECT_EQ(starsystem_jumpTo, ship->starsystem());
    }
}

} // namespace test
