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

//#include <core/common/Global.hpp>
//#include <core/common/constants.hpp>

//#include <core/slots/ItemSlot.hpp>
//#include <core/spaceobjects/Ship.hpp>

//#include <core/builder/spaceobjects/ShipBuilder.hpp>

//#include <core/descriptors/Base.hpp>
#include <core/descriptors/DescriptorGenerator.hpp>
//#include <core/descriptors/DescriptorManager.hpp>

//#include <core/builder/item/equipment/ALL>
//#include <core/builder/item/modules/ALL>
//#include <core/builder/item/artefacts//ALL>
//#include <core/builder/item/other/ALL>

#include <core/item/equipment/ALL>

//#include "helper.hpp"

#include <gtest/gtest.h>

//#include <fstream>

namespace {

void compareBaseEquipmentDescriptors(const descriptor::item::BaseEquipment& descr, const descriptor::item::BaseEquipment& descr_copy)
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

    // descriptor::item::Base
    EXPECT_EQ(descr.race(), descr_copy.race());
    EXPECT_EQ(descr.tech(), descr_copy.tech());
    EXPECT_EQ(descr.condition(), descr_copy.condition());
    EXPECT_EQ(descr.deterioration(), descr_copy.deterioration());
    EXPECT_EQ(descr.mass(), descr_copy.mass());
    EXPECT_EQ(descr.price(), descr_copy.price());

    // descriptor::item::BaseEquipment
    EXPECT_EQ(descr.modules(), descr_copy.modules());
}

} // namespace

TEST(descriptor, bak) {
    descriptor::item::Bak descr = descriptor::item::getNewBak();
    descriptor::item::Bak descr_copy(descr.data());

    compareBaseEquipmentDescriptors(descr, descr_copy);

    // descriptor::item::Bak
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
    EXPECT_EQ(descr.radius(), descr_copy.radius());

    // general
    EXPECT_EQ(descr.data(), descr_copy.data());
    EXPECT_EQ(descr.info(), descr_copy.info());
}

//void commonDataItemCheck(const descriptor::BaseOLD& descr, item::Base* item)
//{
//    //EXPECT_EQ(descr.id(), item->id()); // wrong
//    EXPECT_EQ(descr.type(), (int)item->descriptorType());
//    EXPECT_EQ(descr.race(), (int)item->race());
//    EXPECT_EQ(descr.tech(), (int)item->tech());
//    EXPECT_EQ(descr.modulesNum(), (int)item->modulesNum());
//    EXPECT_EQ(descr.deterioration(), (int)item->deterioration());
//    EXPECT_EQ(descr.mass(), item->mass());
//    EXPECT_EQ(descr.conditionMax(), item->condition());
//    EXPECT_EQ(descr.price(), item->basePrice());
//    //EXPECT_EQ(descr.parentSubTypeId(), (int)bak_equipment->parentSubTypeId());
//}

//TEST(creation,bak)
//{
//    const descriptor::BaseOLD& descr = core::global::get().descriptors().getRand(descriptor::Type::BAK);
//    item::Bak* bak = core::global::get().bakBuilder().getNew( descr );

//    EXPECT_EQ(descr.fuelMax(), bak->fuel());
//    EXPECT_EQ(descr.fuelMax(), bak->fuelMax());
//    commonDataItemCheck(descr, bak);

//    // clean
//    delete bak;
//}

//TEST(equipment, lazer)
//{
//    model::Ship* model = builder::Ship::getNew();
//    control::Ship* ship = new control::Ship(model);

//    item::Lazer* lazer = core::global::get().lazerBuilder().getNew();

//    // initial
//    EXPECT_EQ(0, ship->properties().total_damage);
//    EXPECT_EQ(0, ship->properties().fire_radius_min);
//    EXPECT_EQ(0, ship->properties().fire_radius_max);

//    // event: insert item
//    bool ok = ship->manage(lazer);
//    EXPECT_TRUE(ok);
//    EXPECT_EQ(lazer, ship->weaponComplex().equipedWeakestSlot()->item());
//    EXPECT_EQ(lazer->damage(), ship->properties().total_damage);
//    EXPECT_EQ(lazer->radius(), ship->properties().fire_radius_min);
//    EXPECT_EQ(lazer->radius(), ship->properties().fire_radius_max);

