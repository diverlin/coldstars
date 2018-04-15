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
#include <core/descriptor/item/equipment/Scaner.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/model/item/equipment/Scaner.hpp>

#ifdef USE_MODULES
#include <core/item/modules/ScanerModule.hpp>
#endif

#include <ceti/serialization/macro.hpp>
#include <ceti/Logger.hpp>

namespace core {
namespace control {

Scaner::Scaner(descriptor::ScanerDescr* descr, model::Scaner* model)
    :
      Equipment(descr, model)
    , m_descriptor_scaner(descr)
    , m_model_scaner(model)
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

} // namespace control
} // namespace core
