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

#include "Base.hpp"

namespace descriptor {
namespace item {

class Protector : public BaseEquipment
{
public:
    static const int PROTECTION_MIN;
    static const int PROTECTION_MAX;
    static const float PROTECTION_TECH_RATE;

    static const int MODULES_NUM_MIN;
    static const int MODULES_NUM_MAX;

    static const int MASS_MIN;
    static const int MASS_MAX;
    static const int CONDITION_MIN;
    static const int CONDITION_MAX;

    static const float PROTECTION_WEIGHT;
    static const float MODULES_NUM_WEIGHT;

public:
    Protector();
    ~Protector() = default;
    Protector(const std::string& data);
    std::string data() const;

    void setProtection(int protection) { m_protection = protection; }

    int protection() const { return m_protection; }

    std::string info() const {
        std::string result = "descriptor::item::Protector:\n";
        result += std::string(" protection = ") + std::to_string(m_protection) + "\n";
        result += descriptor::item::BaseEquipment::info();
        return result;
    }

private:
    int m_protection = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<BaseEquipment>(*this);
        ar & m_protection;
    }
};

} // namespace item
} // namespace descriptor

