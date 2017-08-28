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

#include "Session.hpp"

#include <core/manager/EntityManager.hpp>
#include <core/manager/Garbage.hpp>

#include <ceti/Logger.hpp>

namespace core {

Session::Session()
    :
      m_entity(new manager::Entity)
    , m_garbage(new manager::Garbage)
{}

Session::~Session()
{}

Sessions&
Sessions::get()
{
    static Sessions instance;
    return instance;
}

void Sessions::add(int id, Session* session)
{
    if (m_sessions.find(id) != m_sessions.end()) {
        ceti::abort("attempt to registry id =" + std::to_string(id) + " which already exists");
    }
    m_sessions.insert(std::make_pair(id, session));
}

void Sessions::activate(int id) {
    if (m_sessions.find(id) == m_sessions.end()) {
        ceti::abort("attempt to activate id =" + std::to_string(id) + " which doesn't exists");
    }
    m_active = id;
}

Session* Sessions::session() const {
    assert(m_sessions.size()>0);
    assert(m_active != -1);
    const auto& it = m_sessions.find(m_active);
    return it->second;
}


} // core
