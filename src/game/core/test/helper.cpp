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

#include <core/generator/DescriptorGenerator.hpp>

#include <core/descriptor/world/StarSystemDescriptor.hpp>
#include <core/world/starsystem.hpp>
#include <core/builder/world/StarSystemBuilder.hpp>

#include <core/spaceobject/ALL>
#include <core/builder/spaceobject/ALL>
#include <core/model/spaceobject/ALL>

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

StarSystem::StarSystem() {
    model::StarSystem* model = builder::StarSystem::gen();
    m_control = new control::StarSystem(model);
}
StarSystem::~StarSystem() {
//    delete m_control->model();
//    delete m_control;
}

descriptor::StarSystem* StarSystem::descriptor() const { return m_control->descriptor(); }
model::StarSystem* StarSystem::model() const { return m_control->model(); }



Star::Star() {
    model::Star* model = builder::Star::gen();
    m_control = new control::Star(model);
}
Star::~Star() {
//    delete m_control->model();
//    delete m_control;
}

descriptor::Star* Star::descriptor() const { return m_control->descriptor(); }
model::Star* Star::model() const { return m_control->model(); }


Planet::Planet() {
    model::Planet* model = builder::Planet::gen();
    m_control = new control::Planet(model);
}
Planet::~Planet() {
//    delete m_control->model();
//    delete m_control;
}

descriptor::Planet* Planet::descriptor() const { return m_control->descriptor(); }
model::Planet* Planet::model() const { return m_control->model(); }


control::WormHole*
genWormHole() {
    model::WormHole* model = builder::WormHole::gen();
    return new control::WormHole(model);
}

control::Asteroid*
genAsteroid() {
    model::Asteroid* model = builder::Asteroid::gen();
    return new control::Asteroid(model);
}

control::Container*
genContainer() {
    model::Container* model = builder::Container::gen();
    return new control::Container(model);
}

SpaceStation::SpaceStation() {
    model::SpaceStation* model = builder::SpaceStation::gen();
    m_control = new control::SpaceStation(model);
}
SpaceStation::~SpaceStation() {
//    delete m_control->model();
//    delete m_control;
}

descriptor::SpaceStation* SpaceStation::descriptor() const { return m_control->descriptor(); }
model::SpaceStation* SpaceStation::model() const { return m_control->model(); }


Ship::Ship() {
    model::Ship* model = builder::Ship::gen();
    m_control = new control::Ship(model);
}
Ship::~Ship() {
//    delete m_control->model();
//    delete m_control;
}

descriptor::Ship* Ship::descriptor() const { return m_control->descriptor(); }
model::Ship* Ship::model() const { return m_control->model(); }


Satellite::Satellite() {
    model::Satellite* model = builder::Satellite::gen();
    m_control = new control::Satellite(model);
}
Satellite::~Satellite() {
//    delete m_control->model();
//    delete m_control;
}

descriptor::Satellite* Satellite::descriptor() const { return m_control->descriptor(); }
model::Satellite* Satellite::model() const { return m_control->model(); }


namespace item {

//////
Bak::Bak() {
    model::item::Bak* model = builder::item::Bak::gen();
    m_control = new control::item::Bak(model);
}
Bak::~Bak() {
//    delete m_control->model();
//    delete m_control;
}

descriptor::item::Bak* Bak::descriptor() const { return m_control->descriptor(); }
model::item::Bak* Bak::model() const { return m_control->model(); }

//////
Drive::Drive() {
    model::item::Drive* model = builder::item::Drive::gen();
    m_control = new control::item::Drive(model);
}
Drive::~Drive() {
//    delete m_control->model();
//    delete m_control;
}

descriptor::item::Drive* Drive::descriptor() const { return m_control->descriptor(); }
model::item::Drive* Drive::model() const { return m_control->model(); }

//////
Droid::Droid() {
    model::item::Droid* model = builder::item::Droid::gen();
    m_control = new control::item::Droid(model);
}
Droid::~Droid() {
//    delete m_control->model();
//    delete m_control;
}

descriptor::item::Droid* Droid::descriptor() const { return m_control->descriptor(); }
model::item::Droid* Droid::model() const { return m_control->model(); }

//////
Grapple::Grapple() {
    model::item::Grapple* model = builder::item::Grapple::gen();
    m_control = new control::item::Grapple(model);
}
Grapple::~Grapple() {
//    delete m_control->model();
//    delete m_control;
}

descriptor::item::Grapple* Grapple::descriptor() const { return m_control->descriptor(); }
model::item::Grapple* Grapple::model() const { return m_control->model(); }

//////
Lazer::Lazer() {
    model::item::Lazer* model = builder::item::Lazer::gen();
    m_control = new control::item::Lazer(model);
}
Lazer::~Lazer() {
//    delete m_control->model();
//    delete m_control;
}

descriptor::item::Lazer* Lazer::descriptor() const { return m_control->descriptor(); }
model::item::Lazer* Lazer::model() const { return m_control->model(); }

//////
Protector::Protector() {
    model::item::Protector* model = builder::item::Protector::gen();
    m_control = new control::item::Protector(model);
}
Protector::~Protector() {
//    delete m_control->model();
//    delete m_control;
}

descriptor::item::Protector* Protector::descriptor() const { return m_control->descriptor(); }
model::item::Protector* Protector::model() const { return m_control->model(); }

//////
Radar::Radar() {
    model::item::Radar* model = builder::item::Radar::gen();
    m_control = new control::item::Radar(model);
}
Radar::~Radar() {
//    delete m_control->model();
//    delete m_control;
}

descriptor::item::Radar* Radar::descriptor() const { return m_control->descriptor(); }
model::item::Radar* Radar::model() const { return m_control->model(); }

//////
Rocket::Rocket() {
    model::item::Rocket* model = builder::item::Rocket::gen();
    m_control = new control::item::Rocket(model);
}
Rocket::~Rocket() {
//    delete m_control->model();
//    delete m_control;
}

descriptor::item::Rocket* Rocket::descriptor() const { return m_control->descriptor(); }
model::item::Rocket* Rocket::model() const { return m_control->model(); }

//////
Scaner::Scaner() {
    model::item::Scaner* model = builder::item::Scaner::gen();
    m_control = new control::item::Scaner(model);
}
Scaner::~Scaner() {
//    delete m_control->model();
//    delete m_control;
}

descriptor::item::Scaner* Scaner::descriptor() const { return m_control->descriptor(); }
model::item::Scaner* Scaner::model() const { return m_control->model(); }

} // namespace item

} // namespace test
