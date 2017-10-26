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

class CreateGoodsPack : public Create
{
public:
    CreateGoodsPack(int_t, int_t, int);
    CreateGoodsPack(const std::string& data);
    ~CreateGoodsPack() = default;
    std::string data() const;

    int mass() const { return m_mass; }

    std::string info() const {
        std::string result = Create::info();
        result += "descriptor::comm::CreateGoodsPack:\n";
        result += std::string(" mass = ") + std::to_string(m_mass) + "\n";
        return result;
    }

private:
    int m_mass = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Create>(*this);
        ar & m_mass;
    }
};

} // namespace comm
} // namespace descriptor


