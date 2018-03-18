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

#include "World.hpp"

#include <common/Global.hpp>

#include <ai/God.hpp>

#include <world/galaxy.hpp>

#include <core/descriptor/world/GalaxyDescriptor.hpp>

#include <core/session/Session.hpp>
#include <core/manager/DescriptorManager.hpp>

namespace control {

World::World()
{
    core::global::get().god().createWorld();
}

World::~World()
{
}

Galaxy*
World::galaxy() const {
    return core::global::get().god().galaxy();
}

bool World::run() const
{
    while (m_isRunning) {
       core::global::get().god().update();
    }
    return EXIT_SUCCESS;
}

void World::update()
{
   core::global::get().god().update();
}

} // namespace control
