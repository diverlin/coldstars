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


#include <test/descriptor/spaceobject/vehicle.hpp>
#include <test/descriptor/spaceobject/spaceobject.hpp>
#include <test/descriptor/base.hpp>

#include <core/generator/DescriptorGenerator.hpp>
#include <core/descriptor/spaceobject/Ship.hpp>

#include <gtest/gtest.h>

namespace test {

namespace {
void testShipEquality(descriptor::ShipDescr* descr, descriptor::ShipDescr* copy) {
    EXPECT_EQ(descr->type(), descriptor::Type::SHIP);
    EXPECT_EQ(descr->obType(), entity::Type::SHIP);
    EXPECT_EQ(descr->obGroup(), entity::Type::VEHICLE);
}
} // namespace

TEST(descriptor, clone_ship) {
    descriptor::ShipDescr* descr = descriptor::genShip();
    descriptor::ShipDescr* copy = new descriptor::ShipDescr(descr->data());

    testShipEquality(descr, copy);
    testVehicleEquality(descr, copy);
    testSpaceObjectEquality(descr, copy);
//    testBaseViewEquality(descr, copy);
    testBaseEquality(descr, copy);

    delete copy;
}

} // namespace test
