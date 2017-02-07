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
#include "../../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <ceti/Logger.hpp>
#ifdef USE_MODULES
#include <item/modules/DroidModule.hpp>
#endif
#include "../../spaceobjects/Vehicle.hpp"
#include "../../slots/ItemSlot.hpp"


namespace descriptor {
namespace item {

//const int Bak::FUEL_MIN = 10;
//const int Bak::FUEL_MAX = 30;
//const float Bak::FUEL_TECH_RATE = 0.1f;

//const int Bak::MODULES_NUM_MIN = 0;
//const int Bak::MODULES_NUM_MAX = 2;

//const int Bak::MASS_MIN = 10;
//const int Bak::MASS_MAX = 40;
//const int Bak::CONDITION_MIN = 30;
//const int Bak::CONDITION_MAX = 100;

//const float Bak::FUEL_WEIGHT = 0.7;
//const float Bak::MODULES_NUM_WEIGHT = 0.3;

Droid::Droid()
{
    setDescriptor(descriptor::type::DROID_EQUIPMENT);
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
} // namespace descriptor


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

Droid::Droid()
{}

/* virtual */
Droid::~Droid()
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
    float repair_rate        = (float)descriptor()->repair() / EQUIPMENT::DROID::REPAIR_MIN;
    float modules_num_rate   = (float)modulesNum() / EQUIPMENT::DROID::MODULES_NUM_MAX;

    float effectiveness_rate = EQUIPMENT::DROID::REPAIR_WEIGHT * repair_rate +
            EQUIPMENT::DROID::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = (float)m_data.mass / EQUIPMENT::DROID::MASS_MIN;
    float condition_rate     = (float)m_condition / m_data.condition_max;

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
