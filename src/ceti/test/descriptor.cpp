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

#include <ceti/descriptor/Id.hpp>
#include <ceti/descriptor/Property.hpp>
#include <ceti/descriptor/Descriptor.hpp>
#include <ceti/descriptor/Mesh.hpp>


enum {ARMOR, RADIUS, DAMAGE, SPACE, IDLIST};

using namespace ceti::descriptor;

namespace {

std::map<int, Id> getTestData()
{
    std::map<int, Id> ids = {
          { ARMOR, Id( ARMOR, "armor" ) }
        , { RADIUS, Id( RADIUS, "radius" ) }
        , { DAMAGE, Id( DAMAGE, "damage" ) }
        , { SPACE, Id( SPACE, "space" ) }
        , { IDLIST, Id( IDLIST, "id_list" ) }
    };

    return ids;
}
} // namespace

TEST(descriptor, base)
{
    auto ids = getTestData();

    Property p1(ids.at(ARMOR), 10);
    Property p2(ids.at(RADIUS), 20);
    Property p3(ids.at(DAMAGE), 30);
    Property p4(ids.at(IDLIST), "5;4;3;2;1");

    Descriptor descr;
    descr.m_ids = ids;
    descr.add({p1,p2,p3,p4});

    Descriptor descr2(descr);
    EXPECT_TRUE(descr == descr2);

    EXPECT_EQ(descr.get_i(ARMOR), descr2.get_i(ARMOR));
    EXPECT_EQ(descr.get_i(RADIUS), descr2.get_i(RADIUS));
    EXPECT_EQ(descr.get_i(DAMAGE), descr2.get_i(DAMAGE));
    EXPECT_EQ(descr.get_s(IDLIST), descr2.get_s(IDLIST));

    descr2.add( Property(ids.at(SPACE), 40) );
    EXPECT_FALSE(descr == descr2);

    std::cout<<descr2.info();
}

TEST(descriptor, mesh)
{
    Mesh descr(/*type=*/1, "/path/to/model/file.obj", "/path/to/texture/file.jpg", glm::vec3(1.0f, 1.0f, 1.0f));
    Mesh descr2(descr);
    EXPECT_TRUE(descr == descr2);

    EXPECT_EQ(descr.id(), descr2.id());
    EXPECT_EQ(descr.type(), descr2.type());
    EXPECT_EQ(descr.model(), descr2.model());
    EXPECT_EQ(descr.texture(), descr2.texture());
    EXPECT_EQ(descr.orientation(), descr2.orientation());
}
