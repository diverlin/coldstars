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
#include <core/type/EntityType.hpp>

#include <jeti/BaseView.hpp>

namespace view {

class Base : public jeti::view::BaseView {
public:
    Base(int_t id, entity::Type type)
        :
          m_id(id)
        , m_type(type)
    {}
    ~Base() {}

    int_t id() const { return m_id; }
    entity::Type type() const { return m_type; }

private:
    int_t m_id = NONE;
    entity::Type m_type = entity::Type::NONE;
};

} // namespace view
