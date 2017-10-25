
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

#include <memory>
#include <cassert>

namespace descriptor {
class Manager;
}

// workaround
namespace jeti {
class Render;
class Screen;
} // namespace jeti
// workaround

namespace core {

namespace manager {
class Entity;
class Garbage;
} // namespace manager

class Session {
public:
    Session();
    ~Session()=default;

    std::shared_ptr<descriptor::Manager> descriptorsManager() const { return m_descriptorsManager; }
    std::shared_ptr<manager::Entity> entitiesManager() const { return m_entitiesManager; }
    std::shared_ptr<manager::Garbage> garbageManager() const { return m_garbageManager; }

    virtual jeti::Render* render() { assert(false); return nullptr; }
    virtual jeti::Screen* screen() { assert(false); return nullptr; }

private:
    std::shared_ptr<descriptor::Manager> m_descriptorsManager;
    std::shared_ptr<manager::Entity> m_entitiesManager;
    std::shared_ptr<manager::Garbage> m_garbageManager;
};

} // namespace core


