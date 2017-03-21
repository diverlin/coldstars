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

#include <core/model/world/starsystem.hpp>
#include <core/world/starsystem.hpp>

#include <core/builder/world/StarSystemBuilder.hpp>
#include <core/builder/spaceobject/ALL>

#include <core/spaceobject/ALL>

#include <core/manager/EntityManager.hpp>

#include <gtest/gtest.h>


TEST(starsystem, add_remove_objects)
{
    /* create opbjects */
    test::StarSystem starsystem;

    int init_stars = starsystem.model()->stars().size();
    int init_planets = starsystem.model()->planets().size();
    int init_spacestations = starsystem.model()->spacestations().size();
    int init_ships = starsystem.model()->ships().size();
    int init_satellites = starsystem.model()->satellites().size();

    /* pre-add check */
    EXPECT_EQ(starsystem.control()->stars().size(), init_stars);
    EXPECT_EQ(starsystem.control()->planets().size(), init_planets);
    EXPECT_EQ(starsystem.control()->spacestations().size(), init_spacestations);
    EXPECT_EQ(starsystem.control()->ships().size(), init_ships);
    EXPECT_EQ(starsystem.control()->satellites().size(), init_satellites);

    test::Star star;
    test::Planet planet;
//    test::SpaceStation spacestation;
    test::Ship ship;
//    test::Satellite satellite;

    /* add objects */
    starsystem.control()->add(star.model());
    starsystem.control()->add(planet.model());
//    starsystem.control()->add(spacestation.model());
    starsystem.control()->add(ship.model());
//    starsystem.control()->add(satellite.model());

    /* post-add check */
    EXPECT_EQ(starsystem.control()->stars().size(), init_stars + 1);
    EXPECT_EQ(starsystem.control()->planets().size(), init_planets + 1);
//    EXPECT_EQ(starsystem.control()->spacestations().size(), init_spacestations + 1);
    EXPECT_EQ(starsystem.control()->ships().size(), init_ships + 1);
//    EXPECT_EQ(starsystem.control()->satellites().size(), init_satellites + 1);

    assert(false);
    // TODO: implement removing
}
