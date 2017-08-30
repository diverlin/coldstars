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
#include <core/manager/Session.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/common/Global.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

#include <ceti/Logger.hpp>

namespace builder {
namespace item {

control::item::Protector*
Protector::gen()
{
    descriptor::item::Protector* descr = nullptr;
    if (!core::Sessions::get().session()->descriptor()->hasType(descriptor::Type::PROTECTOR_EQUIPMENT)) {
        descr = descriptor::item::genProtector();
    } else {
        descr = core::Sessions::get().session()->descriptor()->randProtector();
    }
    assert(descr);
    return gen(descr);
} 

std::vector<control::item::Protector*>
Protector::gen(int num)
{
    std::vector<control::item::Protector*> result;
    for (int i=0; i<num; ++i) {
        result.push_back(gen());
    }
    return result;
}

control::item::Protector*
Protector::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::item::Protector* descr = core::Sessions::get().session()->descriptor()->protector(descriptor_id);
    control::item::Protector* protector = __genTemplate(descr, ob_id);
    __createInternals(protector, descr);
    return protector;
}

control::item::Protector*
Protector::gen(descriptor::item::Protector* descr)
{
    control::item::Protector* protector = __genTemplate(descr);
    __createInternals(protector, descr);
    return protector;
}

control::item::Protector*
Protector::__genTemplate(descriptor::item::Protector* descr, int_t ob_id)
{
    model::item::Protector* model = new model::item::Protector(descr->id(), ob_id);
    control::item::Protector* protector = new control::item::Protector(descr, model);
    core::shortcuts::entities()->add(protector);
    return protector;
}

void
Protector::__createInternals(control::item::Protector* protector, descriptor::item::Protector* descr)
{     
    Item::_createInternals(protector, descr);
    Equipment::_createInternals(protector, descr);
    protector->model()->setProtection(descr->protection());
}

} // namespace item
} // namespace builder
