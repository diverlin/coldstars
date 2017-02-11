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

#include "Game.hpp"

#include <common/Global.hpp>

#include <ai/God.hpp>

#include <world/galaxy.hpp>

#include <descriptor/GalaxyDescriptor.hpp>
#include <descriptor/DescriptorManager.hpp>

namespace model {

World::World()
{
    auto descriptor = core::global::get().descriptors().galaxy().random();
   core::global::get().god().createWorld(descriptor);
}

World::~World()
{
}

model::Starsystem*
World::activeStarsystem() const {
    assert(false);
//    return core::global::get().god().galaxy()->activeStarsystem();
}

bool World::operator==(const World& rhs) const {
    // todo implement
    return true;
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

} // namespace model
