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

namespace core {

core::control::Droid*
DroidItemBuilder::gen()
{
    core::DroidDescr* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(core::Type::DROID_EQUIPMENT)) {
        descr = core::genDroid();
    } else {
        descr = core::shortcuts::descriptors()->randDroid();
    }
    assert(descr);
    return gen(descr);
}

core::control::Droid*
DroidItemBuilder::gen(int_t descriptor_id, int_t ob_id)
{
    core::DroidDescr* descr = core::shortcuts::descriptors()->droid(descriptor_id);
    core::control::Droid* droid = __genTemplate(descr, ob_id);
    __createInternals(droid, descr);
    return droid;
}

core::control::Droid*
DroidItemBuilder::gen(core::DroidDescr* descr)
{
    core::control::Droid* droid = __genTemplate(descr);
    __createInternals(droid, descr);
    return droid;
}  

core::control::Droid*
DroidItemBuilder::__genTemplate(DroidDescr* descriptor, int id)
{
    DroidModel* model = new DroidModel(descriptor->id(), id);
    assert(model);
    core::control::Droid* droid = new core::control::Droid(descriptor, model);
    assert(droid);
    return droid;
}

void DroidItemBuilder::__createInternals(core::control::Droid* droid, core::DroidDescr* descr)
{     
    ItemBuilder::_createInternals(droid, descr);
    EquipmentBuilder::_createInternals(droid, descr);
    droid->model()->setRepair(descr->repair());
}

} // namespace core
