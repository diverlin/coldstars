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

struct Planetoid : public Orientation
{
public:
    Planetoid() {}
    Planetoid(const std::string& data)
    {
        MACRO_READ_SERIALIZED_DATA
    }
    virtual ~Planetoid() {}

    std::string info() const override {
        std::string result = "Planetoid descriptor: " + ceti::descriptor::BaseView::info();
        result += std::string(" radiusA=") + std::to_string(m_radiusA);
        result += std::string(" radiusB=") + std::to_string(m_radiusB);
        result += std::string(" orbitPhi=") + std::to_string(m_orbitPhi);
        result += std::string(" speed=") + std::to_string(m_speed);
        result += std::string(" clockwise=") + std::to_string(m_clockwise);
        return result;
    }

    int radiusA() const { return m_radiusA; }
    int radiusB() const { return m_radiusB; }
    int orbitPhi() const { return m_orbitPhi; }
    float speed() const { return m_speed; }
    bool clockwise() const { return m_clockwise; }

    void setRadiusA(int radiusA) { m_radiusA = radiusA; }
    void setRadiusB(int radiusB) { m_radiusB = radiusB; }
    void setOrbitPhi(int orbitPhi) { m_orbitPhi = orbitPhi; }
    void setSpeed(int speed) { m_speed = speed; }
    void setClockwise(int clockwise) { m_clockwise = clockwise; }

private:
    int m_radiusA = 0;
    int m_radiusB = 0;
    int m_orbitPhi = 0;
    float m_speed = 0.0f;
    bool m_clockwise = true;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Orientation>(*this);
        ar & m_radiusA;
        ar & m_radiusB;
        ar & m_orbitPhi;
        ar & m_speed;
        ar & m_clockwise;
    }
}; 

} // namespace descriptor





