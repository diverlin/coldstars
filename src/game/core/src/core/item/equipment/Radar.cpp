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

#include "Radar.hpp"
#include <core/descriptor/item/equipment/Radar.hpp>
#include <core/model/item/equipment/Radar.hpp>

#ifdef USE_MODULES
#include <item/modules/RadarModule.hpp>
#endif

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>

namespace control {
namespace item {

Radar::Radar(model::item::Radar* model)
    :
      m_model_radar(model)
{}

/* virtual */
void Radar::updateProperties()
{
    m_radius_add  = 0;
    
#ifdef USE_MODULES
    for (unsigned int i=0; i<modules_vec.size(); i++) {
        radius_add += ((RadarModule*)modules_vec[i])->GetRadiusAdd();
    }
#endif
    model()->setRadius(descriptor()->radius() + m_radius_add);
}

void Radar::countPrice()
{
    float radius_rate         = (float)descriptor()->radius() / descriptor::item::Radar::RADIUS_MIN;

    float modules_num_rate    = (float)descriptor()->modules() / descriptor::item::Radar::MODULES_NUM_MAX;

    float effectiveness_rate  = descriptor::item::Radar::RADIUS_WEIGHT * radius_rate + descriptor::item::Radar::MODULES_NUM_WEIGHT * modules_num_rate;

    float mass_rate           = float(descriptor()->mass()) / descriptor::item::Radar::MASS_MIN;
    float condition_rate      = float(descriptor()->condition()) / m_data.condition_max;

    m_price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void Radar::addUniqueInfo()
{
    //    info.addTitleStr("RADAR");
    //    info.addNameStr("radius:");     info.addValueStr(GetRadiusStr());
}

std::string Radar::radiusStr()
{
    if (m_radius_add) {
        return std::to_string(descriptor()->radius()) + "+" + std::to_string(m_radius_add);
    } else {
        return std::to_string(descriptor()->radius());
    }
}

} // namespace item
} // namespace control
