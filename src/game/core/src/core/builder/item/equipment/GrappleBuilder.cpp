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


#include "GrappleBuilder.hpp"
#include <item/equipment/Grapple.hpp>
#include <managers/EntityManager.hpp>

#include <ceti/Logger.hpp>

#include <common/Global.hpp>

#include <descriptors/Base.hpp>
#include <descriptors/DescriptorManager.hpp>

namespace builder {
namespace item {

model::item::Grapple*
Grapple::__createTemplate()
{
    model::item::Grapple* grapple = new model::item::Grapple;
    assert(grapple);

    assert(false);
//    core::global::get().entityManager().reg(grapple);
    
    return grapple;
} 

model::item::Grapple*
Grapple::getNew()
{
    const descriptor::item::Grapple& descr = core::global::get().descriptors().grapple().random();
    return getNew(descr);
}

model::item::Grapple*
Grapple::getNew(const std::string& data)
{
    descriptor::item::Grapple descr(data);
    assert(descr.descriptor() != descriptor::type::GRAPPLE_EQUIPMENT);
    return getNew(descr);
}

model::item::Grapple*
Grapple::getNew(const descriptor::item::Grapple& descr)
{
    model::item::Grapple* grapple = __createTemplate();
    __createInternals(grapple, descr);

    return grapple;
} 

void
Grapple::__createInternals(model::item::Grapple* grapple, const descriptor::item::Grapple& descr)
{
    assert(false);
//    ItemCommonData data = extractCommonData(descriptor);

//    grapple->SetStrengthOrig(descriptor.strength());
//    grapple->SetRadiusOrig(descriptor.radius());
//    grapple->SetSpeedOrig(descriptor.speed());

//    grapple->setParentSubTypeId(entity::type::GRAPPLE_SLOT_ID);
//    grapple->setItemCommonData(data);
    
//    grapple->updateProperties();
//    grapple->CountPrice();
}

} // namespace item
} // namespace builder
