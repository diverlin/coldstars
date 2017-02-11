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

class Droid : public Equipment
{
public:
    static const int REPAIR_MIN;
    static const int REPAIR_MAX;
    static const float REPAIR_TECH_RATE;

    static const int MODULES_NUM_MIN;
    static const int MODULES_NUM_MAX;

    static const int MASS_MIN;
    static const int MASS_MAX;
    static const int CONDITION_MIN;
    static const int CONDITION_MAX;

    static const float REPAIR_WEIGHT;
    static const float MODULES_NUM_WEIGHT;

public:
    Droid();
    ~Droid() = default;
    Droid(const std::string& data);
    std::string data() const;

    void setRepair(int repair) { m_repair = repair; }

    int repair() const { return m_repair; }

    std::string info() const {
        std::string result = "descriptor::item::Droid:\n";
        result += std::string(" repair = ") + std::to_string(m_repair) + "\n";
        result += descriptor::item::Equipment::info();
        return result;
    }

private:
    int m_repair = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Equipment>(*this);
        ar & m_repair;
    }
};

} // namespace item
} // namespace descriptor

