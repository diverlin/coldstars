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
    control::Ship* ship = test::genShip();
    test::item::Lazer lazer;

    assert(ship->weaponSlots()[0]);

    // init
    EXPECT_EQ(nullptr, ship->weaponSlots()[0]->item());
    EXPECT_EQ(0, ship->properties().total_damage);
    EXPECT_EQ(0, ship->properties().fire_radius_min);
    EXPECT_EQ(0, ship->properties().fire_radius_max);

    // event: insert item
    EXPECT_TRUE(ship->manage(lazer.control()));
    EXPECT_EQ(lazer.control(), ship->weaponSlots()[0]->item());
    EXPECT_EQ(lazer.model()->damage(), ship->properties().total_damage);
    EXPECT_EQ(lazer.model()->radius(), ship->properties().fire_radius_min);
    EXPECT_EQ(lazer.model()->radius(), ship->properties().fire_radius_max);
}

TEST(vehicle, item_rocket)
{
    control::Ship* ship = test::genShip();
    test::item::Rocket rocket;

    assert(ship->weaponSlots()[0]);

    // init
    EXPECT_EQ(nullptr, ship->weaponSlots()[0]->item());
    EXPECT_EQ(0, ship->properties().total_damage);
    EXPECT_EQ(0, ship->properties().fire_radius_min);
    EXPECT_EQ(0, ship->properties().fire_radius_max);

    // event: insert item
    EXPECT_TRUE(ship->manage(rocket.control()));
    EXPECT_EQ(rocket.control(), ship->weaponSlots()[0]->item());
    EXPECT_EQ(rocket.model()->damage(), ship->properties().total_damage);
    EXPECT_EQ(rocket.model()->radius(), ship->properties().fire_radius_min);
    EXPECT_EQ(rocket.model()->radius(), ship->properties().fire_radius_max);
}

TEST(vehicle, item_bak)
{
    control::Ship* ship = test::genShip();
    test::item::Bak bak;

    assert(ship->bakSlots()[0]);

    // init
    EXPECT_EQ(nullptr, ship->bakSlots()[0]->item());
    EXPECT_EQ(0, ship->properties().hyper);

    // insert
    EXPECT_TRUE(ship->manage(bak.control()));
    EXPECT_EQ(bak.control(), ship->bakSlots()[0]->item());

    // post
    EXPECT_EQ(0, ship->properties().hyper); // no drive is set, that's why hyper is 0
}

TEST(vehicle, item_drive)
{
    control::Ship* ship = test::genShip();
    test::item::Drive drive;

    assert(ship->driveSlots()[0]);

    // init
    EXPECT_EQ(nullptr, ship->driveSlots()[0]->item());
    EXPECT_EQ(0, ship->properties().hyper);

    // insert
    EXPECT_TRUE(ship->manage(drive.control()));
    EXPECT_EQ(drive.control(), ship->driveSlots()[0]->item());

    // post
    EXPECT_EQ(0, ship->properties().hyper); // no bak is set that's why hyper is 0
}

TEST(vehicle, item_bak_and_drive)
{
    control::Ship* ship = test::genShip();
    test::item::Bak bak;
    test::item::Drive drive;

    assert(ship->bakSlots()[0]);
    assert(ship->driveSlots()[0]);

    // init
    EXPECT_EQ(0, ship->properties().hyper);

    // insert
    EXPECT_TRUE(ship->manage(bak.control()));
    EXPECT_TRUE(ship->manage(drive.control()));
    int hyper = std::min(bak.model()->fuel(), drive.model()->hyper());
    EXPECT_EQ(hyper, ship->properties().hyper);

    /// bak
    // event: lock item
    bak.control()->doLock();
    EXPECT_EQ(0, ship->properties().hyper);

    // event: unlock item
    bak.control()->doUnlock();
    EXPECT_EQ(hyper, ship->properties().hyper);

    // event: damage item
    bak.control()->doBreak();
    EXPECT_EQ(0, ship->properties().hyper);

    // event: repair item
    bak.control()->doRepair();
    EXPECT_EQ(hyper, ship->properties().hyper);

    /// drive
    // event: lock item
    drive.control()->doLock();
    EXPECT_EQ(0, ship->properties().hyper);

    // event: unlock item
    drive.control()->doUnlock();
    EXPECT_EQ(hyper, ship->properties().hyper);

    // event: damage item
    drive.control()->doBreak();
    EXPECT_EQ(0, ship->properties().hyper);

    // event: repair item
    drive.control()->doRepair();
    EXPECT_EQ(hyper, ship->properties().hyper);
}

