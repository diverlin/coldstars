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

#include <gtest/gtest.h>

namespace test {

Ship::Ship() {
    descriptor::Ship* descr = descriptor::getNewShip();
    model::Ship* model = builder::Ship::getNew(descr);
    m_control = new control::Ship(model, descr);
}
Ship::~Ship() {
    delete m_control->descriptor();
    delete m_control->model();
    delete m_control;
}

descriptor::Ship* Ship::descriptor() const { return m_control->descriptor(); }
model::Ship* Ship::model() const { return m_control->model(); }

namespace item {

Bak::Bak() {
    descriptor::item::Bak* descr = descriptor::item::getNewBak();
    model::item::Bak* model = builder::item::Bak::getNew(descr);
    m_control = new control::item::Bak(model, descr);
}
Bak::~Bak() {
    delete m_control->descriptor();
    delete m_control->model();
    delete m_control;
}

descriptor::item::Bak* Bak::descriptor() const { return m_control->descriptor(); }
model::item::Bak* Bak::model() const { return m_control->model(); }


Drive::Drive() {
    descriptor::item::Drive* descr = descriptor::item::getNewDrive();
    model::item::Drive* model = builder::item::Drive::getNew(descr);
    m_control = new control::item::Drive(model, descr);
}
Drive::~Drive() {
    delete m_control->descriptor();
    delete m_control->model();
    delete m_control;
}

descriptor::item::Drive* Drive::descriptor() const { return m_control->descriptor(); }
model::item::Drive* Drive::model() const { return m_control->model(); }

} // namespace item

} // namespace test
