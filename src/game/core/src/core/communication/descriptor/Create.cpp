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

#include "Create.hpp"

#include <ceti/serialization/macro.hpp>

namespace descriptor {
namespace comm {


Create::Create(int_t descriptor, int_t object)
    :
      Object(object)
    , m_descriptor(descriptor)
{
}

Create::Create(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Create::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace comm
} // namespace descriptor