TEST(vehicle, item_droid)
{
    control::Ship* ship = test::genShip();
    test::item::Droid droid;

    assert(ship->droidSlots()[0]);

    // initial
    EXPECT_EQ(nullptr, ship->droidSlots()[0]->item());
    EXPECT_EQ(0, ship->properties().repair);

    // event: item insert
    EXPECT_TRUE(ship->manage(droid.control()));
    EXPECT_EQ(droid.model()->repair(), ship->properties().repair);
    EXPECT_EQ(droid.control(), ship->droidSlots()[0]->item());

    // event: lock item
    droid.control()->doLock();
    EXPECT_EQ(0, ship->properties().repair);

    // event: unlock item
    droid.control()->doUnlock();
    EXPECT_EQ(droid.model()->repair(), ship->properties().repair);

    // event: damage item
    droid.control()->doBreak();
    EXPECT_EQ(0, ship->properties().repair);

    // event: repair item
    droid.control()->doRepair();
    EXPECT_EQ(droid.model()->repair(), ship->properties().repair);
}

TEST(vehicle, item_grapple)
{
    control::Ship* ship = test::genShip();
    test::item::Grapple grapple;

    assert(ship->grappleSlots()[0]);

    // initial
    EXPECT_EQ(nullptr, ship->grappleSlots()[0]->item());
    EXPECT_EQ(0, ship->properties().grab_strength);
    EXPECT_EQ(0, ship->properties().grab_radius);

    // event: item insert
    EXPECT_TRUE(ship->manage(grapple.control()));
    EXPECT_EQ(grapple.control(), ship->grappleSlots()[0]->item());
    EXPECT_EQ(grapple.model()->strength(), ship->properties().grab_strength);
    EXPECT_EQ(grapple.model()->radius(), ship->properties().grab_radius);

    // event: lock item
    grapple.control()->doLock();
    EXPECT_EQ(0, ship->properties().grab_strength);
    EXPECT_EQ(0, ship->properties().grab_radius);

    // event: unlock item
    grapple.control()->doUnlock();
    EXPECT_EQ(grapple.model()->strength(), ship->properties().grab_strength);
    EXPECT_EQ(grapple.model()->radius(), ship->properties().grab_radius);

    // event: damage item
    grapple.control()->doBreak();
    EXPECT_EQ(0, ship->properties().grab_strength);
    EXPECT_EQ(0, ship->properties().grab_radius);

    // event: repair item
    grapple.control()->doRepair();
    EXPECT_EQ(grapple.model()->strength(), ship->properties().grab_strength);
    EXPECT_EQ(grapple.model()->radius(), ship->properties().grab_radius);
}

TEST(vehicle, item_scaner)
{
    control::Ship* ship = test::genShip();
    test::item::Scaner scaner;

    assert(ship->scanerSlots()[0]);

    // initial
    EXPECT_EQ(nullptr, ship->scanerSlots()[0]->item());
    EXPECT_EQ(0, ship->properties().scan);

    // item insert
    EXPECT_TRUE(ship->manage(scaner.control()));
    EXPECT_EQ(scaner.control(), ship->scanerSlots()[0]->item());
    EXPECT_EQ(scaner.model()->scan(), ship->properties().scan);

    // event: lock item
    scaner.control()->doLock();
    EXPECT_EQ(0, ship->properties().scan);

    // event: unlock item
    scaner.control()->doUnlock();
    EXPECT_EQ(scaner.model()->scan(), ship->properties().scan);

    // event: damage item
    scaner.control()->doBreak();
    EXPECT_EQ(0, ship->properties().scan);

    // event: repair item
    scaner.control()->doRepair();
    EXPECT_EQ(scaner.model()->scan(), ship->properties().scan);
}

