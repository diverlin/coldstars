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

#include <core/model/spaceobject/Vehicle.hpp>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <string>

namespace model {

class SpaceStation : public Vehicle
{
public:
    SpaceStation(int_t);
    ~SpaceStation() = default;
    SpaceStation(const std::string& data);
    std::string data() const;

    int_t innerLand() const { return m_innerLand; }
    void setInnerLand(int_t inner_land) { m_innerLand = inner_land; }

    ceti::InfoTable info() const override final {
        ceti::InfoTable result = SpaceStation::info();
        result.add("model::SpaceStation");
        result.add("innerLand", m_innerLand);
        return result;
    }

private:
    int_t m_innerLand = NONE;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Vehicle>(*this);
        ar & m_innerLand;
    }
};

} // namespace model
