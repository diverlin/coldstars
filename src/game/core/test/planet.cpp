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

#include <core/world/starsystem.hpp>
#include <core/spaceobject/Planet.hpp>

#include <core/builder/world/StarSystemBuilder.hpp>
#include <core/builder/spaceobject/PlanetBuilder.hpp>

#include <gtest/gtest.h>


TEST(planet, create)
{
    control::Planet* planet = builder::Planet::gen();
    assert(planet->land());
}

TEST(planet, add_to_starsystem)
{
    control::StarSystem* starsystem = builder::StarSystem::gen();
    control::Planet* planet = builder::Planet::gen();

    EXPECT_EQ(nullptr, planet->starsystem());
    EXPECT_EQ(place::Type::NONE, planet->place());
    EXPECT_EQ(0, planet->position().length());
    EXPECT_EQ(0, starsystem->planets().size());

    starsystem->add(planet);

    EXPECT_EQ(starsystem, planet->starsystem());
    EXPECT_EQ(place::Type::SPACE, planet->place());
    EXPECT_EQ(planet->radius(), planet->position().length());
    EXPECT_EQ(1, starsystem->planets().size());
}

