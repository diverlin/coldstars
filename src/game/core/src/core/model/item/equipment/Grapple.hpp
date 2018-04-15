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

class GrappleModel : public EquipmentModel
{
public:
    GrappleModel(int_t, int_t);
    ~GrappleModel() = default;
    GrappleModel(const std::string& data);
    std::string data() const;

    void setStrength(int strength)     { m_strength = strength; }
    void setRadius(int radius)         { m_radius = radius; }
    void setSpeed(int speed)           { m_speed = speed; }

    int strength() const { return m_strength; }
    int radius() const { return m_radius; }
    int speed() const { return m_speed; }

    ceti::InfoTable info() const override final {
        ceti::InfoTable result = EquipmentModel::info();
        result.add("model::Grapple");
        result.add("strength", m_strength);
        result.add("radius", m_radius);
        result.add("speed", m_speed);
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
        ar & boost::serialization::base_object<EquipmentModel>(*this);
        ar & m_strength;
        ar & m_radius;
        ar & m_speed;
    }
};

} // namespace model

