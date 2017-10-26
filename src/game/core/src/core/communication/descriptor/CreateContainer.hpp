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

#include <ceti/type/IdType.hpp>
#include <ceti/StringUtils.hpp>

#include <meti/VectorUtils.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace descriptor {
namespace comm {

class CreateContainer : public Create
{
public:
    CreateContainer(int_t, int_t, int_t);
    CreateContainer(const std::string& data);
    ~CreateContainer() = default;
    std::string data() const;

    int item() const { return m_item; }

    std::string info() const {
        std::string result = Create::info();
        result += "descriptor::comm::CreateContainer:\n";
        result += std::string(" item = ") + std::to_string(m_item) + "\n";
        return result;
    }

private:
    int m_item = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Create>(*this);
        ar & m_item;
    }
};

} // namespace comm
} // namespace descriptor


