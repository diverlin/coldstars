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

#include "Scaner.hpp"

#include <ceti/Logger.hpp>
#ifdef USE_MODULES
#include <item/modules/ScanerModule.hpp>
#endif

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>


namespace descriptor {
namespace item {

const int Scaner::SCAN_MIN = 2;
const int Scaner::SCAN_MAX = 40;
const float Scaner::SCAN_TECH_RATE = 0.1f;

const int Scaner::MODULES_NUM_MIN = 0;
const int Scaner::MODULES_NUM_MAX = 2;

const int Scaner::MASS_MIN = 7;
const int Scaner::MASS_MAX = 38;
const int Scaner::CONDITION_MIN = 30;
const int Scaner::CONDITION_MAX = 100;

const float Scaner::SCAN_WEIGHT = 0.7f;
const float Scaner::MODULES_NUM_WEIGHT = 0.3f;


Scaner::Scaner()
{
    setDescriptor(descriptor::type::SCANER_EQUIPMENT);
}

Scaner::Scaner(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Scaner::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespce item
} // namespace descriptor


namespace model {
namespace item {

Scaner::Scaner()
{
    setType(entity::type::EQUIPMENT_ID);
    setSubType(entity::type::SCANER_EQUIPMENT_ID);
}

Scaner::Scaner(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Scaner::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace item
} // namespace model


namespace control {
namespace item {

Scaner::Scaner(model::item::Scaner* model)
    :
      m_model_scaner(model)
{}

/* virtual */
void Scaner::updateProperties()
{
    m_scan_add = 0;

#ifdef USE_MODULES
    for (unsigned int i = 0; i < modules_vec.size(); i++) {
        scan_add += ((ScanerModule*)modules_vec[i])->GetScanAdd();
    }
#endif
    model()->setScan(descriptor()->scan() + m_scan_add);
}

void Scaner::countPrice()
{
    float scan_rate          = float(descriptor()->scan()) / descriptor::item::Scaner::SCAN_MIN;
    float modules_num_rate   = float(descriptor()->modules()) / descriptor::item::Scaner::MODULES_NUM_MAX;

    float effectiveness_rate = descriptor::item::Scaner::SCAN_WEIGHT * scan_rate +
            descriptor::item::Scaner::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = float(descriptor()->mass()) / descriptor::item::Scaner::MASS_MIN;
    float condition_rate     = float(descriptor()->condition()) / descriptor::item::Scaner::CONDITION_MIN;

    m_price = int(3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void Scaner::addUniqueInfo()
{
    //    info.addTitleStr("SCANER");
    //    info.addNameStr("scan:");     info.addValueStr(GetScanStr());
}

std::string Scaner::scanStr()
{
    if (m_scan_add) {
        return std::to_string(descriptor()->scan()) + "+" + std::to_string(m_scan_add);
    } else {
        return std::to_string(descriptor()->scan());
    }
}


} // namespace item
} // namespace control
