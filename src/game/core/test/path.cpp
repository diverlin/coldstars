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

#include <core/part/Path.hpp>

#include <meti/VectorUtils.hpp>

#include <gtest/gtest.h>

namespace test {

namespace {

bool validate_path(const glm::vec3& from,
                   const glm::vec3& to,
                   const std::vector<ceti::Position>& positions,
                   float dist) {
    if (!positions.size()) {
        return false;
    }

    if (positions.size() < 2) {
        return false;
    }

    glm::vec3 p0 = positions.front().center;
    if (glm::length(p0 - from) > dist) {
        return false;
    }

    int first = true;
    for(const auto& _p: positions) {
        const glm::vec3& p = _p.center;
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

    expect_eq_dirty(positions.back().center, to, "center_end");

    return true;
}

} // namespace

TEST(path, calc_direct)
{
    std::vector<ceti::Position> positions;

    // linear path calculation
    std::vector<glm::vec2> offsets = {
        glm::vec2(100, 0),
        glm::vec2(-100, 0),
        glm::vec2(0, 100),
        glm::vec2(0, -100)
    };

    for(const auto& offset: offsets) {
        glm::vec3 from(0,0,0);
        glm::vec3 to(offset.x, offset.y, 0);
        glm::vec3 dir(glm::normalize(to));
        float speed = 1.0f;

        EXPECT_TRUE(path::isLookingTowards(to-from, dir));
        bool result = path::calcDirectPath(positions, from, to, speed);
        EXPECT_TRUE(result);

        EXPECT_TRUE(validate_path(from, to, positions, speed));

        expect_eq(positions.back().center, to, "center");

        int steps = int(std::fabs(glm::length(offset)/speed));
        EXPECT_EQ(positions.size(), steps);

        positions.clear();
    }
}

TEST(path, rotate_vector_around_point)
{
    float r = 100;
    {
        glm::vec3 result = path::rotVec(glm::vec3(0,0,0), glm::vec3(r,0,0), -M_PI/2);
        expect_eq_dirty(result, glm::vec3(r, r, 0), "rot");
    }
    {
        glm::vec3 result = path::rotVec(glm::vec3(0,0,0), glm::vec3(r,0,0), M_PI/2);
        expect_eq_dirty(result, glm::vec3(r, -r, 0), "rot");
    }


    {
        glm::vec3 result = path::rotVec(glm::vec3(0,0,0), glm::vec3(r,0,0), M_PI);
        expect_eq_dirty(result, glm::vec3(2*r, 0, 0), "rot");
    }
    {
        glm::vec3 result = path::rotVec(glm::vec3(0,0,0), glm::vec3(r,0,0), -M_PI);
        expect_eq_dirty(result, glm::vec3(2*r, 0, 0), "rot");
    }
}

TEST(path, calc_round)
{
    float speed = 1.0f;
    float r = path::calcRadius(speed, path::ANGLE_STEP);
    float d = 2*r;
    glm::vec3 from(0,0,0);

    std::vector<std::pair<glm::vec3, glm::vec3>> pairs = {
        std::make_pair(glm::vec3(0,1,0), glm::vec3(d,0,0)),
        std::make_pair(glm::vec3(0,1,0), glm::vec3(-d,0,0)),
        std::make_pair(glm::vec3(-1,0,0), glm::vec3(0,d,0)),
        std::make_pair(glm::vec3(-1,0,0), glm::vec3(0,-d,0)),
        std::make_pair(glm::vec3(1,0,0), glm::vec3(0,d,0)),
        std::make_pair(glm::vec3(1,0,0), glm::vec3(0,-d,0)),
    };

    for(const auto& pair: pairs) {
        std::vector<ceti::Position> positions;

        const auto& dir = pair.first;
        const auto& to = pair.second;

        bool result = path::calcRoundPath(positions, from, to, dir, speed);
        EXPECT_TRUE(result);

        EXPECT_TRUE(validate_path(from, to, positions, speed));

        positions.clear();
    }
}

TEST(path, calc_round_false)
{
    std::vector<ceti::Position> positions;

    glm::vec3 from(0,0,0);
    glm::vec3 to(10, 0, 0);
    glm::vec3 dir(0, 1, 0);
    float speed = 1.0f;

    bool result = path::calcPath(positions, from, to, dir, speed);
    EXPECT_FALSE(result);

    positions.clear();
}

TEST(path, complex)
{
    std::vector<ceti::Position> positions;

    glm::vec3 from(0,0,0);

    glm::vec3 to(800.0f, 800.0f, 0.0f);

    glm::vec3 dir(0, 1, 0);
    float speed = 1.0f;

    bool result = path::calcPath(positions, from, to, dir, speed);
    EXPECT_TRUE(result);

    EXPECT_TRUE(validate_path(from, to, positions, speed));

    expect_eq_dirty(positions.back().center, to,"center");
    expect_eq_dirty(positions.back().direction, glm::normalize(glm::vec3(to-positions.back().direction)), "dir");

    positions.clear();
}

} // namespace test
