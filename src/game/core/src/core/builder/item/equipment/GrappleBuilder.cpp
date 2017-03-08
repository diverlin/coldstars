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
#include <core/model/item/equipment/Grapple.hpp>
#include <core/common/Global.hpp>
#include <descriptor/DescriptorManager.hpp>
#include <core/managers/EntityManager.hpp>

namespace builder {
namespace item {

model::item::Grapple*
Grapple::getNew()
{
    descriptor::item::Grapple* descr = descriptor::Manager::get().randGrapple();
    return getNew(descr);
}

//model::item::Grapple*
//Grapple::getNew(const std::string& data)
//{
//    descriptor::item::Grapple descr(data);
//    assert(descr->descriptor() != descriptor::type::GRAPPLE_EQUIPMENT);
//    return getNew(descr);
//}

model::item::Grapple*
Grapple::getNew(descriptor::item::Grapple* descr)
{
    model::item::Grapple* model = __createTemplate(descr->id());
    __createInternals(model, descr);
    return model;
} 

model::item::Grapple*
Grapple::__createTemplate(int_t descriptor_id)
{
    model::item::Grapple* model = new model::item::Grapple(descriptor_id);
    core::global::get().entityManager().reg(model);
    return model;
}

void
Grapple::__createInternals(model::item::Grapple* model, descriptor::item::Grapple* descr)
{
    Item::_createInternals(model, descr);
    Equipment::_createInternals(model, descr);
    model->setStrength(descr->strength());
    model->setRadius(descr->radius());
    model->setSpeed(descr->speed());
}

} // namespace item
} // namespace builder
