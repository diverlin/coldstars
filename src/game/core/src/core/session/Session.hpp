
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
namespace gui {
class UserInputInSpace;
} // namespace gui
namespace jeti {
class Render;
class Camera;
class Screen;
} // namespace jeti
namespace view {
class StarSystem;
} // namespace view
// workaround

namespace type {
class Collector;
} // namespace type

namespace core {

namespace manager {
class Descriptors;
class Entities;
class Garbage;
} // namespace manager

class Session {
public:
    enum class Type : int { NONE, SERVER, CLIENT };

    Session(Type);
    virtual ~Session()=default;

    std::shared_ptr<manager::Descriptors> descriptors() const { return m_descriptors; }
    std::shared_ptr<manager::Entities> entities() const { return m_entities; }
    std::shared_ptr<manager::Garbage> garbage() const { return m_garbage; }
    const type::Collector& types() const { return *m_types; }

    // interface
    virtual jeti::Render* render() const { assert(false); return nullptr; }
    virtual jeti::Camera* camera() const { assert(false); return nullptr; }
    virtual jeti::Screen* screen() const { assert(false); return nullptr; }
    virtual gui::UserInputInSpace* inputs() const { assert(false); return nullptr; }
    virtual view::StarSystem* view() const { assert(false); return nullptr; }
    //

    virtual void init();

    bool isServer() const { return m_type == Type::SERVER; }

    TurnTimer& turnTimer() { return m_turnTimer; }
    void endTurn() { m_turnTimer.nextTurn(); }

private:
    Type m_type = Type::NONE;
    TurnTimer m_turnTimer;

    std::shared_ptr<manager::Descriptors> m_descriptors;
    std::shared_ptr<manager::Entities> m_entities;
    std::shared_ptr<manager::Garbage> m_garbage;
    type::Collector* m_types = nullptr;
};

} // namespace core


