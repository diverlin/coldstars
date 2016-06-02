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
#include <descriptors/DescriptorManager.hpp>

#include <builder/item/IncludeItemBuilders.hpp>

#include <item/equipment/ALL>

#include "helper.hpp"

#include <fstream>

void commonDataItemCheck(const descriptor::Base& descr, item::Base* item)
{
    EXPECT_EQ(descr.id(), item->id());
    EXPECT_EQ(descr.type(), (int)item->descriptorType());
    EXPECT_EQ(descr.race(), (int)item->race());
    EXPECT_EQ(descr.tech(), (int)item->tech());
    EXPECT_EQ(descr.modulesNum(), (int)item->modulesNum());
    EXPECT_EQ(descr.deterioration(), (int)item->deterioration());
    EXPECT_EQ(descr.mass(), item->mass());
    EXPECT_EQ(descr.conditionMax(), item->condition());
    EXPECT_EQ(descr.price(), item->basePrice());
    //EXPECT_EQ(descr.parentSubTypeId(), (int)bak_equipment->parentSubTypeId());
}

TEST(equipment,bak)
{
    const descriptor::Base& descr = global::get().descriptorManager().getRandom(descriptor::Type::BAK);
    item::equipment::Bak* bak_equipment = global::get().bakBuilder().create( descr );

    EXPECT_EQ(descr.fuelMax(), bak_equipment->fuel());
    EXPECT_EQ(descr.fuelMax(), bak_equipment->fuelMax());
    commonDataItemCheck(descr, bak_equipment);
}

TEST(descriptor,general)
{
    global::get();
    //EXPECT_EQ(global::get().descriptorManager().size());
//    std::string fname = "data.txt";
//    std::fstream filestream;
//    filestream.open(fname);
//    if(filestream.is_open()) {
//        for(int i=0; i<10; ++i) {
//            const descriptor::Base& descr = DescriptorGenerator::getNewBakDescriptor();
//            global::get().descriptorManager().add(descr);
//            filestream<<descr.data()<<std::endl;
//        }
//    } else {
//        throw std::runtime_error("not able to open file="+fname);
//    }
//    filestream.close();

//    std::string line;
//    filestream.open(fname);
//    if(filestream.is_open()) {
//        while(std::getline(filestream, line)) {
//            if (!line.empty()) {
//                const descriptor::Base& descr = descriptor::Base(line);
//                global::get().descriptorManager().add(descr);
//            }
//        }
//    }
//    filestream.close();
}

TEST(ship_with_equipment, bak)
{
    Ship* ship = createNewShip();
    item::equipment::Bak* bak_equipment = global::get().bakBuilder().create( global::get().descriptorManager().getRandom(descriptor::Type::BAK) );

    EXPECT_TRUE(ship->GetComplexDrive().GetBakSlot() != nullptr);
    EXPECT_TRUE(ship->GetComplexDrive().GetBakSlot()->item() == nullptr);
    EXPECT_EQ(ship->properties().hyper, 0);
    ship->manage(bak_equipment);
    EXPECT_TRUE(ship->GetComplexDrive().GetBakSlot()->item() != nullptr);
    EXPECT_EQ(ship->properties().hyper, 0); // no drive is set, that's why hyper is 0
}

TEST(ship_with_equipment, drive)
{
    Ship* ship = createNewShip();
    item::equipment::Drive* drive_equipment = global::get().driveBuilder().create( global::get().descriptorManager().getRandom(descriptor::Type::DRIVE) );

    EXPECT_TRUE(ship->GetComplexDrive().GetDriveSlot() != nullptr);
    EXPECT_TRUE(ship->GetComplexDrive().GetDriveSlot()->item() == nullptr);
    EXPECT_EQ(ship->properties().hyper, 0);
    ship->manage(drive_equipment);
    EXPECT_TRUE(ship->GetComplexDrive().GetDriveSlot()->item() != nullptr);
    EXPECT_EQ(ship->properties().hyper, 0); // no bak is set that's why hyper is 0
}

