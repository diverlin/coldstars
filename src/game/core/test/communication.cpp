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
#include <core/item/others/Bomb.hpp>
#include <core/slots/ItemSlot.hpp>
#include <core/spaceobjects/Container.hpp>
#include <core/spaceobjects/Ship.hpp>

#include <core/item/equipment/ALL>

#include <core/builder/spaceobjects/ShipBuilder.hpp>
#include <core/builder/world/StarSystemBuilder.hpp>
#include <core/builder/item/other/BombBuilder.hpp>
#include <core/builder/spaceobjects/ContainerBuilder.hpp>

#include <core/descriptors/DescriptorManager.hpp>
#include <core/descriptors/Base.hpp>
#include <core/descriptors/Descriptor.hpp>
#include <core/descriptors/Container.hpp>
#include <core/descriptors/DescriptorGenerator.hpp>
#include <core/descriptors/VehicleDescriptorGenerator.hpp>

#include <core/communication/MessageManager.hpp>
#include <core/managers/EntityManager.hpp>

#include <ceti/IdGenerator.hpp>


TEST(communication, create_ship)
{
    auto descriptor = core::global::get().descriptors().getRand(descriptor::Type::VEHICLE);
    int_t obj_id = core::global::get().idGenerator().nextId();
    descriptor::DescriptorOLD descriptor2(descriptor.id(), obj_id);
    core::global::get().messageManager().add(Message(TELEGRAM::CREATE_SHIP, descriptor2.data()));

    model::Ship* ship = model::getShip(obj_id);
    assert(ship);
    EXPECT_EQ(ship->id(), obj_id);
}

TEST(communication, create_bak)
{
    auto descriptor = core::global::get().descriptors().getRand(descriptor::Type::BAK);
    int_t obj_id = core::global::get().idGenerator().nextId();
    descriptor::DescriptorOLD descriptor2(descriptor.id(), obj_id);
    core::global::get().messageManager().add(Message(TELEGRAM::CREATE_BAK, descriptor2.data()));

    assert(false);
//    item::Bak* bak = core::global::get().entityManager().getEntity<item::Bak*>(obj_id);
//    assert(bak);
//    EXPECT_EQ(bak->id(), obj_id);
}

TEST(communication, inject_ship)
{
    //EXPECT_EQ(true, false);
}

//Bomb* getNewBomb(int damage, int radius)
//{
//    const descriptor::Base& descriptor = core::global::get().descriptors().getRand(descriptor::Type::BOMB);
//   core::global::get().messageManager().add(Message(TELEGRAM::CREATE_BOMB, descriptor.data()));

//    Bomb* bomb = static_cast<Bomb*>(core::global::get().entityManager().get(descriptor.id()));
//    assert(bomb);
//    return bomb;
//}

//Container* getNewContainer(const id_type& child_id)
//{
//    auto descriptor = descriptor::Container(child_id);
//   core::global::get().messageManager().add(Message(TELEGRAM::CREATE_CONTAINER, descriptor.data()));

//    Container* container = static_cast<Container*>(core::global::get().entityManager().get(descriptor.id()));
//    assert(container);
//    assert(container->itemSlot());
//    assert(container->itemSlot()->item());
//    assert(container->itemSlot()->item()->id() == child_id);
//    return container;
//}

TEST(comm, new_starsystem)
{
    //    const descriptor::Base& descriptor = core::global::get().descriptors().getRand(descriptor::Type::STARSYSTEM);
    //   core::global::get().messageManager().add(Message(TELEGRAM::CREATE_STARSYSTEM, descriptor.data()));

    //    Starsystem* starsystem = static_cast<Starsystem*>(core::global::get().entityManager().get(descriptor.id()));
    //    assert(starsystem);
    //Starsystem* starsystem = core::global::get().entityManager().get<Starsystem*>(descriptor.id());
}
