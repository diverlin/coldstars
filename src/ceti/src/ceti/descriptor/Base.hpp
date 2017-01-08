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

#include <ceti/serialization/macro.hpp>
#include <ceti/type/IdType.hpp>
#include <ceti/IdGenerator.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <string>

namespace ceti {
namespace descriptor {


class Base
{
public:
    Base(int_t type = -1);
    ~Base()=default;

//    std::string data() const;

    int_t id() const { return m_id; }
    int_t type() const { return m_type; }


    void setType(int_t type) { m_type = type; }

    //std::string info() const = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_id;
        ar & m_type;
    }

    int_t m_id = -1;
    int_t m_type = -1;
    static IdGenerator m_idGenerator;
};


} // namespace descriptor
} // namespace ceti
