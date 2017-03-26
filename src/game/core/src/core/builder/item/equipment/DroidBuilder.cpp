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
    if (!descriptor::Manager::get().hasType(descriptor::Type::DROID_EQUIPMENT)) {
        descr = descriptor::item::genDroid();
    } else {
        descr = descriptor::Manager::get().randDroid();
    }
    assert(descr);
    return gen(descr);
}

control::item::Droid*
Droid::gen(descriptor::item::Droid* descr)
{
    control::item::Droid* droid = __genTemplate(descr->id());
    __createInternals(droid, descr);
    return droid;
}  

control::item::Droid*
Droid::__genTemplate(int_t descriptor_id)
{
    model::item::Droid* model = new model::item::Droid(descriptor_id);
    control::item::Droid* droid = new control::item::Droid(model);
    EntityManager::get().reg(droid);
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
