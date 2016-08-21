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

#include <descriptors/Base.hpp>
#include <descriptors/Hit.hpp>
#include <descriptors/GalaxyDescriptor.hpp>
#include <descriptors/SectorDescriptor.hpp>
#include <descriptors/ExplosionDescriptor.hpp>
#include <descriptors/AddToStarsystemDescriptor.hpp>
#include <descriptors/Container.hpp>

#include <descriptors/VehicleDescriptorGenerator.hpp>
#include <descriptors/DescriptorGenerator.hpp>


TEST(base,serialization)
{
    descriptor::Hit hit1(1, 2, 33);
    descriptor::Hit hit2(hit1.data());
    EXPECT_TRUE(hit2.type() == hit1.type());
    EXPECT_TRUE(hit2.type() == int(descriptor::Type::HIT));
    EXPECT_TRUE(hit2.owner() == hit1.owner());
    EXPECT_TRUE(hit2.target() == hit1.target());
    EXPECT_TRUE(hit2.damage() == hit1.damage());

//    descriptor::Explosion explosion1(0, glm::vec3(100,200,300),0,0);
//    descriptor::Explosion explosion2(explosion1.data());
//    EXPECT_TRUE(explosion1.center.x == explosion2.center.x);
//    EXPECT_TRUE(explosion1.center.y == explosion2.center.y);
//    EXPECT_TRUE(explosion1.center.z == explosion2.center.z);
}

TEST(descriptor,serialization)
{
    descriptor::Hit descriptor(11, 22, 33);
    descriptor::Hit descriptor2(descriptor.data());
    EXPECT_TRUE(descriptor == descriptor2);
}


TEST(descriptor, _new)
{
    using namespace descriptor;
    Property p1("prop1", 1, 10);
    Property p2("prop2", 2, 20);
    Property p3("prop3", 3, 30);

    BaseD descr(1);
    descr.add({p1,p2,p3});

    BaseD descr2(descr);
    EXPECT_TRUE(descr == descr2);

    //std::cout << descr.info();
}
