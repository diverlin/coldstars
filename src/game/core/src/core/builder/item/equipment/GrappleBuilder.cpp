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
#include <core/item/equipment/Grapple.hpp>
#include <core/descriptor/item/equipment/Grapple.hpp>
#include <core/common/Global.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {
namespace item {

control::item::Grapple*
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

control::item::Grapple*
Grapple::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::item::Grapple* descr = descriptor::Manager::get().grapple(descriptor_id);
    control::item::Grapple* grapple = __genTemplate(descr, ob_id);
    __createInternals(grapple, descr);
    return grapple;
}

control::item::Grapple*
Grapple::gen(descriptor::item::Grapple* descr)
{
    control::item::Grapple* grapple = __genTemplate(descr);
    __createInternals(grapple, descr);
    return grapple;
} 

control::item::Grapple*
Grapple::__genTemplate(descriptor::item::Grapple* descr, int_t ob_id)
{
    model::item::Grapple* model = new model::item::Grapple(descr->id(), ob_id);
    control::item::Grapple* grapple = new control::item::Grapple(descr, model);
    manager::Entity::get().add(grapple);
    return grapple;
}

void
Grapple::__createInternals(control::item::Grapple* grapple, descriptor::item::Grapple* descr)
{
    Item::_createInternals(grapple, descr);
    Equipment::_createInternals(grapple, descr);
    grapple->model()->setStrength(descr->strength());
    grapple->model()->setRadius(descr->radius());
    grapple->model()->setSpeed(descr->speed());
}

} // namespace item
} // namespace builder
