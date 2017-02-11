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

void compareBaseEquipmentDescriptors(const descriptor::item::Equipment& descr, const descriptor::item::Equipment& descr_copy)
{
    // descriptor::Base
    EXPECT_EQ(descr.id(), descr_copy.id());
    EXPECT_EQ(descr.descriptor(), descr_copy.descriptor());
    EXPECT_EQ(descr.type(), descr_copy.type());
    EXPECT_EQ(descr.subtype(), descr_copy.subtype());
    EXPECT_EQ(descr.subsubtype(), descr_copy.subsubtype());

    // ceti::descriptor::BaseView
    EXPECT_EQ(descr.texture(), descr_copy.texture());
    EXPECT_EQ(descr.mesh(), descr_copy.mesh());

    // descriptor::Item
    EXPECT_EQ(descr.race(), descr_copy.race());
    EXPECT_EQ(descr.tech(), descr_copy.tech());
    EXPECT_EQ(descr.slotType(), descr_copy.slotType());
    EXPECT_EQ(descr.condition(), descr_copy.condition());
    EXPECT_EQ(descr.deterioration(), descr_copy.deterioration());
    EXPECT_EQ(descr.mass(), descr_copy.mass());
    EXPECT_EQ(descr.price(), descr_copy.price());


//    race::type m_race = race::type::NONE;
//    tech::type m_tech = tech::type::NONE;
//    entity::type m_slotType = entity::type::NONE;
//    int_t m_slot = NONE;

//    int m_lockedTurns = 0;
//    int m_condition = 0;
//    int m_price = 0;
//    int m_mass = 0;
//    int m_deterioration = 0;

    // descriptor::item::Equipment
    EXPECT_EQ(descr.modules(), descr_copy.modules());
}

} // namespace

TEST(descriptor, bak) {
    descriptor::item::Bak descr = descriptor::item::getNewBak();
    descriptor::item::Bak descr_copy(descr.data());

    compareBaseEquipmentDescriptors(descr, descr_copy);

    // descriptor::item::Bak
    EXPECT_EQ(descr.descriptor(), descriptor::type::BAK_EQUIPMENT);
    EXPECT_EQ(descr.fuel(), descr_copy.fuel());

    // general
    EXPECT_EQ(descr.data(), descr_copy.data());
    EXPECT_EQ(descr.info(), descr_copy.info());
}

TEST(descriptor, drive) {
    descriptor::item::Drive descr = descriptor::item::getNewDrive();
    descriptor::item::Drive descr_copy(descr.data());

    compareBaseEquipmentDescriptors(descr, descr_copy);

    // descriptor::item::Drive
    EXPECT_EQ(descr.descriptor(), descriptor::type::DRIVE_EQUIPMENT);
    EXPECT_EQ(descr.speed(), descr_copy.speed());
    EXPECT_EQ(descr.hyper(), descr_copy.hyper());

    // general
    EXPECT_EQ(descr.data(), descr_copy.data());
    EXPECT_EQ(descr.info(), descr_copy.info());
}

TEST(descriptor, droid) {
    descriptor::item::Droid descr = descriptor::item::getNewDroid();
    descriptor::item::Droid descr_copy(descr.data());

    compareBaseEquipmentDescriptors(descr, descr_copy);

    // descriptor::item::Droid
    EXPECT_EQ(descr.descriptor(), descriptor::type::DROID_EQUIPMENT);
    EXPECT_EQ(descr.repair(), descr_copy.repair());

    // general
    EXPECT_EQ(descr.data(), descr_copy.data());
    EXPECT_EQ(descr.info(), descr_copy.info());
}

TEST(descriptor, grapple) {
    descriptor::item::Grapple descr = descriptor::item::getNewGrapple();
    descriptor::item::Grapple descr_copy(descr.data());

    compareBaseEquipmentDescriptors(descr, descr_copy);

    // descriptor::item::Grapple
    EXPECT_EQ(descr.descriptor(), descriptor::type::GRAPPLE_EQUIPMENT);
    EXPECT_EQ(descr.strength(), descr_copy.strength());
    EXPECT_EQ(descr.radius(), descr_copy.radius());
    EXPECT_EQ(descr.speed(), descr_copy.speed());

    // general
    EXPECT_EQ(descr.data(), descr_copy.data());
    EXPECT_EQ(descr.info(), descr_copy.info());
}

TEST(descriptor, lazer) {
    descriptor::item::Lazer descr = descriptor::item::getNewLazer();
    descriptor::item::Lazer descr_copy(descr.data());

    compareBaseEquipmentDescriptors(descr, descr_copy);

    // descriptor::item::Lazer
    EXPECT_EQ(descr.descriptor(), descriptor::type::LAZER_EQUIPMENT);
    EXPECT_EQ(descr.damage(), descr_copy.damage());
    EXPECT_EQ(descr.radius(), descr_copy.radius());

    // general
    EXPECT_EQ(descr.data(), descr_copy.data());
    EXPECT_EQ(descr.info(), descr_copy.info());
}

TEST(descriptor, protector) {
    descriptor::item::Protector descr = descriptor::item::getNewProtector();
    descriptor::item::Protector descr_copy(descr.data());

    compareBaseEquipmentDescriptors(descr, descr_copy);

    // descriptor::item::Protector
    EXPECT_EQ(descr.descriptor(), descriptor::type::PROTECTOR_EQUIPMENT);
    EXPECT_EQ(descr.protection(), descr_copy.protection());

    // general
    EXPECT_EQ(descr.data(), descr_copy.data());
    EXPECT_EQ(descr.info(), descr_copy.info());
}

TEST(descriptor, radar) {
    descriptor::item::Radar descr = descriptor::item::getNewRadar();
    descriptor::item::Radar descr_copy(descr.data());

    compareBaseEquipmentDescriptors(descr, descr_copy);

    // descriptor::item::Radar
    EXPECT_EQ(descr.descriptor(), descriptor::type::RADAR_EQUIPMENT);
    EXPECT_EQ(descr.radius(), descr_copy.radius());

    // general
    EXPECT_EQ(descr.data(), descr_copy.data());
    EXPECT_EQ(descr.info(), descr_copy.info());
}

TEST(descriptor, rocket) {
    descriptor::item::Rocket descr = descriptor::item::getNewRocket();
    descriptor::item::Rocket descr_copy(descr.data());

    compareBaseEquipmentDescriptors(descr, descr_copy);

    // descriptor::item::Rocket
    EXPECT_EQ(descr.descriptor(), descriptor::type::ROCKET_EQUIPMENT);
    EXPECT_EQ(descr.ammo(), descr_copy.ammo());
    EXPECT_EQ(descr.damage(), descr_copy.damage());
    EXPECT_EQ(descr.radius(), descr_copy.radius());

    // general
    EXPECT_EQ(descr.data(), descr_copy.data());
    EXPECT_EQ(descr.info(), descr_copy.info());
}

TEST(descriptor, scaner) {
    descriptor::item::Scaner descr = descriptor::item::getNewScaner();
    descriptor::item::Scaner descr_copy(descr.data());

    compareBaseEquipmentDescriptors(descr, descr_copy);

    // descriptor::item::Scaner
    EXPECT_EQ(descr.descriptor(), descriptor::type::SCANER_EQUIPMENT);
    EXPECT_EQ(descr.scan(), descr_copy.scan());

    // general
    EXPECT_EQ(descr.data(), descr_copy.data());
    EXPECT_EQ(descr.info(), descr_copy.info());
}

