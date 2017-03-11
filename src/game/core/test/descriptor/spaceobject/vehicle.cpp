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


#include <core/descriptor/DescriptorGenerator.hpp>
#include <core/descriptor/spaceobject/ALL>

#include <gtest/gtest.h>

namespace {

void compareSpaceObject(const descriptor::SpaceObject& descr, const descriptor::SpaceObject& copy)
{
    // todo: implement
}

void compareVehicle(const descriptor::Vehicle& descr, const descriptor::Vehicle& copy)
{
    EXPECT_EQ(descr.race(), copy.race());
    EXPECT_EQ(descr.turrelPoints(), copy.turrelPoints());
    EXPECT_EQ(descr.drivePoints(), copy.drivePoints());
    EXPECT_EQ(descr.protectorPoints(), copy.protectorPoints());
    EXPECT_EQ(descr.space(), copy.space());
    EXPECT_EQ(descr.protection(), copy.protection());
#ifdef USE_EXTRA_EQUIPMENT
    EXPECT_EQ(descr.temperature(), copy.temperature());
#endif // USE_EXTRA_EQUIPMENT
    EXPECT_EQ(descr.price(), copy.price());
    EXPECT_EQ(descr.drawTurrels(), copy.drawTurrels());
    EXPECT_EQ(descr.bakSlotNum(), copy.bakSlotNum());

    EXPECT_EQ(descr.driveSlotNum(), copy.driveSlotNum());
    EXPECT_EQ(descr.droidSlotNum(), copy.droidSlotNum());
#ifdef USE_EXTRA_EQUIPMENT
    EXPECT_EQ(descr.energizerSlotNum(), copy.energizerSlotNum());
    EXPECT_EQ(descr.freezerSlotNum(), copy.freezerSlotNum());
#endif // USE_EXTRA_EQUIPMENT
    EXPECT_EQ(descr.grappleSlotNum(), copy.grappleSlotNum());
    EXPECT_EQ(descr.protectorSlotNum(), copy.protectorSlotNum());
    EXPECT_EQ(descr.radarSlotNum(), copy.radarSlotNum());
    EXPECT_EQ(descr.scanerSlotNum(), copy.scanerSlotNum());
    EXPECT_EQ(descr.weaponSlotNum(), copy.weaponSlotNum());
    EXPECT_EQ(descr.artefactSlotNum(), copy.artefactSlotNum());
    EXPECT_EQ(descr.cargoSlotNum(), copy.cargoSlotNum());

    compareSpaceObject(descr, copy);
}

} // namespace

TEST(descriptor, ship) {
    descriptor::Ship descr = *descriptor::genShip();
    descriptor::Ship copy(descr.data());

    EXPECT_EQ(descr.type(), descriptor::Type::SHIP);
    EXPECT_EQ(descr.obType(), entity::Type::VEHICLE);
    EXPECT_EQ(descr.obSubType(), entity::Type::SHIP);
    compareVehicle(descr, copy);
}

TEST(descriptor, satellite) {
    descriptor::Satellite descr = *descriptor::genSatellite();
    descriptor::Satellite copy(descr.data());

    EXPECT_EQ(descr.type(), descriptor::Type::SATELLITE);
    EXPECT_EQ(descr.obType(), entity::Type::VEHICLE);
    EXPECT_EQ(descr.obSubType(), entity::Type::SATELLITE);
    compareVehicle(descr, copy);
}

TEST(descriptor, spacestation) {
    descriptor::SpaceStation descr = *descriptor::genSpaceStation();
    descriptor::SpaceStation copy(descr.data());

    EXPECT_EQ(descr.type(), descriptor::Type::SPACESTATION);
    EXPECT_EQ(descr.obType(), entity::Type::VEHICLE);
    EXPECT_EQ(descr.obSubType(), entity::Type::SPACESTATION);
    compareVehicle(descr, copy);
}
