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

#pragma once

#include <ceti/type/IdType.hpp>

#include <map>

namespace jeti {
class Mesh;

namespace control {
class Material;
} // namespace control

} // namespace jeti

namespace view {
class Base;
} // namespace view


namespace view {

class Cache
{
public:
    Cache();
    ~Cache();

    void add(Base*);
    Base* get(int_t) const;

private:
    void __loadResourcesFor(Base*);

    std::map<int_t, Base*> m_cache;

    std::map<int_t, jeti::Mesh*> m_meshCollector;
    std::map<int_t, jeti::control::Material*> m_materialCollector;
};

} // namespace view

