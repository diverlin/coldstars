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

#include <core/builder/spaceobject/ALL>
#include <core/spaceobject/ALL>
#include <core/common/Global.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <core/descriptor/spaceobject/ALL>

#include <client/view/spaceobject/ALL>

#include <client/common/global.hpp>
#include <client/view/SpaceView.hpp>

#include <jeti/Camera.hpp>

#include <gtest/gtest.h>

namespace {

void validate(descriptor::Base* descr, jeti::view::BaseView* view) {
    descriptor::Material* material_descr = descriptor::Manager::get().material(descr->texture());
    descriptor::Mesh* mesh_descr = descriptor::Manager::get().mesh(descr->mesh());

    EXPECT_NE(descr->texture(), NONE);
    EXPECT_NE(material_descr->path(), "");

    EXPECT_NE(descr->mesh(), NONE);
    EXPECT_NE(mesh_descr->modelPath(), "");
}

} // namespace

TEST(view, star)
{
    client::global::get().init();
    control::Star* star = builder::Star::gen();
    view::Star* view = new view::Star(star);

    validate(star->descriptor(), view);
}

TEST(view, planet)
{
    client::global::get().init();
    control::Planet* planet = builder::Planet::gen();
    view::Planet* view = new view::Planet(planet);

    validate(planet->descriptor(), view);
}

TEST(view, asteroid)
{
    client::global::get().init();
    control::Asteroid* asteroid = builder::Asteroid::gen();
    view::Asteroid* view = new view::Asteroid(asteroid);

    validate(asteroid->descriptor(), view);
}

//TEST(view, ship)
//{
//    //client::global::get().init();
//    control::Ship* ship = builder::Ship::gen();
//    view::Ship* view = new view::Ship(ship);

//    validate(ship->descriptor(), view);
//}

//TEST(view, object_visible)
//{
//    jeti::Screen::Data screen;
//    screen.resize(800, 600);
//    glm::vec3 center;
//    glm::vec3 size3 = glm::vec3(100.0f, 100.0f, 100.0f);

//    float size = std::max(size3.x, size3.y) / 2;

//    std::vector<float> scales = { 0.1f, 1.0f, 2.0f };
//    // std::vector<float> scales = { 0.1f };
//    for (float scale: scales) {
//        // std::cout << "scale=" << scale << std::endl;
//        screen.scale = scale;

//        float threshold = screen.scaledRadius() - size * screen.scale;

//        // object and wordcoords at (0,0,0)
//        screen.worldcoolds = glm::vec3(0.0f, 0.0f, 0.0f);
//        center = glm::vec3(0.0f, 0.0f, 0.0f);
//        EXPECT_TRUE(view::isObjectOnScreen(center, size3, screen));

//        // object inside the screen radius, near to visibility threshold
//        screen.worldcoolds = glm::vec3(0.0f, 0.0f, 0.0f);
//        center = glm::vec3(threshold - 0.1f, 0.0f, 0.0f);
//        EXPECT_TRUE(view::isObjectOnScreen(center, size3, screen));

//        // object out of screen radius, near to visibility threshold
//        screen.worldcoolds = glm::vec3(0.0f, 0.0f, 0.0f);
//        center = glm::vec3(threshold + 0.1f, 0.0f, 0.0f);
//        EXPECT_FALSE(view::isObjectOnScreen(center, size3, screen));

//        // object out of screen radius
//        screen.worldcoolds = glm::vec3(0.0f, 0.0f, 0.0f);
//        center = glm::vec3(threshold + 10000.0f, 0.0f, 0.0f);
//        EXPECT_FALSE(view::isObjectOnScreen(center, size3, screen));
//    }
//}

TEST(view, objectOnScreen)
{
    jeti::Camera camera;
    camera.setPosition(glm::vec3(0,0,0));

    glm::vec3 pos_wc(1000, 1000, 0);
    jeti::Screen::Data screen;
    screen.resize(1000, 1000);

    glm::vec3 pos_sc;
    float scale = 1.0f;

//    pos_sc = view::screenCoord(pos_wc, camera, screen.rect);
//    EXPECT_EQ(glm::vec3(1000, 1000, 0), pos_sc);
//    EXPECT_TRUE(view::isPointInRect(pos_sc, screen.rect, scale));

//    camera.setPosition(glm::vec3(500,0,0));
//    pos_sc = view::screenCoord(pos_wc, camera, screen.rect);
//    EXPECT_EQ(glm::vec3(500, 1000, 0), pos_sc);
//    EXPECT_TRUE(view::isPointInRect(pos_sc, screen.rect, scale));

//    camera.setPosition(glm::vec3(999,999,0));
//    pos_sc = view::screenCoord(pos_wc, camera, screen.rect);
//    EXPECT_EQ(glm::vec3(1, 1, 0), pos_sc);
//    EXPECT_TRUE(view::isPointInRect(pos_sc, screen.rect, scale));

//    camera.setPosition(glm::vec3(-1000,-1000,0));
//    pos_sc = view::screenCoord(pos_wc, camera, screen.rect);
//    EXPECT_EQ(glm::vec3(2000, 2000, 0), pos_sc);
//    EXPECT_FALSE(view::isPointInRect(pos_sc, screen.rect, scale));

//    camera.setPosition(glm::vec3(2001,2001,0));
//    pos_sc = view::screenCoord(pos_wc, camera, screen.rect);
//    EXPECT_EQ(glm::vec3(-1001, -1001, 0), pos_sc);
//    EXPECT_FALSE(view::isPointInRect(pos_sc, screen.rect, scale));
}


