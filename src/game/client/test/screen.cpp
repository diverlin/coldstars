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

#include <jeti/Screen.hpp>

#include <core/builder/spaceobject/ALL>
#include <core/spaceobject/ALL>
#include <client/common/global.hpp>
//#include <core/manager/DescriptorManager.hpp>

//#include <core/descriptor/spaceobject/ALL>

#include <client/view/spaceobject/ALL>

#include <ceti/StringUtils.hpp>

//#include <client/common/global.hpp>
//#include <client/view/StarSystem.hpp>

//#include <jeti/Camera.hpp>

#include <gtest/gtest.h>

#include <glm/gtc/epsilon.hpp>

namespace {
bool epsilonEqual(const glm::vec2& v1, const glm::vec2& v2) {
    float epsilon = 0.0001;
    EXPECT_TRUE(v1.x-v2.x<epsilon);
    EXPECT_TRUE(v1.y-v2.y<epsilon);
    return (v1.x-v2.x<epsilon) && (v1.y-v2.y<epsilon);
}

bool epsilonEqual(const glm::vec3& v1, const glm::vec3& v2) {
    float epsilon = 0.0001;
    EXPECT_TRUE(v1.x-v2.x<epsilon);
    EXPECT_TRUE(v1.y-v2.y<epsilon);
    return (v1.x-v2.x<epsilon) && (v1.y-v2.y<epsilon);
}

} // namespace

TEST(screen, coords)
{
    client::global::get().init();
    jeti::Screen& screen = client::global::get().screen();
    glm::vec2 screen_coord = screen.position();
    glm::vec2 zero(0.0f, 0.0f);
    EXPECT_TRUE(epsilonEqual(screen_coord, zero));

//    {
//        glm::vec2 mouse_pos(200, 200);
//        glm::vec3 world_coord = screen.toWorldCoord(mouse_pos);
//        EXPECT_TRUE(epsilonEqual(world_coord, glm::vec3(mouse_pos, 0.0f)));
//    }

//    {
//        glm::vec2 mouse_pos(200, 200);
//        screen.setPosition(glm::vec2(400, 400));
//        glm::vec3 world_coord = screen.toWorldCoord(mouse_pos);
//        std::cout<<ceti::to_string(world_coord)<<std::endl;
//        EXPECT_TRUE(epsilonEqual(world_coord, glm::vec3(600.f,600.f, 0.0f)));
//    }

}

TEST(view, visibility)
{
    client::global::get().init();
    control::Ship* star = builder::Ship::gen();
    view::Ship* view = new view::Ship(star);
}
