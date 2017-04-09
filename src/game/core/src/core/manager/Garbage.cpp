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

#include <core/common/Base.hpp>
#include <core/manager/EntityManager.hpp>

#include <ceti/Logger.hpp>

namespace manager {

Garbage&
Garbage::get()
{
    static Garbage instance;
    return instance;
}

void Garbage::add(control::Base* ob)
{
    ob->die();

    if (m_garbage.count(ob->id()) == 1) {
        ceti::abort("attempt to registry id =" + std::to_string(ob->id()) + " which already exists");
    }
    m_garbage.insert(std::make_pair(ob->id(), ob));
}

void Garbage::clear()
{
    for(auto pair: m_garbage) {
        manager::EntityManager::get().remove(pair.second);
        delete pair.second->model();
        delete pair.second;
    }
    m_garbage.clear();
}

} // namespace manager
