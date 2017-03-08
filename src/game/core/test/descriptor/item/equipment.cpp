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


#include <core/descriptor/DescriptorGenerator.hpp>
#include <core/descriptor/item/equipment/ALL>

#include <gtest/gtest.h>

namespace {

void compareEquipment(const descriptor::Equipment& descr, const descriptor::Equipment& copy)
{
    // descriptor::Base
    EXPECT_EQ(descr.id(), copy.id());
    EXPECT_EQ(descr.type(), copy.type());
    EXPECT_EQ(descr.obType(), copy.obType());
    EXPECT_EQ(descr.obSubType(), copy.obSubType());
    EXPECT_EQ(descr.obSubSubType(), copy.obSubSubType());

    // ceti::descriptor::BaseView
    EXPECT_EQ(descr.texture(), copy.texture());
    EXPECT_EQ(descr.mesh(), copy.mesh());

    // descriptor::Item
    EXPECT_EQ(descr.race(), copy.race());
    EXPECT_EQ(descr.tech(), copy.tech());
    EXPECT_EQ(descr.slotType(), copy.slotType());
    EXPECT_EQ(descr.condition(), copy.condition());
    EXPECT_EQ(descr.deterioration(), copy.deterioration());
    EXPECT_EQ(descr.mass(), copy.mass());
    EXPECT_EQ(descr.price(), copy.price());

    // descriptor::Equipment
    EXPECT_EQ(descr.modules(), copy.modules());
}

} // namespace

TEST(descriptor, bak) {
    descriptor::item::Bak descr = *descriptor::item::getNewBak();

    EXPECT_EQ(descr.type(), descriptor::Type::BAK_EQUIPMENT);
    EXPECT_EQ(descr.obType(), entity::type::EQUIPMENT);
    EXPECT_EQ(descr.obSubType(), entity::type::BAK_EQUIPMENT);
    EXPECT_EQ(descr.slotType(), entity::type::BAK_SLOT);

    descriptor::item::Bak copy(descr.data());

    compareEquipment(descr, copy);

    // descriptor::item::Bak
    EXPECT_EQ(descr.fuel(), copy.fuel());

    // general
    EXPECT_EQ(descr.data(), copy.data());
    EXPECT_EQ(descr.info(), copy.info());
}

TEST(descriptor, drive) {
    descriptor::item::Drive descr = *descriptor::item::getNewDrive();

    EXPECT_EQ(descr.type(), descriptor::Type::DRIVE_EQUIPMENT);
    EXPECT_EQ(descr.obType(), entity::type::EQUIPMENT);
    EXPECT_EQ(descr.obSubType(), entity::type::DRIVE_EQUIPMENT);
    EXPECT_EQ(descr.slotType(), entity::type::DRIVE_SLOT);

    descriptor::item::Drive copy(descr.data());

    compareEquipment(descr, copy);

    // descriptor::item::Drive
    EXPECT_EQ(descr.speed(), copy.speed());
    EXPECT_EQ(descr.hyper(), copy.hyper());

    // general
    EXPECT_EQ(descr.data(), copy.data());
    EXPECT_EQ(descr.info(), copy.info());
}

TEST(descriptor, droid) {
    descriptor::item::Droid descr = *descriptor::item::getNewDroid();

    EXPECT_EQ(descr.type(), descriptor::Type::DROID_EQUIPMENT);
    EXPECT_EQ(descr.obType(), entity::type::EQUIPMENT);
    EXPECT_EQ(descr.obSubType(), entity::type::DROID_EQUIPMENT);
    EXPECT_EQ(descr.slotType(), entity::type::DROID_SLOT);

    descriptor::item::Droid copy(descr.data());

    compareEquipment(descr, copy);

    // descriptor::item::Droid
    EXPECT_EQ(descr.repair(), copy.repair());

    // general
    EXPECT_EQ(descr.data(), copy.data());
    EXPECT_EQ(descr.info(), copy.info());
}

TEST(descriptor, grapple) {
    descriptor::item::Grapple descr = *descriptor::item::getNewGrapple();

    EXPECT_EQ(descr.type(), descriptor::Type::GRAPPLE_EQUIPMENT);
    EXPECT_EQ(descr.obType(), entity::type::EQUIPMENT);
    EXPECT_EQ(descr.obSubType(), entity::type::GRAPPLE_EQUIPMENT);
    EXPECT_EQ(descr.slotType(), entity::type::GRAPPLE_SLOT);

    descriptor::item::Grapple copy(descr.data());

    compareEquipment(descr, copy);

    // descriptor::item::Grapple
    EXPECT_EQ(descr.strength(), copy.strength());
    EXPECT_EQ(descr.radius(), copy.radius());
    EXPECT_EQ(descr.speed(), copy.speed());

    // general
    EXPECT_EQ(descr.data(), copy.data());
    EXPECT_EQ(descr.info(), copy.info());
}

