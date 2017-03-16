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


#include "DroidBuilder.hpp"
#include <core/model/item/equipment/Droid.hpp>
#include <core/descriptor/item/equipment/Droid.hpp>
#include <core/descriptor/DescriptorManager.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/common/Global.hpp>

namespace builder {
namespace item {

model::item::Droid*
Droid::gen()
{
    descriptor::item::Droid* descr = descriptor::Manager::get().randDroid();
    model::item::Droid* model = __genTemplate(descr->id());
    __createInternals(model, descr);
    return model;
}

//model::item::Droid*
//Droid::gen(const std::string& data)
//{
//    descriptor::item::Droid descr(data);
//    assert(descr->descriptor() != descriptor::type::DROID_EQUIPMENT);
//    return gen(descr);
//}

model::item::Droid*
Droid::gen(descriptor::item::Droid* descr)
{
    model::item::Droid* model = __genTemplate(descr->id());
    __createInternals(model, descr);
    return model;
}  

model::item::Droid*
Droid::__genTemplate(int_t descriptor_id)
{
    model::item::Droid* model = new model::item::Droid(descriptor_id);
    core::global::get().entityManager().reg(model);
    return model;
}

void Droid::__createInternals(model::item::Droid* model, descriptor::item::Droid* descr)
{     
    Item::_createInternals(model, descr);
    Equipment::_createInternals(model, descr);
    model->setRepair(descr->repair());
}

} // namespace item
} // namespace builder
