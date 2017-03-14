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
#include <core/descriptor/DescriptorManager.hpp>
#include <core/model/item/equipment/Radar.hpp>

#ifdef USE_MODULES
#include <core/item/modules/RadarModule.hpp>
#endif

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>

namespace control {
namespace item {

Radar::Radar(model::item::Radar* model)
    :
      Equipment(model, descriptor::Manager::get().radar(model->descriptor()))
    , m_model_radar(model)
    , m_descriptor_radar(descriptor::Manager::get().radar(model->descriptor()))
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
