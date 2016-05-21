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

#include <descriptors/Base.hpp>
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

    EXPECT_TRUE(ship->GetComplexDrive().GetBakSlot() != nullptr);
    EXPECT_TRUE(ship->GetComplexDrive().GetBakSlot()->item() == nullptr);
    EXPECT_EQ(ship->GetProperties().hyper, 0);
    ship->manage(bak_equipment);
    EXPECT_TRUE(ship->GetComplexDrive().GetBakSlot()->item() != nullptr);
    EXPECT_EQ(ship->GetProperties().hyper, 0);
}

TEST(equipment,drive)
{
    Ship* ship = createNewShip();
    DriveEquipment* drive_equipment = global::get().driveBuilder().create(generateDriveDescriptor());

    EXPECT_TRUE(ship->GetComplexDrive().GetDriveSlot() != nullptr);
    EXPECT_TRUE(ship->GetComplexDrive().GetDriveSlot()->item() == nullptr);
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

    EXPECT_TRUE(ship->slotDroid()->item() == nullptr);
    ship->manage(droid_equipment);
    EXPECT_TRUE(ship->slotDroid()->item() != nullptr);
}

TEST(equipment,grapple)
{
    Ship* ship = createNewShip();
    GrappleEquipment* grapple_equipment = global::get().grappleBuilder().create(generateGrappleDescriptor());

    EXPECT_TRUE(ship->slotGrapple()->item() == nullptr);
    ship->manage(grapple_equipment);
    EXPECT_TRUE(ship->slotGrapple()->item() != nullptr);
}

TEST(equipment,scaner)
{
    Ship* ship = createNewShip();
    ScanerEquipment* scaner_equipment = global::get().scanerBuilder().create(generateScanerDescriptor());

    EXPECT_TRUE(ship->slotScaner()->item() == nullptr);
    ship->manage(scaner_equipment);
    EXPECT_TRUE(ship->slotScaner()->item() != nullptr);
}

TEST(equipment,radar)
{
    Ship* ship = createNewShip();
    RadarEquipment* radar_equipment = global::get().radarBuilder().create(generateRadarDescriptor());

    EXPECT_TRUE(ship->slotRadar()->item() == nullptr);
    ship->manage(radar_equipment);
    EXPECT_TRUE(ship->slotRadar()->item() != nullptr);
}

TEST(equipment,protector)
{
    Ship* ship = createNewShip();
    ProtectorEquipment* protector_equipment = global::get().protectorBuilder().create(generateProtectorDescriptor());

    EXPECT_TRUE(ship->GetComplexProtector().GetProtectorSlot()->item() == nullptr);
    ship->manage(protector_equipment);
    EXPECT_TRUE(ship->GetComplexProtector().GetProtectorSlot()->item() != nullptr);
}

TEST(equipment,freespace)
{
    Ship* ship = createNewShip();

    std::vector<BaseItem*> items;
    items.push_back( global::get().protectorBuilder().create(generateProtectorDescriptor()) );
    items.push_back( global::get().protectorBuilder().create(generateProtectorDescriptor()) );
    items.push_back( global::get().protectorBuilder().create(generateProtectorDescriptor()) );

    EXPECT_TRUE(ship->mass() == ship->free_space());

    int weight_extra = 0;
    for (auto item: items) {
        weight_extra += item->mass();
        ship->manage(item);
    }

    EXPECT_TRUE(ship->free_space() - (ship->mass() + weight_extra));
}

