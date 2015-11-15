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
#include <descriptors/HitDescriptor.hpp>
#include <descriptors/ExplosionDescriptor.hpp>

#include <descriptors/StarSystemDescriptorGenerator.hpp>
#include <descriptors/VehicleDescriptorGenerator.hpp>
#include <descriptors/items/BombDescriptorGenerator.hpp>
#include <descriptors/ContainerDescriptorGenerator.hpp>

#include <communication/MessageManager.hpp>
#include <managers/EntityManager.hpp>
#include <common/IdGenerator.hpp>

#include <ceti/myStr.hpp>

namespace {

Ship* createNewShip()
{
    // queue create messages
    auto descriptor = generateVehicleDescriptor();
    global::get().messageManager().add(getMessage(descriptor));

    // get entities
    Ship* ship = static_cast<Ship*>(global::get().entityManager().get(descriptor.id));
    assert(ship);
    return ship;
}

Bomb* createNewBomb()
{
    // queue create messages
    auto descriptor = generateBombDescriptor();
    global::get().messageManager().add(getMessage(descriptor));

    // get entities
    Bomb* bomb = static_cast<Bomb*>(global::get().entityManager().get(descriptor.id));
    assert(bomb);
    return bomb;
}

Container* createNewContainer(const ID& child_id)
{
    // queue create messages
    auto descriptor = generateContainerDescriptor(child_id);
    global::get().messageManager().add(getMessage(descriptor));

    // get entities
    Container* container = static_cast<Container*>(global::get().entityManager().get(descriptor.id));
    assert(container);
    return container;
}

StarSystem* createNewStarSystem()
{
    // queue create messages
    auto descriptor = generateStarSystemDescriptor();
    global::get().messageManager().add(getMessage(descriptor));

    // process messages
    global::get().messageManager().runLoop();

    // get entities
    StarSystem* starsystem = static_cast<StarSystem*>(global::get().entityManager().get(descriptor.id));
    assert(starsystem);
    return starsystem;
}

}

TEST(base,serialization)
{
    HitDescriptor hit1(1, 2, 33);
    HitDescriptor hit2(hit1.data());
    EXPECT_TRUE(hit2.agressor == hit1.agressor);
    EXPECT_TRUE(hit2.victim == hit1.victim);
    EXPECT_TRUE(hit2.damage == hit1.damage);

    VehicleDescriptor vehicle1;
    vehicle1.race_id = TYPE::RACE::R7_ID;
    VehicleDescriptor vehicle2(vehicle1.data());
    EXPECT_TRUE(vehicle2.race_id == vehicle1.race_id);

    ExplosionDescriptor explosion1(0, glm::vec3(100,200,300),0,0);
    ExplosionDescriptor explosion2(explosion1.data());
    EXPECT_TRUE(explosion1.center.x == explosion2.center.x);
    EXPECT_TRUE(explosion1.center.y == explosion2.center.y);
    EXPECT_TRUE(explosion1.center.z == explosion2.center.z);
}

TEST(base,hit)
{
    // shortcuts
    MessageManager& messageManager = global::get().messageManager();

    // create entities
    Ship* ship1 = createNewShip();
    Ship* ship2 = createNewShip();

    // hit entity
    messageManager.add(getMessage(HitDescriptor(ship1->id(), ship2->id(), 33), 0.3));
    messageManager.add(getMessage(HitDescriptor(ship1->id(), ship2->id(), 22), 0.2));
    messageManager.add(getMessage(HitDescriptor(ship1->id(), ship2->id(), 11), 0.1));
    messageManager.add(getMessage(HitDescriptor(ship1->id(), ship2->id(), ship2->criticalDamage()), 0.4));

    EXPECT_FALSE(ship2->isDying());

    // process messaging
    messageManager.runLoop();

    EXPECT_TRUE(ship2->isDying());
}

TEST(base,bomb)
{
    // shortcuts
    MessageManager& messageManager = global::get().messageManager();

    // create entities
    StarSystem* starsystem = createNewStarSystem();
    Ship* ship = createNewShip();
    Bomb* bomb = createNewBomb();
    Container* container = createNewContainer(bomb->id());
    assert(container->itemSlot());
    assert(container->itemSlot()->item());
    EXPECT_TRUE(container->itemSlot()->item()->id() == bomb->id());

    // simulate bomb explosion
    messageManager.add(getMessage(HitDescriptor(ship->id(), container->id(), container->armor())));
    messageManager.add(getMessage(ExplosionDescriptor(starsystem->id(), glm::vec3(0), 100, 200)));

    // process messaging
    messageManager.runLoop();

    EXPECT_TRUE(container->isDying());
    //EXPECT_TRUE(ship->isDying());
}


