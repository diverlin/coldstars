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
#include <core/session/Shortcuts.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace core {

core::control::Bak*
BakItemBuilder::gen(descriptor::Bak* descr)
{
    core::control::Bak* bak = __genTemplate(descr);
    __createInternals(bak, descr);
    return bak;
}

core::control::Bak*
BakItemBuilder::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::Bak* descr = core::shortcuts::descriptors()->bak(descriptor_id);
    core::control::Bak* bak = __genTemplate(descr, ob_id);
    __createInternals(bak, descr);
    return bak;
}

core::control::Bak*
BakItemBuilder::gen()
{
    descriptor::Bak* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::BAK_EQUIPMENT)) {
        descr = descriptor::genBak();
    } else {
        descr = core::shortcuts::descriptors()->randBak();
    }
    assert(descr);
    return gen(descr);
}


core::control::Bak*
BakItemBuilder::__genTemplate(descriptor::Bak* descriptor, int_t id)
{
    model::Bak* model = new model::Bak(descriptor->id(), id);
    assert(model);
    core::control::Bak* bak = new core::control::Bak(descriptor, model);
    assert(bak);
    return bak;
}

void
BakItemBuilder::__createInternals(core::control::Bak* bak, descriptor::Bak* descr)
{
    ItemBuilder::_createInternals(bak, descr);
    EquipmentBuilder::_createInternals(bak, descr);
    bak->model()->setFuel(descr->fuel());
}

} // namespace core
