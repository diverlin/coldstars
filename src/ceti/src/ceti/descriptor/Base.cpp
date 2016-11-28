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

#include "Base.hpp"


namespace ceti {

namespace descriptor {

IdGenerator Base::m_idGenerator;


Base::Base(int_t type)
    :
      m_type(type)
{
    m_id = m_idGenerator.nextId();
}

Base::Base(int_t type, int_t id)
    :
      m_type(type)
    , m_id(id)
{
    if (id == -1) {
        m_id = m_idGenerator.nextId();
    }
}

Base::~Base()
{
}


} // namespace descriptor
} // namespace ceti

