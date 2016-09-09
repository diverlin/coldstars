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

#include <ceti/StringUtils.hpp>

#include <glm/glm.hpp>


TEST(string_utils, base)
{
    glm::vec3 v(-100.994f, 100.123f, 99999.9988f);
    EXPECT_EQ(std::string("(-100.994,100.123,100000)"), ceti::to_string(v));

    float f = -1.9991f;
    EXPECT_EQ(std::string("-1.9991"), ceti::to_string(f));
}
