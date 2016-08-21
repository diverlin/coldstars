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
    Property p1(IDs.at(ARMOR), 10);
    Property p2(IDs.at(RADIUS), 20);
    Property p3(IDs.at(DAMAGE), 30);

    BaseD descr;
    descr.add({p1,p2,p3});

    BaseD descr2(descr);
    EXPECT_TRUE(descr == descr2);

    EXPECT_EQ(descr.get(ARMOR), descr2.get(ARMOR));
    EXPECT_EQ(descr.get(RADIUS), descr2.get(RADIUS));
    EXPECT_EQ(descr.get(DAMAGE), descr2.get(DAMAGE));

    descr2.add( Property(IDs.at(FUEL_MAX), 40) );
    EXPECT_FALSE(descr == descr2);

    std::cout<<descr2.info();
}
