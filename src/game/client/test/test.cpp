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

#include <client/view/Star.hpp>
#include <client/common/global.hpp>

#include <gtest/gtest.h>

TEST(resources, viewer)
{
    client::global::get().init();
    auto star_descr = core::global::get().descriptors().star().random();

    model::Star* model = builder::Star::getNew(star_descr);
    control::Star* control = new control::Star(model);
    view::Star* view = new view::Star(model);

    auto* material_descr = core::global::get().descriptors().material().get(star_descr.texture());

    EXPECT_NE(star_descr.texture(), -1);
    EXPECT_NE(material_descr->path(), "");
    EXPECT_EQ(star_descr.texture(), view->model()->material());
}
