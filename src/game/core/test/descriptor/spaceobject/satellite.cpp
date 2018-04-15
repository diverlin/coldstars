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
#include <core/descriptor/spaceobject/Satellite.hpp>

#include <gtest/gtest.h>

namespace test {

namespace {
void testSatelliteEquality(core::SatelliteDescr* descr, core::SatelliteDescr* copy) {
    EXPECT_EQ(descr->type(), core::Type::SATELLITE);
    EXPECT_EQ(descr->obType(), entity::Type::SATELLITE);
    EXPECT_EQ(descr->obGroup(), entity::Type::VEHICLE);
}
} // namespace

TEST(core, clone_satellite) {
    core::SatelliteDescr* descr = core::genSatellite();
    core::SatelliteDescr* copy = new core::SatelliteDescr(descr->data());

    testSatelliteEquality(descr, copy);
    testVehicleEquality(descr, copy);
    testSpaceObjectEquality(descr, copy);
//    testBaseViewEquality(descr, copy);
    testBaseEquality(descr, copy);

    delete copy;
}

} // namespace test