TEST(ship_with_equipment, bak_and_drive)
{
    Ship* ship = createNewShip();
    item::equipment::Bak* bak_equipment = global::get().bakBuilder().create( global::get().descriptorManager().getRandom(descriptor::Type::BAK) );
    item::equipment::Drive* drive_equipment = global::get().driveBuilder().create( global::get().descriptorManager().getRandom(descriptor::Type::DRIVE) );

    EXPECT_EQ(ship->properties().hyper, 0);
    ship->manage(bak_equipment);
    ship->manage(drive_equipment);
    EXPECT_EQ(ship->properties().hyper, std::min(bak_equipment->fuel(), drive_equipment->hyper()));
}

TEST(ship_with_equipment, droid)
{
    Ship* ship = createNewShip();
    item::equipment::Droid* droid_equipment = global::get().droidBuilder().create( global::get().descriptorManager().getRandom(descriptor::Type::DROID) );

    EXPECT_TRUE(ship->slotDroid()->item() == nullptr);
    ship->manage(droid_equipment);
    EXPECT_TRUE(ship->slotDroid()->item() != nullptr);
}

TEST(ship_with_equipment, grapple)
{
    Ship* ship = createNewShip();
    item::equipment::Grapple* grapple_equipment = global::get().grappleBuilder().create( global::get().descriptorManager().getRandom(descriptor::Type::GRAPPLE) );

    EXPECT_TRUE(ship->slotGrapple()->item() == nullptr);
    ship->manage(grapple_equipment);
    EXPECT_TRUE(ship->slotGrapple()->item() != nullptr);
}

TEST(ship_with_equipment, scaner)
{
    Ship* ship = createNewShip();
    item::equipment::Scaner* scaner_equipment = global::get().scanerBuilder().create( global::get().descriptorManager().getRandom(descriptor::Type::SCANER) );

    EXPECT_TRUE(ship->slotScaner()->item() == nullptr);
    ship->manage(scaner_equipment);
    EXPECT_TRUE(ship->slotScaner()->item() != nullptr);
}

TEST(ship_with_equipment, radar)
{
    Ship* ship = createNewShip();
    item::equipment::Radar* radar_equipment = global::get().radarBuilder().create( global::get().descriptorManager().getRandom(descriptor::Type::RADAR) );

    EXPECT_TRUE(ship->slotRadar()->item() == nullptr);
    ship->manage(radar_equipment);
    EXPECT_TRUE(ship->slotRadar()->item() != nullptr);
}

TEST(ship_with_equipment, protector)
{
    Ship* ship = createNewShip();
    item::equipment::Protector* protector_equipment = global::get().protectorBuilder().create( global::get().descriptorManager().getRandom(descriptor::Type::PROTECTOR) );

    EXPECT_TRUE(ship->GetComplexProtector().GetProtectorSlot()->item() == nullptr);
    ship->manage(protector_equipment);
    EXPECT_TRUE(ship->GetComplexProtector().GetProtectorSlot()->item() != nullptr);
}

TEST(ship_with_equipment, freespace)
{
    Ship* ship = createNewShip();

    std::vector<item::Base*> items;
    items.push_back( global::get().protectorBuilder().create( global::get().descriptorManager().getRandom(descriptor::Type::PROTECTOR) ) );
    items.push_back( global::get().protectorBuilder().create( global::get().descriptorManager().getRandom(descriptor::Type::PROTECTOR) ) );
    items.push_back( global::get().protectorBuilder().create( global::get().descriptorManager().getRandom(descriptor::Type::PROTECTOR) ) );

    EXPECT_EQ(ship->mass(), ship->freeSpace());

    int weight_extra = 0;
    for (auto item: items) {
        weight_extra += item->mass();
        ship->manage(item);
    }

    EXPECT_EQ(ship->freeSpace(), ship->mass() - weight_extra);
}

