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
#include <core/descriptor/item/equipment/Grapple.hpp>
#include <core/common/Global.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {
namespace item {

model::item::Grapple*
Grapple::gen()
{
    descriptor::item::Grapple* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::GRAPPLE_EQUIPMENT)) {
        descr = descriptor::item::genGrapple();
    } else {
        descr = descriptor::Manager::get().randGrapple();
    }
    assert(descr);
    return gen(descr);
}

model::item::Grapple*
Grapple::gen(descriptor::item::Grapple* descr)
{
    model::item::Grapple* model = __genTemplate(descr->id());
    __createInternals(model, descr);
    return model;
} 

model::item::Grapple*
Grapple::__genTemplate(int_t descriptor_id)
{
    model::item::Grapple* model = new model::item::Grapple(descriptor_id);
    EntityManager::get().reg(model);
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
