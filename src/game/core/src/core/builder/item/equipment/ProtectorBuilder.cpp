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


#include <builder/item/equipment/ProtectorBuilder.hpp>
#include <item/equipment/Protector.hpp>
#include <managers/EntityManager.hpp>

#include <ceti/Logger.hpp>

#include <common/Global.hpp>

#include <descriptors/Base.hpp>
#include <descriptors/DescriptorManager.hpp>

namespace builder {
namespace item {

model::item::Protector*
Protector::createTemplate()
{
    model::item::Protector* protector = new model::item::Protector;
    assert(protector);

    assert(false);
    //core::global::get().entityManager().reg(protector);
    
    return protector;
} 

std::vector<model::item::Protector*>
Protector::getNew(int num)
{
    std::vector<model::item::Protector*> result;
    for (int i=0; i<num; ++i) {
        result.push_back(getNew());
    }
    return result;
}

model::item::Protector*
Protector::getNew()
{
    const descriptor::item::Protector& descr = core::global::get().descriptors().protector().random();
    model::item::Protector* protector = createTemplate();
    createInternals(protector, descr);

    return protector;
} 

model::item::Protector*
Protector::getNew(const std::string& data)
{
    descriptor::item::Protector descr(data);
    assert(descr.descriptor() != descriptor::type::PROTECTOR_EQUIPMENT);
    return getNew(descr);
}

model::item::Protector*
Protector::getNew(const descriptor::item::Protector& descr)
{
    model::item::Protector* protector = createTemplate();
    createInternals(protector, descr);

    return protector;
}

void
Protector::createInternals(model::item::Protector* protector, const descriptor::item::Protector& descr)
{     
    assert(false);
//    ItemCommonData common_data = extractCommonData(descriptor);

//    protector->SetProtectionOrig(descriptor.protection());
//    protector->setParentSubTypeId(entity::type::PROTECTOR_SLOT_ID);
//    protector->setItemCommonData(common_data);

//    protector->updateProperties();
//    protector->CountPrice();
}

} // namespace item
} // namespace builder
