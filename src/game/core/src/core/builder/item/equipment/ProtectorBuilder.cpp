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


#include "ProtectorBuilder.hpp"
#include <core/model/item/equipment/Protector.hpp>
#include <core/item/equipment/Protector.hpp>
#include <core/descriptor/item/equipment/Protector.hpp>
#include <core/session/Shortcuts.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/common/Global.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

#include <ceti/Logger.hpp>

namespace core {

core::control::Protector*
ProtectorItemBuilder::gen()
{
    descriptor::ProtectorDescr* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::PROTECTOR_EQUIPMENT)) {
        descr = descriptor::genProtector();
    } else {
        descr = core::shortcuts::descriptors()->randProtector();
    }
    assert(descr);
    return gen(descr);
} 

std::vector<core::control::Protector*>
ProtectorItemBuilder::gen(int num)
{
    std::vector<core::control::Protector*> result;
    for (int i=0; i<num; ++i) {
        result.push_back(gen());
    }
    return result;
}

core::control::Protector*
ProtectorItemBuilder::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::ProtectorDescr* descr = core::shortcuts::descriptors()->protector(descriptor_id);
    core::control::Protector* protector = __genTemplate(descr, ob_id);
    __createInternals(protector, descr);
    return protector;
}

core::control::Protector*
ProtectorItemBuilder::gen(descriptor::ProtectorDescr* descr)
{
    core::control::Protector* protector = __genTemplate(descr);
    __createInternals(protector, descr);
    return protector;
}

core::control::Protector*
ProtectorItemBuilder::__genTemplate(descriptor::ProtectorDescr* descriptor, int_t id)
{
    model::Protector* model = new model::Protector(descriptor->id(), id);
    assert(model);
    core::control::Protector* protector = new core::control::Protector(descriptor, model);
    assert(protector);
    return protector;
}

void
ProtectorItemBuilder::__createInternals(core::control::Protector* protector, descriptor::ProtectorDescr* descr)
{     
    ItemBuilder::_createInternals(protector, descr);
    EquipmentBuilder::_createInternals(protector, descr);
    protector->model()->setProtection(descr->protection());
}

} // namespace core
