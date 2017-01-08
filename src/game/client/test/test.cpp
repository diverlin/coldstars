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

#include <core/builder/spaceobjects/ALL>
#include <core/spaceobjects/ALL>
#include <core/common/Global.hpp>
#include <core/descriptors/DescriptorManager.hpp>
#include <core/descriptors/StarDescriptor.hpp>
#include <core/descriptors/PlanetDescriptor.hpp>
#include <core/descriptors/AsteroidDescriptor.hpp>
//#include <core/descriptors/ShipDescriptor.hpp>

#include <client/view/Star.hpp>
#include <client/view/Planet.hpp>
//#include <client/view/Ship.hpp>
#include <client/view/Asteroid.hpp>

#include <client/common/global.hpp>

#include <gtest/gtest.h>

namespace {

template<typename T1, typename T2>
void validate(const T1& descr, T2* view) {

    descriptor::Material* material_descr = core::global::get().descriptors().material().get(descr.texture());
    descriptor::Mesh* mesh_descr = core::global::get().descriptors().mesh().get(descr.mesh());

    EXPECT_NE(descr.texture(), -1);
    EXPECT_NE(material_descr->path(), "");
    EXPECT_EQ(descr.texture(), view->model()->material());

    EXPECT_NE(descr.mesh(), -1);
    EXPECT_NE(mesh_descr->modelPath(), "");
    EXPECT_EQ(descr.mesh(), view->model()->mesh());
}

} // namespace

TEST(view, star)
{
    client::global::get().init();
    auto descr = core::global::get().descriptors().star().random();

    model::Star* model = builder::Star::getNew(descr);
    view::Star* view = new view::Star(model);

    validate(descr, view);
}

TEST(view, planet)
{
    client::global::get().init();
    auto descr = core::global::get().descriptors().planet().random();

    model::Planet* model = builder::Planet::getNew(descr);
    view::Planet* view = new view::Planet(model);

    validate(descr, view);
}

TEST(view, asteroid)
{
    client::global::get().init();
    auto descr = core::global::get().descriptors().asteroid().random();

    model::Asteroid* model = builder::Asteroid::getNew(descr);
    view::Asteroid* view = new view::Asteroid(model);

    validate(descr, view);
}

//TEST(view, ship)
//{
//    client::global::get().init();
////    auto descr = core::global::get().descriptors().ship().random();

////    model::Ship* model = builder::Ship::getNew(descr);
////    view::Ship* view = new view::Ship(model);

//    validate(descr, view);
//}
