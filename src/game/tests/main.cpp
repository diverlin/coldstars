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
#include <descriptors/AddToStarsystemDescriptor.hpp>

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
    auto descriptor = generateVehicleDescriptor();
    global::get().messageManager().add(Message(TELEGRAM::CREATE_SHIP, descriptor.data()));

    Ship* ship = static_cast<Ship*>(global::get().entityManager().get(descriptor.id));
    assert(ship);
    return ship;
}

Bomb* createNewBomb()
{
    auto descriptor = generateBombDescriptor();
    global::get().messageManager().add(Message(TELEGRAM::CREATE_BOMB, descriptor.data()));

    Bomb* bomb = static_cast<Bomb*>(global::get().entityManager().get(descriptor.id));
    assert(bomb);
    return bomb;
}

Container* createNewContainer(const id_type& child_id)
{
    auto descriptor = generateContainerDescriptor(child_id);
    global::get().messageManager().add(Message(TELEGRAM::CREATE_CONTAINER, descriptor.data()));

    Container* container = static_cast<Container*>(global::get().entityManager().get(descriptor.id));
    assert(container);
    assert(container->itemSlot());
    assert(container->itemSlot()->item());
    assert(container->itemSlot()->item()->id() == child_id);
    return container;
}

StarSystem* createNewStarSystem()
{
    auto descriptor = generateStarSystemDescriptor();
    global::get().messageManager().add(Message(TELEGRAM::CREATE_STARSYSTEM, descriptor.data()));

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
    MessageManager& messageManager = global::get().messageManager();

    Ship* ship1 = createNewShip();
    Ship* ship2 = createNewShip();

    messageManager.add(Message(TELEGRAM::HIT, HitDescriptor(ship1->id(), ship2->id(), 3).data(), 0.3));
    messageManager.add(Message(TELEGRAM::HIT, HitDescriptor(ship1->id(), ship2->id(), 2).data(), 0.2));
    messageManager.add(Message(TELEGRAM::HIT, HitDescriptor(ship1->id(), ship2->id(), 1).data(), 0.1));

    messageManager.runLoop();

    EXPECT_FALSE(ship2->isDying());
}

TEST(base,critical_hit)
{
    MessageManager& messageManager = global::get().messageManager();

    Ship* ship1 = createNewShip();
    Ship* ship2 = createNewShip();

    messageManager.add(Message(TELEGRAM::HIT, HitDescriptor(ship1->id(), ship2->id(), ship2->criticalDamage()).data(), 0.4));

    messageManager.runLoop();

    EXPECT_TRUE(ship2->isDying());
}

TEST(base,bomb)
{
    MessageManager& messageManager = global::get().messageManager();

    StarSystem* starsystem = createNewStarSystem();
    Ship* ship = createNewShip();
    Bomb* bomb = createNewBomb();
    Container* container = createNewContainer(bomb->id());

    glm::vec3 ship_pos = glm::vec3(200, 200, 0);
    glm::vec3 ship_angle = glm::vec3(45, 0, 0);

    messageManager.add(Message(TELEGRAM::STARSYSTEM_ADD_SHIP, AddToStarsystemDescriptor(starsystem->id(), ship->id(), ship_pos, ship_angle).data()));
    messageManager.add(Message(TELEGRAM::STARSYSTEM_ADD_CONTAINER, AddToStarsystemDescriptor(starsystem->id(), container->id(), ship_pos, ship_angle).data()));
    messageManager.add(Message(TELEGRAM::HIT, HitDescriptor(ship->id(), container->id(), container->armor()).data()));

    messageManager.runLoop();

    EXPECT_EQ(ship_pos, ship->center());
    EXPECT_EQ(ship_pos, container->center());

    //messageManager.add(getMessage(HitDescriptor(ship->id(), container->id(), container->armor())));
//    messageManager.add(getMessage(ExplosionDescriptor(starsystem->id(), glm::vec3(0), 100, 200)));

//    EXPECT_TRUE(container->isDying());
//    EXPECT_TRUE(ship->isDying());
}


