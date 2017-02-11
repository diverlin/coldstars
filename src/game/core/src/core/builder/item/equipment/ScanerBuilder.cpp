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
#include <item/equipment/Scaner.hpp>
#include <managers/EntityManager.hpp>

#include <ceti/Logger.hpp>

#include <common/Global.hpp>

#include <descriptors/Base.hpp>
#include <descriptors/DescriptorManager.hpp>

namespace builder {
namespace item {

model::item::Scaner*
ScanerBuilder::getNew()
{
    const descriptor::item::Scaner& descr = core::global::get().descriptors().scaner().random();
    model::item::Scaner* model = __createTemplate();
    __createInternals(model, descr);

    return model;
}

model::item::Scaner*
ScanerBuilder::getNew(const std::string& data)
{
    descriptor::item::Scaner descr(data);
    assert(descr.descriptor() != descriptor::type::SCANER_EQUIPMENT);
    return getNew(descr);
}

model::item::Scaner*
ScanerBuilder::getNew(const descriptor::item::Scaner& descr)
{
    model::item::Scaner* model = __createTemplate();
    __createInternals(model, descr);

    return model;
} 

model::item::Scaner*
ScanerBuilder::__createTemplate()
{
    model::item::Scaner* model = new model::item::Scaner;
    assert(model);

    assert(false);
    //core::global::get().entityManager().reg(scaner);

    return model;
}

void
ScanerBuilder::__createInternals(model::item::Scaner* model, const descriptor::item::Scaner& descr)
{
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
