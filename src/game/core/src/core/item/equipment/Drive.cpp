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
#include <core/model/item/equipment/Drive.hpp>

#ifdef USE_MODULES
#include <core/item/modules/DriveModule.hpp>
#endif // USE_MODULES

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>

namespace core {
namespace control {

Drive::Drive(DriveDescr* descr, model::Drive* model)
    :
      Equipment(descr, model)
    , m_descriptor_drive(descr)
    , m_model_drive(model)
{

}

int Drive::speed() const { return model()->speed(); }

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

} // namespace control
} // namespace core

