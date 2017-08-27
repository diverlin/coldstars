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

namespace model {
namespace item {

class Drive : public Equipment
{
public:
    Drive(int_t, int_t);
    ~Drive() = default;
    Drive(const std::string& data);
    std::string data() const;

    void setSpeed(int speed) { m_speed = speed; }
    void setHyper(int hyper) { m_hyper = hyper; }

    int speed() const { return m_speed; }
    int hyper() const { return m_hyper; }

    ceti::InfoTable info() const override final {
        ceti::InfoTable result = Equipment::info();
        result.add("model::Drive");
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
} // namespace model

