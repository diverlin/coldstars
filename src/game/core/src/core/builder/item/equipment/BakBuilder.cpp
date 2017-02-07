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
#include <item/equipment/Bak.hpp>
#include <managers/EntityManager.hpp>

#include <descriptors/DescriptorManager.hpp>
#include <descriptors/Base.hpp>

//#include <ceti/Logger.hpp>

#include <common/Global.hpp>

namespace builder {
namespace item {

model::item::Bak*
Bak::getNew()
{
    const descriptor::BaseOLD& descriptor = core::global::get().descriptors().getRand(descriptor::Type::BAK);
    return getNew(descriptor);
}

model::item::Bak*
Bak::getNew(const descriptor::BaseOLD& descr)
{
    descriptor::BaseOLD descriptor(descr.data());
    model::item::Bak* bak = __createTemplate();
    __createInternals(bak, descriptor);
    
    return bak;
}

model::item::Bak*
Bak::getNew(const std::string& data)
{
    return getNew(descriptor::BaseOLD(data));
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
Bak::__createInternals(model::item::Bak* bak, const descriptor::BaseOLD& descriptor)
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
