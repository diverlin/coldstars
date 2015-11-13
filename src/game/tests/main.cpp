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

#include <common/Global.hpp>
#include <world/starsystem.hpp>
#include <items/others/Bomb.hpp>
#include <slots/ItemSlot.hpp>
#include <spaceobjects/Container.hpp>
#include <spaceobjects/Ship.hpp>

#include <builder/spaceobjects/ShipBuilder.hpp>
#include <builder/world/GalaxyBuilder.hpp>
#include <builder/world/SectorBuilder.hpp>
#include <builder/world/StarSystemBuilder.hpp>
#include <builder/items/other/BombBuilder.hpp>
#include <builder/spaceobjects/ContainerBuilder.hpp>
#include <descriptors/GalaxyDescriptor.hpp>
#include <descriptors/SectorDescriptor.hpp>
#include <descriptors/StarSystemDescriptor.hpp>
#include <descriptors/HitEvent.hpp>

#include <communication/MessageManager.hpp>
#include <managers/EntityManager.hpp>

#include <ceti/myStr.hpp>

TEST(base, serialization)
{
    HitEvent hit1(101, 102, 33);
    HitEvent hit2(hit1.data());
    assert(hit2.agressor == hit1.agressor);
    assert(hit2.victim == hit1.victim);
    assert(hit2.damage == hit1.damage);
}

TEST(base,message)
{
    // create managers
    auto entityManager = new EntityManager;
    auto messageManager = new MessageManager;

    // create builders
    auto shipBuilder = new ShipBuilder;

    // create entities
    auto ship1 = shipBuilder->create();
    auto ship2 = shipBuilder->create();

    // register entities
    entityManager->reg(ship1);
    entityManager->reg(ship2);

    // messages
    messageManager->add(getMessage(HitEvent(ship1->id(), ship2->id(), 33), 0.3));
    messageManager->add(getMessage(HitEvent(ship1->id(), ship2->id(), 22), 0.2));
    messageManager->add(getMessage(HitEvent(ship1->id(), ship2->id(), 11), 0.1));
    messageManager->add(getMessage(HitEvent(ship1->id(), ship2->id(), ship2->criticalDamage()), 0.4));

    // process messaging
    messageManager->runLoop();

    assert(ship2->isDying());
}

TEST(base,bomb)
{
//    // create managers
//    auto entityManager = new EntityManager;
//    auto messageManager = new MessageManager;

//    // create builders
//    auto starsystemBuilder = new StarSystemBuilder;
//    auto shipBuilder = new ShipBuilder;
//    //auto bombBuilder = new BombBuilder;
//    auto containerBuilder = new ContainerBuilder;

//    // create entities
//    auto starsystem = starsystemBuilder->create(StarSystemDescriptor());
//    auto ship = shipBuilder->create(/*ShipDescriptor()*/);
//    //auto bomb = bombBuilder->create(/*BombDescriptor()*/);
//    //auto container = containerBuilder->create(bomb);

//    // register entities
//    entityManager->reg(starsystem);
//    entityManager->reg(ship);
//    //entityManager->reg(bomb);
//    //entityManager->reg(container);

    //messageManager->add(Message(TELEGRAM::CREATE_STARSYSTEM, 0, 0, ""));
//    messageManager->add(Message(TELEGRAM::CREATE_SHIP, 0, 0, ""));
//    messageManager->add(Message(TELEGRAM::CREATE_CONTAINER, 0, 0, ""));

////    messageManager->add(Message(TELEGRAM::STARSYSTEM_ADD_SHIP, ship->id(), starsystem->id(), ""));
////    messageManager->add(Message(TELEGRAM::STARSYSTEM_ADD_SHIP, ship->id(), starsystem->id(), ""));
////    messageManager->add(Message(TELEGRAM::STARSYSTEM_ADD_CONTAINER, container->id(), starsystem->id(), ""));

//    // process messaging
//    messageManager->runLoop();

//    // simulate bomb explosion
////    container->hit(container->armor());
////    ship->hit(ship->criticalDamage());
//    //starsystem->update(1);

//    assert(ship);
////    assert(container->isDying());
////    assert(ship->isDying());
//    // check consequences
//    //EXPECT_FALSE(true);

}


