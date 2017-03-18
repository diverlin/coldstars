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
    test::Ship ship;
    test::item::Lazer lazer;

    assert(ship.control()->weaponSlots()[0]);

    // init
    EXPECT_EQ(nullptr, ship.control()->weaponSlots()[0]->item());
    EXPECT_EQ(0, ship.control()->properties().total_damage);
    EXPECT_EQ(0, ship.control()->properties().fire_radius_min);
    EXPECT_EQ(0, ship.control()->properties().fire_radius_max);

    // event: insert item
    EXPECT_TRUE(ship.control()->manage(lazer.control()));
    EXPECT_EQ(lazer.control(), ship.control()->weaponSlots()[0]->item());
    EXPECT_EQ(lazer.model()->damage(), ship.control()->properties().total_damage);
    EXPECT_EQ(lazer.model()->radius(), ship.control()->properties().fire_radius_min);
    EXPECT_EQ(lazer.model()->radius(), ship.control()->properties().fire_radius_max);
}

TEST(vehicle, item_rocket)
{
    test::Ship ship;
    test::item::Rocket rocket;

    assert(ship.control()->weaponSlots()[0]);

    // init
    EXPECT_EQ(nullptr, ship.control()->weaponSlots()[0]->item());
    EXPECT_EQ(0, ship.control()->properties().total_damage);
    EXPECT_EQ(0, ship.control()->properties().fire_radius_min);
    EXPECT_EQ(0, ship.control()->properties().fire_radius_max);

    // event: insert item
    EXPECT_TRUE(ship.control()->manage(rocket.control()));
    EXPECT_EQ(rocket.control(), ship.control()->weaponSlots()[0]->item());
    EXPECT_EQ(rocket.model()->damage(), ship.control()->properties().total_damage);
    EXPECT_EQ(rocket.model()->radius(), ship.control()->properties().fire_radius_min);
    EXPECT_EQ(rocket.model()->radius(), ship.control()->properties().fire_radius_max);
}

TEST(vehicle, item_bak)
{
    test::Ship ship;
    test::item::Bak bak;

    assert(ship.control()->bakSlots()[0]);

    // init
    EXPECT_EQ(nullptr, ship.control()->bakSlots()[0]->item());
    EXPECT_EQ(0, ship.control()->properties().hyper);

    // insert
    EXPECT_TRUE(ship.control()->manage(bak.control()));
    EXPECT_EQ(bak.control(), ship.control()->bakSlots()[0]->item());

    // post
    EXPECT_EQ(0, ship.control()->properties().hyper); // no drive is set, that's why hyper is 0
}

TEST(vehicle, item_drive)
{
    test::Ship ship;
    test::item::Drive drive;

    assert(ship.control()->driveSlots()[0]);

    // init
    EXPECT_EQ(nullptr, ship.control()->driveSlots()[0]->item());
    EXPECT_EQ(0, ship.control()->properties().hyper);

    // insert
    EXPECT_TRUE(ship.control()->manage(drive.control()));
    EXPECT_EQ(drive.control(), ship.control()->driveSlots()[0]->item());

    // post
    EXPECT_EQ(0, ship.control()->properties().hyper); // no bak is set that's why hyper is 0
}

TEST(vehicle, item_bak_and_drive)
{
    test::Ship ship;
    test::item::Bak bak;
    test::item::Drive drive;

    assert(ship.control()->bakSlots()[0]);
    assert(ship.control()->driveSlots()[0]);

    // init
    EXPECT_EQ(0, ship.control()->properties().hyper);

    // insert
    EXPECT_TRUE(ship.control()->manage(bak.control()));
    EXPECT_TRUE(ship.control()->manage(drive.control()));
    int hyper = std::min(bak.model()->fuel(), drive.model()->hyper());
    EXPECT_EQ(hyper, ship.control()->properties().hyper);

    /// bak
    // event: lock item
    bak.control()->doLock();
    EXPECT_EQ(0, ship.control()->properties().hyper);

    // event: unlock item
    bak.control()->doUnlock();
    EXPECT_EQ(hyper, ship.control()->properties().hyper);

    // event: damage item
    bak.control()->doBreak();
    EXPECT_EQ(0, ship.control()->properties().hyper);

    // event: repair item
    bak.control()->doRepair();
    EXPECT_EQ(hyper, ship.control()->properties().hyper);

    /// drive
    // event: lock item
    drive.control()->doLock();
    EXPECT_EQ(0, ship.control()->properties().hyper);

    // event: unlock item
    drive.control()->doUnlock();
    EXPECT_EQ(hyper, ship.control()->properties().hyper);

    // event: damage item
    drive.control()->doBreak();
    EXPECT_EQ(0, ship.control()->properties().hyper);

    // event: repair item
    drive.control()->doRepair();
    EXPECT_EQ(hyper, ship.control()->properties().hyper);
}

