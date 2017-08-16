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

#include <core/common/Global.hpp>
#include <core/world/starsystem.hpp>
#include <core/item/other/Bomb.hpp>
#include <core/slot/ItemSlot.hpp>
#include <core/spaceobject/Container.hpp>
#include <core/spaceobject/Ship.hpp>

#include <core/model/spaceobject/Ship.hpp>

#include <core/model/item/equipment/ALL>
#include <core/model/world/starsystem.hpp>

#include <core/item/equipment/ALL>

#include <core/builder/spaceobject/ShipBuilder.hpp>
#include <core/builder/world/StarSystemBuilder.hpp>
#include <core/builder/item/other/BombBuilder.hpp>
#include <core/builder/spaceobject/ContainerBuilder.hpp>

#include <core/manager/DescriptorManager.hpp>
#include <core/descriptor/Base.hpp>
#include <core/descriptor/spaceobject/ALL>
#include <core/descriptor/item/equipment/ALL>

#include <core/descriptor/comm/Creation.hpp>

#include <core/generator/DescriptorGenerator.hpp>

#include <core/communication/TelegrammManager.hpp>
#include <core/manager/EntityManager.hpp>

#include <ceti/IdGenerator.hpp>


TEST(communication, create_starsystem)
{
    int_t ob_id = manager::Entities::get().genId();

    descriptor::StarSystem* descriptor = descriptor::genStarSystem();
    descriptor::comm::Creation creation(ob_id, descriptor->id());

    core::global::get().messageManager().add(comm::Telegramm(comm::Telegramm::Type::CREATE_STARSYSTEM, creation.data()));

    control::StarSystem* starsystem = manager::Entities::get().starsystem(ob_id);
    EXPECT_EQ(descriptor->id(), starsystem->model()->descriptor());
}

TEST(communication, create_ship)
{
    int_t ob_id = manager::Entities::get().genId();

    descriptor::Ship* descriptor = descriptor::genShip();
    descriptor::comm::Creation creation(ob_id, descriptor->id());

    core::global::get().messageManager().add(comm::Telegramm(comm::Telegramm::Type::CREATE_SHIP, creation.data()));

    control::Ship* ship = manager::Entities::get().ship(ob_id);
    EXPECT_EQ(descriptor->id(), ship->model()->descriptor());
}

TEST(communication, create_bak)
{
    int_t ob_id = manager::Entities::get().genId();

    descriptor::item::Bak* descriptor = descriptor::item::genBak();
    descriptor::comm::Creation creation(ob_id, descriptor->id());

    core::global::get().messageManager().add(comm::Telegramm(comm::Telegramm::Type::CREATE_BAK, creation.data()));

    control::item::Bak* bak = manager::Entities::get().bak(ob_id);
    EXPECT_EQ(descriptor->id(), bak->model()->descriptor());
}

TEST(communication, inject_ship)
{
    //EXPECT_EQ(true, false);
}

//Bomb* getNewBomb(int damage, int radius)
//{
//    descriptor::Base* descriptor = descriptor::Manager::get().getRand(descriptor::Type::BOMB);
//    core::global::get().messageManager().add(Message(TELEGRAM::CREATE_BOMB, descriptor.data()));

//    Bomb* bomb = static_cast<Bomb*>(manager::EntityManager::get().get(descriptor.id()));
//    assert(bomb);
//    return bomb;
//}

//Container* getNewContainer(const id_type& child_id)
//{
//    auto descriptor = descriptor::Container(child_id);
//   core::global::get().messageManager().add(Message(TELEGRAM::CREATE_CONTAINER, descriptor.data()));

//    Container* container = static_cast<Container*>(manager::EntityManager::get().get(descriptor.id()));
//    assert(container);
//    assert(container->itemSlot());
//    assert(container->itemSlot()->item());
//    assert(container->itemSlot()->item()->id() == child_id);
//    return container;
//}
