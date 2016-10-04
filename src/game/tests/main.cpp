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
#include <item/others/Bomb.hpp>
#include <slots/ItemSlot.hpp>
#include <spaceobjects/Container.hpp>
#include <spaceobjects/Ship.hpp>
#include <spaceobjects/Planet.hpp>
#include <spaceobjects/Asteroid.hpp>

#include <builder/spaceobjects/AsteroidBuilder.hpp>
#include <builder/spaceobjects/ShipBuilder.hpp>
#include <builder/world/GalaxyBuilder.hpp>
#include <builder/world/SectorBuilder.hpp>
#include <builder/world/StarSystemBuilder.hpp>
#include <builder/item/other/BombBuilder.hpp>
#include <builder/spaceobjects/ContainerBuilder.hpp>

#include <descriptors/DescriptorManager.hpp>
#include <descriptors/Base.hpp>
#include <descriptors/Container.hpp>
#include <descriptors/Hit.hpp>
#include <descriptors/GalaxyDescriptor.hpp>
#include <descriptors/SectorDescriptor.hpp>
#include <descriptors/ExplosionDescriptor.hpp>
#include <descriptors/AddToStarsystemDescriptor.hpp>

#include <descriptors/VehicleDescriptorGenerator.hpp>
#include <descriptors/DescriptorGenerator.hpp>

#include <communication/MessageManager.hpp>

#include <ctime>

#include <builder/item/equipment/ALL>
#include <builder/item/modules/ALL>
#include <builder/item/artefacts//ALL>
#include <builder/item/other/ALL>

#include <world/galaxy.hpp>
#include <world/Sector.hpp>
#include <world/starsystem.hpp>

#include <item/equipment/ALL>

#include "helper.hpp"

TEST(descriptor,accessors)
{
    descriptor::Hit descriptor(22, 33, 44);
    EXPECT_EQ(descriptor.owner(), 22);
    EXPECT_EQ(descriptor.target(), 33);
    EXPECT_EQ(descriptor.damage(), 44);
    ASSERT_THROW(descriptor.radius(), std::runtime_error);
}

TEST(base,hit)
{
    MessageManager& messageManager = global::get().messageManager();

    Ship* ship1 = ShipBuilder::getNew();
    Ship* ship2 = ShipBuilder::getNew();

    messageManager.add(Message(TELEGRAM::HIT, descriptor::Hit(ship1->id(), ship2->id(), 3).data(), 0.3));
    messageManager.add(Message(TELEGRAM::HIT, descriptor::Hit(ship1->id(), ship2->id(), 2).data(), 0.2));
    messageManager.add(Message(TELEGRAM::HIT, descriptor::Hit(ship1->id(), ship2->id(), 1).data(), 0.1));

    messageManager.runLoop();

    EXPECT_FALSE(ship2->isDying());
}

TEST(base,critical_hit)
{
    MessageManager& messageManager = global::get().messageManager();

    Ship* ship1 = ShipBuilder::getNew();
    Ship* ship2 = ShipBuilder::getNew();

    messageManager.add(Message(TELEGRAM::HIT, descriptor::Hit(ship1->id(), ship2->id(), ship2->criticalDamage()).data(), 0.4));

    messageManager.runLoop();

    EXPECT_TRUE(ship2->isDying());
}

TEST(base,bomb)
{
//    MessageManager& messageManager = global::get().messageManager();

//    Starsystem* starsystem = StarsystemBuilder::getNew();
//    Ship* ship = ShipBuilder::getNew();
//    Bomb* bomb = BombBuilder::getNew(); //getNewBomb(1000, 1000);
//    Container* container = getNewContainer(bomb->id());

//    const glm::vec3 ship_pos = glm::vec3(200, 200, 0);
//    const glm::vec3 ship_angle = glm::vec3(45, 0, 0);

//    // todo strange undef error //messageManager.add(Message(TELEGRAM::STARSYSTEM_ADD_SHIP, AddToStarsystemDescriptor(starsystem->id(), ship->id(), ship_pos, ship_angle).data()));
//    // todo strange undef error //messageManager.add(Message(TELEGRAM::STARSYSTEM_ADD_CONTAINER, AddToStarsystemDescriptor(starsystem->id(), container->id(), ship_pos, ship_angle).data()));
//    messageManager.add(Message(TELEGRAM::HIT, descriptor::Hit(ship->id(), container->id(), container->armor()).data()));

//    messageManager.runLoop();

    //    EXPECT_EQ(ship_pos, ship->center()); TODO: fix FAIL
    //    EXPECT_EQ(ship_pos, container->center());

    //messageManager.add(getMessage(HitDescriptor(ship->id(), container->id(), container->armor())));
    //    messageManager.add(getMessage(ExplosionDescriptor(starsystem->id(), glm::vec3(0), 100, 200)));

    //    EXPECT_TRUE(container->isDying());
    //    EXPECT_TRUE(ship->isDying());
}

TEST(descriptor,manager)
{
    // TODO fix fail
//    DescriptorManager& descriptor_manager = global::get().descriptorManager();
//    descriptor::Hit descriptor_hit(1, 2, 3);
//    descriptor::Base descriptor_starsystem = generateStarSystemDescriptor();
//    descriptor::Base descriptor_bak = generateBakDescriptor();
//    descriptor_manager.add(descriptor_hit);
//    descriptor_manager.add(descriptor_starsystem);
//    descriptor_manager.add(descriptor_bak);

//    EXPECT_EQ(descriptor_manager.get(descriptor_hit.id()), descriptor_hit);

//    EXPECT_EQ(descriptor_manager.getRandom(descriptor::Type::HIT).type(), int(descriptor::Type::HIT));
//    EXPECT_EQ(descriptor_manager.getRandom(descriptor::Type::STARSYSTEM).type(), int(descriptor::Type::STARSYSTEM));
//    EXPECT_EQ(descriptor_manager.getRandom(descriptor::Type::BAK).type(), int(descriptor::Type::BAK));
}

TEST(clone, galaxy)
{
    const auto& descriptor = global::get().descriptors().galaxy().random();
    auto g1 = global::get().galaxyBuilder().create(descriptor);
    auto g2 = global::get().galaxyBuilder().create(descriptor);
    EXPECT_EQ(*g1, *g2);
}

TEST(clone, sector)
{
    const auto& descriptor = global::get().descriptors().sector().random();
    auto s1 = global::get().sectorBuilder().create(descriptor);
    auto s2 = global::get().sectorBuilder().create(descriptor);
    EXPECT_EQ(*s1, *s2);
}

TEST(clone, starsystem)
{
    const auto& descriptor = global::get().descriptors().starsystem().random();
    auto s1 = global::get().starsystemBuilder().create(descriptor);
    auto s2 = global::get().starsystemBuilder().create(descriptor);
    EXPECT_EQ(*s1, *s2);
}

TEST(model, asteroid)
{
    model::Asteroid* model1 = builder::Asteroid::create();
    model::Asteroid* model2 = new model::Asteroid(model1->data());
    EXPECT_EQ(model1->data(), model2->data());

    delete model1;
    delete model2;
}
