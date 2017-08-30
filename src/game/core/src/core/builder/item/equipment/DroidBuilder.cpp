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
#include <core/item/equipment/Droid.hpp>
#include <core/descriptor/item/equipment/Droid.hpp>
#include <core/manager/Session.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/common/Global.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {
namespace item {

control::item::Droid*
Droid::gen()
{
    descriptor::item::Droid* descr = nullptr;
    if (!core::Sessions::get().session()->descriptor()->hasType(descriptor::Type::DROID_EQUIPMENT)) {
        descr = descriptor::item::genDroid();
    } else {
        descr = core::Sessions::get().session()->descriptor()->randDroid();
    }
    assert(descr);
    return gen(descr);
}

control::item::Droid*
Droid::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::item::Droid* descr = core::Sessions::get().session()->descriptor()->droid(descriptor_id);
    control::item::Droid* droid = __genTemplate(descr, ob_id);
    __createInternals(droid, descr);
    return droid;
}

control::item::Droid*
Droid::gen(descriptor::item::Droid* descr)
{
    control::item::Droid* droid = __genTemplate(descr);
    __createInternals(droid, descr);
    return droid;
}  

control::item::Droid*
Droid::__genTemplate(descriptor::item::Droid* descr, int ob_id)
{
    model::item::Droid* model = new model::item::Droid(descr->id(), ob_id);
    control::item::Droid* droid = new control::item::Droid(descr, model);
    core::Sessions::get().session()->entity()->add(droid);
    return droid;
}

void Droid::__createInternals(control::item::Droid* droid, descriptor::item::Droid* descr)
{     
    Item::_createInternals(droid, descr);
    Equipment::_createInternals(droid, descr);
    droid->model()->setRepair(descr->repair());
}

} // namespace item
} // namespace builder
