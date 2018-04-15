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

#include "helper.hpp"

#include <core/builder/spaceobject/ShipBuilder.hpp>
#include <core/descriptor/spaceobject/Ship.hpp>
#include <core/model/spaceobject/Ship.hpp>
#include <core/spaceobject/Ship.hpp>

#include <core/builder/item/equipment/ALL>
#include <core/descriptor/item/equipment/ALL>
#include <core/model/item/equipment/ALL>
#include <core/item/equipment/ALL>

#include <core/slot/ItemSlot.hpp>

#include <gtest/gtest.h>


TEST(vehicle, item_lazer)
{
    core::control::Ship* ship = core::ShipBuilder::gen();
    core::control::Lazer* lazer = core::LazerItemBuilder::gen();

    assert(ship->weaponSlots().front());

    // init
    EXPECT_EQ(nullptr, ship->weaponSlots().front()->item());
    EXPECT_EQ(0, ship->properties().total_damage);
    EXPECT_EQ(0, ship->properties().fire_radius_min);
    EXPECT_EQ(0, ship->properties().fire_radius_max);

    // event: insert item
    EXPECT_TRUE(ship->manage(lazer));
    EXPECT_EQ(lazer, ship->weaponSlots().front()->item());
    EXPECT_EQ(lazer->model()->damage(), ship->properties().total_damage);
    EXPECT_EQ(lazer->model()->radius(), ship->properties().fire_radius_min);
    EXPECT_EQ(lazer->model()->radius(), ship->properties().fire_radius_max);
}

TEST(vehicle, item_rocket)
{
    core::control::Ship* ship = core::ShipBuilder::gen();
    core::control::Rocket* rocket = core::RocketItemBuilder::gen();

    assert(ship->weaponSlots().front());

    // init
    EXPECT_EQ(nullptr, ship->weaponSlots().front()->item());
    EXPECT_EQ(0, ship->properties().total_damage);
    EXPECT_EQ(0, ship->properties().fire_radius_min);
    EXPECT_EQ(0, ship->properties().fire_radius_max);

    // event: insert item
    EXPECT_TRUE(ship->manage(rocket));
    EXPECT_EQ(rocket, ship->weaponSlots().front()->item());
    EXPECT_EQ(rocket->model()->damage(), ship->properties().total_damage);
    EXPECT_EQ(rocket->model()->radius(), ship->properties().fire_radius_min);
    EXPECT_EQ(rocket->model()->radius(), ship->properties().fire_radius_max);
}

TEST(vehicle, item_bak)
{
    core::control::Ship* ship = core::ShipBuilder::gen();
    core::control::Bak* bak = core::BakItemBuilder::gen();

    assert(ship->bakSlots().front());

    // init
    EXPECT_EQ(nullptr, ship->bakSlots().front()->item());
    EXPECT_EQ(0, ship->properties().hyper);

    // insert
    EXPECT_TRUE(ship->manage(bak));
    EXPECT_EQ(bak, ship->bakSlots().front()->item());

    // post
    EXPECT_EQ(0, ship->properties().hyper); // no drive is set, that's why hyper is 0
}

TEST(vehicle, item_drive)
{
    core::control::Ship* ship = core::ShipBuilder::gen();
    core::control::Drive* drive = core::DriveItemBuilder::gen();

    assert(ship->driveSlots().front());

    // init
    EXPECT_EQ(nullptr, ship->driveSlots().front()->item());
    EXPECT_EQ(0, ship->properties().hyper);

    // insert
    EXPECT_TRUE(ship->manage(drive));
    EXPECT_EQ(drive, ship->driveSlots().front()->item());

    // post
    EXPECT_EQ(0, ship->properties().hyper); // no bak is set that's why hyper is 0
}

