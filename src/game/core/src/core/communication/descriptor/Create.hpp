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

#include "SingleIdDescr.hpp"

#include <ceti/type/IdType.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace core {

class CreateComDescr : public SingleIdDescr
{
public:
    CreateComDescr(int_t, int_t);
    CreateComDescr(const std::string& data);
    CreateComDescr() = default;
    ~CreateComDescr() = default;
    std::string data() const;

    int_t descriptor() const { return m_descriptor; }

    std::string info() const {
        std::string result = SingleIdDescr::info();
        result += "Create:\n";
        result += std::string(" descriptor = ") + std::to_string(m_descriptor) + "\n";
        return result;
    }

private:
    int_t m_descriptor = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SingleIdDescr>(*this);
        ar & m_descriptor;
    }
};

} // namespace core