//    // clean
//    delete model;
//    delete ship;
//    delete lazer;
//}

//TEST(equipment, rocket)
//{
//    model::Ship* model = builder::Ship::getNew();
//    control::Ship* ship = new control::Ship(model);

//    item::Rocket* rocket = core::global::get().rocketBuilder().getNew();

//    // initial
//    EXPECT_EQ(0, ship->properties().total_damage);
//    EXPECT_EQ(0, ship->properties().fire_radius_min);
//    EXPECT_EQ(0, ship->properties().fire_radius_max);

//    // event: insert item
//    bool ok = ship->manage(rocket);
//    EXPECT_TRUE(ok);
//    EXPECT_EQ(rocket, ship->weaponComplex().equipedWeakestSlot()->item());
//    EXPECT_EQ(rocket->damage(), ship->properties().total_damage);
//    EXPECT_EQ(rocket->radius(), ship->properties().fire_radius_min);
//    EXPECT_EQ(rocket->radius(), ship->properties().fire_radius_max);

//    // clean
//    delete model;
//    delete ship;
//    delete rocket;
//}

//TEST(equipment, bak)
//{
//    model::Ship* model = builder::Ship::getNew();
//    control::Ship* ship = new control::Ship(model);

//    item::Bak* bak = core::global::get().bakBuilder().getNew();

//    // initial
//    EXPECT_TRUE(ship->driveComplex().bakSlot()->item() == nullptr);
//    EXPECT_EQ(0, ship->properties().hyper);

//    // event: insert item
//    bool ok = ship->manage(bak);
//    EXPECT_TRUE(ok);
//    EXPECT_EQ(bak, ship->driveComplex().bakSlot()->item());
//    EXPECT_EQ(0, ship->properties().hyper); // no drive is set, that's why hyper is 0

//    // clean
//    delete model;
//    delete ship;
//    delete bak;
//}

//TEST(equipment, drive)
//{
//    model::Ship* model = builder::Ship::getNew();
//    control::Ship* ship = new control::Ship(model);

//    item::Drive* drive = core::global::get().driveBuilder().getNew();

//    // initial
//    EXPECT_TRUE(ship->driveComplex().driveSlot()->item() == nullptr);
//    EXPECT_EQ(0, ship->properties().hyper);

//    // event: insert item
//    bool ok = ship->manage(drive);
//    EXPECT_TRUE(ok);
//    EXPECT_EQ(drive, ship->driveComplex().driveSlot()->item());
//    EXPECT_EQ(0, ship->properties().hyper); // no bak is set that's why hyper is 0

//    // clean
//    delete model;
//    delete ship;
//    delete drive;
//}

//TEST(equipment, bak_and_drive)
//{
//    model::Ship* model = builder::Ship::getNew();
//    control::Ship* ship = new control::Ship(model);

//    item::Bak* bak = core::global::get().bakBuilder().getNew();
//    item::Drive* drive = core::global::get().driveBuilder().getNew();

//    // initial
//    EXPECT_EQ(ship->properties().hyper, 0);

//    // event: insert items
//    bool ok1 = ship->manage(bak);
//    bool ok2 = ship->manage(drive);
//    // check
//    EXPECT_TRUE(ok1);
//    EXPECT_TRUE(ok2);
//    int hyper = std::min(bak->fuel(), drive->hyper());
//    EXPECT_EQ(hyper, ship->properties().hyper);

//    /// bak
//    // event: lock item
//    bak->doLock();
//    EXPECT_EQ(0, ship->properties().hyper);

//    // event: unlock item
//    bak->doUnlock();
//    EXPECT_EQ(hyper, ship->properties().hyper);

//    // event: damage item
//    bak->doBreak();
//    EXPECT_EQ(0, ship->properties().hyper);

//    // event: repair item
//    bak->doRepair();
//    EXPECT_EQ(hyper, ship->properties().hyper);

