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

#include "SpaceObject.hpp"

namespace descriptor {

struct PlanetoidDescr : public SpaceObjectDescr
{
public:
    PlanetoidDescr() = default;
    ~PlanetoidDescr() = default;

    void setRadiusA(int radiusA) { m_radiusA = radiusA; }
    void setRadiusB(int radiusB) { m_radiusB = radiusB; }
    void setOrbitPhi(int orbitPhi) { m_orbitPhi = orbitPhi; }
    void setSpeed(float speed) { m_speed = speed; }
    void setClockwise(int clockwise) { m_clockwise = clockwise; }
    void setAtmosphereMaterial(int_t material) { m_atmosphereMaterial = material; }

    int radiusA() const { return m_radiusA; }
    int radiusB() const { return m_radiusB; }
    int orbitPhi() const { return m_orbitPhi; }
    float speed() const { return m_speed; }
    bool clockwise() const { return m_clockwise; }
    int_t atmosphereMaterial() const { return m_atmosphereMaterial; }

    ceti::InfoTable info() const override {
        ceti::InfoTable result = SpaceObjectDescr::info();
        result.add("Planetoid descriptor");
        result.add("radius", m_radiusA);
        result.add("radiusB", m_radiusB);
        result.add("orbitPhi", m_orbitPhi);
        result.add("speed", m_speed);
        result.add("clockwise", m_clockwise);
        result.add("atmosphereTexture", m_atmosphereMaterial);
        return result;
    }

private:
    int m_radiusA = 0;
    int m_radiusB = 0;
    int m_orbitPhi = 0;
    float m_speed = 0.0f;
    bool m_clockwise = true;
    int_t m_atmosphereMaterial = NONE;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SpaceObjectDescr>(*this);
        ar & m_radiusA;
        ar & m_radiusB;
        ar & m_orbitPhi;
        ar & m_speed;
        ar & m_clockwise;
        ar & m_atmosphereMaterial;
    }
}; 

} // namespace descriptor





