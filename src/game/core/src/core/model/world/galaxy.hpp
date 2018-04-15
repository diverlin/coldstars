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

#include <core/model/Base.hpp>

#include <meti/VectorUtils.hpp>

#include <ceti/Pack.hpp>

#include <boost/serialization/vector.hpp>

namespace core {
class GalaxyDescr;
} // namespace descriptor


namespace model {

class Galaxy : public Base {

public:
    Galaxy(int_t, int_t);
    ~Galaxy() = default;
    Galaxy(const std::string& data);
    std::string data() const;

    void add(int_t sector) { m_sectors.add(sector); }

private:
    ceti::pack<int_t> m_sectors;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<model::Base>(*this);
        ar & m_sectors;
    }
};

} // namespace model
