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

#include <core/spaceobject/SpaceObject.hpp>

namespace descriptor {

class Bullet : public SpaceObject {

public:
    Bullet();
    ~Bullet() = default;
    Bullet(const std::string& data);
    std::string data() const;

    float speedMin() const { return m_speedMin; }
    float speedMax() const { return m_speedMax; }
    float deltaSpeed() const { return m_deltaSpeed; }
    //float m_angularSpeed = 0.0; // do we need that?

    void setSpeedMin(float speedMin) { m_speedMin = speedMin; }
    void setSpeedMax(float speedMax) { m_speedMax = speedMax; }
    void setDeltaSpeed(float deltaSpeed) { m_deltaSpeed = deltaSpeed; }

    ceti::InfoTable info() const override final {
        ceti::InfoTable result = SpaceObject::info();
        result.add("descriptor::Bullet");
        result.add("speedMin", m_speedMin);
        result.add("speedMax", m_speedMax);
        result.add("deltaSpeed", m_deltaSpeed);
        return result;
    }

private:
    float m_speedMin = 0.2f;
    float m_speedMax = 2.0f;
    float m_deltaSpeed = 0.01f;
    //    float m_angularSpeed = 0.0; // do we need that?

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<SpaceObject>(*this);
        ar & m_speedMin;
        ar & m_speedMax;
        ar & m_deltaSpeed;
        //        ar & m_angularSpeed;
    }
};

} // namespace descriptor

