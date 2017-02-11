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


#include "RadarBuilder.hpp"
#include <core/descriptor/item/equipment/Radar.hpp>
#include <core/descriptor/DescriptorManager.hpp>
#include <core/model/item/equipment/Radar.hpp>
#include <core/common/Global.hpp>

namespace builder {
namespace item {

model::item::Radar*
Radar::getNew()
{
    const descriptor::item::Radar& descr = core::global::get().descriptors().radar().random();
    model::item::Radar* radar = __createTemplate();
    __createInternals(radar, descr);

    return radar;
}

model::item::Radar*
Radar::getNew(const std::string& data)
{
    descriptor::item::Radar descr(data);
    assert(descr.descriptor() != descriptor::type::RADAR_EQUIPMENT);
    return getNew(descr);
}

model::item::Radar*
Radar::getNew(const descriptor::item::Radar& descr)
{
    model::item::Radar* radar = __createTemplate();
    __createInternals(radar, descr);

    return radar;
} 

model::item::Radar*
Radar::__createTemplate()
{
    model::item::Radar* radar = new model::item::Radar;
    assert(radar);

    assert(false);
//    core::global::get().entityManager().reg(radar);

    return radar;
}

void Radar::__createInternals(model::item::Radar* radar, const descriptor::item::Radar& descr)
{
    assert(false);
//    ItemCommonData common_data = extractCommonData(descriptor);

//    radar->SetRadiusOrig(descriptor.radius());
//    radar->setParentSubTypeId(entity::type::RADAR_SLOT_ID);
//    radar->setItemCommonData(common_data);

//    radar->updateProperties();
//    radar->CountPrice();
}

} // namespace item
} // namespace builder