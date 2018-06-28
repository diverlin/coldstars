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

#include <ceti/TagsComponent.hpp>

#include <gtest/gtest.h>

TEST(tags, common)
{
    ceti::TagsComponent::reg("star, asteroid, item, race1, inhabited, planet, cold, agressive");

    ceti::TagsComponent component1;
    component1.add("star, race1, cold");

    ceti::TagsComponent component2;
    component2.add("star, cold");

    ceti::TagsComponent component3;
    component3.add("star");

    ceti::TagsComponent component4;
    component4.add("star, inhabited");

    ceti::TagsComponent component5;
    component5.add("planet, inhabited");

    EXPECT_TRUE(component1.tags() == ceti::TagsComponent::ids_from("star, race1, cold"));
    EXPECT_TRUE(component1.match(component2.tags()));
    EXPECT_TRUE(component1.match(component3.tags()));
    EXPECT_TRUE(component2.match(component3.tags()));
    EXPECT_TRUE(component4.match(component3.tags()));
    EXPECT_FALSE(component3.match(component4.tags()));
    EXPECT_FALSE(component1.match(component4.tags()));
    EXPECT_FALSE(component1.match(component5.tags()));
}
