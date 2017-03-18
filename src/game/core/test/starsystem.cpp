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

#include <core/world/starsystem.hpp>

#include <core/builder/world/StarSystemBuilder.hpp>
#include <core/builder/spaceobject/ALL>

#include <core/spaceobject/ALL>

#include <core/manager/EntityManager.hpp>

#include <gtest/gtest.h>


TEST(starsystem, add_objects)
{
    /* create opbjects */
    test::StarSystem starsystem;
    test::Star star;
    test::Planet planet;
    test::Ship ship;

    /* pre-add check */
    EXPECT_EQ(starsystem.control()->stars().size(), 0);
    EXPECT_EQ(starsystem.control()->planets().size(), 0);
    EXPECT_EQ(starsystem.control()->vehicles().size(), 0);

    /* add objects */
    starsystem.control()->add(star.control());
    starsystem.control()->add(planet.control());

    glm::vec3 pos(0.0f);
    glm::vec3 dir(0.0f, 1.0f, 0.0f);
    starsystem.control()->add(ship.control(), pos, dir);

    /* post-add check */
    EXPECT_EQ(starsystem.control()->stars().size(), 1);
    EXPECT_EQ(starsystem.control()->planets().size(), 1);
    EXPECT_EQ(starsystem.control()->vehicles().size(), 1);

    assert(starsystem.control()->vehicles()[0]);
    assert(false);
//    Vehicle* vehicle = starsystem->vehicles()[0];
//    assert(false);
//    //EXPECT_EQ(vehicle, ship);
//    EXPECT_EQ(vehicle->position(), pos);
//    EXPECT_EQ(vehicle->direction(), dir);
}
