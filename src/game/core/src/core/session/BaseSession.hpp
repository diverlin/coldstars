
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

namespace type {
class Collector;
} // namespace type

namespace core {

class Player;

namespace manager {
class Descriptors;
class Entities;
class Garbage;
} // namespace manager

class BaseSession {
public:
    BaseSession(int id=0);
    virtual ~BaseSession()=default;

    int id() const { return m_id; }

    std::shared_ptr<manager::Descriptors> descriptors() const { return m_descriptors; }
    std::shared_ptr<manager::Entities> entities() const { return m_entities; }
    std::shared_ptr<manager::Garbage> garbage() const { return m_garbage; }
    const type::Collector& types() const { return *m_types; }

    virtual void init(bool);

    const std::string& info() const { return m_info; }

    bool isServer() const { return (m_id == 0); }
    bool isClient() const { return (m_id > 0); }

    TurnTimer& turnTimer() { return m_turnTimer; }
    void endTurn() { m_turnTimer.nextTurn(); }

private:
    int m_id = -1;  // id with 0 is server, id above 0 are clients
    TurnTimer m_turnTimer;

    std::shared_ptr<manager::Descriptors> m_descriptors;
    std::shared_ptr<manager::Entities> m_entities;
    std::shared_ptr<manager::Garbage> m_garbage;
    type::Collector* m_types = nullptr;

    std::string m_info;
};

} // namespace core


