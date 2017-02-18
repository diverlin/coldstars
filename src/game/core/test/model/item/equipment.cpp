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
//    EXPECT_EQ(model->type(), copy->type());
//    EXPECT_EQ(model->subtype(), copy->subtype());
//    EXPECT_EQ(model->subsubtype(), copy->subsubtype());

    // model::Item
    EXPECT_EQ(model->condition(), copy->condition());

    // model::Equipment

}

} // namespace

TEST(model, bak) {
    init();

    model::item::Bak* model = builder::item::Bak::getNew();

//    EXPECT_EQ(model->type(), entity::type::EQUIPMENT);
//    EXPECT_EQ(model->subtype(), entity::type::BAK_EQUIPMENT);

    model::item::Bak* copy = new model::item::Bak(model->data());

    compareEquipment(model, copy);

    // model::item::Bak
    EXPECT_EQ(model->fuel(), copy->fuel());

    // general
    EXPECT_EQ(model->data(), copy->data());

    delete model;
    delete copy;
}

TEST(model, drive) {
    model::item::Drive* model = builder::item::Drive::getNew();

//    EXPECT_EQ(model->type(), entity::type::EQUIPMENT);
//    EXPECT_EQ(model->subtype(), entity::type::DRIVE_EQUIPMENT);

    model::item::Drive* copy = new model::item::Drive(model->data());

    compareEquipment(model, copy);

    // model::item::Drive
    EXPECT_EQ(model->speed(), copy->speed());
    EXPECT_EQ(model->hyper(), copy->hyper());

    // general
    EXPECT_EQ(model->data(), copy->data());
}

//TEST(model, droid) {
//    model::item::Droid descr = model::item::getNewDroid();

//    EXPECT_EQ(model->descriptor(), model::type::DROID_EQUIPMENT);
//    EXPECT_EQ(model->slotType(), entity::type::DROID_SLOT);

//    model::item::Droid copy(model->data());

//    compareEquipmentDescriptors(descr, copy);

//    // model::item::Droid
//    EXPECT_EQ(model->repair(), copy->repair());

//    // general
//    EXPECT_EQ(model->data(), copy->data());
//    EXPECT_EQ(model->info(), copy->info());
//}

//TEST(model, grapple) {
//    model::item::Grapple descr = model::item::getNewGrapple();

//    EXPECT_EQ(model->descriptor(), model::type::GRAPPLE_EQUIPMENT);
//    EXPECT_EQ(model->slotType(), entity::type::GRAPPLE_SLOT);

//    model::item::Grapple copy(model->data());

//    compareEquipmentDescriptors(descr, copy);

//    // model::item::Grapple
//    EXPECT_EQ(model->strength(), copy->strength());
//    EXPECT_EQ(model->radius(), copy->radius());
//    EXPECT_EQ(model->speed(), copy->speed());

//    // general
//    EXPECT_EQ(model->data(), copy->data());
//    EXPECT_EQ(model->info(), copy->info());
//}

//TEST(model, lazer) {
//    model::item::Lazer descr = model::item::getNewLazer();

//    EXPECT_EQ(model->descriptor(), model::type::LAZER_EQUIPMENT);
//    EXPECT_EQ(model->slotType(), entity::type::WEAPON_SLOT);

//    model::item::Lazer copy(model->data());

//    compareEquipmentDescriptors(descr, copy);

//    // model::item::Lazer
//    EXPECT_EQ(model->damage(), copy->damage());
//    EXPECT_EQ(model->radius(), copy->radius());

//    // general
//    EXPECT_EQ(model->data(), copy->data());
//    EXPECT_EQ(model->info(), copy->info());
//}

//TEST(model, protector) {
//    model::item::Protector descr = model::item::getNewProtector();

//    EXPECT_EQ(model->descriptor(), model::type::PROTECTOR_EQUIPMENT);
//    EXPECT_EQ(model->slotType(), entity::type::PROTECTOR_SLOT);

//    model::item::Protector copy(model->data());

//    compareEquipmentDescriptors(descr, copy);

//    // model::item::Protector
//    EXPECT_EQ(model->protection(), copy->protection());

//    // general
//    EXPECT_EQ(model->data(), copy->data());
//    EXPECT_EQ(model->info(), copy->info());
//}

//TEST(model, radar) {
//    model::item::Radar descr = model::item::getNewRadar();

//    EXPECT_EQ(model->descriptor(), model::type::RADAR_EQUIPMENT);
//    EXPECT_EQ(model->slotType(), entity::type::RADAR_SLOT);

//    model::item::Radar copy(model->data());

//    compareEquipmentDescriptors(descr, copy);

//    // model::item::Radar
//    EXPECT_EQ(model->radius(), copy->radius());

//    // general
//    EXPECT_EQ(model->data(), copy->data());
//    EXPECT_EQ(model->info(), copy->info());
//}

//TEST(model, rocket) {
//    model::item::Rocket descr = model::item::getNewRocket();

//    EXPECT_EQ(model->descriptor(), model::type::ROCKET_EQUIPMENT);
//    EXPECT_EQ(model->slotType(), entity::type::WEAPON_SLOT);

//    model::item::Rocket copy(model->data());

//    compareEquipmentDescriptors(descr, copy);

//    // model::item::Rocket
//    EXPECT_EQ(model->ammo(), copy->ammo());
//    EXPECT_EQ(model->damage(), copy->damage());
//    EXPECT_EQ(model->radius(), copy->radius());

//    // general
//    EXPECT_EQ(model->data(), copy->data());
//    EXPECT_EQ(model->info(), copy->info());
//}

//TEST(model, scaner) {
//    model::item::Scaner descr = model::item::getNewScaner();

//    EXPECT_EQ(model->descriptor(), model::type::SCANER_EQUIPMENT);
//    EXPECT_EQ(model->slotType(), entity::type::SCANER_SLOT);

//    model::item::Scaner copy(model->data());

//    compareEquipmentDescriptors(descr, copy);

//    // model::item::Scaner
//    EXPECT_EQ(model->scan(), copy->scan());

//    // general
//    EXPECT_EQ(model->data(), copy->data());
//    EXPECT_EQ(model->info(), copy->info());
//}

