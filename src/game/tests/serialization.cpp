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

#include <descriptors/Descriptor.hpp>
#include <descriptors/HitDescriptor.hpp>
#include <descriptors/GalaxyDescriptor.hpp>
#include <descriptors/SectorDescriptor.hpp>
#include <descriptors/ExplosionDescriptor.hpp>
#include <descriptors/AddToStarsystemDescriptor.hpp>

#include <descriptors/VehicleDescriptorGenerator.hpp>
#include <descriptors/DescriptorGenerator.hpp>
#include <descriptors/ContainerDescriptorGenerator.hpp>

TEST(base,serialization)
{
    Descriptor hit1 = generateHitDescriptor(1, 2, 33);
    Descriptor hit2(hit1.data());
    EXPECT_TRUE(hit2.owner() == hit1.owner());
    EXPECT_TRUE(hit2.target() == hit1.target());
    EXPECT_TRUE(hit2.damage() == hit1.damage());

    VehicleDescriptor vehicle1;
    vehicle1.race_id = TYPE::RACE::R7_ID;
    VehicleDescriptor vehicle2(vehicle1.data());
    EXPECT_TRUE(vehicle2.race_id == vehicle1.race_id);

    ExplosionDescriptor explosion1(0, glm::vec3(100,200,300),0,0);
    ExplosionDescriptor explosion2(explosion1.data());
    EXPECT_TRUE(explosion1.center.x == explosion2.center.x);
    EXPECT_TRUE(explosion1.center.y == explosion2.center.y);
    EXPECT_TRUE(explosion1.center.z == explosion2.center.z);
}

TEST(descriptor,serialization)
{
    Descriptor descriptor({{Descriptor::KEY_ID, "11"}, {Descriptor::KEY_DAMAGE, "22"}, {Descriptor::KEY_RADIUS, "33"}});
    Descriptor descriptor2(descriptor.data());
    EXPECT_TRUE(descriptor == descriptor2);
}

