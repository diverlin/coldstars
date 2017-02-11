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
#include <core/item/equipment/Droid.hpp>
#include <core/common/Global.hpp>
#include <core/descriptors/DescriptorManager.hpp>

namespace builder {
namespace item {

model::item::Droid*
Droid::__createTemplate()
{
    model::item::Droid* droid = new model::item::Droid;
    assert(droid);

    assert(false);
    //core::global::get().entityManager().reg(droid);
    
    return droid;
} 

model::item::Droid*
Droid::getNew()
{
    const descriptor::item::Droid& descr = core::global::get().descriptors().droid().random();
    model::item::Droid* droid = __createTemplate();
    __createInternals(droid, descr);

    return droid;
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
    model::item::Droid* droid = __createTemplate();
    __createInternals(droid, descr);

    return droid;
}  

void Droid::__createInternals(model::item::Droid* droid, const descriptor::item::Droid& descr)
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
