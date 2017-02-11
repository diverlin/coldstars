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

#include "Drive.hpp"
#include <core/descriptor/item/equipment/Drive.hpp>

#ifdef USE_MODULES
#include <core/item/modules/DriveModule.hpp>
#endif // USE_MODULES

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>

namespace model {
namespace item {

Drive::Drive()
{
    setType(entity::type::EQUIPMENT_ID);
    setSubType(entity::type::DRIVE_EQUIPMENT_ID);
}

Drive::Drive(const std::string& data)
{
    MACRO_READ_SERIALIZED_DATA
}

std::string
Drive::data() const
{
    MACRO_SAVE_SERIALIZED_DATA
}

} // namespace item
} // namespace model


namespace control {
namespace item {

Drive::Drive(model::item::Drive* model)
    :
      m_model_drive(model)
{

}

/* virtual */
void Drive::updateProperties()
{     
    m_speed_add = 0;
    m_hyper_add = 0;
#ifdef USE_MODULES
    for (unsigned int i=0; i<modules_vec.size(); i++) {
        m_speed_add += ((DriveModule*)modules_vec[i])->GetSpeedAdd();
        m_hyper_add += ((DriveModule*)modules_vec[i])->GetHyperAdd();
    }
#endif
    model()->setSpeed(descriptor()->speed() + m_speed_add);
    model()->setHyper(descriptor()->hyper() + m_hyper_add);
}

void Drive::CountPrice()
{
    float speed_rate         = (float)descriptor()->speed() / descriptor::item::Drive::SPEED_MIN;
    float hyper_rate         = (float)descriptor()->hyper() / descriptor::item::Drive::HYPER_MIN;
    float modules_num_rate   = (float)modulesNum() / descriptor::item::Drive::MODULES_NUM_MAX;

    float effectiveness_rate = descriptor::item::Drive::SPEED_WEIGHT * speed_rate +
            descriptor::item::Drive::HYPER_WEIGHT * hyper_rate +
            descriptor::item::Drive::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate          = (float)m_data.mass / descriptor::item::Drive::MASS_MIN;
    float condition_rate     = (float)m_condition / m_data.condition_max;

    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Drive::addUniqueInfo()
{
    //        info.addTitleStr("DRIVE");
    //        info.addNameStr("speed:");     info.addValueStr(GetSpeedStr());
    //        info.addNameStr("hyper:");     info.addValueStr(GetHyperStr());
}             

std::string Drive::speedStr()
{
    if (m_speed_add) {
        return std::to_string(descriptor()->speed()) + "+" + std::to_string(m_speed_add);
    } else {
        return std::to_string(descriptor()->speed());
    }
}

std::string Drive::hyperStr()
{
    if (m_hyper_add) {
        return std::to_string(descriptor()->hyper()) + "+" + std::to_string(m_hyper_add); }
    else {
        return std::to_string(descriptor()->hyper());
    }
}

} // namespace item
} // namespace control


