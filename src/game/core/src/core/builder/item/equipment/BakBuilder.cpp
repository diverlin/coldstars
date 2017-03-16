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


#include "BakBuilder.hpp"
#include <core/model/item/equipment/Bak.hpp>
#include <core/descriptor/item/equipment/Bak.hpp>
#include <core/descriptor/DescriptorManager.hpp>
#include <core/common/Global.hpp>
#include <core/manager/EntityManager.hpp>

namespace builder {
namespace item {

model::item::Bak*
Bak::gen()
{
    descriptor::item::Bak* descr = descriptor::Manager::get().randBak();
    return gen(descr);
}

//model::item::Bak*
//Bak::gen(const std::string& data)
//{
//    descriptor::item::Bak descr(data);
//    assert(descr->descriptor() != descriptor::type::BAK_EQUIPMENT);
//    return gen(descr);
//}

model::item::Bak*
Bak::gen(descriptor::item::Bak* descr)
{
    model::item::Bak* model = __genTemplate(descr->id());
    __createInternals(model, descr);
    return model;
}

model::item::Bak*
Bak::__genTemplate(int_t descriptor_id)
{
    model::item::Bak* model = new model::item::Bak(descriptor_id);
    core::global::get().entityManager().reg(model);
    return model;
}

void
Bak::__createInternals(model::item::Bak* model, descriptor::item::Bak* descr)
{
    Item::_createInternals(model, descr);
    Equipment::_createInternals(model, descr);
    model->setFuel(descr->fuel());
}

} // namespace item
} // namespace builder
