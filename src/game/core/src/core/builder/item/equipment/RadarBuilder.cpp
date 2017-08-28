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
#include <core/manager/Session.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {
namespace item {

control::item::Radar*
Radar::gen()
{
    descriptor::item::Radar* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::RADAR_EQUIPMENT)) {
        descr = descriptor::item::genRadar();
    } else {
        descr = descriptor::Manager::get().randRadar();
    }
    assert(descr);
    return gen(descr);
}

control::item::Radar*
Radar::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::item::Radar* descr = descriptor::Manager::get().radar(descriptor_id);
    control::item::Radar* radar = __genTemplate(descr, ob_id);
    __createInternals(radar, descr);
    return radar;
}

control::item::Radar*
Radar::gen(descriptor::item::Radar* descr)
{
    control::item::Radar* radar = __genTemplate(descr);
    __createInternals(radar, descr);
    return radar;
} 

control::item::Radar*
Radar::__genTemplate(descriptor::item::Radar* descr, int_t ob_id)
{
    model::item::Radar* model = new model::item::Radar(descr->id(), ob_id);
    control::item::Radar* radar = new control::item::Radar(descr, model);
    core::Sessions::get().session()->entity()->add(radar);
    return radar;
}

void
Radar::__createInternals(control::item::Radar* radar, descriptor::item::Radar* descr)
{
    Item::_createInternals(radar, descr);
    Equipment::_createInternals(radar, descr);
    radar->model()->setRadius(descr->radius());
}

} // namespace item
} // namespace builder
