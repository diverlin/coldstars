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

#include <core/descriptor/Base.hpp>

#include <ceti/StringUtils.hpp>

#include <vector>
#include <boost/serialization/vector.hpp>

namespace descriptor {

struct StarSystem : public Base
{
public:
    StarSystem();
    StarSystem(const std::string&);
    std::string data() const;
    ~StarSystem() = default;

    const std::vector<int_t>& stars() const { return m_stars; }
    const std::vector<int_t>& planets() const { return m_planets; }

    std::string info() const {
        std::string result = "descriptor::StarSystem: " + Base::info();
        result += ceti::to_string(" stars: ", m_stars);
        result += ceti::to_string(" planets: ", m_planets);
        return result;
    }

private:
    std::vector<int_t> m_stars;
    std::vector<int_t> m_planets;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Base>(*this);
        ar & m_stars;
        ar & m_planets;
    }
}; 

} // namespace descriptor





