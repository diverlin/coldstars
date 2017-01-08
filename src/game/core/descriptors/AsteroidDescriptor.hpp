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

#include "PlanetoidDescriptor.hpp"

namespace descriptor {

class Asteroid : public Planetoid
{

public:
    static const int ARMOR_MIN;
    static const int ARMOR_MAX;
    static const int SCALE_MIN;
    static const int SCALE_MAX;
    static const int DISTANCE_MIN;
    static const int DISTANCE_MAX;
    static const int SPEED_MIN;
    static const int SPEED_MAX;

public:
    Asteroid() = default;
    Asteroid(const std::string& data) {
        MACRO_READ_SERIALIZED_DATA
    }
    virtual ~Asteroid() = default;

    std::string info() const override final {
        std::string result = "Asteroid descriptor: " + Planetoid::info();
        return result;
    }

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Planetoid>(*this);
    }
};

} // namespace descriptor