TEST(vehicle, item_droid)
{
    test::Ship ship;
    test::item::Droid droid;

    assert(ship.control()->droidSlots()[0]);

    // initial
    EXPECT_EQ(nullptr, ship.control()->droidSlots()[0]->item());
    EXPECT_EQ(0, ship.control()->properties().repair);

    // event: item insert
    EXPECT_TRUE(ship.control()->manage(droid.control()));
    EXPECT_EQ(droid.model()->repair(), ship.control()->properties().repair);
    EXPECT_EQ(droid.control(), ship.control()->droidSlots()[0]->item());

    // event: lock item
    droid.control()->doLock();
    EXPECT_EQ(0, ship.control()->properties().repair);

    // event: unlock item
    droid.control()->doUnlock();
    EXPECT_EQ(droid.model()->repair(), ship.control()->properties().repair);

    // event: damage item
    droid.control()->doBreak();
    EXPECT_EQ(0, ship.control()->properties().repair);

    // event: repair item
    droid.control()->doRepair();
    EXPECT_EQ(droid.model()->repair(), ship.control()->properties().repair);
}

TEST(vehicle, item_grapple)
{
    test::Ship ship;
    test::item::Grapple grapple;

    assert(ship.control()->grappleSlots()[0]);

    // initial
    EXPECT_EQ(nullptr, ship.control()->grappleSlots()[0]->item());
    EXPECT_EQ(0, ship.control()->properties().grab_strength);
    EXPECT_EQ(0, ship.control()->properties().grab_radius);

    // event: item insert
    EXPECT_TRUE(ship.control()->manage(grapple.control()));
    EXPECT_EQ(grapple.control(), ship.control()->grappleSlots()[0]->item());
    EXPECT_EQ(grapple.model()->strength(), ship.control()->properties().grab_strength);
    EXPECT_EQ(grapple.model()->radius(), ship.control()->properties().grab_radius);

    // event: lock item
    grapple.control()->doLock();
    EXPECT_EQ(0, ship.control()->properties().grab_strength);
    EXPECT_EQ(0, ship.control()->properties().grab_radius);

    // event: unlock item
    grapple.control()->doUnlock();
    EXPECT_EQ(grapple.model()->strength(), ship.control()->properties().grab_strength);
    EXPECT_EQ(grapple.model()->radius(), ship.control()->properties().grab_radius);

    // event: damage item
    grapple.control()->doBreak();
    EXPECT_EQ(0, ship.control()->properties().grab_strength);
    EXPECT_EQ(0, ship.control()->properties().grab_radius);

    // event: repair item
    grapple.control()->doRepair();
    EXPECT_EQ(grapple.model()->strength(), ship.control()->properties().grab_strength);
    EXPECT_EQ(grapple.model()->radius(), ship.control()->properties().grab_radius);
}

TEST(vehicle, item_scaner)
{
    test::Ship ship;
    test::item::Scaner scaner;

    assert(ship.control()->scanerSlots()[0]);

    // initial
    EXPECT_EQ(nullptr, ship.control()->scanerSlots()[0]->item());
    EXPECT_EQ(0, ship.control()->properties().scan);

    // item insert
    EXPECT_TRUE(ship.control()->manage(scaner.control()));
    EXPECT_EQ(scaner.control(), ship.control()->scanerSlots()[0]->item());
    EXPECT_EQ(scaner.model()->scan(), ship.control()->properties().scan);

    // event: lock item
    scaner.control()->doLock();
    EXPECT_EQ(0, ship.control()->properties().scan);

    // event: unlock item
    scaner.control()->doUnlock();
    EXPECT_EQ(scaner.model()->scan(), ship.control()->properties().scan);

    // event: damage item
    scaner.control()->doBreak();
    EXPECT_EQ(0, ship.control()->properties().scan);

    // event: repair item
    scaner.control()->doRepair();
    EXPECT_EQ(scaner.model()->scan(), ship.control()->properties().scan);
}

