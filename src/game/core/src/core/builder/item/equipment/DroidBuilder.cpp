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
#include <core/common/Global.hpp>
#include <core/descriptor/DescriptorManager.hpp>
#include <core/managers/EntityManager.hpp>

namespace builder {
namespace item {

model::item::Droid*
Droid::getNew()
{
    const descriptor::item::Droid& descr = core::global::get().descriptors().droid().random();
    model::item::Droid* model = __createTemplate(descr.id());
    __createInternals(model, descr);
    return model;
}

model::item::Droid*
Droid::getNew(const std::string& data)
{
    descriptor::item::Droid descr(data);
    assert(descr.descriptor() != descriptor::type::DROID_EQUIPMENT);
    return getNew(descr);
}

model::item::Droid*
Droid::getNew(const descriptor::item::Droid& descr)
{
    model::item::Droid* model = __createTemplate(descr.id());
    __createInternals(model, descr);
    return model;
}  

model::item::Droid*
Droid::__createTemplate(int_t descriptor_id)
{
    model::item::Droid* model = new model::item::Droid(descriptor_id);
    core::global::get().entityManager().reg(model);
    return model;
}

void Droid::__createInternals(model::item::Droid* model, const descriptor::item::Droid& descr)
{     
    assert(false);
//    ItemCommonData common_data = extractCommonData(descr);

//    droid->SetRepairOrig(descriptor.repair());
//    droid->setParentSubTypeId(entity::type::DROID_SLOT_ID);
//    droid->setItemCommonData(common_data);

//    droid->updateProperties();
//    droid->CountPrice();
}

} // namespace item
} // namespace builder