TEST(vehicle, item_bak_and_drive)
{
    auto ship = core::ShipBuilder::gen();
    auto bak = core::BakItemBuilder::gen();
    auto drive = core::DriveItemBuilder::gen();

    assert(ship->bakSlots().front());
    assert(ship->driveSlots().front());

    // init
    EXPECT_EQ(0, ship->properties().hyper);

    // insert
    EXPECT_TRUE(ship->manage(bak));
    EXPECT_TRUE(ship->manage(drive));
    int hyper = std::min(bak->model()->fuel(), drive->model()->hyper());
    EXPECT_EQ(hyper, ship->properties().hyper);

    /// bak
    // event: lock item
    bak->lock();
    EXPECT_EQ(0, ship->properties().hyper);

    // event: unlock item
    bak->unlock();
    EXPECT_EQ(hyper, ship->properties().hyper);

    // event: damage item
    bak->corrupt();
    EXPECT_EQ(0, ship->properties().hyper);

    // event: repair item
    bak->repair();
    EXPECT_EQ(hyper, ship->properties().hyper);

    /// drive
    // event: lock item
    drive->lock();
    EXPECT_EQ(0, ship->properties().hyper);

    // event: unlock item
    drive->unlock();
    EXPECT_EQ(hyper, ship->properties().hyper);

    // event: damage item
    drive->corrupt();
    EXPECT_EQ(0, ship->properties().hyper);

    // event: repair item
    drive->repair();
    EXPECT_EQ(hyper, ship->properties().hyper);
}

TEST(vehicle, item_droid)
{
    auto ship = core::ShipBuilder::gen();
    auto droid = core::DroidItemBuilder::gen();

    assert(ship->droidSlots().front());

    // initial
    EXPECT_EQ(nullptr, ship->droidSlots().front()->item());
    EXPECT_EQ(0, ship->properties().repair);

    // event: item insert
    EXPECT_TRUE(ship->manage(droid));
    EXPECT_EQ(droid->model()->repair(), ship->properties().repair);
    EXPECT_EQ(droid, ship->droidSlots().front()->item());

    // event: lock item
    droid->lock();
    EXPECT_EQ(0, ship->properties().repair);

    // event: unlock item
    droid->unlock();
    EXPECT_EQ(droid->model()->repair(), ship->properties().repair);

    // event: damage item
    droid->corrupt();
    EXPECT_EQ(0, ship->properties().repair);

    // event: repair item
    droid->repair();
    EXPECT_EQ(droid->model()->repair(), ship->properties().repair);
}

TEST(vehicle, item_grapple)
{
    auto ship = core::ShipBuilder::gen();
    auto grapple = core::GrappleItemBuilder::gen();

    assert(ship->grappleSlots().front());

    // initial
    EXPECT_EQ(nullptr, ship->grappleSlots().front()->item());
    EXPECT_EQ(0, ship->properties().grab_strength);
    EXPECT_EQ(0, ship->properties().grab_radius);

    // event: item insert
    EXPECT_TRUE(ship->manage(grapple));
    EXPECT_EQ(grapple, ship->grappleSlots().front()->item());
    EXPECT_EQ(grapple->model()->strength(), ship->properties().grab_strength);
    EXPECT_EQ(grapple->model()->radius(), ship->properties().grab_radius);

    // event: lock item
    grapple->lock();
    EXPECT_EQ(0, ship->properties().grab_strength);
    EXPECT_EQ(0, ship->properties().grab_radius);

    // event: unlock item
    grapple->unlock();
    EXPECT_EQ(grapple->model()->strength(), ship->properties().grab_strength);
    EXPECT_EQ(grapple->model()->radius(), ship->properties().grab_radius);

    // event: damage item
    grapple->corrupt();
    EXPECT_EQ(0, ship->properties().grab_strength);
    EXPECT_EQ(0, ship->properties().grab_radius);

    // event: repair item
    grapple->repair();
    EXPECT_EQ(grapple->model()->strength(), ship->properties().grab_strength);
    EXPECT_EQ(grapple->model()->radius(), ship->properties().grab_radius);
}

