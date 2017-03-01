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

#include "helper2.hpp"

#include <core/descriptor/DescriptorGenerator.hpp>
#include <core/builder/spaceobjects/ShipBuilder.hpp>
#include <core/spaceobjects/Ship.hpp>

// Bak
#include <core/builder/item/equipment/BakBuilder.hpp>
#include <core/descriptor/item/equipment/Bak.hpp>
#include <core/model/item/equipment/Bak.hpp>
#include <core/item/equipment/Bak.hpp>

// Drive
#include <core/builder/item/equipment/DriveBuilder.hpp>
#include <core/descriptor/item/equipment/Drive.hpp>
#include <core/model/item/equipment/Drive.hpp>
#include <core/item/equipment/Drive.hpp>

// Droid
#include <core/builder/item/equipment/DroidBuilder.hpp>
#include <core/descriptor/item/equipment/Droid.hpp>
#include <core/model/item/equipment/Droid.hpp>
#include <core/item/equipment/Droid.hpp>

// Grapple
#include <core/builder/item/equipment/GrappleBuilder.hpp>
#include <core/descriptor/item/equipment/Grapple.hpp>
#include <core/model/item/equipment/Grapple.hpp>
#include <core/item/equipment/Grapple.hpp>

// Lazer
#include <core/builder/item/equipment/LazerBuilder.hpp>
#include <core/descriptor/item/equipment/Lazer.hpp>
#include <core/model/item/equipment/Lazer.hpp>
#include <core/item/equipment/Lazer.hpp>

// Protector
#include <core/builder/item/equipment/ProtectorBuilder.hpp>
#include <core/descriptor/item/equipment/Protector.hpp>
#include <core/model/item/equipment/Protector.hpp>
#include <core/item/equipment/Protector.hpp>

// Radar
#include <core/builder/item/equipment/RadarBuilder.hpp>
#include <core/descriptor/item/equipment/Radar.hpp>
#include <core/model/item/equipment/Radar.hpp>
#include <core/item/equipment/Radar.hpp>

// Rocket
#include <core/builder/item/equipment/RocketBuilder.hpp>
#include <core/descriptor/item/equipment/Rocket.hpp>
#include <core/model/item/equipment/Rocket.hpp>
#include <core/item/equipment/Rocket.hpp>

// Scaner
#include <core/builder/item/equipment/ScanerBuilder.hpp>
#include <core/descriptor/item/equipment/Scaner.hpp>
#include <core/model/item/equipment/Scaner.hpp>
#include <core/item/equipment/Scaner.hpp>

#include <gtest/gtest.h>

namespace test {

Ship::Ship() {
    descriptor::Ship* descr = descriptor::getNewShip();
    model::Ship* model = builder::Ship::getNew(descr);
    m_control = new control::Ship(model, descr);
}
Ship::~Ship() {
//    delete m_control->descriptor();
    delete m_control->model();
    delete m_control;
}

descriptor::Ship* Ship::descriptor() const { return m_control->descriptor(); }
model::Ship* Ship::model() const { return m_control->model(); }

namespace item {

//////
Bak::Bak() {
    descriptor::item::Bak* descr = descriptor::item::getNewBak();
    model::item::Bak* model = builder::item::Bak::getNew(descr);
    m_control = new control::item::Bak(model, descr);
}
Bak::~Bak() {
    //delete m_control->descriptor();
    delete m_control->model();
    delete m_control;
}

descriptor::item::Bak* Bak::descriptor() const { return m_control->descriptor(); }
model::item::Bak* Bak::model() const { return m_control->model(); }

//////
Drive::Drive() {
    descriptor::item::Drive* descr = descriptor::item::getNewDrive();
    model::item::Drive* model = builder::item::Drive::getNew(descr);
    m_control = new control::item::Drive(model, descr);
}
Drive::~Drive() {
//    delete m_control->descriptor();
    delete m_control->model();
    delete m_control;
}

descriptor::item::Drive* Drive::descriptor() const { return m_control->descriptor(); }
model::item::Drive* Drive::model() const { return m_control->model(); }

//////
Droid::Droid() {
    descriptor::item::Droid* descr = descriptor::item::getNewDroid();
    model::item::Droid* model = builder::item::Droid::getNew(descr);
    m_control = new control::item::Droid(model, descr);
}
Droid::~Droid() {
//    delete m_control->descriptor();
    delete m_control->model();
    delete m_control;
}

descriptor::item::Droid* Droid::descriptor() const { return m_control->descriptor(); }
model::item::Droid* Droid::model() const { return m_control->model(); }

//////
Grapple::Grapple() {
    descriptor::item::Grapple* descr = descriptor::item::getNewGrapple();
    model::item::Grapple* model = builder::item::Grapple::getNew(descr);
    m_control = new control::item::Grapple(model, descr);
}
Grapple::~Grapple() {
//    delete m_control->descriptor();
    delete m_control->model();
    delete m_control;
}

descriptor::item::Grapple* Grapple::descriptor() const { return m_control->descriptor(); }
model::item::Grapple* Grapple::model() const { return m_control->model(); }

//////
Lazer::Lazer() {
    descriptor::item::Lazer* descr = descriptor::item::getNewLazer();
    model::item::Lazer* model = builder::item::Lazer::getNew(descr);
    m_control = new control::item::Lazer(model, descr);
}
Lazer::~Lazer() {
//    delete m_control->descriptor();
    delete m_control->model();
    delete m_control;
}

descriptor::item::Lazer* Lazer::descriptor() const { return m_control->descriptor(); }
model::item::Lazer* Lazer::model() const { return m_control->model(); }

//////
Protector::Protector() {
    descriptor::item::Protector* descr = descriptor::item::getNewProtector();
    model::item::Protector* model = builder::item::Protector::getNew(descr);
    m_control = new control::item::Protector(model, descr);
}
Protector::~Protector() {
//    delete m_control->descriptor();
    delete m_control->model();
    delete m_control;
}

descriptor::item::Protector* Protector::descriptor() const { return m_control->descriptor(); }
model::item::Protector* Protector::model() const { return m_control->model(); }

//////
Radar::Radar() {
    descriptor::item::Radar* descr = descriptor::item::getNewRadar();
    model::item::Radar* model = builder::item::Radar::getNew(descr);
    m_control = new control::item::Radar(model, descr);
}
Radar::~Radar() {
//    delete m_control->descriptor();
    delete m_control->model();
    delete m_control;
}

descriptor::item::Radar* Radar::descriptor() const { return m_control->descriptor(); }
model::item::Radar* Radar::model() const { return m_control->model(); }

//////
Rocket::Rocket() {
    descriptor::item::Rocket* descr = descriptor::item::getNewRocket();
    model::item::Rocket* model = builder::item::Rocket::getNew(descr);
    m_control = new control::item::Rocket(model, descr);
}
Rocket::~Rocket() {
//    delete m_control->descriptor();
    delete m_control->model();
    delete m_control;
}

descriptor::item::Rocket* Rocket::descriptor() const { return m_control->descriptor(); }
model::item::Rocket* Rocket::model() const { return m_control->model(); }

//////
Scaner::Scaner() {
    descriptor::item::Scaner* descr = descriptor::item::getNewScaner();
    model::item::Scaner* model = builder::item::Scaner::getNew(descr);
    m_control = new control::item::Scaner(model, descr);
}
Scaner::~Scaner() {
//    delete m_control->descriptor();
    delete m_control->model();
    delete m_control;
}

descriptor::item::Scaner* Scaner::descriptor() const { return m_control->descriptor(); }
model::item::Scaner* Scaner::model() const { return m_control->model(); }

} // namespace item

} // namespace test
