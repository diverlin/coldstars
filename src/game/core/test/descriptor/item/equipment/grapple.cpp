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

#include <test/descriptor/base.hpp>
#include <test/descriptor/item/item.hpp>
#include <test/descriptor/item/equipment/equipment.hpp>

#include <core/generator/DescriptorGenerator.hpp>
#include <core/descriptor/item/equipment/Grapple.hpp>

#include <gtest/gtest.h>

namespace test {

TEST(descriptor, clone_grapple) {
    descriptor::GrappleDescr* descr = descriptor::genGrapple();
    descriptor::GrappleDescr* copy = new descriptor::GrappleDescr(descr->data());

    EXPECT_EQ(descr->type(), descriptor::Type::GRAPPLE_EQUIPMENT);
    EXPECT_EQ(descr->obType(), entity::Type::GRAPPLE_EQUIPMENT);
    EXPECT_EQ(descr->obGroup(), entity::Type::EQUIPMENT);
    //EXPECT_EQ(descr->slotType(), entity::Type::GRAPPLE_SLOT);

    EXPECT_EQ(descr->strength(), copy->strength());
    EXPECT_EQ(descr->radius(), copy->radius());
    EXPECT_EQ(descr->speed(), copy->speed());

    EXPECT_EQ(descr->data(), copy->data());
    EXPECT_EQ(descr->info(), copy->info());

    testEquipmentEquality(descr, copy);
    testItemEquality(descr, copy);
//    testBaseViewEquality(descr, copy);
    testBaseEquality(descr, copy);

    delete copy;
}

} // namespace test
