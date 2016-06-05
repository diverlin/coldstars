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

#include <builder/item/equipment/ALL>
#include <builder/item/modules/ALL>
#include <builder/item/artefacts//ALL>
#include <builder/item/other/ALL>

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

TEST(creation,bak)
{
    const descriptor::Base& descr = global::get().descriptors().getRand(descriptor::Type::BAK);
    item::equipment::Bak* bak_equipment = global::get().bakBuilder().getNew( descr );

    EXPECT_EQ(descr.fuelMax(), bak_equipment->fuel());
    EXPECT_EQ(descr.fuelMax(), bak_equipment->fuelMax());
    commonDataItemCheck(descr, bak_equipment);
}

TEST(equipment, bak)
{
    Ship* ship = createNewShip();
    item::equipment::Bak* bak_equipment = global::get().bakBuilder().getNew();

    EXPECT_TRUE(ship->driveComplex().GetBakSlot() != nullptr);
    EXPECT_TRUE(ship->driveComplex().GetBakSlot()->item() == nullptr);
    EXPECT_EQ(ship->properties().hyper, 0);
    ship->manage(bak_equipment);
    EXPECT_TRUE(ship->driveComplex().GetBakSlot()->item() != nullptr);
    EXPECT_EQ(ship->properties().hyper, 0); // no drive is set, that's why hyper is 0
}

TEST(equipment, drive)
{
    Ship* ship = createNewShip();
    item::equipment::Drive* drive_equipment = global::get().driveBuilder().getNew();

    EXPECT_TRUE(ship->driveComplex().GetDriveSlot() != nullptr);
    EXPECT_TRUE(ship->driveComplex().GetDriveSlot()->item() == nullptr);
    EXPECT_EQ(ship->properties().hyper, 0);
    ship->manage(drive_equipment);
    EXPECT_TRUE(ship->driveComplex().GetDriveSlot()->item() != nullptr);
    EXPECT_EQ(ship->properties().hyper, 0); // no bak is set that's why hyper is 0
}

TEST(equipment, bak_and_drive)
{
    Ship* ship = createNewShip();
    item::equipment::Bak* bak_equipment = global::get().bakBuilder().getNew();
    item::equipment::Drive* drive_equipment = global::get().driveBuilder().getNew();

    EXPECT_EQ(ship->properties().hyper, 0);
    ship->manage(bak_equipment);
    ship->manage(drive_equipment);
    EXPECT_EQ(ship->properties().hyper, std::min(bak_equipment->fuel(), drive_equipment->hyper()));
}

TEST(equipment, droid)
{
    Ship* ship = createNewShip();
    item::equipment::Droid* droid_equipment = global::get().droidBuilder().getNew();

    EXPECT_TRUE(ship->droidSlot()->item() == nullptr);
    ship->manage(droid_equipment);
    EXPECT_TRUE(ship->droidSlot()->item() != nullptr);
}

TEST(equipment, grapple)
{
    Ship* ship = createNewShip();
    item::equipment::Grapple* grapple_equipment = global::get().grappleBuilder().getNew();

    EXPECT_TRUE(ship->grappleSlot()->item() == nullptr);
    ship->manage(grapple_equipment);
    EXPECT_TRUE(ship->grappleSlot()->item() != nullptr);
}

TEST(equipment, scaner)
{
    Ship* ship = createNewShip();
    item::equipment::Scaner* scaner_equipment = global::get().scanerBuilder().getNew();

    EXPECT_TRUE(ship->scanerSlot()->item() == nullptr);
    ship->manage(scaner_equipment);
    EXPECT_TRUE(ship->scanerSlot()->item() != nullptr);
}

TEST(equipment, radar)
{
    Ship* ship = createNewShip();
    item::equipment::Radar* radar_equipment = global::get().radarBuilder().getNew();

    EXPECT_TRUE(ship->radarSlot()->item() == nullptr);
    ship->manage(radar_equipment);
    EXPECT_TRUE(ship->radarSlot()->item() != nullptr);
}

TEST(equipment, protector)
{
    Ship* ship = createNewShip();
    item::equipment::Protector* protector_equipment = global::get().protectorBuilder().getNew();

    EXPECT_TRUE(ship->protectorComplex().GetProtectorSlot()->item() == nullptr);
    ship->manage(protector_equipment);
    EXPECT_TRUE(ship->protectorComplex().GetProtectorSlot()->item() != nullptr);
}

TEST(equipment, freespace)
{
    Ship* ship = createNewShip();

    std::vector<item::equipment::Protector*> items = global::get().protectorBuilder().getNew(3);
    EXPECT_EQ(ship->mass(), ship->freeSpace());

    int weight_extra = 0;
    for (auto item: items) {
        weight_extra += item->mass();
        ship->manage(item);
    }

    EXPECT_EQ(ship->freeSpace(), ship->space() - weight_extra);
    EXPECT_EQ(weight_extra, ship->mass());
}

