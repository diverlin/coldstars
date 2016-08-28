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

#include "Base.hpp"
#include "Id.hpp"
#include "Property.hpp"

#include <boost/serialization/map.hpp>

namespace ceti {
namespace descriptor {


class Descriptor : public Base
{
public:
    Descriptor(const int_t& type = -1, const int_t& id = -1);
    Descriptor(const std::string& data);
    ~Descriptor();

    std::string data() const;

    bool operator==(const Descriptor& rhs) const;

    const int_t& get(int) const;

    void add(const Property&);
    void add(const std::vector<Property>&);

    std::string info() const;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Base>(*this);
        ar & m_intValues;
        ar & m_strValues;
    }

    std::map<int, int_t> m_intValues;
    std::map<int, std::string> m_strValues;

public:
    static std::map<int, Id> m_ids;
};


} // namespace descriptor
} // namespace ceti