//    /// drive
//    // event: lock item
//    drive->doLock();
//    EXPECT_EQ(0, ship->properties().hyper);

//    // event: unlock item
//    drive->doUnlock();
//    EXPECT_EQ(hyper, ship->properties().hyper);

//    // event: damage item
//    drive->doBreak();
//    EXPECT_EQ(0, ship->properties().hyper);

//    // event: repair item
//    drive->doRepair();
//    EXPECT_EQ(hyper, ship->properties().hyper);

//    // clean
//    delete model;
//    delete ship;
//    delete bak;
//    delete drive;
//}

//TEST(equipment, droid)
//{
//    model::Ship* model = builder::Ship::getNew();
//    control::Ship* ship = new control::Ship(model);

//    item::Droid* droid = core::global::get().droidBuilder().getNew();

//    // initial
//    EXPECT_TRUE(ship->droidSlot()->item() == nullptr);
//    EXPECT_EQ(0, ship->properties().repair);

//    // event: item insert
//    bool ok = ship->manage(droid);
//    EXPECT_TRUE(ok);
//    EXPECT_EQ(droid, ship->droidSlot()->item());
//    EXPECT_EQ(droid->repair(), ship->properties().repair);

//    // event: lock item
//    droid->doLock();
//    EXPECT_EQ(0, ship->properties().repair);

//    // event: unlock item
//    droid->doUnlock();
//    EXPECT_EQ(droid->repair(), ship->properties().repair);

//    // event: damage item
//    droid->doBreak();
//    EXPECT_EQ(0, ship->properties().repair);

//    // event: repair item
//    droid->doRepair();
//    EXPECT_EQ(droid->repair(), ship->properties().repair);

//    // clean
//    delete model;
//    delete ship;
//    delete droid;
//}

//TEST(equipment, grapple)
//{
//    model::Ship* model = builder::Ship::getNew();
//    control::Ship* ship = new control::Ship(model);

//    item::Grapple* grapple = core::global::get().grappleBuilder().getNew();

//    // initial
//    EXPECT_TRUE(ship->grappleSlot()->item() == nullptr);
//    EXPECT_EQ(0, ship->properties().grab_strength);
//    EXPECT_EQ(0, ship->properties().grab_radius);

//    // event: item insert
//    bool ok = ship->manage(grapple);
//    EXPECT_TRUE(ok);
//    EXPECT_EQ(ship->grappleSlot()->item(), grapple);
//    EXPECT_EQ(grapple->strength(), ship->properties().grab_strength);
//    EXPECT_EQ(grapple->radius(), ship->properties().grab_radius);

//    // event: lock item
//    grapple->doLock();
//    EXPECT_EQ(0, ship->properties().grab_strength);
//    EXPECT_EQ(0, ship->properties().grab_radius);

//    // event: unlock item
//    grapple->doUnlock();
//    EXPECT_EQ(grapple->strength(), ship->properties().grab_strength);
//    EXPECT_EQ(grapple->radius(), ship->properties().grab_radius);

//    // event: damage item
//    grapple->doBreak();
//    EXPECT_EQ(0, ship->properties().grab_strength);
//    EXPECT_EQ(0, ship->properties().grab_radius);

//    // event: repair item
//    grapple->doRepair();
//    EXPECT_EQ(grapple->strength(), ship->properties().grab_strength);
//    EXPECT_EQ(grapple->radius(), ship->properties().grab_radius);

//    // clean
//    delete model;
//    delete ship;
//    delete grapple;
//}

//TEST(equipment, scaner)
//{
//    model::Ship* model = builder::Ship::getNew();
//    control::Ship* ship = new control::Ship(model);

//    item::Scaner* scaner = core::global::get().scanerBuilder().getNew();

//    // initial
//    EXPECT_TRUE(ship->scanerSlot()->item() == nullptr);
//    EXPECT_EQ(0, ship->properties().scan);

//    // item insert
//    bool ok = ship->manage(scaner);
//    EXPECT_TRUE(ok);
//    EXPECT_EQ(ship->scanerSlot()->item(), scaner);
//    EXPECT_EQ(scaner->scan(), ship->properties().scan);

