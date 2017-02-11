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

#include "Droid.hpp"
#include <core/descriptor/item/equipment/Droid.hpp>

#ifdef USE_MODULES
#include <core/item/modules/DroidModule.hpp>
#endif

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>

namespace model {
namespace item {

Droid::Droid()
{
    setType(entity::type::EQUIPMENT_ID);
    setSubType(entity::type::DROID_EQUIPMENT_ID);
}

Droid::Droid(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Droid::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace item
} // namespace model



namespace control {
namespace item {

Droid::Droid(model::item::Droid* model)
    :
      m_model_droid(model)
{}

/* virtual */
void Droid::updateProperties()
{
    m_repair_add = 0;
#ifdef USE_MODULES
    for (unsigned int i = 0; i < modules_vec.size(); i++) {
        repair_add += ((DroidModule*)modules_vec[i])->GetRepairAdd();
    }
#endif
    model()->setRepair(descriptor()->repair() + m_repair_add);
}

/* virtual */
void Droid::updateInStatic()
{
    assert(false);
//    if (isFunctioning()) {
//        if (!slot()->vehicleOwner()->isArmorFull()) {
//            slot()->vehicleOwner()->increaseArmor(m_repair);
//            deteriorationEvent();
//        }
//    }
    _updateLock();
}

void Droid::CountPrice()
{
    float repair_rate        = (float)descriptor()->repair() / descriptor::item::Droid::REPAIR_MIN;
    float modules_num_rate   = (float)descriptor()->modules() / descriptor::item::Droid::MODULES_NUM_MAX;

    float effectiveness_rate = descriptor::item::Droid::REPAIR_WEIGHT * repair_rate +
            descriptor::item::Droid::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = float(descriptor()->mass()) / descriptor::item::Droid::MASS_MIN;
    float condition_rate     = float(descriptor()->condition()) / descriptor::item::Droid::CONDITION_MIN;

    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Droid::addUniqueInfo()
{
    //    info.addTitleStr("DROID");
    //    info.addNameStr("repair:");     info.addValueStr(GetRepairStr());
}


std::string Droid::GetRepairStr()
{
    if (m_repair_add) {
        return std::to_string(descriptor()->repair()) + "+" + std::to_string(m_repair_add);
    } else {
        return std::to_string(descriptor()->repair());
    }
}

} // namespace item
} // namespace control
