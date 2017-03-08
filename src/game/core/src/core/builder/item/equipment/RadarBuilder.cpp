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
#include <core/managers/EntityManager.hpp>

namespace builder {
namespace item {

model::item::Radar*
Radar::getNew()
{
    descriptor::item::Radar* descr = descriptor::Manager::get().radar().random();
    model::item::Radar* model = __createTemplate(descr->id());
    __createInternals(model, descr);

    return model;
}

//model::item::Radar*
//Radar::getNew(const std::string& data)
//{
//    descriptor::item::Radar descr(data);
//    assert(descr->descriptor() != descriptor::type::RADAR_EQUIPMENT);
//    return getNew(descr);
//}

model::item::Radar*
Radar::getNew(descriptor::item::Radar* descr)
{
    model::item::Radar* model = __createTemplate(descr->id());
    __createInternals(model, descr);
    return model;
} 

model::item::Radar*
Radar::__createTemplate(int_t descriptor_id)
{
    model::item::Radar* model = new model::item::Radar(descriptor_id);
    core::global::get().entityManager().reg(model);
    return model;
}

void
Radar::__createInternals(model::item::Radar* model, descriptor::item::Radar* descr)
{
    Item::_createInternals(model, descr);
    Equipment::_createInternals(model, descr);
    model->setRadius(descr->radius());
}

} // namespace item
} // namespace builder
