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
#include <core/spaceobject/Planet.hpp>
#include <core/spaceobject/Asteroid.hpp>
#include <core/type/TelegramType.hpp>

#include <core/model/spaceobject/Ship.hpp>
#include <core/model/spaceobject/Asteroid.hpp>
#include <core/model/world/starsystem.hpp>
#include <core/model/world/Sector.hpp>
#include <core/model/world/galaxy.hpp>

#include <core/builder/spaceobject/AsteroidBuilder.hpp>
#include <core/builder/spaceobject/ShipBuilder.hpp>
#include <core/builder/world/GalaxyBuilder.hpp>
#include <core/builder/world/SectorBuilder.hpp>
#include <core/builder/world/StarSystemBuilder.hpp>
#include <core/builder/item/other/BombBuilder.hpp>
#include <core/builder/spaceobject/ContainerBuilder.hpp>
#include <core/builder/spaceobject/AsteroidBuilder.hpp>

#include <core/manager/DescriptorManager.hpp>
#include <core/descriptor/Base.hpp>
#include <core/descriptor/spaceobject/Container.hpp>

#include <core/communication/descriptor/Hit.hpp>
#include <core/communication/descriptor/AddToStarsystem.hpp>

#include <core/descriptor/world/GalaxyDescriptor.hpp>
#include <core/descriptor/world/SectorDescriptor.hpp>
#include <core/descriptor/ExplosionDescriptor.hpp>

#include <core/generator/DescriptorGenerator.hpp>

#include <core/communication/TelegramHub.hpp>

#include <core/builder/item/equipment/ALL>
#ifdef USE_MODULES
#include <core/builder/item/module/ALL>
#endif
#ifdef USE_ARTEFACTS
#include <core/builder/item/artefacts/ALL>
#endif
#include <core/builder/item/other/ALL>

#include <core/world/ALL>

#include <core/item/equipment/ALL>

#include "helper.hpp"

#include <ctime>

TEST(descriptor, accessors)
{
    descriptor::comm::Hit descriptor(22, 33, 44);
    EXPECT_EQ(descriptor.owner(), 22);
    EXPECT_EQ(descriptor.target(), 33);
    EXPECT_EQ(descriptor.damage(), 44);
}

TEST(base, hit)
{
    core::comm::TelegramHub& messageHub = core::global::get().telegramHub();

    core::control::Ship* ship1 = GovermentBuilder::ShipBuilder::gen();
    core::control::Ship* ship2 = GovermentBuilder::ShipBuilder::gen();

    assert(false);
//    messageHub.add(core::comm::Telegram(telegram::Type::HIT, descriptor::comm::Hit(ship1->id(), ship2->id(), 3).data(), 0.3));
//    messageHub.add(core::comm::Telegram(telegram::Type::HIT, descriptor::comm::Hit(ship1->id(), ship2->id(), 2).data(), 0.2));
//    messageHub.add(core::comm::Telegram(telegram::Type::HIT, descriptor::comm::Hit(ship1->id(), ship2->id(), 1).data(), 0.1));

    //messageHub.runLoop();

    EXPECT_FALSE(ship2->isAlive());
}

TEST(base, critical_hit)
{
    assert(false);
//    core::comm::TelegramHub& messageHub = core::global::get().TelegramHub();

//    control::Ship* ship1 = builder::Ship::gen();
//    control::Ship* ship2 = builder::Ship::gen();

//    messageHub.add(core::comm::Telegram(core::comm::Telegram::Type::HIT, descriptor::comm::Hit(ship1->id(), ship2->id(), 100000).data(), 0.4));

//    //messageManager.runLoop();

//    EXPECT_TRUE(ship2->isAlive());
}

TEST(base, bomb)
{
//    MessageManager& messageManager = core::global::get().messageManager();

//    Starsystem* starsystem = StarsystemBuilder::gen();
//    Ship* ship = ShipBuilder::gen();
//    Bomb* bomb = BombBuilder::gen(); //getNewBomb(1000, 1000);
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

TEST(descriptor, manager)
{
    // TODO fix fail
//    DescriptorManager& descriptor_manager = core::global::get().descriptorManager();
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
    core::control::Galaxy* galaxy = GovermentBuilder::GalaxyBuilder::gen();

    // clone
    model::Galaxy* model = new model::Galaxy(galaxy->model()->data());
    core::control::Galaxy* clone = new core::control::Galaxy(galaxy->descriptor(), model);

    EXPECT_EQ(galaxy->model()->data(), clone->model()->data());

    // clear
    delete model;
    delete clone;
}

TEST(clone, sector)
{
    core::control::Sector* sector = GovermentBuilder::SectorBuilder::gen();

    // clone
    model::Sector* model = new model::Sector(sector->model()->data());
    core::control::Sector* clone = new core::control::Sector(sector->descriptor(), model);

    EXPECT_EQ(sector->model()->data(), clone->model()->data());

    // clear
    delete model;
    delete clone;
}

TEST(clone, starsystem)
{
    core::control::StarSystem* starsystem = GovermentBuilder::StarSystemBuilder::gen();

    // clone
    model::StarSystem* model = new model::StarSystem(starsystem->model()->data());
    core::control::StarSystem* clone = new core::control::StarSystem(starsystem->descriptor(), model);

    EXPECT_EQ(starsystem->model()->data(), clone->model()->data());

    // clear
    delete model;
    delete clone;
}

TEST(clone, asteroid)
{
    core::control::Asteroid* asteroid = GovermentBuilder::AsteroidBuilder::gen();

    // clone
    model::Asteroid* model = new model::Asteroid(asteroid->model()->data());
    core::control::Asteroid* clone = new core::control::Asteroid(asteroid->descriptor(), model);

    EXPECT_EQ(asteroid->model()->data(), clone->model()->data());

    // clear
    delete model;
    delete clone;
}
