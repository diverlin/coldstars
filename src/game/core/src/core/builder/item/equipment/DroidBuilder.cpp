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
#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/common/Global.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {
namespace item {

core::control::item::Droid*
Droid::gen()
{
    descriptor::item::Droid* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::DROID_EQUIPMENT)) {
        descr = descriptor::item::genDroid();
    } else {
        descr = core::shortcuts::descriptors()->randDroid();
    }
    assert(descr);
    return gen(descr);
}

core::control::item::Droid*
Droid::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::item::Droid* descr = core::shortcuts::descriptors()->droid(descriptor_id);
    core::control::item::Droid* droid = __genTemplate(descr, ob_id);
    __createInternals(droid, descr);
    return droid;
}

core::control::item::Droid*
Droid::gen(descriptor::item::Droid* descr)
{
    core::control::item::Droid* droid = __genTemplate(descr);
    __createInternals(droid, descr);
    return droid;
}  

core::control::item::Droid*
Droid::__genTemplate(descriptor::item::Droid* descriptor, int id)
{
    model::item::Droid* model = new model::item::Droid(descriptor->id(), id);
    assert(model);
    core::control::item::Droid* droid = new core::control::item::Droid(descriptor, model);
    assert(droid);
    return droid;
}

void Droid::__createInternals(core::control::item::Droid* droid, descriptor::item::Droid* descr)
{     
    Item::_createInternals(droid, descr);
    Equipment::_createInternals(droid, descr);
    droid->model()->setRepair(descr->repair());
}

} // namespace item
} // namespace builder
