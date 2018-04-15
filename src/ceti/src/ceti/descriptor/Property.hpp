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

#include <meti/VectorUtils.hpp>

#include <string>

namespace ceti {

class PropertyDescr : public IdDescr {
public:
    enum {INT, FLOAT, STR, VEC3};

    PropertyDescr(const IdDescr& id, int_t value)
        :
          IdDescr(id)
        , valueType(INT)
        , intValue(value)
    {}

    PropertyDescr(const IdDescr& id, int value)
        :
          IdDescr(id)
        , valueType(INT)
        , intValue(value)
    {}

    PropertyDescr(const IdDescr& id, float value)
        :
          IdDescr(id)
        , valueType(FLOAT)
        , floatValue(value)
    {}

    PropertyDescr(const IdDescr& id, const std::string& value)
        :
          IdDescr(id)
        , valueType(STR)
        , strValue(value)
    {}

    PropertyDescr(const IdDescr& id, const meti::vec3& value)
        :
          IdDescr(id)
        , valueType(VEC3)
        , vec3Value(value)
    {}

    int valueType;
    int_t intValue = 0;
    float floatValue = 0.0f;
    std::string strValue = "";
    meti::vec3 vec3Value = meti::vec3(0.0f);
};

} // namespace ceti
