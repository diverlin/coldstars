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
#include <core/item/equipment/Bak.hpp>
#include <core/managers/EntityManager.hpp>
#include <core/descriptors/DescriptorManager.hpp>
#include <core/common/Global.hpp>

namespace builder {
namespace item {

model::item::Bak*
Bak::getNew()
{
    const descriptor::item::Bak& descr = core::global::get().descriptors().bak().random();
    return getNew(descr);
}

model::item::Bak*
Bak::getNew(const std::string& data)
{
    descriptor::item::Bak descr(data);
    assert(descr.descriptor() != descriptor::type::BAK_EQUIPMENT);
    return getNew(descr);
}

model::item::Bak*
Bak::getNew(const descriptor::item::Bak& descr)
{
    model::item::Bak* bak = __createTemplate();
    __createInternals(bak, descr);
    
    return bak;
}

model::item::Bak*
Bak::__createTemplate()
{
    model::item::Bak* bak = new model::item::Bak;
    assert(bak);

    assert(false);
//    core::global::get().entityManager().reg(bak);
    return bak;
}

void
Bak::__createInternals(model::item::Bak* bak, const descriptor::item::Bak& descriptor)
{
    assert(false);
//    assert(descriptor.type() == (int)descriptor::Type::BAK);

//    ItemCommonData data = extractCommonData(descriptor);

//    bak->setFuelMaxOrig(descriptor.fuelMax());
//    bak->setFuel(descriptor.fuelMax()); // ?? max or not, second descriptor should be used
//    bak->setParentSubTypeId(entity::type::BAK_SLOT_ID);
//    bak->setItemCommonData(data);

//    bak->updateProperties();
//    bak->countPrice();
}

} // namespace item
} // namespace builder
