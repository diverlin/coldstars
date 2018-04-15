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

#include <core/communication/descriptor/Create.hpp>

#include <core/generator/DescriptorGenerator.hpp>

#include <core/communication/TelegramHub.hpp>
#include <core/manager/EntityManager.hpp>

#include <ceti/IdGenerator.hpp>


TEST(communication, create_starsystem)
{
    assert(false);
//    int_t ob_id = core::manager::Entity::get().genId();

//    StarSystem* descriptor = genStarSystem();
//    Create create(ob_id, descriptor->id());

//    core::global::get().TelegramHub().add(Telegram(telegram::Type::CREATE_STARSYSTEM, creation.data()));

//    control::StarSystem* starsystem = core::manager::Entity::get().starsystem(ob_id);
//    EXPECT_EQ(descriptor->id(), starsystem->model()->descriptor());
}

TEST(communication, create_ship)
{
    assert(false);
//    int_t ob_id = core::manager::Entity::get().genId();

//    Ship* descriptor = genShip();
//    Create create(ob_id, descriptor->id());

//    core::global::get().TelegramHub().add(Telegram(Telegram::Type::CREATE_SHIP, creation.data()));

//    control::Ship* ship = core::manager::Entity::get().ship(ob_id);
//    EXPECT_EQ(descriptor->id(), ship->model()->descriptor());
}

TEST(communication, create_bak)
{
    assert(false);
//    int_t ob_id = core::manager::Entity::get().genId();

//    Bak* descriptor = genBak();
//    Create create(ob_id, descriptor->id());

//    core::global::get().TelegramHub().add(Telegram(Telegram::Type::CREATE_BAK, creation.data()));

//    control::Bak* bak = core::manager::Entity::get().bak(ob_id);
//    EXPECT_EQ(descriptor->id(), bak->model()->descriptor());
}

TEST(communication, inject_ship)
{
    //EXPECT_EQ(true, false);
}

//Bomb* getNewBomb(int damage, int radius)
//{
//    Base* descriptor = Manager::get().getRand(Type::BOMB);
//    core::global::get().messageManager().add(Message(TELEGRAM::CREATE_BOMB, descriptor.data()));

//    Bomb* bomb = static_cast<Bomb*>(manager::EntityManager::get().get(descriptor.id()));
//    assert(bomb);
//    return bomb;
//}

//Container* getNewContainer(const id_type& child_id)
//{
//    auto descriptor = Container(child_id);
//   core::global::get().messageManager().add(Message(TELEGRAM::CREATE_CONTAINER, descriptor.data()));

//    Container* container = static_cast<Container*>(manager::EntityManager::get().get(descriptor.id()));
//    assert(container);
//    assert(container->itemSlot());
//    assert(container->itemSlot()->item());
//    assert(container->itemSlot()->item()->id() == child_id);
//    return container;
//}
