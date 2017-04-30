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

#include "BaseView.hpp"

#include <core/common/Base.hpp>
#include <core/descriptor/Base.hpp>

namespace view {

Base::Base(control::Base* base)
    :
      m_control_base(base)
{}

Base::~Base()
{}

int_t Base::id() const { return m_control_base->id(); }
entity::Type Base::type() const { return m_control_base->type(); }
int_t Base::mesh() const { return m_control_base->descriptor()->mesh(); }
int_t Base::texture() const { return m_control_base->descriptor()->texture(); }

} // namespace view