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
#include <common/constants.hpp>

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
    //EXPECT_EQ(descr.id(), item->id()); // wrong
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
    item::equipment::Bak* bak = global::get().bakBuilder().getNew( descr );

    EXPECT_EQ(descr.fuelMax(), bak->fuel());
    EXPECT_EQ(descr.fuelMax(), bak->fuelMax());
    commonDataItemCheck(descr, bak);

    // clean
    delete bak;
}

TEST(equipment, lazer)
{
    Ship* ship = ShipBuilder::getNew();
    item::equipment::Lazer* lazer = global::get().lazerBuilder().getNew();

    // initial
    EXPECT_EQ(ship->properties().avr_damage, 0);
    EXPECT_EQ(ship->properties().avr_fire_radius, 0);

    // event: insert item
    bool ok = ship->manage(lazer);
    EXPECT_TRUE(ok);
    EXPECT_EQ(ship->properties().avr_damage, lazer->damage());
    EXPECT_EQ(ship->properties().avr_fire_radius, lazer->radius());

    // clean
    delete ship;
    delete lazer;
}

TEST(equipment, rocket)
{
    Ship* ship = ShipBuilder::getNew();
    item::equipment::Rocket* rocket = global::get().rocketBuilder().getNew();

    // initial
    EXPECT_EQ(ship->properties().avr_damage, 0);
    EXPECT_EQ(ship->properties().avr_fire_radius, 0);

    // event: insert item
    bool ok = ship->manage(rocket);
    EXPECT_TRUE(ok);
    EXPECT_EQ(ship->properties().avr_damage, rocket->damage());
    EXPECT_EQ(ship->properties().avr_fire_radius, rocket->radius());

    // clean
    delete ship;
    delete rocket;
}

TEST(equipment, bak)
{
    Ship* ship = ShipBuilder::getNew();
    item::equipment::Bak* bak = global::get().bakBuilder().getNew();

    // initial
    EXPECT_TRUE(ship->driveComplex().bakSlot()->item() == nullptr);
    EXPECT_EQ(ship->properties().hyper, 0);

    // event: insert item
    bool ok = ship->manage(bak);
    EXPECT_TRUE(ok);
    EXPECT_EQ(ship->driveComplex().bakSlot()->item(), bak);
    EXPECT_EQ(ship->properties().hyper, 0); // no drive is set, that's why hyper is 0

    // clean
    delete ship;
    delete bak;
}

TEST(equipment, drive)
{
    Ship* ship = ShipBuilder::getNew();
    item::equipment::Drive* drive = global::get().driveBuilder().getNew();

    // initial
    EXPECT_TRUE(ship->driveComplex().driveSlot()->item() == nullptr);
    EXPECT_EQ(ship->properties().hyper, 0);

    // event: insert item
    bool ok = ship->manage(drive);
    EXPECT_TRUE(ok);
    EXPECT_EQ(ship->driveComplex().driveSlot()->item(), drive);
    EXPECT_EQ(ship->properties().hyper, 0); // no bak is set that's why hyper is 0

    // clean
    delete ship;
    delete drive;
}

TEST(equipment, bak_and_drive)
{
    Ship* ship = ShipBuilder::getNew();
    item::equipment::Bak* bak = global::get().bakBuilder().getNew();
    item::equipment::Drive* drive = global::get().driveBuilder().getNew();

    // initial
    EXPECT_EQ(ship->properties().hyper, 0);

    // event: insert items
    bool ok1 = ship->manage(bak);
    bool ok2 = ship->manage(drive);
    // check
    EXPECT_TRUE(ok1);
    EXPECT_TRUE(ok2);
    int hyper = std::min(bak->fuel(), drive->hyper());
    EXPECT_EQ(ship->properties().hyper, hyper);

    /// bak
    // event: lock item
    bak->doLock();
    EXPECT_EQ(ship->properties().hyper, 0);

    // event: unlock item
    bak->doUnlock();
    EXPECT_EQ(ship->properties().hyper, hyper);

    // event: damage item
    bak->doBreak();
    EXPECT_EQ(ship->properties().hyper, 0);

    // event: repair item
    bak->doRepair();
    EXPECT_EQ(ship->properties().hyper, hyper);

    /// drive
    // event: lock item
    drive->doLock();
    EXPECT_EQ(ship->properties().hyper, 0);

    // event: unlock item
    drive->doUnlock();
    EXPECT_EQ(ship->properties().hyper, hyper);

    // event: damage item
    drive->doBreak();
    EXPECT_EQ(ship->properties().hyper, 0);

    // event: repair item
    drive->doRepair();
    EXPECT_EQ(ship->properties().hyper, hyper);

    // clean
    delete ship;
    delete bak;
    delete drive;
}

TEST(equipment, droid)
{
    Ship* ship = ShipBuilder::getNew();
    item::equipment::Droid* droid = global::get().droidBuilder().getNew();

    // initial
    EXPECT_TRUE(ship->droidSlot()->item() == nullptr);
    EXPECT_EQ(ship->properties().repair, 0);

    // event: item insert
    bool ok = ship->manage(droid);
    EXPECT_TRUE(ok);
    EXPECT_EQ(ship->droidSlot()->item(), droid);
    EXPECT_EQ(ship->properties().repair, droid->repair());

    // event: lock item
    droid->doLock();
    EXPECT_EQ(ship->properties().repair, 0);

    // event: unlock item
    droid->doUnlock();
    EXPECT_EQ(ship->properties().repair, droid->repair());

    // event: damage item
    droid->doBreak();
    EXPECT_EQ(ship->properties().repair, 0);

    // event: repair item
    droid->doRepair();
    EXPECT_EQ(ship->properties().repair, droid->repair());

    // clean
    delete ship;
    delete droid;
}

