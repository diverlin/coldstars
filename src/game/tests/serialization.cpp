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


TEST(descriptor,serialization)
{
    descriptor::Hit descriptor(11, 22, 33);
    descriptor::Hit descriptor2(descriptor.data());
    EXPECT_TRUE(descriptor == descriptor2);
}


TEST(descriptor, base)
{
    using namespace descriptor;
    Property p1(Id(1, "prop1"), 10);
    Property p2(Id(2, "prop2"), 20);
    Property p3(Id(3, "prop3"), 30);

    BaseD descr;
    descr.add({p1,p2,p3});

    BaseD descr2(descr);
    EXPECT_TRUE(descr == descr2);

    descr2.add( Property(Id(4, "prop4"), 40) );
    EXPECT_FALSE(descr == descr2);
}
