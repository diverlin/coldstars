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

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace descriptor {
namespace comm {

class Creation
{
public:
    Creation(int_t, int_t);
    Creation(const std::string& data);
    Creation() = default;
    ~Creation() = default;
    std::string data() const;

    int_t descriptor() const { return m_descriptor; }
    int_t object() const { return m_object; }

    std::string info() const {
        std::string result = "descriptor::comm::Create:\n";
        result += std::string(" descriptor = ") + std::to_string(m_descriptor) + "\n";
        result += std::string(" object = ") + std::to_string(m_object) + "\n";
        return result;
    }

private:
    int_t m_descriptor = NONE;
    int_t m_object = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_descriptor;
        ar & m_object;
    }
};

} // namespace comm
} // namespace descriptor