//    // event: lock item
//    scaner->doLock();
//    EXPECT_EQ(0, ship->properties().scan);

//    // event: unlock item
//    scaner->doUnlock();
//    EXPECT_EQ(scaner->scan(), ship->properties().scan);

//    // event: damage item
//    scaner->doBreak();
//    EXPECT_EQ(0, ship->properties().scan);

//    // event: repair item
//    scaner->doRepair();
//    EXPECT_EQ(scaner->scan(), ship->properties().scan);

//    // clean
//    delete model;
//    delete ship;
//    delete scaner;
//}

//TEST(equipment, radar)
//{
//    model::Ship* model = builder::Ship::getNew();
//    control::Ship* ship = new control::Ship(model);

//    item::Radar* radar = core::global::get().radarBuilder().getNew();

//    // initial
//    EXPECT_TRUE(ship->radarSlot()->item() == nullptr);
//    EXPECT_EQ(VISIBLE_DISTANCE_WITHOUT_RADAR, ship->properties().radar);

//    // event: item insert
//    bool ok = ship->manage(radar);
//    EXPECT_TRUE(ok);
//    EXPECT_EQ(radar, ship->radarSlot()->item());
//    EXPECT_EQ(radar->radius(), ship->properties().radar);

//    // event: lock item
//    radar->doLock();
//    EXPECT_EQ(VISIBLE_DISTANCE_WITHOUT_RADAR, ship->properties().radar);

//    // event: unlock item
//    radar->doUnlock();
//    EXPECT_EQ(radar->radius(), ship->properties().radar);

//    // event: damage item
//    radar->doBreak();
//    EXPECT_EQ(VISIBLE_DISTANCE_WITHOUT_RADAR, ship->properties().radar);

//    // event: repair item
//    radar->doRepair();
//    EXPECT_EQ(radar->radius(), ship->properties().radar);

//    // clean
//    delete model;
//    delete ship;
//    delete radar;
//}

//TEST(equipment, protector)
//{
//    model::Ship* model = builder::Ship::getNew();
//    control::Ship* ship = new control::Ship(model);

//    item::Protector* protector = core::global::get().protectorBuilder().getNew();

//    // initial
//    EXPECT_TRUE(ship->protectorComplex().protectorSlot()->item() == nullptr);
//    EXPECT_EQ(ship->vehicleDescriptor().protection(), ship->properties().protection);

//    // event: item insert
//    bool ok = ship->manage(protector);
//    EXPECT_TRUE(ok);
//    EXPECT_EQ(protector, ship->protectorComplex().protectorSlot()->item());
//    int protection = ship->vehicleDescriptor().protection() + protector->protection();
//    EXPECT_EQ(protection, ship->properties().protection);

//    // event: lock item
//    protector->doLock();
//    EXPECT_EQ(ship->vehicleDescriptor().protection(), ship->properties().protection);

//    // event: unlock item
//    protector->doUnlock();
//    EXPECT_EQ(protection, ship->properties().protection);

//    // event: damage item
//    protector->doBreak();
//    EXPECT_EQ(ship->vehicleDescriptor().protection(), ship->properties().protection);

//    // event: repair item
//    protector->doRepair();
//    EXPECT_EQ(protection, ship->properties().protection);

//    // clean
//    delete model;
//    delete ship;
//    delete protector;
//}

//TEST(equipment, freespace)
//{
//    model::Ship* model = builder::Ship::getNew();
//    control::Ship* ship = new control::Ship(model);

//    // initial
//    EXPECT_EQ(ship->model()->mass(), ship->freeSpace());

//    // event: generate and insert item list
//    std::vector<item::Protector*> items = core::global::get().protectorBuilder().getNew(3);
//    int weight = 0;
//    for (auto item: items) {
//        weight += item->mass();
//        bool ok = ship->manage(item);
//        EXPECT_TRUE(ok);
//    }
//    // check space
//    EXPECT_EQ(ship->space() - weight, ship->freeSpace());
//    EXPECT_EQ(weight, ship->model()->mass());

//    // clean
//    delete model;
//    delete ship;
//    for (auto item: items) {
//        delete item;
//    }
//}

