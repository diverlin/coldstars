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

#include <core/common/Global.hpp>

#include <core/descriptors/Base.hpp>
#include <core/descriptors/DescriptorManager.hpp>
#include <core/descriptors/DescriptorGenerator.hpp>

#include <core/builder/world/StarSystemBuilder.hpp>
#include <core/builder/spaceobjects/ALL>
#include <core/builder/item/equipment/ALL>

#include <core/world/starsystem.hpp>
#include <core/item/equipment/ALL>
#include <core/spaceobjects/ALL>
#include <core/slots/ItemSlot.hpp>

#include <core/managers/EntityManager.hpp>

#include <gtest/gtest.h>

TEST(ship, create)
{
    descriptor::Ship descr = descriptor::getNewShip();
    model::Ship* model = builder::Ship::getNew(descr);
    control::Ship* control = new control::Ship(model);

//    control::Ship* ship = control::getNewShip();
}

TEST(ship, drop_item_to_space)
{
    /* create objects */
    control::Starsystem* starsystem = control::getNewStarsystem();
    control::Ship* ship = control::getNewShip();

    /* equip ship */
    model::item::Drive* drive = builder::item::Drive::getNew();
    assert(false);
//    ship->manage(drive);

    /* add ship */
    glm::vec3 pos(100.0f);
    glm::vec3 dir(0.0f, 1.0f, 0.0f);
    EXPECT_EQ(ship->model()->place(), type::place::NONE);
    starsystem->add(ship->model(), pos, dir);
    EXPECT_EQ(ship->model()->place(), type::place::KOSMOS);

    /* drop item to space */
    EXPECT_EQ(starsystem->containers().size(), 0);
    EXPECT_TRUE(ship->dropItemToSpace(type::entity::DRIVE_SLOT_ID));
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
    model::Ship* model_ship1 = builder::Ship::getNew(/*full_equiped=*/true);
    model::Ship* model_ship2 = builder::Ship::getNew(/*full_equiped=*/true);

    control::Ship* ship1 = new control::Ship(model_ship1);
    control::Ship* ship2 = new control::Ship(model_ship2);

    float distance = 10.0f;

    /* add objects */
    starsystem->add(model_ship1, /*pos=*/glm::vec3(0.0f), /*dir=*/glm::vec3(0.0f, 1.0f, 0.0f));
    starsystem->add(model_ship2, /*pos=*/glm::vec3(distance), /*dir=*/glm::vec3(0.0f, 1.0f, 0.0f));

    /* initiate shoot */
    ship1->prepareWeapons();
    ship1->weaponComplex().activateWeapons();
    ship1->setWeaponTarget(model_ship2);
    int damage = ship1->guessDamage(distance) * ship2->adjustDissipateFilter();
    int armor_init = model_ship2->armor();
    ship1->fire(/*timer=*/0, /*rate=*/1.0);
    EXPECT_TRUE((armor_init - damage) - model_ship2->armor() <= 1);

    // clean
    delete model_ship1;
    delete model_ship2;
    delete ship1;
    delete ship2;
}



TEST(ship, criticalDamage)
{
    /* create objects */
    model::Ship* model1 = builder::Ship::getNew(/*full_equiped=*/true);
    control::Ship* ship1 = new control::Ship(model1);

    assert(false);
    //ship1->hit(model1->criticalDamage());
    EXPECT_EQ(0, model1->armor());

    // clean
    delete model1;
    delete ship1;
}



