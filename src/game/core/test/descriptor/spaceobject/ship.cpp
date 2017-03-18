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


#include "vehicle.hpp"
#include "spaceobject.hpp"

#include <core/descriptor/DescriptorGenerator.hpp>
#include <core/descriptor/spaceobject/Ship.hpp>

#include <gtest/gtest.h>

namespace test {

TEST(descriptor, ship) {
    descriptor::Ship* descr = descriptor::genShip();
    descriptor::Ship* copy = new descriptor::Ship(descr->data());

    EXPECT_EQ(descr->type(), descriptor::Type::SHIP);
    EXPECT_EQ(descr->obType(), entity::Type::VEHICLE);
    EXPECT_EQ(descr->obSubType(), entity::Type::SHIP);

    testVehicleEquality(descr, copy);
    testSpaceObjectEquality(descr, copy);
}

} // namespace test
