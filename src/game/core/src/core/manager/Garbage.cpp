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

#include "Garbage.hpp"

#include <core/Base.hpp>
#include <core/session/Shortcuts.hpp>
#include <core/manager/EntityManager.hpp>

#include <ceti/Logger.hpp>

namespace core {
namespace manager {

void Garbage::add(control::Base* ob)
{
    if (ob->isAlive()) {
        // executaed for children
        ob->die();
    }

    if (m_entities.find(ob->id()) != m_entities.end()) {
        ceti::abort("attempt to registry id =" + std::to_string(ob->id()) + " which already exists");
    }
    m_entities.insert(std::make_pair(ob->id(), ob));
}

void Garbage::erase()
{
    for(const auto& pair: m_entities) {
        control::Base* ob = pair.second;
        core::shortcuts::entities()->remove(ob);
        delete ob->model();
        delete ob;
    }
    m_entities.clear();
}

} // namespace manager
} // core
