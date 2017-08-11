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

#include <jeti/Render.hpp>
#include <jeti/Camera.hpp>

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
    EXPECT_TRUE(std::fabs(v1.x-v2.x)<epsilon);
    EXPECT_TRUE(std::fabs(v1.y-v2.y)<epsilon);
    return (std::fabs(v1.x-v2.x)<epsilon) && (std::fabs(v1.y-v2.y)<epsilon);
}

bool epsilonEqual(const glm::vec3& v1, const glm::vec3& v2) {
    std::cout<<"compare="<<ceti::to_string(v1)<<" and "<<ceti::to_string(v2)<<std::endl;
    float epsilon = 0.0001;
    EXPECT_TRUE(std::fabs(v1.x-v2.x)<epsilon);
    EXPECT_TRUE(std::fabs(v1.y-v2.y)<epsilon);
    return (std::fabs(v1.x-v2.x)<epsilon) && (std::fabs(v1.y-v2.y)<epsilon);
}

} // namespace

TEST(coords, screen2word)
{
    client::global::get().init();
    jeti::Render& render = client::global::get().render();
    int w = render.width();
    int h = render.height();
    assert(w>0);
    assert(h>0);


    std::vector<float> scales;
    scales.push_back(0.1f);
    scales.push_back(1.0f);
    scales.push_back(2.0f);
    scales.push_back(10.0f);

    for (const float scale: scales) {
        render.camera()->setPosition(glm::vec3(0));
        render.setScaleBase(scale);

        glm::vec3 screen_coord = render.camera()->position();
        glm::vec3 zero(0,0,0);

        EXPECT_TRUE(epsilonEqual(zero, screen_coord));

        {
            glm::vec3 mouse_pos(w/2,h/2,0);
            glm::vec3 world_coord = render.toWorldCoord(mouse_pos);
            EXPECT_TRUE(epsilonEqual(zero, world_coord));
        }

        {
            glm::vec3 mouse_pos(w,h,0);
            glm::vec3 world_coord = render.toWorldCoord(mouse_pos);
            EXPECT_TRUE(epsilonEqual(glm::vec3(scale*w/2,scale*h/2,0), world_coord));
        }

        {
            glm::vec3 mouse_pos(w,h,0);
            render.camera()->setPosition(glm::vec3(-w/2,-h/2,0));
            glm::vec3 world_coord = render.toWorldCoord(mouse_pos);
            EXPECT_TRUE(epsilonEqual(zero, world_coord));
        }
    }
}


TEST(coords, word2screen)
{
    client::global::get().init();
    jeti::Render& render = client::global::get().render();
    int w = render.width();
    int h = render.height();
    assert(w>0);
    assert(h>0);


    std::vector<float> scales;
    scales.push_back(0.1f);
    scales.push_back(1.0f);
    scales.push_back(2.0f);
    scales.push_back(10.0f);

    for (const float scale: scales) {
        render.camera()->setPosition(glm::vec3(0));
        render.setScaleBase(scale);

        glm::vec3 screen_coord = render.camera()->position();
        glm::vec3 zero(0,0,0);

        EXPECT_TRUE(epsilonEqual(zero, screen_coord));

        {
            glm::vec3 world_coord(zero);
            glm::vec3 screen_coord;
            render.toScreenCoord(world_coord, screen_coord);
            EXPECT_TRUE(epsilonEqual(glm::vec3(w/2,h/2,0), screen_coord));
        }

        {
            glm::vec3 world_coord(w/2*scale,h/2*scale,0);
            glm::vec3 screen_coord;
            render.toScreenCoord(world_coord, screen_coord);
            EXPECT_TRUE(epsilonEqual(glm::vec3(w,h,0), screen_coord));
        }

        {
            glm::vec3 world_coord(zero);
            render.camera()->setPosition(glm::vec3(-w/2*scale,-h/2*scale,0));
            glm::vec3 screen_coord;
            render.toScreenCoord(world_coord, screen_coord);
            EXPECT_TRUE(epsilonEqual(glm::vec3(w,h,0), screen_coord));
        }
    }
}

TEST(view, visibility)
{
    client::global::get().init();
    control::Ship* star = builder::Ship::gen();
    view::Ship* view = new view::Ship(star);
}
