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


#include <core/descriptor/Base.hpp>
#include <ceti/descriptor/BaseView.hpp>

#include <gtest/gtest.h>

namespace  test {

void testBaseEquality(descriptor::Base* descr, descriptor::Base* copy)
{
    EXPECT_EQ(descr->id(), copy->id());
    EXPECT_EQ(descr->type(), copy->type());
    EXPECT_EQ(descr->obType(), copy->obType());
    EXPECT_EQ(descr->obGroup(), copy->obGroup());
    EXPECT_EQ(descr->obClass(), copy->obClass());
    EXPECT_EQ(descr->mesh(), copy->mesh());
    //EXPECT_EQ(descr->texture(), copy->texture());
}

//void testBaseViewEquality(ceti::descriptor::BaseView* descr, ceti::descriptor::BaseView* copy)
//{
//    EXPECT_EQ(descr->texture(), copy->texture());
//    EXPECT_EQ(descr->mesh(), copy->mesh());
//}


} // namespace test
