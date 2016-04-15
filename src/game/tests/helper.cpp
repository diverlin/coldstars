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
#include <common/IdGenerator.hpp>
#include <world/starsystem.hpp>
#include <items/others/Bomb.hpp>
#include <slots/ItemSlot.hpp>
#include <spaceobjects/Container.hpp>
#include <spaceobjects/Ship.hpp>

#include <builder/spaceobjects/ShipBuilder.hpp>
#include <builder/world/StarSystemBuilder.hpp>
#include <builder/items/other/BombBuilder.hpp>
#include <builder/spaceobjects/ContainerBuilder.hpp>

#include <descriptors/DescriptorManager.hpp>
#include <descriptors/Base.hpp>
#include <descriptors/Container.hpp>
#include <descriptors/DescriptorGenerator.hpp>
#include <descriptors/VehicleDescriptorGenerator.hpp>

#include <communication/MessageManager.hpp>
#include <managers/EntityManager.hpp>

Ship* createNewShip()
{
    auto descriptor = generateVehicleDescriptor();
    global::get().messageManager().add(Message(TELEGRAM::CREATE_SHIP, descriptor.data()));

    Ship* ship = static_cast<Ship*>(global::get().entityManager().get(descriptor.id));
    assert(ship);
    return ship;
}


Bomb* createNewBomb(int damage, int radius)
{
    descriptor::Base descriptor = generateBombDescriptor(damage, radius);
    global::get().messageManager().add(Message(TELEGRAM::CREATE_BOMB, descriptor.data()));

    Bomb* bomb = static_cast<Bomb*>(global::get().entityManager().get(descriptor.id()));
    assert(bomb);
    return bomb;
}

Container* createNewContainer(const id_type& child_id)
{
    auto descriptor = descriptor::Container(global::get().idGenerator().nextId(), child_id);
    global::get().messageManager().add(Message(TELEGRAM::CREATE_CONTAINER, descriptor.data()));

    Container* container = static_cast<Container*>(global::get().entityManager().get(descriptor.id()));
    assert(container);
    assert(container->itemSlot());
    assert(container->itemSlot()->item());
    assert(container->itemSlot()->item()->id() == child_id);
    return container;
}

StarSystem* createNewStarSystem()
{
    descriptor::Base descriptor = generateStarSystemDescriptor();
    global::get().messageManager().add(Message(TELEGRAM::CREATE_STARSYSTEM, descriptor.data()));

    StarSystem* starsystem = static_cast<StarSystem*>(global::get().entityManager().get(descriptor.id()));
    assert(starsystem);
    return starsystem;
}

void init_equipment_descriptors()
{
    DescriptorManager& descriptor_manager = global::get().descriptorManager();

    bool generate_new = true;
    if (generate_new) {
        descriptor_manager.add(generateBakDescriptor());
        descriptor_manager.add(generateDriveDescriptor());
        descriptor_manager.add(generateDroidDescriptor());
        descriptor_manager.add(generateGrappleDescriptor());
        descriptor_manager.add(generateScanerDescriptor());
        descriptor_manager.add(generateRadarDescriptor());
        descriptor_manager.add(generateProtectorDescriptor());
    } else {
        // todo: read from file
    }
}

