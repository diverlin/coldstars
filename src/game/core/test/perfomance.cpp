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
#include <core/communication/descriptor/Hit.hpp>
#include <core/generator/DescriptorGenerator.hpp>

#include <gtest/gtest.h>

#include <ctime>

//const int interation_num = 1000;

//TEST(base,perfomance1)
//{
//    clock_t begin = std::clock();
//    Hit hit1(1, 2, 33);
//    for (int i=0; i<interation_num; ++i) {
//        Hit hit2(hit1.data());
//        hit2.owner() == hit1.owner();
//        hit2.target() == hit1.target();
//        hit2.damage() == hit1.damage();
//    }

//    clock_t end = std::clock();
//    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//    std::cout<<"elapsed_secs="<<elapsed_secs<<std::endl;
//    EXPECT_TRUE(elapsed_secs < 1);
//}

//TEST(base,perfomance2)
//{
//    clock_t begin = std::clock();
//    Hit hit1(1, 2, 33);
//    for (int i=0; i<interation_num; ++i) {
//        Hit hit2(hit1.data());
//        hit2.owner() == hit1.owner();
//        hit2.target() == hit1.target();
//        hit2.damage() == hit1.damage();
//    }

//    clock_t end = std::clock();
//    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//    std::cout<<"elapsed_secs="<<elapsed_secs<<std::endl;
//    EXPECT_TRUE(elapsed_secs < 1);
//}

