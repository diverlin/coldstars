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


#include <builder/item/equipment/RadarBuilder.hpp>
#include <item/equipment/Radar.hpp>
#include <managers/EntityManager.hpp>

#include <ceti/Logger.hpp>

#include <common/Global.hpp>

#include <descriptors/Base.hpp>
#include <descriptors/DescriptorManager.hpp>

namespace item {

RadarBuilder::RadarBuilder()
{}

RadarBuilder::~RadarBuilder()
{}

Radar* RadarBuilder::createTemplate(int_t id) const
{
    Radar* radar = new Radar(id);
    assert(radar);

    assert(false);
//    core::global::get().entityManager().reg(radar);
    
    return radar;
} 

Radar* RadarBuilder::getNew() const
{
    const descriptor::BaseOLD& descriptor = core::global::get().descriptors().getRand(descriptor::Type::RADAR);
    Radar* radar = createTemplate();
    createInternals(radar, descriptor);

    return radar;
}

Radar* RadarBuilder::getNew(const descriptor::BaseOLD& descriptor) const
{
    Radar* radar = createTemplate();
    createInternals(radar, descriptor);

    return radar;
} 

void RadarBuilder::createInternals(Radar* radar, const descriptor::BaseOLD& descriptor) const
{     
    ItemCommonData common_data = extractCommonData(descriptor);

    radar->SetRadiusOrig(descriptor.radius());
    radar->setParentSubTypeId(entity::type::RADAR_SLOT_ID);
    radar->setItemCommonData(common_data);

    radar->updateProperties();
    radar->CountPrice();
}

} // namespace item
