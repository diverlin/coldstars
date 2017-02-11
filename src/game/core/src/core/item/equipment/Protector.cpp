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

#include "Protector.hpp"

#ifdef USE_MODULES
#include <core/item/modules/ProtectorModule.hpp>
#endif

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>

namespace descriptor {
namespace item {

const int Protector::PROTECTION_MIN = 3;
const int Protector::PROTECTION_MAX = 30;
const float Protector::PROTECTION_TECH_RATE = 0.1f;

const int Protector::MODULES_NUM_MIN = 0;
const int Protector::MODULES_NUM_MAX = 2;

const int Protector::CONDITION_MIN = 2000;
const int Protector::CONDITION_MAX = 10000;
const int Protector::MASS_MIN = 20;
const int Protector::MASS_MAX = 80;

const float Protector::PROTECTION_WEIGHT = 0.8f;
const float Protector::MODULES_NUM_WEIGHT = 0.2f;

Protector::Protector()
{
    setDescriptor(descriptor::type::PROTECTOR_EQUIPMENT);
}

Protector::Protector(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Protector::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespce item
} // namespace descriptor


namespace model {
namespace item {

Protector::Protector()
{
    setType(entity::type::EQUIPMENT_ID);
    setSubType(entity::type::PROTECTOR_EQUIPMENT_ID);
}

Protector::Protector(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Protector::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace item
} // namespace model


namespace control {
namespace item {

Protector::Protector(model::item::Protector* model)
    :
      m_model_protector(model)
{
}

/* virtual */
void Protector::updateProperties()
{   
    m_protection_add  = 0;

#ifdef USE_MODULES
    for (unsigned int i = 0; i < modules_vec.size(); i++) {
        protection_add += ((ProtectorModule*)modules_vec[i])->GetProtectionAdd();
    }
#endif

    model()->setProtection(descriptor()->protection() + m_protection_add);
}

void Protector::CountPrice()
{
    float protection_rate    = (float)descriptor()->protection() / descriptor::item::Protector::PROTECTION_MIN;
    float modules_num_rate   = (float)descriptor()->modules() / descriptor::item::Protector::MODULES_NUM_MAX;

    float effectiveness_rate = descriptor::item::Protector::PROTECTION_WEIGHT * protection_rate +
            descriptor::item::Protector::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = float(descriptor()->mass()) / descriptor::item::Protector::MASS_MIN;
    float condition_rate     = float(descriptor()->condition()) / descriptor::item::Protector::CONDITION_MIN;

    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Protector::addUniqueInfo()
{
    //        info.addTitleStr("PROTECTOR");
    //        info.addNameStr("protection:");     info.addValueStr(GetProtectionStr());
}

std::string Protector::protectionStr()
{
    if (m_protection_add) {
        return std::to_string(descriptor()->protection()) + "+" + std::to_string(m_protection_add); }
    else {
        return std::to_string(descriptor()->protection());
    }
}

} // namespace item
} // namespace control
