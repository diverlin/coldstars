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
#include <core/item/equipment/Bak.hpp>
#include <core/descriptor/item/equipment/Bak.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/common/Global.hpp>
#include <core/manager/Session.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {
namespace item {

control::item::Bak*
Bak::gen(descriptor::item::Bak* descr)
{
    control::item::Bak* bak = __genTemplate(descr);
    __createInternals(bak, descr);
    return bak;
}

control::item::Bak*
Bak::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::item::Bak* descr = core::Sessions::get().session()->descriptor()->bak(descriptor_id);
    control::item::Bak* bak = __genTemplate(descr, ob_id);
    __createInternals(bak, descr);
    return bak;
}

control::item::Bak*
Bak::gen()
{
    descriptor::item::Bak* descr = nullptr;
    if (!core::Sessions::get().session()->descriptor()->hasType(descriptor::Type::BAK_EQUIPMENT)) {
        descr = descriptor::item::genBak();
    } else {
        descr = core::Sessions::get().session()->descriptor()->randBak();
    }
    assert(descr);
    return gen(descr);
}


control::item::Bak*
Bak::__genTemplate(descriptor::item::Bak* descr, int_t ob_id)
{
    model::item::Bak* model = new model::item::Bak(descr->id(), ob_id);
    control::item::Bak* bak = new control::item::Bak(descr, model);
    core::Sessions::get().session()->entity()->add(bak);
    return bak;
}

void
Bak::__createInternals(control::item::Bak* bak, descriptor::item::Bak* descr)
{
    Item::_createInternals(bak, descr);
    Equipment::_createInternals(bak, descr);
    bak->model()->setFuel(descr->fuel());
}

} // namespace item
} // namespace builder
