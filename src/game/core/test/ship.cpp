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
#include <core/generator/DescriptorGenerator.hpp>

#include <core/builder/world/StarSystemBuilder.hpp>
#include <core/builder/spaceobject/ALL>
#include <core/builder/item/equipment/ALL>

#include <core/world/starsystem.hpp>
#include <core/item/equipment/ALL>
#include <core/spaceobject/ALL>
#include <core/slot/ItemSlot.hpp>

#include <core/model/spaceobject/Ship.hpp>
#include <core/descriptor/spaceobject/Ship.hpp>

#include <core/manager/EntityManager.hpp>

#include <gtest/gtest.h>

TEST(ship, create)
{
    test::Ship ship;

    EXPECT_EQ(ship.descriptor()->bakSlotNum(), ship.control()->bakSlots().size());
    EXPECT_EQ(ship.descriptor()->driveSlotNum(), ship.control()->driveSlots().size());
    EXPECT_EQ(ship.descriptor()->radarSlotNum(), ship.control()->radarSlots().size());
    EXPECT_EQ(ship.descriptor()->scanerSlotNum(), ship.control()->scanerSlots().size());
    EXPECT_EQ(ship.descriptor()->grappleSlotNum(), ship.control()->grappleSlots().size());
    EXPECT_EQ(ship.descriptor()->droidSlotNum(), ship.control()->droidSlots().size());
    EXPECT_EQ(ship.descriptor()->protectorSlotNum(), ship.control()->protectorSlots().size());
    EXPECT_EQ(ship.descriptor()->weaponSlotNum(), ship.control()->weaponSlots().size());
    EXPECT_EQ(ship.descriptor()->cargoSlotNum(), ship.control()->cargoSlots().size());
}

TEST(ship, equip)
{
    test::Ship ship;

    test::item::Bak bak;
    test::item::Drive drive;
    test::item::Droid droid;
    test::item::Grapple grapple;
    test::item::Lazer lazer;
    test::item::Protector protector;
    test::item::Radar radar;
    test::item::Rocket rocket;
    test::item::Scaner scaner;

    ship.control()->manage(bak.control());
    ship.control()->manage(drive.control());
    ship.control()->manage(droid.control());
    ship.control()->manage(grapple.control());
    ship.control()->manage(lazer.control());
    ship.control()->manage(protector.control());
    ship.control()->manage(rocket.control());
    ship.control()->manage(scaner.control());
}

TEST(ship, drop_item_to_space)
{
    /* create objects */
    test::StarSystem starsystem;
    test::Ship ship;

    /* equip ship */
    model::item::Drive* drive = builder::item::Drive::gen();
    assert(false);
//    ship->manage(drive);

    /* add ship */
    glm::vec3 pos(100.0f);
    glm::vec3 dir(0.0f, 1.0f, 0.0f);
    EXPECT_EQ(ship.model()->place(), place::type::NONE);
    starsystem.control()->add(ship.control(), pos, dir);
    EXPECT_EQ(ship.model()->place(), place::type::KOSMOS);

    /* drop item to space */
    EXPECT_EQ(starsystem.control()->containers().size(), 0);
    EXPECT_TRUE(ship.control()->dropItemToSpace(entity::Type::DRIVE_SLOT));
    EXPECT_EQ(starsystem.control()->containers().size(), 1);
    assert(starsystem.control()->containers()[0]);
    assert(false);
//    Container* container = starsystem->containers()[0];
//    EXPECT_EQ(container->position(), pos);
//    EXPECT_EQ(container->place(), type::place::KOSMOS);
//    EXPECT_EQ(container->itemSlot()->item(), drive);
}

TEST(ship, base_ship_shoot)
{
    /* create objects */
    test::StarSystem starsystem;
    test::Ship ship1;
    test::Ship ship2;

    float distance = 10.0f;

    /* add objects */
    starsystem.control()->add(ship1.control(), /*pos=*/glm::vec3(0.0f), /*dir=*/glm::vec3(0.0f, 1.0f, 0.0f));
    starsystem.control()->add(ship2.control(), /*pos=*/glm::vec3(distance), /*dir=*/glm::vec3(0.0f, 1.0f, 0.0f));

    /* initiate shoot */
    ship1.control()->prepareWeapons();
    ship1.control()->weaponComplex().activateWeapons();
    ship1.control()->setWeaponTarget(ship2.model());
    int damage = ship1.control()->guessDamage(distance) * ship2.control()->adjustDissipateFilter();
    int armor_init = ship2.model()->armor();
    ship1.control()->fire(/*timer=*/0, /*rate=*/1.0);
    EXPECT_TRUE((armor_init - damage) - ship2.model()->armor() <= 1);
}

