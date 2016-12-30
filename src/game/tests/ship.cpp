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

#include <gtest/gtest.h>

#include <common/Global.hpp>

#include <descriptors/Base.hpp>
#include <descriptors/DescriptorManager.hpp>

#include <builder/world/StarSystemBuilder.hpp>
#include <builder/spaceobjects/ALL>
#include <builder/item/equipment/ALL>

#include <world/starsystem.hpp>
#include <item/equipment/ALL>
#include <spaceobjects/ALL>
#include <slots/ItemSlot.hpp>

TEST(ship, drop_item_to_space)
{
    /* create objects */
    Starsystem* starsystem = StarsystemBuilder::create();
    Ship* ship = ShipBuilder::getNew();

    /* equip ship */
    item::equipment::Drive* drive =core::global::get().driveBuilder().getNew();
    ship->manage(drive);

    /* add ship */
    glm::vec3 pos(100.0f);
    glm::vec3 dir(0.0f, 1.0f, 0.0f);
    EXPECT_EQ(ship->place(), type::place::NONE);
    starsystem->add(ship, pos, dir);
    EXPECT_EQ(ship->place(), type::place::KOSMOS);

    /* drop item to space */
    EXPECT_EQ(starsystem->containers().size(), 0);
    EXPECT_TRUE(ship->dropItemToSpace(type::entity::DRIVE_SLOT_ID));
    EXPECT_EQ(starsystem->containers().size(), 1);
    assert(starsystem->containers()[0]);
    Container* container = starsystem->containers()[0];
    EXPECT_EQ(container->position(), pos);
    EXPECT_EQ(container->place(), type::place::KOSMOS);
    EXPECT_EQ(container->itemSlot()->item(), drive);
}

TEST(ship, base_ship_shoot)
{
    /* create objects */
    Starsystem* starsystem = StarsystemBuilder::create();
    Ship* ship1 = ShipBuilder::getNew(/*full_equiped=*/true);
    Ship* ship2 = ShipBuilder::getNew(/*full_equiped=*/true);

    float distance = 10.0f;

    /* add objects */
    starsystem->add(ship1, /*pos=*/glm::vec3(0.0f), /*dir=*/glm::vec3(0.0f, 1.0f, 0.0f));
    starsystem->add(ship2, /*pos=*/glm::vec3(distance), /*dir=*/glm::vec3(0.0f, 1.0f, 0.0f));

    /* initiate shoot */
    ship1->prepareWeapons();
    ship1->weaponComplex().activateWeapons();
    ship1->setWeaponTarget(ship2);
    int damage = ship1->guessDamage(distance) * ship2->adjustDissipateFilter();
    int armor_init = ship2->armor();
    ship1->fire(/*timer=*/0, /*rate=*/1.0);
    EXPECT_TRUE((armor_init - damage) - ship2->armor() <= 1);
}



TEST(ship, criticalDamage)
{
    /* create objects */
    Ship* ship1 = ShipBuilder::getNew(/*full_equiped=*/true);
    ship1->hit(ship1->criticalDamage());
    EXPECT_EQ(0, ship1->armor());
}



