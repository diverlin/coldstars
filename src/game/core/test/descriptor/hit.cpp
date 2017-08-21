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

#include <core/descriptor/comm/Hit.hpp>

#include <gtest/gtest.h>

TEST(descriptor, clone_hit)
{
    descriptor::comm::Hit descr(11, 22, 33);
    descriptor::comm::Hit copy(descr.data());

    EXPECT_EQ(11, copy.owner());
    EXPECT_EQ(22, copy.target());
    EXPECT_EQ(33, copy.damage());

    EXPECT_EQ(descr.owner(), copy.owner());
    EXPECT_EQ(descr.target(), copy.target());
    EXPECT_EQ(descr.damage(), copy.damage());
}
