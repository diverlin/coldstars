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

#include "Texture.hpp"
#include <core/type/DescriptorType.hpp>

#include <sstream>

namespace descriptor {

Material::Material(int_t type)
{
    setType(int_t(Type::MATERIAL));
    setObType(type);
}

Material::Material(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

bool
Material::operator==(const Material& rhs) const
{
    return data() == rhs.data();
}

std::string
Material::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace descriptor
