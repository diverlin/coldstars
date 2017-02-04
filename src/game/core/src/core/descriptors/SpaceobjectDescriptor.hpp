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

#include "OrientationDescriptor.hpp"

namespace descriptor {

struct SpaceObject : public Orientation
{
public:
    SpaceObject() = default;
    SpaceObject(const std::string& data) {
        MACRO_READ_SERIALIZED_DATA
    }
    virtual ~SpaceObject() = default;

    std::string info() const {
        std::string result = "SpaceObject descriptor:\n";
        result += std::string(" armor=") + std::to_string(m_armor) + "\n";
        result += Orientation::info();
        return result;
    }

    int armor() const { return m_armor; }

    void setArmor(int armor) { m_armor = armor; }

private:
    int m_armor = 0;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Orientation>(*this);
        ar & m_armor;
    }
}; 

} // namespace descriptor





