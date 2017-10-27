
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

# pragma once

#include <core/common/TurnTimer.hpp>

#include <memory>
#include <cassert>

// workaround
class UserInputInSpace;
namespace jeti {
class Render;
class Camera;
class Screen;
} // namespace jeti
namespace view {
class StarSystem;
} // namespace view
// workaround

namespace descriptor {
class Manager;
}

namespace type {
class Collector;
} // namespace type

namespace core {

namespace manager {
class Entity;
class Garbage;
} // namespace manager

class Session {
public:
    Session();
    virtual ~Session()=default;

    std::shared_ptr<descriptor::Manager> descriptorsManager() const { return m_descriptorsManager; }
    std::shared_ptr<manager::Entity> entitiesManager() const { return m_entitiesManager; }
    std::shared_ptr<manager::Garbage> garbageManager() const { return m_garbageManager; }
    const type::Collector& types() const { return *m_types; }

    // interface
    virtual jeti::Render* render() const { assert(false); return nullptr; }
    virtual jeti::Camera* camera() const { assert(false); return nullptr; }
    virtual jeti::Screen* screen() const { assert(false); return nullptr; }
    virtual UserInputInSpace* inputs() const { assert(false); return nullptr; }
    virtual view::StarSystem* view() const { assert(false); return nullptr; }
    //

    virtual void init() {}

    TurnTimer& turnTimer() { return m_turnTimer; }
    void endTurn() { m_turnTimer.nextTurn(); }

private:
    TurnTimer m_turnTimer;

    std::shared_ptr<descriptor::Manager> m_descriptorsManager;
    std::shared_ptr<manager::Entity> m_entitiesManager;
    std::shared_ptr<manager::Garbage> m_garbageManager;
    type::Collector* m_types = nullptr;
};

} // namespace core


