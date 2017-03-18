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
#include <core/descriptor/item/equipment/Protector.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/common/Global.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

#include <ceti/Logger.hpp>

namespace builder {
namespace item {

model::item::Protector*
Protector::gen()
{
    descriptor::item::Protector* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::PROTECTOR_EQUIPMENT)) {
        descr = descriptor::item::genProtector();
    } else {
        descr = descriptor::Manager::get().randProtector();
    }
    assert(descr);
    return gen(descr);
} 

std::vector<model::item::Protector*>
Protector::gen(int num)
{
    std::vector<model::item::Protector*> result;
    for (int i=0; i<num; ++i) {
        result.push_back(gen());
    }
    return result;
}

model::item::Protector*
Protector::gen(descriptor::item::Protector* descr)
{
    model::item::Protector* model = __genTemplate(descr->id());
    __createInternals(model, descr);
    return model;
}

model::item::Protector*
Protector::__genTemplate(int_t descriptor_id)
{
    model::item::Protector* model = new model::item::Protector(descriptor_id);
    core::global::get().entityManager().reg(model);
    return model;
}

void
Protector::__createInternals(model::item::Protector* model, descriptor::item::Protector* descr)
{     
    Item::_createInternals(model, descr);
    Equipment::_createInternals(model, descr);
    model->setProtection(descr->protection());
}

} // namespace item
} // namespace builder
