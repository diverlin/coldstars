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

#include <ceti/InfoTable.hpp>

#include <gtest/gtest.h>

TEST(infotable, common)
{
    ceti::InfoTable table;
    table.add("header");
    table.add("label1", "value1");
    table.add("label2", 2);
    table.add("label3", 3.1f);
    table.add("label4", glm::vec3(1.0f, 2.0f, 3.0f));
    table.add("label5", std::vector<int_t>({1,2,3,4,5}));

    std::string expected("header:;label1:value1;label2:2;label3:3.10;label4:(1.00, 2.00, 3.00);label5:1,2,3,4,5,;");
    EXPECT_EQ(expected, table.str());


    ceti::InfoTable table2;
    table2.add("header2");
    table2.add("label1", "value1");
    table2.add("label2", 2);
    table2.add("label3", 3.2f);
    table2.add("label4", glm::vec3(1.0f, 2.0f, 3.0f));
    table2.add("label5", std::vector<int_t>({5,4,3,2,1}));

    std::string expected_diff = "key=header: value1= vs value2=key absent\n\
key=label3: value1=3.10 vs value2=3.20\n\
key=label5: value1=1,2,3,4,5, vs value2=5,4,3,2,1,\n\
key=header2: value1=key absent vs value2=\n";

    EXPECT_EQ(expected_diff, table.diff(table2));
    EXPECT_EQ("", table.diff(table));
}
