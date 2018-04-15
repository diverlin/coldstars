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

void compareEquipment(core::EquipmentModel* model, core::EquipmentModel* copy)
{
    // Base
    EXPECT_EQ(model->id(), copy->id());
    EXPECT_EQ(model->descriptor(), copy->descriptor());

    // Item
    EXPECT_EQ(model->condition(), copy->condition());

    // Equipment

}

} // namespace

TEST(core, bak) {
    core::BakModel* model = core::BakItemBuilder::gen()->model();
    core::BakModel* copy = new core::BakModel(model->data());

    compareEquipment(model, copy);

    // Bak
    EXPECT_EQ(model->fuel(), copy->fuel());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(core, drive) {
    core::DriveModel* model = core::DriveItemBuilder::gen()->model();
    core::DriveModel* copy = new core::DriveModel(model->data());

    compareEquipment(model, copy);

    // Drive
    EXPECT_EQ(model->speed(), copy->speed());
    EXPECT_EQ(model->hyper(), copy->hyper());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(core, droid) {
    core::DroidModel* model = core::DroidItemBuilder::gen()->model();
    core::DroidModel* copy = new core::DroidModel(model->data());

    compareEquipment(model, copy);

    // Droid
    EXPECT_EQ(model->repair(), copy->repair());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(core, grapple) {
    core::GrappleModel* model = core::GrappleItemBuilder::gen()->model();
    core::GrappleModel* copy = new core::GrappleModel(model->data());

    compareEquipment(model, copy);

    // Grapple
    EXPECT_EQ(model->strength(), copy->strength());
    EXPECT_EQ(model->radius(), copy->radius());
    EXPECT_EQ(model->speed(), copy->speed());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(core, lazer) {
    core::LazerModel* model = core::LazerItemBuilder::gen()->model();
    core::LazerModel* copy = new core::LazerModel(model->data());

    compareEquipment(model, copy);

    // Lazer
    EXPECT_EQ(model->damage(), copy->damage());
    EXPECT_EQ(model->radius(), copy->radius());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(core, protector) {
    core::ProtectorModel* model = core::ProtectorItemBuilder::gen()->model();
    core::ProtectorModel* copy = new core::ProtectorModel(model->data());

    compareEquipment(model, copy);

    // Protector
    EXPECT_EQ(model->protection(), copy->protection());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(core, radar) {
    core::RadarModel* model = core::RadarItemBuilder::gen()->model();
    core::RadarModel* copy = new core::RadarModel(model->data());

    compareEquipment(model, copy);

    // Radar
    EXPECT_EQ(model->radius(), copy->radius());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(core, rocket) {
    core::RocketModel* model = core::RocketItemBuilder::gen()->model();
    core::RocketModel* copy = new core::RocketModel(model->data());

    compareEquipment(model, copy);

    // Rocket
    EXPECT_EQ(model->ammo(), copy->ammo());
    EXPECT_EQ(model->damage(), copy->damage());
    EXPECT_EQ(model->radius(), copy->radius());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

TEST(core, scaner) {
    core::ScanerModel* model = core::ScanerItemBuilder::gen()->model();
    core::ScanerModel* copy = new core::ScanerModel(model->data());

    compareEquipment(model, copy);

    // Scaner
    EXPECT_EQ(model->scan(), copy->scan());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

