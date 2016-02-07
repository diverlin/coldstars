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

#include <common/Global.hpp>

#include <slots/ItemSlot.hpp>
#include <spaceobjects/Ship.hpp>

#include <builder/spaceobjects/ShipBuilder.hpp>

#include <descriptors/Descriptor.hpp>
#include <descriptors/DescriptorGenerator.hpp>

#include <builder/items/IncludeItemBuilders.hpp>

#include <items/equipment/BakEquipment.hpp>
#include <items/equipment/DriveEquipment.hpp>
#include <items/equipment/DroidEquipment.hpp>
#include <items/equipment/GrappleEquipment.hpp>
#include <items/equipment/ScanerEquipment.hpp>
#include <items/equipment/RadarEquipment.hpp>
#include <items/equipment/ProtectorEquipment.hpp>

#include "helper.hpp"

TEST(equipment,bak)
{
    Ship* ship = createNewShip();
    BakEquipment* bak_equipment = global::get().bakBuilder().create(generateBakDescriptor());

    EXPECT_FALSE(ship->GetComplexDrive().GetBakSlot()->item() != nullptr);
    EXPECT_EQ(ship->GetProperties().hyper, 0);
    ship->manage(bak_equipment);
    EXPECT_TRUE(ship->GetComplexDrive().GetBakSlot()->item() != nullptr);
    EXPECT_EQ(ship->GetProperties().hyper, 0);
}

TEST(equipment,drive)
{
    Ship* ship = createNewShip();
    DriveEquipment* drive_equipment = global::get().driveBuilder().create(generateDriveDescriptor());

    EXPECT_FALSE(ship->GetComplexDrive().GetDriveSlot()->item() != nullptr);
    EXPECT_EQ(ship->GetProperties().hyper, 0);
    ship->manage(drive_equipment);
    EXPECT_TRUE(ship->GetComplexDrive().GetDriveSlot()->item() != nullptr);
    EXPECT_EQ(ship->GetProperties().hyper, 0);
}

TEST(equipment,bak_plus_drive)
{
    Ship* ship = createNewShip();
    BakEquipment* bak_equipment = global::get().bakBuilder().create(generateBakDescriptor());
    DriveEquipment* drive_equipment = global::get().driveBuilder().create(generateDriveDescriptor());

    EXPECT_EQ(ship->GetProperties().hyper, 0);
    ship->manage(bak_equipment);
    ship->manage(drive_equipment);
    EXPECT_EQ(ship->GetProperties().hyper, std::min(bak_equipment->fuel(), drive_equipment->hyper()));
}

TEST(equipment,droid)
{
    Ship* ship = createNewShip();
    DroidEquipment* droid_equipment = global::get().droidBuilder().create(generateDroidDescriptor());

    EXPECT_FALSE(ship->droidSlot()->item() != nullptr);
    ship->manage(droid_equipment);
    EXPECT_TRUE(ship->droidSlot()->item() != nullptr);
}

TEST(equipment,grapple)
{
    Ship* ship = createNewShip();
    GrappleEquipment* grapple_equipment = global::get().grappleBuilder().create(generateGrappleDescriptor());

    EXPECT_FALSE(ship->grappleSlot()->item() != nullptr);
    ship->manage(grapple_equipment);
    EXPECT_TRUE(ship->grappleSlot()->item() != nullptr);
}

TEST(equipment,scaner)
{
    Ship* ship = createNewShip();
    ScanerEquipment* scaner_equipment = global::get().scanerBuilder().create(generateScanerDescriptor());

    EXPECT_FALSE(ship->scanerSlot()->item() != nullptr);
    ship->manage(scaner_equipment);
    EXPECT_TRUE(ship->scanerSlot()->item() != nullptr);
}

TEST(equipment,radar)
{
    Ship* ship = createNewShip();
    RadarEquipment* radar_equipment = global::get().radarBuilder().create(generateRadarDescriptor());

    EXPECT_FALSE(ship->radarSlot()->item() != nullptr);
    ship->manage(radar_equipment);
    EXPECT_TRUE(ship->radarSlot()->item() != nullptr);
}

TEST(equipment,protector)
{
    Ship* ship = createNewShip();
    ProtectorEquipment* protector_equipment = global::get().protectorBuilder().create(generateProtectorDescriptor());

    EXPECT_FALSE(ship->GetComplexProtector().GetProtectorSlot()->item() != nullptr);
    ship->manage(protector_equipment);
    EXPECT_TRUE(ship->GetComplexProtector().GetProtectorSlot()->item() != nullptr);
}


//TEST(ship,equipment)
//{
//    // back test
////    EXPECT_FALSE(ship->GetComplexDrive().GetBakSlot()->item() != nullptr);
////    EXPECT_EQ(ship->GetProperties().hyper, 0);
////    int old_free_space = ship->GetProperties().free_space;
////    ship->manage(bak_equipment);
////    EXPECT_TRUE(ship->GetComplexDrive().GetBakSlot()->item() != nullptr);
////    EXPECT_EQ(ship->GetProperties().hyper, 0);
////    EXPECT_EQ(ship->GetProperties().free_space, old_free_space - bak_equipment->mass()); // to fix
////    //std::cout<<"old_free_space="<<old_free_space<<" "<<bak_equipment->mass();

//    // drive test
//    EXPECT_FALSE(ship->GetComplexDrive().GetDriveSlot()->item() != nullptr);
//    EXPECT_EQ(ship->GetProperties().hyper, 0);
//    ship->manage(drive_equipment);
//    old_free_space = ship->GetProperties().free_space;
//    EXPECT_TRUE(ship->GetComplexDrive().GetDriveSlot()->item() != nullptr);
//    EXPECT_EQ(ship->GetProperties().hyper, std::min(bak_equipment->fuel(), drive_equipment->hyper()));
//    EXPECT_EQ(ship->GetProperties().free_space, old_free_space - drive_equipment->mass());
//}
