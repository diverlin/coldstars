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

class ProtectorDescr : public EquipmentDescr
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
    ProtectorDescr();
    ~ProtectorDescr() = default;
    ProtectorDescr(const std::string& data);
    std::string data() const;

    void setProtection(int protection) { m_protection = protection; }

    int protection() const { return m_protection; }

    ceti::InfoTable info() const {
        ceti::InfoTable result = descriptor::EquipmentDescr::info();
        result.add("descriptor::Protector");
        result.add("protection", m_protection);
        return result;
    }

private:
    int m_protection = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<EquipmentDescr>(*this);
        ar & m_protection;
    }
};

} // namespace descriptor

