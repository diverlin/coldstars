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

#include <meti/VectorUtils.hpp>
#include <core/part/DriveComplex.hpp>

#include <gtest/gtest.h>

namespace test {

TEST(path, calc_direct)
{
    std::vector<glm::vec3> centers;
    std::vector<glm::vec3> directions;

    // linear path calculation
    std::vector<glm::vec2> offsets = { glm::vec2(100, 0),
                                       glm::vec2(-100, 0),
                                       glm::vec2(0, 100),
                                       glm::vec2(0, -100)};
    for(const auto offset: offsets) {
        assert(offset.x != offset.y != 0); // otherwise it will not be linear

        glm::vec3 from(0,0,0);
        glm::vec3 to(offset.x, offset.y, 0);
        glm::vec3 dir(glm::normalize(to));
        float speed = 1.0f;

        bool result = complex::calcDirectPath(centers, directions, from, to, dir, speed);
        EXPECT_TRUE(result);

        expect_eq(centers.back(), to);

        int steps = std::fabs(glm::length(offset)/speed);
        EXPECT_EQ(centers.size(), steps);

        centers.clear();
        directions.clear();
    }
}

TEST(path, calc_round)
{
    expect_eq(meti::OX, glm::cross(meti::OY, meti::OZ));

    std::vector<glm::vec3> centers;
    std::vector<glm::vec3> directions;

    glm::vec3 from(0,0,0);
    glm::vec3 to(100, 100, 0);
    glm::vec3 dir(0, 1, 0);
    float speed = 1.0f;

    bool result = complex::calcRoundPath(centers, directions, from, to, dir, speed);
    EXPECT_TRUE(result);

    expect_eq_dirty(directions.back(), glm::normalize(glm::vec3(to-centers.back())));

    centers.clear();
    directions.clear();
}

} // namespace test
