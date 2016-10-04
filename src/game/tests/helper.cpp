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
#include <ceti/IdGenerator.hpp>
#include <world/starsystem.hpp>
#include <item/others/Bomb.hpp>
#include <slots/ItemSlot.hpp>
#include <spaceobjects/Container.hpp>
#include <spaceobjects/Ship.hpp>

#include <builder/spaceobjects/ShipBuilder.hpp>
#include <builder/world/StarSystemBuilder.hpp>
#include <builder/item/other/BombBuilder.hpp>
#include <builder/spaceobjects/ContainerBuilder.hpp>

#include <descriptors/DescriptorManager.hpp>
#include <descriptors/Base.hpp>
#include <descriptors/Container.hpp>
#include <descriptors/DescriptorGenerator.hpp>
#include <descriptors/VehicleDescriptorGenerator.hpp>

#include <communication/MessageManager.hpp>
#include <managers/EntityManager.hpp>

Container* getNewContainer(const int_t& child_id)
{
    auto descriptor = descriptor::Container(child_id);
    global::get().messageManager().add(Message(TELEGRAM::CREATE_CONTAINER, descriptor.data()));

    Container* container = global::get().entityManager().getEntity<Container*>(descriptor.id());
    assert(container->itemSlot());
    assert(container->itemSlot()->item());
    assert(container->itemSlot()->item()->id() == child_id);
    return container;
}

