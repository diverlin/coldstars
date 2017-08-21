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

#include "helper.hpp"

#include <core/type/PlaceType.hpp>
#include <core/common/Global.hpp>
#include <core/descriptor/Base.hpp>

#include <core/manager/EntityManager.hpp>
#include <core/manager/Garbage.hpp>

#include <core/pilot/Npc.hpp>

#include <core/builder/world/ALL>
#include <core/builder/spaceobject/ALL>
#include <core/builder/item/equipment/ALL>

#include <core/world/ALL>
#include <core/item/equipment/ALL>
#include <core/spaceobject/ALL>

#include <core/spaceobject/Ship.hpp>
#include <core/descriptor/spaceobject/Ship.hpp>
#include <core/model/spaceobject/Ship.hpp>

#include <ceti/Pack.hpp>

#include <gtest/gtest.h>

TEST(garbage, ship_with_items)
{
    auto& garbage = core::manager::Garbage::get();
    auto& entities = core::manager::Entity::get();

    auto ship = builder::Ship::gen();
    builder::Ship::equip(ship);
    auto items = ship->__items();
    auto npc = ship->npc();

    // collect ids
    ceti::pack<int_t> ids;

    ids.add(ship->id());
    if (npc) {
        ids.add(npc->id());
    }
    for(auto item: items) {
        ids.add(item->id());
    }

    // not in the garbage
    for(int_t id: ids) {
        EXPECT_FALSE(garbage.contain(id));
    }

    // kill
    ship->die();
    garbage.add(ship);

    // in the garbage
    for(int_t id: ids) {
        EXPECT_TRUE(garbage.contain(id));
    }

    // in the entities manager
    for(int_t id: ids) {
        EXPECT_TRUE(entities.contain(id));
    }

    // delete objects
    garbage.erase();

    // not in the garbage
    for(int_t id: ids) {
        EXPECT_FALSE(garbage.contain(id));
    }

    // not in the entities manager
    for(int_t id: ids) {
        EXPECT_FALSE(entities.contain(id));
    }
}

