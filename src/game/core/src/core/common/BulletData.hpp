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

#include <string>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class BulletData
{
public:
    BulletData() {}

    int damage() const { return m_damage; }
    int armor() const { return m_armor; }
    int liveTime() const { return m_liveTime; }
    float speedMin() const { return m_speedMin; }
    float speedMax() const { return m_speedMax; }
    float deltaSpeed() const { return m_deltaSpeed; }
    //float m_angularSpeed = 0.0; // do we need that?

    void setDamage(int damage) { m_damage = damage; }
    void setArmor(int armor) { m_armor = armor; }
    void setLiveTime(int liveTime) { m_liveTime = liveTime; }
    void setSpeedMin(float speedMin) { m_speedMin = speedMin; }
    void setSpeedMax(float speedMax) { m_speedMax = speedMax; }
    void setDeltaSpeed(float deltaSpeed) { m_deltaSpeed = deltaSpeed; }

    std::string info() const {
        std::string result = "BulletData:\n";
        result += std::string(" damage = ") + std::to_string(m_damage) + "\n";
        result += std::string(" armor = ") + std::to_string(m_armor) + "\n";
        result += std::string(" liveTime = ") + std::to_string(m_liveTime) + "\n";
        result += std::string(" speedMin = ") + std::to_string(m_speedMin) + "\n";
        result += std::string(" speedMax = ") + std::to_string(m_speedMax) + "\n";
        result += std::string(" deltaSpeed = ") + std::to_string(m_deltaSpeed) + "\n";
        return result;
    }

private:
    int m_damage = 0;
    int m_armor = 0;
    int m_liveTime = 0;
    float m_speedMin = 0.0;
    float m_speedMax = 0.0;
    float m_deltaSpeed = 0.0;
    //    float m_angularSpeed = 0.0; // do we need that?

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & m_damage;
        ar & m_armor;
        ar & m_liveTime;
        ar & m_speedMin;
        ar & m_speedMax;
        ar & m_deltaSpeed;
        //        ar & m_angularSpeed;
    }
};

