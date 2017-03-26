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
#include <core/descriptor/item/equipment/Protector.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/model/item/equipment/Protector.hpp>

#ifdef USE_MODULES
#include <core/item/modules/ProtectorModule.hpp>
#endif

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>

namespace control {
namespace item {

Protector::Protector(model::item::Protector* model)
    :
      Equipment(model, descriptor::Manager::get().protector(model->descriptor()))
    , m_model_protector(model)
    , m_descriptor_protector(descriptor::Manager::get().protector(model->descriptor()))
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
