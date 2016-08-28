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

#include <ceti/descriptor/Descriptor.hpp>
#include <ceti/descriptor/Mesh.hpp>


TEST(descriptor, base)
{
    using namespace descriptor;
    Property p1(IDs.at(ARMOR), 10);
    Property p2(IDs.at(RADIUS), 20);
    Property p3(IDs.at(DAMAGE), 30);
    Property p4(IDs.at(IDLIST), "5;4;3;2;1");

    Descriptor descr;
    descr.m_ids = descriptor::IDs;
    descr.add({p1,p2,p3,p4});

    Descriptor descr2(descr);
    EXPECT_TRUE(descr == descr2);

    EXPECT_EQ(descr.get(ARMOR), descr2.get(ARMOR));
    EXPECT_EQ(descr.get(RADIUS), descr2.get(RADIUS));
    EXPECT_EQ(descr.get(DAMAGE), descr2.get(DAMAGE));

    descr2.add( Property(IDs.at(FUEL_MAX), 40) );
    EXPECT_FALSE(descr == descr2);

    std::cout<<descr2.info();
}

TEST(descriptor, mesh)
{
    using namespace descriptor;
    Mesh descr(/*type=*/1, "/path/to/model/file.obj", "/path/to/texture/file.jpg", glm::vec3(1.0f, 1.0f, 1.0f));
    Mesh descr2(descr);
    EXPECT_TRUE(descr == descr2);

    EXPECT_EQ(descr.id(), descr2.id());
    EXPECT_EQ(descr.type(), descr2.type());
    EXPECT_EQ(descr.model(), descr2.model());
    EXPECT_EQ(descr.texture(), descr2.texture());
    EXPECT_EQ(descr.orientation(), descr2.orientation());
}
