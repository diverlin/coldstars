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
//#include <common/constants.hpp>

//#include <slots/ItemSlot.hpp>
#include <world/starsystem.hpp>

#include <slots/ItemSlot.hpp>

#include <spaceobjects/Vehicle.hpp>
#include <spaceobjects/Ship.hpp>
#include <spaceobjects/Container.hpp>

#include <builder/world/StarSystemBuilder.hpp>
#include <builder/spaceobjects/StarBuilder.hpp>
#include <builder/spaceobjects/PlanetBuilder.hpp>
#include <builder/spaceobjects/ShipBuilder.hpp>

#include <descriptors/Base.hpp>
#include <descriptors/DescriptorManager.hpp>

#include <builder/item/equipment/ALL>
//#include <builder/item/modules/ALL>
//#include <builder/item/artefacts//ALL>
//#include <builder/item/other/ALL>

#include <item/equipment/ALL>

//#include "helper.hpp"

//#include <fstream>

TEST(creation, starsystem)
{
    const descriptor::Base& descr = global::get().descriptors().getRand(descriptor::Type::STARSYSTEM);
    Starsystem* starsystem = StarsystemBuilder::getNew( descr );

    EXPECT_EQ(starsystem->stars().size(), 0);
    EXPECT_EQ(starsystem->planets().size(), 0);
    EXPECT_EQ(starsystem->vehicles().size(), 0);

    Star* star = StarBuilder::getNew();
    Planet* planet = PlanetBuilder::getNew();
    Ship* ship = ShipBuilder::getNew();

    starsystem->add(star);
    starsystem->add(planet);

    glm::vec3 pos(0.0f);
    glm::vec3 dir(0.0f, 1.0f, 0.0f);
    starsystem->add(ship, pos, dir);

    EXPECT_EQ(starsystem->stars().size(), 1);
    EXPECT_EQ(starsystem->planets().size(), 1);
    EXPECT_EQ(starsystem->vehicles().size(), 1);

    assert(starsystem->vehicles()[0]);
    Vehicle* vehicle = starsystem->vehicles()[0];
    EXPECT_EQ(vehicle, ship);
    EXPECT_EQ(vehicle->position(), pos);
    EXPECT_EQ(vehicle->direction(), dir);
}

TEST(ship, drop_item)
{
    Starsystem* starsystem = StarsystemBuilder::getNew();
    Ship* ship = ShipBuilder::getNew();

    // equip ship
    item::equipment::Drive* drive = global::get().driveBuilder().getNew();
    ship->install(drive);

    // add ship
    glm::vec3 pos(100.0f);
    glm::vec3 dir(0.0f, 1.0f, 0.0f);
    EXPECT_EQ(ship->place(), type::place::NONE);
    starsystem->add(ship, pos, dir);
    EXPECT_EQ(ship->place(), type::place::KOSMOS);

    // drop item
    EXPECT_EQ(starsystem->containers().size(), 0);
    EXPECT_TRUE(ship->dropItemToSpace(type::entity::DRIVE_SLOT_ID));
    EXPECT_EQ(starsystem->containers().size(), 1);
    assert(starsystem->containers()[0]);
    Container* container = starsystem->containers()[0];
    EXPECT_EQ(container->position(), pos);
    EXPECT_EQ(container->place(), type::place::KOSMOS);
    EXPECT_EQ(container->itemSlot()->item(), drive);
}







