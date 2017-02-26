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
#include <core/descriptor/item/equipment/Bak.hpp>
#include <core/model/item/equipment/Bak.hpp>

#ifdef USE_MODULES
#include <core/item/modules/BakModule.hpp>
#endif // USE_MODULES

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>


namespace control {
namespace item {

Bak::Bak(model::item::Bak* model, descriptor::item::Bak* descr)
    :
      Equipment(model, descr)
    , m_model_bak(model)
    , m_descriptor_bak(descr)
{}

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

void Bak::addUniqueInfo()
{
//    info.addTitleStr("BAK");
//    info.addNameStr("fuel:");      info.addValueStr( GetFuelStr() );
}

std::string Bak::fuelStr()
{
    if (m_fuelMax_add) {
        return std::to_string(descriptor()->fuel()) + "/" + std::to_string(model()->fuel());
    } else {
        return std::to_string(descriptor()->fuel()) + "+" + std::to_string(m_fuelMax_add) + "/" + std::to_string(model()->fuel());
    }
}

} // namespace item
} // namespace control
