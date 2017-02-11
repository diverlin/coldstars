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

#include "Equipment.hpp"


namespace descriptor {
namespace item {

class Grapple : public Equipment
{
public:
    static const int STRENGTH_MIN;
    static const int STRENGTH_MAX;
    static const float STRENGTH_TECH_RATE;

    static const int RADIUS_MIN;
    static const int RADIUS_MAX;
    static const float RADIUS_TECH_RATE;

    static const int SPEED_MIN;
    static const int SPEED_MAX;
    static const float SPEED_TECH_RATE;

    static const int MODULES_NUM_MIN;
    static const int MODULES_NUM_MAX;
    static const int MASS_MIN;
    static const int MASS_MAX;
    static const int CONDITION_MIN;
    static const int CONDITION_MAX;

    static const float STRENGTH_WEIGHT;
    static const float RADIUS_WEIGHT;
    static const float SPEED_WEIGHT;
    static const float MAXNUMITEM_WEIGHT;
    static const float MODULES_NUM_WEIGHT;

public:
    Grapple();
    ~Grapple() = default;
    Grapple(const std::string& data);
    std::string data() const;

    void setStrength(int strength)     { m_strength = strength; }
    void setRadius(int radius)         { m_radius = radius; }
    void setSpeed(int speed)           { m_speed = speed; }

    int strength() const { return m_strength; }
    int radius() const { return m_radius; }
    int speed() const { return m_speed; }

    std::string info() const {
        std::string result = "descriptor::item::Grapple:\n";
        result += std::string(" strength = ") + std::to_string(m_strength) + "\n";
        result += std::string(" radius = ") + std::to_string(m_radius) + "\n";
        result += std::string(" speed = ") + std::to_string(m_speed) + "\n";
        result += descriptor::item::Equipment::info();
        return result;
    }

private:
    int m_strength = 0;
    int m_radius = 0;
    int m_speed = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Equipment>(*this);
        ar & m_strength;
        ar & m_radius;
        ar & m_speed;
    }
};

} // namespace item
} // namespace descriptor
