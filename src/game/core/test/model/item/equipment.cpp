///*
//     Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>

//     This program is free software; you can redistribute it and/or
//     modify it under the terms of the GNU General Public License
//     as published by the Free Software Foundation; either version 2
//     of the License, or (at your option) any later version.

//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.

//     You should have received a copy of the GNU General Public License
//     along with this program; if not, write to the Free Software
//     Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//*/


#include <core/builder/item/equipment/ALL>
#include <core/model/item/equipment/ALL>

#include <core/common/Global.hpp>
#include <core/descriptor/DescriptorManager.hpp>

#include <gtest/gtest.h>

namespace {

void init()
{
    core::global::get().descriptors().generate();
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
    init();

    model::item::Bak* model = builder::item::Bak::getNew();
    model::item::Bak* copy = new model::item::Bak(model->data());

    compareEquipment(model, copy);

    // model::item::Bak
    EXPECT_EQ(model->fuel(), copy->fuel());

    // general
    EXPECT_EQ(model->data(), copy->data());

    // clean
    delete model;
    delete copy;
}

TEST(model, drive) {
    model::item::Drive* model = builder::item::Drive::getNew();
    model::item::Drive* copy = new model::item::Drive(model->data());

    compareEquipment(model, copy);

    // model::item::Drive
    EXPECT_EQ(model->speed(), copy->speed());
    EXPECT_EQ(model->hyper(), copy->hyper());

    // general
    EXPECT_EQ(model->data(), copy->data());

    // clean
    delete model;
    delete copy;
}

TEST(model, droid) {
    model::item::Droid* model = builder::item::Droid::getNew();
    model::item::Droid* copy = new model::item::Droid(model->data());

    compareEquipment(model, copy);

    // model::item::Droid
    EXPECT_EQ(model->repair(), copy->repair());

    // general
    EXPECT_EQ(model->data(), copy->data());

    // clean
    delete model;
    delete copy;
}

TEST(model, grapple) {
    model::item::Grapple* model = builder::item::Grapple::getNew();
    model::item::Grapple* copy = new model::item::Grapple(model->data());

    compareEquipment(model, copy);

    // model::item::Grapple
    EXPECT_EQ(model->strength(), copy->strength());
    EXPECT_EQ(model->radius(), copy->radius());
    EXPECT_EQ(model->speed(), copy->speed());

    // general
    EXPECT_EQ(model->data(), copy->data());

    // clean
    delete model;
    delete copy;
}

TEST(model, lazer) {
    model::item::Lazer* model = builder::item::Lazer::getNew();
    model::item::Lazer* copy = new model::item::Lazer(model->data());

    compareEquipment(model, copy);

    // model::item::Lazer
    EXPECT_EQ(model->damage(), copy->damage());
    EXPECT_EQ(model->radius(), copy->radius());

    // general
    EXPECT_EQ(model->data(), copy->data());

    // clean
    delete model;
    delete copy;
}

TEST(model, protector) {
    model::item::Protector* model = builder::item::Protector::getNew();
    model::item::Protector* copy = new model::item::Protector(model->data());

    compareEquipment(model, copy);

    // model::item::Protector
    EXPECT_EQ(model->protection(), copy->protection());

    // general
    EXPECT_EQ(model->data(), copy->data());

    // clean
    delete model;
    delete copy;
}

TEST(model, radar) {
    model::item::Radar* model = builder::item::Radar::getNew();
    model::item::Radar* copy = new model::item::Radar(model->data());

    compareEquipment(model, copy);

    // model::item::Radar
    EXPECT_EQ(model->radius(), copy->radius());

    // general
    EXPECT_EQ(model->data(), copy->data());

    // clean
    delete model;
    delete copy;
}

TEST(model, rocket) {
    model::item::Rocket* model = builder::item::Rocket::getNew();
    model::item::Rocket* copy = new model::item::Rocket(model->data());

    compareEquipment(model, copy);

    // model::item::Rocket
    EXPECT_EQ(model->ammo(), copy->ammo());
    EXPECT_EQ(model->damage(), copy->damage());
    EXPECT_EQ(model->radius(), copy->radius());

    // general
    EXPECT_EQ(model->data(), copy->data());

    // clean
    delete model;
    delete copy;
}

TEST(model, scaner) {
    model::item::Scaner* model = builder::item::Scaner::getNew();
    model::item::Scaner* copy = new model::item::Scaner(model->data());

    compareEquipment(model, copy);

    // model::item::Scaner
    EXPECT_EQ(model->scan(), copy->scan());

    // general
    EXPECT_EQ(model->data(), copy->data());

    // clean
    delete model;
    delete copy;
}