TEST(descriptor, lazer) {
    descriptor::item::Lazer descr = *descriptor::item::getNewLazer();

    EXPECT_EQ(descr.type(), descriptor::Type::LAZER_EQUIPMENT);
    EXPECT_EQ(descr.obType(), entity::type::EQUIPMENT);
    EXPECT_EQ(descr.obSubType(), entity::type::LAZER_EQUIPMENT);
    EXPECT_EQ(descr.slotType(), entity::type::WEAPON_SLOT);

    descriptor::item::Lazer copy(descr.data());

    compareEquipment(descr, copy);

    // descriptor::item::Lazer
    EXPECT_EQ(descr.damage(), copy.damage());
    EXPECT_EQ(descr.radius(), copy.radius());

    // general
    EXPECT_EQ(descr.data(), copy.data());
    EXPECT_EQ(descr.info(), copy.info());
}

TEST(descriptor, protector) {
    descriptor::item::Protector descr = *descriptor::item::getNewProtector();

    EXPECT_EQ(descr.type(), descriptor::Type::PROTECTOR_EQUIPMENT);
    EXPECT_EQ(descr.obType(), entity::type::EQUIPMENT);
    EXPECT_EQ(descr.obSubType(), entity::type::PROTECTOR_EQUIPMENT);
    EXPECT_EQ(descr.slotType(), entity::type::PROTECTOR_SLOT);

    descriptor::item::Protector copy(descr.data());

    compareEquipment(descr, copy);

    // descriptor::item::Protector
    EXPECT_EQ(descr.protection(), copy.protection());

    // general
    EXPECT_EQ(descr.data(), copy.data());
    EXPECT_EQ(descr.info(), copy.info());
}

TEST(descriptor, radar) {
    descriptor::item::Radar descr = *descriptor::item::getNewRadar();

    EXPECT_EQ(descr.type(), descriptor::Type::RADAR_EQUIPMENT);
    EXPECT_EQ(descr.obType(), entity::type::EQUIPMENT);
    EXPECT_EQ(descr.obSubType(), entity::type::RADAR_EQUIPMENT);
    EXPECT_EQ(descr.slotType(), entity::type::RADAR_SLOT);

    descriptor::item::Radar copy(descr.data());

    compareEquipment(descr, copy);

    // descriptor::item::Radar
    EXPECT_EQ(descr.radius(), copy.radius());

    // general
    EXPECT_EQ(descr.data(), copy.data());
    EXPECT_EQ(descr.info(), copy.info());
}

TEST(descriptor, rocket) {
    descriptor::item::Rocket descr = *descriptor::item::getNewRocket();

    EXPECT_EQ(descr.type(), descriptor::Type::ROCKET_EQUIPMENT);
    EXPECT_EQ(descr.obType(), entity::type::EQUIPMENT);
    EXPECT_EQ(descr.obSubType(), entity::type::ROCKET_EQUIPMENT);
    EXPECT_EQ(descr.slotType(), entity::type::WEAPON_SLOT);

    descriptor::item::Rocket copy(descr.data());

    compareEquipment(descr, copy);

    // descriptor::item::Rocket
    EXPECT_EQ(descr.ammo(), copy.ammo());
    EXPECT_EQ(descr.damage(), copy.damage());
    EXPECT_EQ(descr.radius(), copy.radius());

    // general
    EXPECT_EQ(descr.data(), copy.data());
    EXPECT_EQ(descr.info(), copy.info());
}

TEST(descriptor, scaner) {
    descriptor::item::Scaner descr = *descriptor::item::getNewScaner();

    EXPECT_EQ(descr.type(), descriptor::Type::SCANER_EQUIPMENT);
    EXPECT_EQ(descr.obType(), entity::type::EQUIPMENT);
    EXPECT_EQ(descr.obSubType(), entity::type::SCANER_EQUIPMENT);
    EXPECT_EQ(descr.slotType(), entity::type::SCANER_SLOT);

    descriptor::item::Scaner copy(descr.data());

    compareEquipment(descr, copy);

    // descriptor::item::Scaner
    EXPECT_EQ(descr.scan(), copy.scan());

    // general
    EXPECT_EQ(descr.data(), copy.data());
    EXPECT_EQ(descr.info(), copy.info());
}

