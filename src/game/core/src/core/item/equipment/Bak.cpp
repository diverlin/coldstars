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

#include "Bak.hpp"
#include <core/common/constants.hpp>
#ifdef USE_MODULES
#include <core/item/modules/BakModule.hpp>
#endif // USE_MODULES

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>


namespace descriptor {
namespace item {

const int Bak::FUEL_MIN = 10;
const int Bak::FUEL_MAX = 30;
const float Bak::FUEL_TECH_RATE = 0.1f;

const int Bak::MODULES_NUM_MIN = 0;
const int Bak::MODULES_NUM_MAX = 2;

const int Bak::MASS_MIN = 10;
const int Bak::MASS_MAX = 40;
const int Bak::CONDITION_MIN = 30;
const int Bak::CONDITION_MAX = 100;

const float Bak::FUEL_WEIGHT = 0.7;
const float Bak::MODULES_NUM_WEIGHT = 0.3;

Bak::Bak()
{
    setDescriptor(descriptor::type::BAK_EQUIPMENT);
}

Bak::Bak(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Bak::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace item
} // namespace descriptor


namespace model {
namespace item {

Bak::Bak()
{
    setType(entity::type::EQUIPMENT_ID);
    setSubType(entity::type::BAK_EQUIPMENT_ID);
}

Bak::Bak(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Bak::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace item
} // namespace model



namespace control {
namespace item {

int
Bak::fuelMiss() const
{
    return (m_fuelMax - model()->fuel());
}

void Bak::increaseFuel(int fuel)
{
    fuel += model()->fuel();
    if (fuel > m_fuelMax) {
        fuel = m_fuelMax;
    }
    model()->setFuel(fuel);
}    
                                    
/* virtual */            
void Bak::updateProperties()
{
    int m_fuelMax_add = 0;
#ifdef USE_MODULES
    for (unsigned int i=0; i<modules_vec.size(); i++) {
        m_fuel_add += ((BakModule*)modules_vec[i])->GetFuelMaxAdd();
    }
#endif
    m_fuelMax = descriptor()->fuel() + m_fuelMax_add;
}

void Bak::countPrice()
{
    float fuel_rate          = (float)descriptor()->fuel() / descriptor::item::Bak::FUEL_MIN;
    float modules_num_rate   = (float)modulesNum() / descriptor::item::Bak::MODULES_NUM_MAX;
    
    float effectiveness_rate = descriptor::item::Bak::FUEL_WEIGHT * fuel_rate +
                               descriptor::item::Bak::MODULES_NUM_WEIGHT * modules_num_rate;
    
    float mass_rate          = (float)m_data.mass / descriptor::item::Bak::MASS_MIN;
    float condition_rate     = (float)m_condition / m_data.condition_max;
    
    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Bak::addUniqueInfo()
{
//    info.addTitleStr("BAK");
//    info.addNameStr("fuel:");      info.addValueStr( GetFuelStr() );
}


std::string Bak::getFuelStr()
{
    if (m_fuelMaxAdd) {
        return std::to_string(descriptor()->fuel()) + "/" + std::to_string(model()->fuel());
    } else {
        return std::to_string(descriptor()->fuel()) + "+" + std::to_string(m_fuelMaxAdd) + "/" + std::to_string(model()->fuel());
    }
}

} // namespace item
} // namespace control
