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

#include <descriptor/comm/Create.hpp>

#include <meti/VectorUtils.hpp>
#include <ceti/StringUtils.hpp>

namespace descriptor {
namespace comm {

class AddingPositional {
public:
    AddingPositional(int_t, int_t, const meti::vec3& position = glm::vec3());
    AddingPositional(const std::string& data);
    AddingPositional() = default;
    ~AddingPositional() = default;
    std::string data() const;

    int_t parent() const { return m_parent; }
    int_t object() const { return m_object; }
    const meti::vec3& position() const { return m_position; }

    std::string info() const {
        std::string result = "descriptor::comm::AddingPositional:\n";
        result += std::string(" parent = ") + std::to_string(m_parent) + "\n";
        result += std::string(" object = ") + std::to_string(m_object) + "\n";
        result += std::string(" position = ") + ceti::to_string(m_position) + "\n";
        return result;
    }

private:
    int_t m_parent = NONE;
    int_t m_object = NONE;
    meti::vec3 m_position;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_parent;
        ar & m_object;
        ar & m_position;
    }
};

} // namespace comm
} // namespace descriptor


