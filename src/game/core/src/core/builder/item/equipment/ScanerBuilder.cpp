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
#include <core/manager/EntityManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {
namespace item {

control::item::Scaner*
Scaner::gen()
{
    descriptor::item::Scaner* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::SCANER_EQUIPMENT)) {
        descr = descriptor::item::genScaner();
    } else {
        descr = descriptor::Manager::get().randScaner();
    }
    assert(descr);
    return gen(descr);
}

control::item::Scaner*
Scaner::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::item::Scaner* descr = descriptor::Manager::get().scaner(descriptor_id);
    control::item::Scaner* scaner = __genTemplate(descr, ob_id);
    __createInternals(scaner, descr);
    return scaner;
}

control::item::Scaner*
Scaner::gen(descriptor::item::Scaner* descr)
{
    control::item::Scaner* scaner = __genTemplate(descr);
    __createInternals(scaner, descr);
    return scaner;
} 

control::item::Scaner*
Scaner::__genTemplate(descriptor::item::Scaner* descr, int_t ob_id)
{
    model::item::Scaner* model = new model::item::Scaner(descr->id(), ob_id);
    control::item::Scaner* scaner = new control::item::Scaner(model, descr);
    EntityManager::get().reg(scaner);
    return scaner;
}

void
Scaner::__createInternals(control::item::Scaner* scaner, descriptor::item::Scaner* descr)
{
    Item::_createInternals(scaner, descr);
    Equipment::_createInternals(scaner, descr);
    scaner->model()->setScan(descr->scan());
}

} // namespace item
} // namespace builder