TEST(equipment, grapple)
{
    Ship* ship = ShipBuilder::getNew();
    item::equipment::Grapple* grapple = global::get().grappleBuilder().getNew();

    // initial
    EXPECT_TRUE(ship->grappleSlot()->item() == nullptr);
    EXPECT_EQ(ship->properties().grab_strength, 0);
    EXPECT_EQ(ship->properties().grab_radius, 0);

    // event: item insert
    bool ok = ship->manage(grapple);
    EXPECT_TRUE(ok);
    EXPECT_EQ(ship->grappleSlot()->item(), grapple);
    EXPECT_EQ(ship->properties().grab_strength, grapple->strength());
    EXPECT_EQ(ship->properties().grab_radius, grapple->radius());

    // event: lock item
    grapple->doLock();
    EXPECT_EQ(ship->properties().grab_strength, 0);
    EXPECT_EQ(ship->properties().grab_radius, 0);

    // event: unlock item
    grapple->doUnlock();
    EXPECT_EQ(ship->properties().grab_strength, grapple->strength());
    EXPECT_EQ(ship->properties().grab_radius, grapple->radius());

    // event: damage item
    grapple->doBreak();
    EXPECT_EQ(ship->properties().grab_strength, 0);
    EXPECT_EQ(ship->properties().grab_radius, 0);

    // event: repair item
    grapple->doRepair();
    EXPECT_EQ(ship->properties().grab_strength, grapple->strength());
    EXPECT_EQ(ship->properties().grab_radius, grapple->radius());

    // clean
    delete ship;
    delete grapple;
}

TEST(equipment, scaner)
{
    Ship* ship = ShipBuilder::getNew();
    item::equipment::Scaner* scaner = global::get().scanerBuilder().getNew();

    // initial
    EXPECT_TRUE(ship->scanerSlot()->item() == nullptr);
    EXPECT_EQ(ship->properties().scan, 0);

    // item insert
    bool ok = ship->manage(scaner);
    EXPECT_TRUE(ok);
    EXPECT_EQ(ship->scanerSlot()->item(), scaner);
    EXPECT_EQ(ship->properties().scan, scaner->scan());

    // event: lock item
    scaner->doLock();
    EXPECT_EQ(ship->properties().scan, 0);

    // event: unlock item
    scaner->doUnlock();
    EXPECT_EQ(ship->properties().scan, scaner->scan());

    // event: damage item
    scaner->doBreak();
    EXPECT_EQ(ship->properties().scan, 0);

    // event: repair item
    scaner->doRepair();
    EXPECT_EQ(ship->properties().scan, scaner->scan());

    // clean
    delete ship;
    delete scaner;
}

TEST(equipment, radar)
{
    Ship* ship = ShipBuilder::getNew();
    item::equipment::Radar* radar = global::get().radarBuilder().getNew();

    // initial
    EXPECT_TRUE(ship->radarSlot()->item() == nullptr);
    EXPECT_EQ(ship->properties().radar, VISIBLE_DISTANCE_WITHOUT_RADAR);

    // event: item insert
    bool ok = ship->manage(radar);
    EXPECT_TRUE(ok);
    EXPECT_EQ(ship->radarSlot()->item(), radar);
    EXPECT_EQ(ship->properties().radar, radar->radius());

    // event: lock item
    radar->doLock();
    EXPECT_EQ(ship->properties().radar, VISIBLE_DISTANCE_WITHOUT_RADAR);

    // event: unlock item
    radar->doUnlock();
    EXPECT_EQ(ship->properties().radar, radar->radius());

    // event: damage item
    radar->doBreak();
    EXPECT_EQ(ship->properties().radar, VISIBLE_DISTANCE_WITHOUT_RADAR);

    // event: repair item
    radar->doRepair();
    EXPECT_EQ(ship->properties().radar, radar->radius());

    // clean
    delete ship;
    delete radar;
}

TEST(equipment, protector)
{
    Ship* ship = ShipBuilder::getNew();
    item::equipment::Protector* protector = global::get().protectorBuilder().getNew();

    // initial
    EXPECT_TRUE(ship->protectorComplex().protectorSlot()->item() == nullptr);
    EXPECT_EQ(ship->properties().protection, ship->vehicleDescriptor().protection);

    // event: item insert
    bool ok = ship->manage(protector);
    EXPECT_TRUE(ok);
    EXPECT_EQ(ship->protectorComplex().protectorSlot()->item(), protector);
    int protection = ship->vehicleDescriptor().protection + protector->protection();
    EXPECT_EQ(ship->properties().protection, protection);

    // event: lock item
    protector->doLock();
    EXPECT_EQ(ship->properties().protection, ship->vehicleDescriptor().protection);

    // event: unlock item
    protector->doUnlock();
    EXPECT_EQ(ship->properties().protection, protection);

    // event: damage item
    protector->doBreak();
    EXPECT_EQ(ship->properties().protection, ship->vehicleDescriptor().protection);

    // event: repair item
    protector->doRepair();
    EXPECT_EQ(ship->properties().protection, protection);

    // clean
    delete ship;
    delete protector;
}

TEST(equipment, freespace)
{
    Ship* ship = ShipBuilder::getNew();

    // initial
    EXPECT_EQ(ship->mass(), ship->freeSpace());

    // event: generate and insert item list
    std::vector<item::equipment::Protector*> items = global::get().protectorBuilder().getNew(3);
    int weight = 0;
    for (auto item: items) {
        weight += item->mass();
        bool ok = ship->manage(item);
        EXPECT_TRUE(ok);
    }
    // check space
    EXPECT_EQ(ship->freeSpace(), ship->space() - weight);
    EXPECT_EQ(ship->mass(), weight);

    // clean
    delete ship;
    for (auto item: items) {
        delete item;
    }
}

