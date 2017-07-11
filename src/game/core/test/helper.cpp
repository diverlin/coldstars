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

#include "helper.hpp"

#include <core/manager/EntityManager.hpp>
#include <core/manager/DescriptorManager.hpp>

namespace test {

void expect_eq(const meti::vec3& actual, const meti::vec3& expected)
{
    EXPECT_EQ(actual.x, expected.x);
    EXPECT_EQ(actual.y, expected.y);
    EXPECT_EQ(actual.z, expected.z);
}

void expect_eq_dirty(const meti::vec3& actual, const meti::vec3& expected)
{
    float precision = 0.1f;
    EXPECT_TRUE(std::fabs(actual.x-expected.x) < precision);
    EXPECT_TRUE(std::fabs(actual.y-expected.y) < precision);
    EXPECT_TRUE(std::fabs(actual.z-expected.z) < precision);
}


} // namespace test
