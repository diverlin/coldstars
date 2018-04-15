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

namespace core {

class BakModel : public EquipmentModel
{
public:
    BakModel(int_t, int_t);
    ~BakModel() = default;
    BakModel(const std::string& data);
    std::string data() const;

    void setFuel(int fuel) { m_fuel = fuel; }

    int fuel() const { return m_fuel; }

    ceti::InfoTable info() const override final {
        ceti::InfoTable result = EquipmentModel::info();
        result.add("Bak");
        result.add("fuel", m_fuel);
        return result;
    }

private:
    int m_fuel = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<EquipmentModel>(*this);
        ar & m_fuel;
    }
};

} // namespace model



