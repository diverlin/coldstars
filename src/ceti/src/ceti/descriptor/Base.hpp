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

#include <ceti/serialization/macro.hpp>

#include <string>

namespace ceti {
namespace descriptor {

class Base
{
public:
    Base() = default;
    ~Base() = default;

    int_t id() const { return m_id; }
    int_t type() const { return m_type; }
    int_t obType() const { return m_obType; }

    void setId(int_t id) { m_id = id; }
    void setType(int_t type) { m_type = type; }
    void setObType(int_t obType) { m_obType = obType; }

private:
    int_t m_id = NONE;
    int_t m_type = NONE;
    int_t m_obType = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_id;
        ar & m_type;
        ar & m_obType;
    }
};

} // namespace descriptor
} // namespace ceti
