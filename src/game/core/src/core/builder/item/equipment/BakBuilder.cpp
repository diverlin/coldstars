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

namespace item {
namespace equipment {

BakBuilder::BakBuilder()
{
}

BakBuilder::~BakBuilder()
{}

model::item::equipment::Bak*
BakBuilder::getNew()
{
    const descriptor::BaseOLD& descriptor = core::global::get().descriptors().getRand(descriptor::Type::BAK);
    return getNew(descriptor);
}

model::item::equipment::Bak*
BakBuilder::getNew(const descriptor::BaseOLD& descr)
{
    descriptor::BaseOLD descriptor(descr.data());
    int_t id = NONE;
    if (descr.type() == (int_t)descriptor::Type::DESCRIPTOR) {
        descriptor = core::global::get().descriptors().get(descr.descriptor());
        id = descr.objId();
    }

    model::item::equipment::Bak* bak = __createTemplate(id);
    __createInternals(bak, descriptor);
    
    return bak;
}

model::item::equipment::Bak*
BakBuilder::getNew(const std::string& data)
{
    return getNew(descriptor::BaseOLD(data));
}

model::item::equipment::Bak*
BakBuilder::__createTemplate(int_t id)
{
    if (id == NONE) {
        id = core::global::get().idGenerator().nextId();
    }
    model::item::equipment::Bak* bak = new model::item::equipment::Bak;
    assert(bak);

    assert(false);
//    core::global::get().entityManager().reg(bak);
    return bak;
}

void
BakBuilder::__createInternals(model::item::equipment::Bak* bak, const descriptor::BaseOLD& descriptor)
{
    assert(descriptor.type() == (int)descriptor::Type::BAK);

    ItemCommonData data = extractCommonData(descriptor);

    bak->setFuelMaxOrig(descriptor.fuelMax());
    bak->setFuel(descriptor.fuelMax()); // ?? max or not, second descriptor should be used
    bak->setParentSubTypeId(type::entity::BAK_SLOT_ID);
    bak->setItemCommonData(data);

    assert(false);
//    bak->updateProperties();
//    bak->countPrice();
}

} // namespace equipment
} // namespace item

