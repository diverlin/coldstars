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

#include <glm/gtc/epsilon.hpp>
//#include <glm/gtc/constants.hpp>

#include <ceti/StringUtils.hpp>

#include <meti/VectorUtils.hpp>
#include <meti/QuaternionUtils.hpp>

namespace {
void print(const glm::vec3& orig, const glm::vec3& expect, const glm::vec3& actual)
{
    std::cout<<"orig  : "<<ceti::to_string(orig)<<std::endl;
    std::cout<<"expect: "<<ceti::to_string(expect)<<std::endl;
    std::cout<<"actual: "<<ceti::to_string(actual)<<std::endl;
}
} // namespace


//TEST(meti, quanternion_90_OZ)
//{
//    glm::quat Qz;

//    // vector in XY plane (1.0, 1.0) turn around axis Z on 90 degree
//    glm::vec3 p_orig =   glm::normalize(glm::vec3( 1.0, 1.0, 0.0));
//    glm::vec3 p_expect = glm::normalize(glm::vec3(-1.0, 1.0, 0.0));
////    glm::vec4 p_expect2 = glm::normalize(glm::vec4(-1.0, 1.0, 0.0, 0.0));

//    meti::quatFromAngleAndAxis(Qz, M_PI/2, meti::AXIS_Z);
////    glm::mat4 Rm = glm::toMat4(Qz);

//    glm::vec3 p_actual = Qz * p_orig;
//    print(p_orig, p_expect, p_actual);

//    EXPECT_TRUE(meti::equal(p_expect, p_actual));

////    glm::vec4 p_actual2 = Rm * glm::vec4(p_orig.x, p_orig.y, p_orig.z, 0.0);

////    EXPECT_TRUE(meti::equal(p_expect2, p_actual2));
//}


TEST(meti, quanternion_90_OZ)
{
    // vector in XY plane (1.0, 1.0) turn around axis Z on 90 degree
    glm::vec3 p_orig =   glm::normalize(glm::vec3( 1.0, 1.0, 0.0));
    glm::vec3 p_expect = glm::normalize(glm::vec3(-1.0, 1.0, 0.0));

    glm::quat Qz;
    meti::quatFromAngleAndAxis(Qz, M_PI/2, meti::OZ);

    glm::vec3 p_actual = Qz * p_orig;
    print(p_orig, p_expect, p_actual);

    EXPECT_TRUE(meti::checkEqualVec(p_expect, p_actual));
    EXPECT_TRUE(meti::checkEqual(glm::length(p_orig), glm::length(p_actual)));
}

TEST(meti, quanternion_180_OZ)
{
    // vector in XY plane (1.0, 1.0) turn around axis Z on 180 degree
    glm::vec3 p_orig =   glm::normalize(glm::vec3( 1.0, 1.0, 0.0));
    glm::vec3 p_expect = glm::normalize(glm::vec3(-1.0, -1.0, 0.0));

    glm::quat Qz;
    meti::quatFromAngleAndAxis(Qz, M_PI, meti::OZ);

    glm::vec3 p_actual = Qz * p_orig;
    print(p_orig, p_expect, p_actual);

    EXPECT_TRUE(meti::checkEqualVec(p_expect, p_actual));
    EXPECT_TRUE(meti::checkEqual(glm::length(p_orig), glm::length(p_actual)));
}

TEST(meti, quanternion_270_OZ)
{
    // vector in XY plane (1.0, 1.0) turn around axis Z on 270 degree
    glm::vec3 p_orig =   glm::normalize(glm::vec3( 1.0, 1.0, 0.0));
    glm::vec3 p_expect = glm::normalize(glm::vec3(1.0, -1.0, 0.0));

    glm::quat Qz;
    meti::quatFromAngleAndAxis(Qz, 3*M_PI/2, meti::OZ);

    glm::vec3 p_actual = Qz * p_orig;
    print(p_orig, p_expect, p_actual);

    EXPECT_TRUE(meti::checkEqualVec(p_expect, p_actual));
    EXPECT_TRUE(meti::checkEqual(glm::length(p_orig), glm::length(p_actual)));
}

TEST(meti, quanternion_360_OZ)
{
    // vector in XY plane (1.0, 1.0) turn around axis OZ on 360 degree
    glm::vec3 p_orig =   glm::normalize(glm::vec3( 1.0, 1.0, 0.0));
    glm::vec3 p_expect = glm::normalize(glm::vec3(1.0, 1.0, 0.0));

    glm::quat Qz;
    meti::quatFromAngleAndAxis(Qz, 2*M_PI, meti::OZ);

    glm::vec3 p_actual = Qz * p_orig;
    print(p_orig, p_expect, p_actual);

    EXPECT_TRUE(meti::checkEqualVec(p_expect, p_actual));
    EXPECT_TRUE(meti::checkEqual(glm::length(p_orig), glm::length(p_actual)));
}

TEST(meti, quanternion_45_OX)
{
//    // vector in XY plane (1.0, 1.0) turn around axis Z on 90 degree
//    glm::vec3 p_orig =   glm::normalize(glm::vec3( 1.0, 1.0, 0.0));
//    glm::vec3 p_expect = glm::normalize(glm::vec3(-1.0, 1.0, 0.0));

//    glm::quat Qz;
//    meti::quatFromAngleAndAxis(Qz, M_PI/2, meti::AXIS_Z);

//    glm::vec3 p_actual = Qz * p_orig;
//    print(p_orig, p_expect, p_actual);

//    EXPECT_TRUE(meti::equal(p_expect, p_actual));
}

//TEST(meti, quanternion)
//{
//    glm::quat Qx, Qy, Qz;

//    QuatFromAngleAndAxis(Qx, angle.x, meti::AXIS_X);
//    QuatFromAngleAndAxis(Qy, angle.y, meti::AXIS_Y);
//    QuatFromAngleAndAxis(Qz, angle.z, meti::AXIS_Z);

//    glm::mat4 Rm = glm::toMat4(Qx*Qy*Qz);


//    {
////    glm::quat quat;
////    glm::vec3 origin_dir(0.0, 0.0, 1.0);
////    glm::vec3 target_dir(0.0, 1.0, 0.0);
////    meti::quatBetweenVectors(quat, origin_dir, target_dir);
//    }

    //auto ids = getTestData();

    //Property p1(ids.at(INT1), 10);
    //Property p2(ids.at(INT2), 20);
    //Property p3(ids.at(INT3), 30);
    //Property p4(ids.at(FLOAT), 2.7f);
    //Property p5(ids.at(STRING1), "5;4;3;2;1");
    //Property p6(ids.at(VEC3), meti::vec3(1.0f, 2.0f, 3.0f));

    //Descriptor descr(0);
    //descr.m_ids = ids;
    //descr.add({p1,p2,p3,p4,p5,p6});

    //Descriptor descr2(descr);
    //EXPECT_TRUE(descr == descr2);

    //EXPECT_EQ(descr.get_i(INT1), descr2.get_i(INT1));
    //EXPECT_EQ(descr.get_i(INT2), descr2.get_i(INT2));
    //EXPECT_EQ(descr.get_i(INT3), descr2.get_i(INT3));
    //EXPECT_EQ(descr.get_f(FLOAT), descr2.get_f(FLOAT));
    //EXPECT_EQ(descr.get_s(STRING1), descr2.get_s(STRING1));
    //EXPECT_EQ(descr.get_v3(VEC3), descr2.get_v3(VEC3));

    //descr2.add( Property(ids.at(INT4), 40) );
    //EXPECT_FALSE(descr == descr2);

//    std::cout<<descr.info();
//    std::cout<<descr2.info();
//}