TEST(vehicle, item_scaner)
{
    auto ship = core::ShipBuilder::gen();
    auto scaner = core::ScanerItemBuilder::gen();

    assert(ship->scanerSlots().front());

    // initial
    EXPECT_EQ(nullptr, ship->scanerSlots().front()->item());
    EXPECT_EQ(0, ship->properties().scan);

    // item insert
    EXPECT_TRUE(ship->manage(scaner));
    EXPECT_EQ(scaner, ship->scanerSlots().front()->item());
    EXPECT_EQ(scaner->model()->scan(), ship->properties().scan);

    // event: lock item
    scaner->lock();
    EXPECT_EQ(0, ship->properties().scan);

    // event: unlock item
    scaner->unlock();
    EXPECT_EQ(scaner->model()->scan(), ship->properties().scan);

    // event: damage item
    scaner->corrupt();
    EXPECT_EQ(0, ship->properties().scan);

    // event: repair item
    scaner->repair();
    EXPECT_EQ(scaner->model()->scan(), ship->properties().scan);
}

TEST(vehicle, item_radar)
{
    auto ship = core::ShipBuilder::gen();
    auto radar = core::RadarItemBuilder::gen();

    assert(ship->radarSlots().front());

    // initial
    EXPECT_EQ(nullptr, ship->radarSlots().front()->item() );
    EXPECT_EQ(VISIBLE_DISTANCE_WITHOUT_RADAR, ship->properties().radar);

    // event: item insert
    EXPECT_TRUE(ship->manage(radar) );
    EXPECT_EQ(radar, ship->radarSlots().front()->item());
    EXPECT_EQ(radar->model()->radius(), ship->properties().radar);

    // event: lock item
    radar->lock();
    EXPECT_EQ(VISIBLE_DISTANCE_WITHOUT_RADAR, ship->properties().radar);

    // event: unlock item
    radar->unlock();
    EXPECT_EQ(radar->model()->radius(), ship->properties().radar);

    // event: damage item
    radar->corrupt();
    EXPECT_EQ(VISIBLE_DISTANCE_WITHOUT_RADAR, ship->properties().radar);

    // event: repair item
    radar->repair();
    EXPECT_EQ(radar->model()->radius(), ship->properties().radar);
}

TEST(vehicle, item_protector)
{
    auto ship = core::ShipBuilder::gen();
    auto protector = core::ProtectorItemBuilder::gen();

    assert(ship->protectorSlots().front());

    // initial
    EXPECT_EQ(nullptr, ship->protectorSlots().front()->item());
    EXPECT_EQ(ship->descriptor()->protection(), ship->properties().protection);

    // event: item insert
    EXPECT_TRUE(ship->manage(protector) );
    EXPECT_EQ(protector, ship->protectorSlots().front()->item());
    int protection = ship->descriptor()->protection() + protector->model()->protection();
    EXPECT_EQ(protection, ship->properties().protection);

    // event: lock item
    protector->lock();
    EXPECT_EQ(ship->descriptor()->protection(), ship->properties().protection);

    // event: unlock item
    protector->unlock();
    EXPECT_EQ(protection, ship->properties().protection);

    // event: damage item
    protector->corrupt();
    EXPECT_EQ(ship->descriptor()->protection(), ship->properties().protection);

    // event: repair item
    protector->repair();
    EXPECT_EQ(protection, ship->properties().protection);
}

TEST(vehicle, cargo_load)
{
    core::control::Ship* ship = core::ShipBuilder::gen();

    int cargo_num = ship->descriptor()->cargoSlotNum();
    for(int i=0; i<cargo_num; ++i) {
        auto item = core::ScanerItemBuilder::gen();
        EXPECT_TRUE(ship->load(item));
    }

    auto item = core::ScanerItemBuilder::gen();
    EXPECT_FALSE(ship->load(item));

    EXPECT_EQ(0, ship->properties().scan);
}

TEST(vehicle, freespace)
{
    core::control::Ship* ship = core::ShipBuilder::gen();

    // init
    EXPECT_EQ(ship->descriptor()->space(), ship->freeSpace());

    // event: generate and insert item list
    int taken_mass = 0;
    int cargo_num = ship->descriptor()->cargoSlotNum();
    for (int i=0; i<cargo_num; ++i) {
        core::control::Bak* item = core::BakItemBuilder::gen();
        taken_mass += item->descriptor()->mass();
        EXPECT_TRUE(ship->manage(item));
        EXPECT_EQ(ship->space() - taken_mass, ship->freeSpace());
        EXPECT_EQ(taken_mass, ship->mass());
    }
}

