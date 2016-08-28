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

#include "Id.hpp"

#include <ceti/type/IdType.hpp>

#include <string>

namespace ceti {
namespace descriptor {

class Property : public Id {
public:
    enum {INT, STR};

    Property(const Id& id, const int_t& value)
        :
          Id(id)
        , valueType(INT)
        , intValue(value)
    {}
    Property(const Id& id, const std::string& value)
        :
          Id(id)
        , valueType(STR)
        , strValue(value)
    {}
    int valueType;
    int_t intValue = 0;
    std::string strValue = "";
};

} // namespace descriptor
} // namespace ceti
