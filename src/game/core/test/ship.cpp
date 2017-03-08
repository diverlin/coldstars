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

#include "helper2.hpp"

#include <core/common/Global.hpp>

#include <core/descriptor/Base.hpp>
#include <core/descriptor/DescriptorManager.hpp>
#include <core/descriptor/DescriptorGenerator.hpp>

#include <core/builder/world/StarSystemBuilder.hpp>
#include <core/builder/spaceobjects/ALL>
#include <core/builder/item/equipment/ALL>

#include <core/world/starsystem.hpp>
#include <core/item/equipment/ALL>
#include <core/spaceobjects/ALL>
#include <core/slots/ItemSlot.hpp>

#include <core/model/spaceobject/Ship.hpp>

#include <core/managers/EntityManager.hpp>

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
    control::Starsystem* starsystem = control::getNewStarsystem();
    test::Ship ship;

    /* equip ship */
    model::item::Drive* drive = builder::item::Drive::getNew();
    assert(false);
//    ship->manage(drive);

    /* add ship */
    glm::vec3 pos(100.0f);
    glm::vec3 dir(0.0f, 1.0f, 0.0f);
    EXPECT_EQ(ship.model()->place(), place::type::NONE);
    starsystem->add(ship.model(), pos, dir);
    EXPECT_EQ(ship.model()->place(), place::type::KOSMOS);

    /* drop item to space */
    EXPECT_EQ(starsystem->containers().size(), 0);
    EXPECT_TRUE(ship.control()->dropItemToSpace(entity::type::DRIVE_SLOT));
    EXPECT_EQ(starsystem->containers().size(), 1);
    assert(starsystem->containers()[0]);
    assert(false);
//    Container* container = starsystem->containers()[0];
//    EXPECT_EQ(container->position(), pos);
//    EXPECT_EQ(container->place(), type::place::KOSMOS);
//    EXPECT_EQ(container->itemSlot()->item(), drive);
}

TEST(ship, base_ship_shoot)
{
    /* create objects */
    control::Starsystem* starsystem = control::getNewStarsystem();
    test::Ship ship1;
    test::Ship ship2;

    float distance = 10.0f;

    /* add objects */
    starsystem->add(ship1.model(), /*pos=*/glm::vec3(0.0f), /*dir=*/glm::vec3(0.0f, 1.0f, 0.0f));
    starsystem->add(ship2.model(), /*pos=*/glm::vec3(distance), /*dir=*/glm::vec3(0.0f, 1.0f, 0.0f));

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

} // namespace

TEST(ship, clone)
{
    descriptor::Manager::get().generate();

    test::Ship ship;
    test::item::Scaner item;

    ship.control()->manage(item.control());

    model::Ship* model = new model::Ship(ship.model()->data());
    control::Ship* control = new control::Ship(model, ship.descriptor());

    compareShipModels(ship.model(), model);

    EXPECT_EQ(ship.control()->properties().scan, item.descriptor()->scan());
    EXPECT_EQ(ship.control()->properties().scan, control->properties().scan);
}


