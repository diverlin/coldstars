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


enum { INT1, INT2, INT3, INT4, STRING1, FLOAT, VEC3 };

using namespace ceti::descriptor;

namespace {

std::map<int, Id> getTestData()
{
    std::map<int, Id> ids = {
          { INT1, Id( INT1, "int1" ) }
        , { INT2, Id( INT2, "int2" ) }
        , { INT3, Id( INT3, "int3" ) }
        , { INT4, Id( INT4, "int4" ) }
        , { STRING1, Id( STRING1, "string1" ) }
        , { FLOAT, Id( FLOAT, "float" ) }
        , { VEC3, Id( VEC3, "vec3" ) }
    };

    return ids;
}
} // namespace

TEST(descriptor, base)
{
    auto ids = getTestData();

    Property p1(ids.at(INT1), 10);
    Property p2(ids.at(INT2), 20);
    Property p3(ids.at(INT3), 30);
    Property p4(ids.at(FLOAT), 2.7f);
    Property p5(ids.at(STRING1), "5;4;3;2;1");
    Property p6(ids.at(VEC3), meti::vec3(1.0f, 2.0f, 3.0f));

    Descriptor descr;
    descr.m_ids = ids;
    descr.add({p1,p2,p3,p4,p5,p6});

    Descriptor descr2(descr);
    EXPECT_TRUE(descr == descr2);

    EXPECT_EQ(descr.get_i(INT1), descr2.get_i(INT1));
    EXPECT_EQ(descr.get_i(INT2), descr2.get_i(INT2));
    EXPECT_EQ(descr.get_i(INT3), descr2.get_i(INT3));
    EXPECT_EQ(descr.get_f(FLOAT), descr2.get_f(FLOAT));
    EXPECT_EQ(descr.get_s(STRING1), descr2.get_s(STRING1));
    EXPECT_EQ(descr.get_v3(VEC3), descr2.get_v3(VEC3));

    descr2.add( Property(ids.at(INT4), 40) );
    EXPECT_FALSE(descr == descr2);

//    std::cout<<descr.info();
//    std::cout<<descr2.info();
}

TEST(descriptor, mesh)
{
    Mesh descr(/*type=*/1, "/path/to/model/file.obj", "/path/to/texture/file.jpg", meti::vec3(1.0f, 1.0f, 1.0f));
    Mesh descr2(descr);
    EXPECT_TRUE(descr == descr2);

    EXPECT_EQ(descr.id(), descr2.id());
    EXPECT_EQ(descr.type(), descr2.type());
    EXPECT_EQ(descr.model(), descr2.model());
    EXPECT_EQ(descr.texture(), descr2.texture());
    EXPECT_EQ(descr.orientation(), descr2.orientation());
}
