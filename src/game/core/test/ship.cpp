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

#include <core/managers/EntityManager.hpp>

#include <gtest/gtest.h>

namespace {
namespace test {

class Ship {
public:
    Ship() {
        descriptor::Ship* descr = descriptor::getNewShip();
        model::Ship* model = builder::Ship::getNew(descr);
        m_control = new control::Ship(model, descr);
    }
    ~Ship() {
        delete m_control->descriptor();
        delete m_control->model();
        delete m_control;
    }

    descriptor::Ship* descriptor() const { return m_control->descriptor(); }
    model::Ship* model() const { return m_control->model(); }
    control::Ship* control() const { return m_control; }

private:
    control::Ship* m_control = nullptr;
};

} // namespace test
} // namespace

TEST(ship, create)
{
    test::Ship ship;
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



