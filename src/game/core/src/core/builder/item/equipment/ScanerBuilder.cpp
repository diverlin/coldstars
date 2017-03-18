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


#include "ScanerBuilder.hpp"
#include <core/descriptor/item/equipment/Scaner.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/model/item/equipment/Scaner.hpp>
#include <core/common/Global.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {
namespace item {

model::item::Scaner*
Scaner::gen()
{
    descriptor::item::Scaner* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::SCANER_EQUIPMENT)) {
        descr = descriptor::item::genScaner();
    } else {
        descr = descriptor::Manager::get().randScaner();
    }
    assert(descr);
    return gen(descr);
}

model::item::Scaner*
Scaner::gen(descriptor::item::Scaner* descr)
{
    model::item::Scaner* model = __genTemplate(descr->id());
    __createInternals(model, descr);

    return model;
} 

model::item::Scaner*
Scaner::__genTemplate(int_t descriptor_id)
{
    model::item::Scaner* model = new model::item::Scaner(descriptor_id);
    core::global::get().entityManager().reg(model);

    return model;
}

void
Scaner::__createInternals(model::item::Scaner* model, descriptor::item::Scaner* descr)
{
    Item::_createInternals(model, descr);
    Equipment::_createInternals(model, descr);
    model->setScan(descr->scan());
}

} // namespace item
} // namespace builder
