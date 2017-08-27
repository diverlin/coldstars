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

class Drive : public Equipment
{
public:
    static const float OVERLOAD_RATE;
    static const float OVERLOAD_DETERIORATION_RATE;

    static const int SPEED_MIN;
    static const int SPEED_MAX;
    static const float SPEED_TECH_RATE;

    static const int HYPER_MIN;
    static const int HYPER_MAX;
    static const float HYPER_TECH_RATE;

    static const int MODULES_NUM_MIN;
    static const int MODULES_NUM_MAX;

    static const int MASS_MIN;
    static const int MASS_MAX;
    static const int CONDITION_MIN;
    static const int CONDITION_MAX;

    static const float SPEED_WEIGHT;
    static const float HYPER_WEIGHT;
    static const float MODULES_NUM_WEIGHT;


public:
    Drive();
    Drive(const std::string& data);
    ~Drive() = default;
    std::string data() const;

    void setSpeed(int speed) { m_speed = speed; }
    void setHyper(int hyper) { m_hyper = hyper; }

    int speed() const { return m_speed; }
    int hyper() const { return m_hyper; }

    ceti::InfoTable info() const override final {
        ceti::InfoTable result = descriptor::Equipment::info();
        result.add("descriptor::item::Drive");
        result.add("speed", m_speed);
        result.add("hyper", m_hyper);
        return result;
    }

private:
    int m_speed = 0;
    int m_hyper = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Equipment>(*this);
        ar & m_speed;
        ar & m_hyper;
    }
};

} // namespace item
} // namespace descriptor


