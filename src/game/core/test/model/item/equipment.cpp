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
//    Manager::generate();
}

void compareEquipment(model::EquipmentModel* model, model::EquipmentModel* copy)
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
    model::BakModel* model = core::BakItemBuilder::gen()->model();
    model::BakModel* copy = new model::BakModel(model->data());

    compareEquipment(model, copy);

    // model::Bak
    EXPECT_EQ(model->fuel(), copy->fuel());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, drive) {
    model::DriveModel* model = core::DriveItemBuilder::gen()->model();
    model::DriveModel* copy = new model::DriveModel(model->data());

    compareEquipment(model, copy);

    // model::Drive
    EXPECT_EQ(model->speed(), copy->speed());
    EXPECT_EQ(model->hyper(), copy->hyper());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, droid) {
    model::DroidModel* model = core::DroidItemBuilder::gen()->model();
    model::DroidModel* copy = new model::DroidModel(model->data());

    compareEquipment(model, copy);

    // model::Droid
    EXPECT_EQ(model->repair(), copy->repair());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, grapple) {
    model::GrappleModel* model = core::GrappleItemBuilder::gen()->model();
    model::GrappleModel* copy = new model::GrappleModel(model->data());

    compareEquipment(model, copy);

    // model::Grapple
    EXPECT_EQ(model->strength(), copy->strength());
    EXPECT_EQ(model->radius(), copy->radius());
    EXPECT_EQ(model->speed(), copy->speed());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, lazer) {
    model::LazerModel* model = core::LazerItemBuilder::gen()->model();
    model::LazerModel* copy = new model::LazerModel(model->data());

    compareEquipment(model, copy);

    // model::Lazer
    EXPECT_EQ(model->damage(), copy->damage());
    EXPECT_EQ(model->radius(), copy->radius());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, protector) {
    model::ProtectorModel* model = core::ProtectorItemBuilder::gen()->model();
    model::ProtectorModel* copy = new model::ProtectorModel(model->data());

    compareEquipment(model, copy);

    // model::Protector
    EXPECT_EQ(model->protection(), copy->protection());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, radar) {
    model::RadarModel* model = core::RadarItemBuilder::gen()->model();
    model::RadarModel* copy = new model::RadarModel(model->data());

    compareEquipment(model, copy);

    // model::Radar
    EXPECT_EQ(model->radius(), copy->radius());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, rocket) {
    model::RocketModel* model = core::RocketItemBuilder::gen()->model();
    model::RocketModel* copy = new model::RocketModel(model->data());

    compareEquipment(model, copy);

    // model::Rocket
    EXPECT_EQ(model->ammo(), copy->ammo());
    EXPECT_EQ(model->damage(), copy->damage());
    EXPECT_EQ(model->radius(), copy->radius());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(model, scaner) {
    model::ScanerModel* model = core::ScanerItemBuilder::gen()->model();
    model::ScanerModel* copy = new model::ScanerModel(model->data());

    compareEquipment(model, copy);

    // model::Scaner
    EXPECT_EQ(model->scan(), copy->scan());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

