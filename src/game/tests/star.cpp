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

#include <common/Global.hpp>
//#include <common/constants.hpp>

//#include <slots/ItemSlot.hpp>
#include <spaceobjects/Star.hpp>

#include <builder/spaceobjects/StarBuilder.hpp>

#include <descriptors/Base.hpp>
//#include <descriptors/DescriptorGenerator.hpp>
#include <descriptors/DescriptorManager.hpp>

//#include <builder/item/equipment/ALL>
//#include <builder/item/modules/ALL>
//#include <builder/item/artefacts//ALL>
//#include <builder/item/other/ALL>

//#include <item/equipment/ALL>

//#include "helper.hpp"

//#include <fstream>


TEST(creation, star)
{
    const descriptor::BaseOLD& descr = global::get().descriptors().getRand(descriptor::Type::STAR);
    model::Star* star = builder::StarBuilder::getNew(descr);

    EXPECT_EQ(descr.armor(), star->armor());
}
