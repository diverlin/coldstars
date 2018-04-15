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
#include <core/model/item/equipment/Radar.hpp>
#include <core/item/equipment/Radar.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/common/Global.hpp>
#include <core/session/Shortcuts.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace core {

core::control::Radar*
RadarItemBuilder::gen()
{
    core::RadarDescr* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(core::Type::RADAR_EQUIPMENT)) {
        descr = core::genRadar();
    } else {
        descr = core::shortcuts::descriptors()->randRadar();
    }
    assert(descr);
    return gen(descr);
}

core::control::Radar*
RadarItemBuilder::gen(int_t descriptor_id, int_t ob_id)
{
    core::RadarDescr* descr = core::shortcuts::descriptors()->radar(descriptor_id);
    core::control::Radar* radar = __genTemplate(descr, ob_id);
    __createInternals(radar, descr);
    return radar;
}

core::control::Radar*
RadarItemBuilder::gen(core::RadarDescr* descr)
{
    core::control::Radar* radar = __genTemplate(descr);
    __createInternals(radar, descr);
    return radar;
} 

core::control::Radar*
RadarItemBuilder::__genTemplate(RadarDescr* descriptor, int_t id)
{
    model::Radar* model = new model::Radar(descriptor->id(), id);
    assert(model);
    core::control::Radar* radar = new core::control::Radar(descriptor, model);
    assert(radar);
    return radar;
}

void
RadarItemBuilder::__createInternals(core::control::Radar* radar, core::RadarDescr* descr)
{
    ItemBuilder::_createInternals(radar, descr);
    EquipmentBuilder::_createInternals(radar, descr);
    radar->model()->setRadius(descr->radius());
}

} // namespace core