TEST(vehicle, item_radar)
{
    test::Ship ship;
    test::item::Radar radar;

    assert(ship.control()->radarSlots()[0]);

    // initial
    EXPECT_EQ(nullptr, ship.control()->radarSlots()[0]->item() );
    EXPECT_EQ(VISIBLE_DISTANCE_WITHOUT_RADAR, ship.control()->properties().radar);

    // event: item insert
    EXPECT_TRUE(ship.control()->manage(radar.control()) );
    EXPECT_EQ(radar.control(), ship.control()->radarSlots()[0]->item());
    EXPECT_EQ(radar.model()->radius(), ship.control()->properties().radar);

    // event: lock item
    radar.control()->doLock();
    EXPECT_EQ(VISIBLE_DISTANCE_WITHOUT_RADAR, ship.control()->properties().radar);

    // event: unlock item
    radar.control()->doUnlock();
    EXPECT_EQ(radar.model()->radius(), ship.control()->properties().radar);

    // event: damage item
    radar.control()->doBreak();
    EXPECT_EQ(VISIBLE_DISTANCE_WITHOUT_RADAR, ship.control()->properties().radar);

    // event: repair item
    radar.control()->doRepair();
    EXPECT_EQ(radar.model()->radius(), ship.control()->properties().radar);
}

TEST(vehicle, item_protector)
{
    test::Ship ship;
    test::item::Protector protector;

    assert(ship.control()->protectorSlots()[0]);

    // initial
    EXPECT_EQ(nullptr, ship.control()->protectorSlots()[0]->item());
    EXPECT_EQ(ship.descriptor()->protection(), ship.control()->properties().protection);

    // event: item insert
    EXPECT_TRUE(ship.control()->manage(protector.control()) );
    EXPECT_EQ(protector.control(), ship.control()->protectorSlots()[0]->item());
    int protection = ship.descriptor()->protection() + protector.model()->protection();
    EXPECT_EQ(protection, ship.control()->properties().protection);

    // event: lock item
    protector.control()->doLock();
    EXPECT_EQ(ship.descriptor()->protection(), ship.control()->properties().protection);

    // event: unlock item
    protector.control()->doUnlock();
    EXPECT_EQ(protection, ship.control()->properties().protection);

    // event: damage item
    protector.control()->doBreak();
    EXPECT_EQ(ship.descriptor()->protection(), ship.control()->properties().protection);

    // event: repair item
    protector.control()->doRepair();
    EXPECT_EQ(protection, ship.control()->properties().protection);
}

TEST(vehicle, cargo_load)
{
    test::Ship ship;

    int cargo_num = ship.descriptor()->cargoSlotNum();
    for(int i=0; i<cargo_num; ++i) {
        test::item::Scaner item;
        EXPECT_TRUE(ship.control()->load(item.control()));
    }

    test::item::Scaner item;
    EXPECT_FALSE(ship.control()->load(item.control()));

    EXPECT_EQ(0, ship.control()->properties().scan);
}

TEST(vehicle, freespace)
{
    test::Ship ship;

    // init
    EXPECT_EQ(ship.descriptor()->space(), ship.control()->freeSpace());

    // event: generate and insert item list
    int taken_mass = 0;
    test::pVector<test::item::Bak*> items;
    int cargo_num = ship.descriptor()->cargoSlotNum();
    for (int i=0; i<cargo_num; ++i) {
        test::item::Bak* item = new test::item::Bak;
        items.push_back(item);
        taken_mass += item->descriptor()->mass();
        EXPECT_TRUE(ship.control()->manage(item->control()));
        EXPECT_EQ(ship.control()->space() - taken_mass, ship.control()->freeSpace());
        EXPECT_EQ(taken_mass, ship.control()->mass());
    }
}

