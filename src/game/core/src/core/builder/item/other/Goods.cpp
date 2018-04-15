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


#include "Goods.hpp"
#include <core/model/item/other/Goods.hpp>
#include <core/item/other/Goods.hpp>
#include <core/descriptor/item/other/Goods.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/common/Global.hpp>
#include <core/session/Shortcuts.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace core {

core::control::Goods*
GoodsBuilder::gen(descriptor::Goods* descriptor)
{
    core::control::Goods* control = __genTemplate(descriptor);
    __createInternals(control, descriptor);
    return control;
}

core::control::Goods*
GoodsBuilder::gen(int_t descriptor_id, int_t object_id)
{
    descriptor::Goods* descriptor = core::shortcuts::descriptors()->goods(descriptor_id);
    core::control::Goods* control = __genTemplate(descriptor, object_id);
    __createInternals(control, descriptor);
    return control;
}

core::control::Goods*
GoodsBuilder::gen()
{
    descriptor::Goods* descriptor = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::GOODS)) {
        descriptor = descriptor::genGoods();
    } else {
        descriptor = core::shortcuts::descriptors()->randGoods();
    }
    assert(descriptor);
    return gen(descriptor);
}


core::control::Goods*
GoodsBuilder::__genTemplate(descriptor::Goods* descriptor, int_t object_id)
{
    model::Goods* model = new model::Goods(descriptor->id(), object_id);
    assert(model);
    core::control::Goods* control = new core::control::Goods(descriptor, model);
    assert(control);
    return control;
}

void
GoodsBuilder::__createInternals(core::control::Goods* control, descriptor::Goods* descriptor)
{
}

} // namespace core
