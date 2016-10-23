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

#include <world/starsystem.hpp>
#include <builder/world/StarSystemBuilder.hpp>

#include <builder/spaceobjects/ALL>

#include <spaceobjects/ALL>

TEST(starsystem, add_objects)
{
    /* create opbjects */
    Starsystem* starsystem = StarsystemBuilder::create();

    model::Star* star = builder::Star::getNew();
    model::Planet* planet = builder::Planet::getNew();
    Ship* ship = ShipBuilder::getNew();

    /* pre-add check */
    EXPECT_EQ(starsystem->stars().size(), 0);
    EXPECT_EQ(starsystem->planets().size(), 0);
    EXPECT_EQ(starsystem->vehicles().size(), 0);

    /* add objects */
    starsystem->add(star);
    starsystem->add(planet);

    glm::vec3 pos(0.0f);
    glm::vec3 dir(0.0f, 1.0f, 0.0f);
    starsystem->add(ship, pos, dir);

    /* post-add check */
    EXPECT_EQ(starsystem->stars().size(), 1);
    EXPECT_EQ(starsystem->planets().size(), 1);
    EXPECT_EQ(starsystem->vehicles().size(), 1);

    assert(starsystem->vehicles()[0]);
    Vehicle* vehicle = starsystem->vehicles()[0];
    EXPECT_EQ(vehicle, ship);
    EXPECT_EQ(vehicle->position(), pos);
    EXPECT_EQ(vehicle->direction(), dir);
}
