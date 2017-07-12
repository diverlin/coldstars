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

namespace {

bool validate_path(const std::vector<glm::vec3>& v, float dist) {
    if (!v.size()) {
        return false;
    }

    if (v.size() < 2) {
        return false;
    }

    glm::vec3 p0 = v.front();
    int first = true;
    for(const auto& p: v) {
        if (first) {
            first = false;
            continue;
        }
        float diff = glm::length(p0-p);
        if (diff > 1.001f * dist) {
            return false;
        }
        if (diff < 0.999f * dist) {
            return false;
        }
        p0=p;
    }

    return true;
}

} // namespace

TEST(path, calc_direct)
{
    std::vector<glm::vec3> centers;
    std::vector<glm::vec3> directions;

    // linear path calculation
    std::vector<glm::vec2> offsets = { glm::vec2(100, 0),
                                       glm::vec2(-100, 0),
                                       glm::vec2(0, 100),
                                       glm::vec2(0, -100)};
    for(const auto& offset: offsets) {
        glm::vec3 from(0,0,0);
        glm::vec3 to(offset.x, offset.y, 0);
        glm::vec3 dir(glm::normalize(to));
        float speed = 1.0f;

        bool result = complex::calcDirectPath(centers, directions, from, to, dir, speed);
        EXPECT_TRUE(result);

        EXPECT_TRUE(validate_path(centers, speed));

        expect_eq(centers.back(), to);

        int steps = int(std::fabs(glm::length(offset)/speed));
        EXPECT_EQ(centers.size(), steps);

        centers.clear();
        directions.clear();
    }
}

TEST(path, calc_round_ok)
{
    std::vector<glm::vec3> centers;
    std::vector<glm::vec3> directions;

    glm::vec3 from(0,0,0);
    glm::vec3 to(100, 100, 0);
    glm::vec3 dir(0, 1, 0);
    float speed = 1.0f;

    bool result = complex::calcRoundPath(centers, directions, from, to, dir, speed);
    EXPECT_TRUE(result);

    EXPECT_TRUE(validate_path(centers, speed));

    expect_eq_dirty(directions.back(), glm::normalize(glm::vec3(to-centers.back())));

    centers.clear();
    directions.clear();
}

TEST(path, calc_round_false)
{
    std::vector<glm::vec3> centers;
    std::vector<glm::vec3> directions;

    glm::vec3 from(0,0,0);
    glm::vec3 to(10, 0, 0);
    glm::vec3 dir(0, 1, 0);
    float speed = 1.0f;

    bool result = complex::calcRoundPath(centers, directions, from, to, dir, speed);
    EXPECT_FALSE(result);

    centers.clear();
    directions.clear();
}

TEST(path, complex)
{
    std::vector<glm::vec3> centers;
    std::vector<glm::vec3> directions;

    glm::vec3 from(0,0,0);
//    std::vector<glm::vec3> to = {glm::vec3(100, 100, 0),
//                                 glm::vec3(200, 100, 0),
//                                 glm::vec3(300, -200, 0),
//                                 glm::vec3(800, 800, 0)};

    glm::vec3 to(800.0f, 800.0f, 0.0f);

    glm::vec3 dir(0, 1, 0);
    float speed = 1.0f;

    bool result = complex::calcPath(centers, directions, from, to, dir, speed);
    EXPECT_FALSE(result);

    EXPECT_TRUE(validate_path(centers, speed));

    centers.clear();
    directions.clear();
}

} // namespace test
