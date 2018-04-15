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


#include <core/builder/item/equipment/ALL>
#include <core/model/item/equipment/ALL>
#include <core/item/equipment/ALL>

#include <core/common/Global.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <gtest/gtest.h>

namespace {

void init()
{
    assert(false);
//    descriptor::Manager::generate();
}

void compareEquipment(model::Equipment* model, model::Equipment* copy)
{
    // model::Base
    EXPECT_EQ(model->id(), copy->id());
    EXPECT_EQ(model->descriptor(), copy->descriptor());

    // model::Item
    EXPECT_EQ(model->condition(), copy->condition());

    // model::Equipment

}

} // namespace

TEST(model, bak) {
    model::Bak* model = core::BakItemBuilder::gen()->model();
    model::Bak* copy = new model::Bak(model->data());

    compareEquipment(model, copy);

    // model::Bak
    EXPECT_EQ(model->fuel(), copy->fuel());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, drive) {
    model::Drive* model = core::DriveItemBuilder::gen()->model();
    model::Drive* copy = new model::Drive(model->data());

    compareEquipment(model, copy);

    // model::Drive
    EXPECT_EQ(model->speed(), copy->speed());
    EXPECT_EQ(model->hyper(), copy->hyper());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, droid) {
    model::Droid* model = core::DroidItemBuilder::gen()->model();
    model::Droid* copy = new model::Droid(model->data());

    compareEquipment(model, copy);

    // model::Droid
    EXPECT_EQ(model->repair(), copy->repair());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, grapple) {
    model::Grapple* model = core::GrappleItemBuilder::gen()->model();
    model::Grapple* copy = new model::Grapple(model->data());

    compareEquipment(model, copy);

    // model::Grapple
    EXPECT_EQ(model->strength(), copy->strength());
    EXPECT_EQ(model->radius(), copy->radius());
    EXPECT_EQ(model->speed(), copy->speed());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, lazer) {
    model::Lazer* model = core::LazerItemBuilder::gen()->model();
    model::Lazer* copy = new model::Lazer(model->data());

    compareEquipment(model, copy);

    // model::Lazer
    EXPECT_EQ(model->damage(), copy->damage());
    EXPECT_EQ(model->radius(), copy->radius());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, protector) {
    model::Protector* model = core::ProtectorItemBuilder::gen()->model();
    model::Protector* copy = new model::Protector(model->data());

    compareEquipment(model, copy);

    // model::Protector
    EXPECT_EQ(model->protection(), copy->protection());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, radar) {
    model::Radar* model = core::RadarItemBuilder::gen()->model();
    model::Radar* copy = new model::Radar(model->data());

    compareEquipment(model, copy);

    // model::Radar
    EXPECT_EQ(model->radius(), copy->radius());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, rocket) {
    model::Rocket* model = core::RocketItemBuilder::gen()->model();
    model::Rocket* copy = new model::Rocket(model->data());

    compareEquipment(model, copy);

    // model::Rocket
    EXPECT_EQ(model->ammo(), copy->ammo());
    EXPECT_EQ(model->damage(), copy->damage());
    EXPECT_EQ(model->radius(), copy->radius());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, scaner) {
    model::Scaner* model = core::ScanerItemBuilder::gen()->model();
    model::Scaner* copy = new model::Scaner(model->data());

    compareEquipment(model, copy);

    // model::Scaner
    EXPECT_EQ(model->scan(), copy->scan());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

