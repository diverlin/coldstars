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
#include <core/item/equipment/Scaner.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/model/item/equipment/Scaner.hpp>
#include <core/common/Global.hpp>
#include <core/session/Shortcuts.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace core {

core::control::item::Scaner*
ScanerItemBuilder::gen()
{
    descriptor::item::Scaner* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::SCANER_EQUIPMENT)) {
        descr = descriptor::item::genScaner();
    } else {
        descr = core::shortcuts::descriptors()->randScaner();
    }
    assert(descr);
    return gen(descr);
}

core::control::item::Scaner*
ScanerItemBuilder::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::item::Scaner* descr = core::shortcuts::descriptors()->scaner(descriptor_id);
    core::control::item::Scaner* scaner = __genTemplate(descr, ob_id);
    __createInternals(scaner, descr);
    return scaner;
}

core::control::item::Scaner*
ScanerItemBuilder::gen(descriptor::item::Scaner* descr)
{
    core::control::item::Scaner* scaner = __genTemplate(descr);
    __createInternals(scaner, descr);
    return scaner;
} 

core::control::item::Scaner*
ScanerItemBuilder::__genTemplate(descriptor::item::Scaner* descr, int_t ob_id)
{
    model::item::Scaner* model = new model::item::Scaner(descr->id(), ob_id);
    assert(model);
    core::control::item::Scaner* scaner = new core::control::item::Scaner(descr, model);
    assert(scaner);
    return scaner;
}

void
ScanerItemBuilder::__createInternals(core::control::item::Scaner* scaner, descriptor::item::Scaner* descr)
{
    ItemBuilder::_createInternals(scaner, descr);
    EquipmentBuilder::_createInternals(scaner, descr);
    scaner->model()->setScan(descr->scan());
}

} // namespace builder
