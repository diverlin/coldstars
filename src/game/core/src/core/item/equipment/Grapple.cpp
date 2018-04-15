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

#include "Grapple.hpp"
#include <core/descriptor/item/equipment/Grapple.hpp>
#include <core/model/item/equipment/Grapple.hpp>

#ifdef USE_MODULES
#include <core/item/modules/GrappleModule.hpp>
#endif

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>

namespace core {
namespace control {

Grapple::Grapple(descriptor::item::Grapple* descr, model::item::Grapple* model)
    :
      Equipment(descr, model)
    , m_descriptor_grapple(descr)
    , m_model_grapple(model)
{}

/* virtual */
void Grapple::updateProperties()
{
    m_strength_add   = 0;
    m_radius_add     = 0;
    m_speed_add      = 0;
    
#ifdef USE_MODULES
    for (unsigned int i = 0; i < modules_vec.size(); i++) {
        strength_add   += ((GrappleModule*)modules_vec[i])->GetStrengthAdd();
        radius_add     += ((GrappleModule*)modules_vec[i])->GetRadiusAdd();
        speed_add      += ((GrappleModule*)modules_vec[i])->GetSpeedAdd();
    }
#endif
    model()->setStrength(descriptor()->strength() + m_strength_add);
    model()->setRadius(descriptor()->radius() + m_radius_add);
    model()->setSpeed(descriptor()->speed() + m_speed_add);
}

void Grapple::addUniqueInfo()
{        
    //    info.addTitleStr("GRAPPLE");

    //    info.addNameStr("strength:");        info.addValueStr(GetStrengthStr() + "/" + std::to_string(free_strength));
    //    info.addNameStr("radius:");          info.addValueStr(GetRadiusStr());
    //    info.addNameStr("speed:");           info.addValueStr(GetSpeedStr());
}

std::string Grapple::strengthStr()
{
    if (m_strength_add) {
        return std::to_string(descriptor()->strength()) + "+" + std::to_string(m_strength_add);
    } else {
        return std::to_string(descriptor()->strength());
    }
}

std::string Grapple::radiusStr()
{
    if (m_radius_add) {
        return std::to_string(descriptor()->radius()) + "+" + std::to_string(m_radius_add);
    } else {
        return std::to_string(descriptor()->radius());
    }
}

std::string Grapple::speedStr()
{
    if (m_speed_add) {
        return std::to_string(descriptor()->speed()) + "+" + std::to_string(m_speed_add);
    } else {
        return std::to_string(descriptor()->speed());
    }
}

} // namespace control
} // naemspace core
