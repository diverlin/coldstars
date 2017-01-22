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

#include <core/common/Global.hpp>
#include <ceti/IdGenerator.hpp>

#include <core/world/starsystem.hpp>
#include <core/item/others/Bomb.hpp>
#include <core/slots/ItemSlot.hpp>
#include <core/spaceobjects/Container.hpp>
#include <core/spaceobjects/Ship.hpp>

#include <core/builder/spaceobjects/ShipBuilder.hpp>
#include <core/builder/world/StarSystemBuilder.hpp>
#include <core/builder/item/other/BombBuilder.hpp>
#include <core/builder/spaceobjects/ContainerBuilder.hpp>

#include <core/descriptors/DescriptorManager.hpp>
#include <core/descriptors/Base.hpp>
#include <core/descriptors/Container.hpp>
#include <core/descriptors/DescriptorGenerator.hpp>
#include <core/descriptors/VehicleDescriptorGenerator.hpp>

#include <core/communication/MessageManager.hpp>
#include <core/managers/EntityManager.hpp>

#include <gtest/gtest.h>

model::Container*
getNewContainer(int_t child_id)
{
    auto descriptor = descriptor::Container(child_id);
    core::global::get().messageManager().add(Message(TELEGRAM::CREATE_CONTAINER, descriptor.data()));

    assert(false);
//    model::Container* container = core::global::get().entityManager().getEntity<Container*>(descriptor.id());
//    assert(container->itemSlot());
//    assert(container->itemSlot()->item());
//    assert(container->itemSlot()->item()->id() == child_id);
//    return container;
}

