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

//#include "Base.hpp"
#include <core/type/TelegramType.hpp>

#include <ceti/type/IdType.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace descriptor {
namespace comm {

class Creation /*: public Base*/
{
public:
    Creation(int_t, int_t);
    Creation(const std::string& data);
    ~Creation() = default;
    std::string data() const;

//    void setObId(int_t obId) { m_obId = obId; }
//    void setObDescriptor(int_t obDescriptor) { m_obDescriptor = obDescriptor; }

    int_t obId() const { return m_obId; }
    int_t obDescriptor() const { return m_obDescriptor; }

    std::string info() const {
        std::string result = "comm::descriptor::Creation:\n";
        result += std::string(" obId = ") + std::to_string(m_obId) + "\n";
        result += std::string(" obDescriptor = ") + std::to_string(m_obDescriptor) + "\n";
        return result;
    }

private:
    int_t m_obId = NONE;
    int_t m_obDescriptor = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
//        ar & boost::serialization::base_object<Base>(*this);
        ar & m_obId;
        ar & m_obDescriptor;
    }
};

} // namespace comm
} // namespace descriptor