TEST(ship, criticalDamage)
{
    /* create objects */
    test::Ship ship;

    ship.control()->hit(ship.control()->criticalDamage());
    EXPECT_EQ(0, ship.model()->armor());
}

namespace {

void compareSpaceObjectModels(model::SpaceObject* m1, model::SpaceObject* m2)
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

void compareVehileModels(model::Vehicle* m1, model::Vehicle* m2)
{
    EXPECT_EQ(m1->npc(), m2->npc());
    EXPECT_EQ(m1->dock(), m2->dock());
    EXPECT_EQ(m1->land(), m2->land());
    EXPECT_EQ(m1->items(), m2->items());

//    EXPECT_EQ(m1->properties(), m2->properties());
//    EXPECT_EQ(m1->needs(), m2->needs());

    compareSpaceObjectModels(m1, m2);
}

void compareShipModels(model::Ship* m1, model::Ship* m2)
{
    EXPECT_EQ(m1->data(), m2->data());

    compareVehileModels(m1, m2);
}

void compareVehicleControls(control::Vehicle* c1, control::Vehicle* c2)
{
    EXPECT_EQ(c1->properties().free_space, c2->properties().free_space);
    EXPECT_EQ(c1->properties().protection, c2->properties().protection);
    EXPECT_EQ(c1->properties().radar, c2->properties().radar);
    EXPECT_EQ(c1->properties().speed, c2->properties().speed);
    EXPECT_EQ(c1->properties().energy, c2->properties().energy);
    EXPECT_EQ(c1->properties().hyper, c2->properties().hyper);
    EXPECT_EQ(c1->properties().repair, c2->properties().repair);
    EXPECT_EQ(c1->properties().freeze, c2->properties().freeze);
    EXPECT_EQ(c1->properties().scan, c2->properties().scan);
    EXPECT_EQ(c1->properties().grab_strength, c2->properties().grab_strength);
    EXPECT_EQ(c1->properties().grab_radius, c2->properties().grab_radius);
    EXPECT_EQ(c1->properties().temperature, c2->properties().temperature);
    EXPECT_EQ(c1->properties().artefact_gravity, c2->properties().artefact_gravity);
    EXPECT_EQ(c1->properties().artefact_protection, c2->properties().artefact_protection);
    EXPECT_EQ(c1->properties().total_damage, c2->properties().total_damage);
    EXPECT_EQ(c1->properties().fire_radius_min, c2->properties().fire_radius_min);
    EXPECT_EQ(c1->properties().fire_radius_max, c2->properties().fire_radius_max);
    EXPECT_EQ(c1->properties().equipment_radar, c2->properties().equipment_radar);
    EXPECT_EQ(c1->properties().shield_effect_enabled, c2->properties().shield_effect_enabled);
    EXPECT_EQ(c1->properties().hibernate_mode_enabled, c2->properties().hibernate_mode_enabled);
}

void compareShipControls(control::Ship* c1, control::Ship* c2)
{
    compareVehicleControls(c1, c2);
}

} // namespace


void testShipClone(const test::Ship& ship)
{
    model::Ship* model = new model::Ship(ship.model()->data());
    control::Ship* control = new control::Ship(model);

    compareShipModels(ship.model(), model);
    compareShipControls(ship.control(), control);
}

TEST(ship, clone)
{
    // items
    test::item::Bak bak;
    test::item::Drive drive;
    test::item::Scaner scaner;
    test::item::Droid droid;
    test::item::Radar radar;
    test::item::Protector protector;
    test::item::Protector protector2;
    test::item::Lazer lazer;
    //test::item::Rocket rocket;

    test::Ship ship;
    ship.control()->manage(bak.control());
    ship.control()->manage(drive.control());
    ship.control()->manage(scaner.control());
    ship.control()->manage(droid.control());
    ship.control()->manage(radar.control());
    ship.control()->manage(protector.control());
    ship.control()->load(protector2.control());
    ship.control()->load(lazer.control());
    //ship.control()->load(rocket.control());

    testShipClone(ship);
}



