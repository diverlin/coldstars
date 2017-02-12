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
#include <core/model/item/equipment/Scaner.hpp>

#include <core/common/Global.hpp>
#include <core/descriptor/DescriptorManager.hpp>
#include <core/managers/EntityManager.hpp>

//#include <ceti/Logger.hpp>

namespace builder {
namespace item {

model::item::Scaner*
Scaner::getNew()
{
    const descriptor::item::Scaner& descr = core::global::get().descriptors().scaner().random();
    model::item::Scaner* model = __createTemplate(descr.id());
    __createInternals(model, descr);

    return model;
}

model::item::Scaner*
Scaner::getNew(const std::string& data)
{
    descriptor::item::Scaner descr(data);
    assert(descr.descriptor() != descriptor::type::SCANER_EQUIPMENT);
    return getNew(descr);
}

model::item::Scaner*
Scaner::getNew(const descriptor::item::Scaner& descr)
{
    model::item::Scaner* model = __createTemplate(descr.id());
    __createInternals(model, descr);

    return model;
} 

model::item::Scaner*
Scaner::__createTemplate(int_t descriptor_id)
{
    model::item::Scaner* model = new model::item::Scaner(descriptor_id);
    assert(model);

    core::global::get().entityManager().reg(model);

    return model;
}

void
Scaner::__createInternals(model::item::Scaner* model, const descriptor::item::Scaner& descr)
{
    descriptor::item::Scaner copy(descr);

    Item::_createInternals(model, &copy);
    Equipment::_createInternals(model, &copy);
    assert(false);
//    ItemCommonData common_data = extractCommonData(descriptor);
    
//    scaner->setScanOrig(descriptor.scan());
//    scaner->setParentSubTypeId(entity::type::SCANER_SLOT_ID);
//    scaner->setItemCommonData(common_data);

//    scaner->updateProperties();
//    scaner->countPrice();
}

} // namespace item
} // namespace builder