TEST(vehicle, item_radar)
{
    control::Ship* ship = test::genShip();
    test::item::Radar radar;

    assert(ship->radarSlots()[0]);

    // initial
    EXPECT_EQ(nullptr, ship->radarSlots()[0]->item() );
    EXPECT_EQ(VISIBLE_DISTANCE_WITHOUT_RADAR, ship->properties().radar);

    // event: item insert
    EXPECT_TRUE(ship->manage(radar.control()) );
    EXPECT_EQ(radar.control(), ship->radarSlots()[0]->item());
    EXPECT_EQ(radar.model()->radius(), ship->properties().radar);

    // event: lock item
    radar.control()->doLock();
    EXPECT_EQ(VISIBLE_DISTANCE_WITHOUT_RADAR, ship->properties().radar);

    // event: unlock item
    radar.control()->doUnlock();
    EXPECT_EQ(radar.model()->radius(), ship->properties().radar);

    // event: damage item
    radar.control()->doBreak();
    EXPECT_EQ(VISIBLE_DISTANCE_WITHOUT_RADAR, ship->properties().radar);

    // event: repair item
    radar.control()->doRepair();
    EXPECT_EQ(radar.model()->radius(), ship->properties().radar);
}

TEST(vehicle, item_protector)
{
    control::Ship* ship = test::genShip();
    test::item::Protector protector;

    assert(ship->protectorSlots()[0]);

    // initial
    EXPECT_EQ(nullptr, ship->protectorSlots()[0]->item());
    EXPECT_EQ(ship->descriptor()->protection(), ship->properties().protection);

    // event: item insert
    EXPECT_TRUE(ship->manage(protector.control()) );
    EXPECT_EQ(protector.control(), ship->protectorSlots()[0]->item());
    int protection = ship->descriptor()->protection() + protector.model()->protection();
    EXPECT_EQ(protection, ship->properties().protection);

    // event: lock item
    protector.control()->doLock();
    EXPECT_EQ(ship->descriptor()->protection(), ship->properties().protection);

    // event: unlock item
    protector.control()->doUnlock();
    EXPECT_EQ(protection, ship->properties().protection);

    // event: damage item
    protector.control()->doBreak();
    EXPECT_EQ(ship->descriptor()->protection(), ship->properties().protection);

    // event: repair item
    protector.control()->doRepair();
    EXPECT_EQ(protection, ship->properties().protection);
}

TEST(vehicle, cargo_load)
{
    control::Ship* ship = test::genShip();

    int cargo_num = ship->descriptor()->cargoSlotNum();
    for(int i=0; i<cargo_num; ++i) {
        test::item::Scaner item;
        EXPECT_TRUE(ship->load(item.control()));
    }

    test::item::Scaner item;
    EXPECT_FALSE(ship->load(item.control()));

    EXPECT_EQ(0, ship->properties().scan);
}

TEST(vehicle, freespace)
{
    control::Ship* ship = test::genShip();

    // init
    EXPECT_EQ(ship->descriptor()->space(), ship->freeSpace());

    // event: generate and insert item list
    int taken_mass = 0;
    test::pVector<test::item::Bak*> items;
    int cargo_num = ship->descriptor()->cargoSlotNum();
    for (int i=0; i<cargo_num; ++i) {
        test::item::Bak* item = new test::item::Bak;
        items.push_back(item);
        taken_mass += item->descriptor()->mass();
        EXPECT_TRUE(ship->manage(item->control()));
        EXPECT_EQ(ship->space() - taken_mass, ship->freeSpace());
        EXPECT_EQ(taken_mass, ship->mass());
    }
}

