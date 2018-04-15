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
#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/manager/EntityManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace core {

core::control::Grapple*
GrappleItemBuilder::gen()
{
    core::GrappleDescr* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(core::Type::GRAPPLE_EQUIPMENT)) {
        descr = core::genGrapple();
    } else {
        descr = core::shortcuts::descriptors()->randGrapple();
    }
    assert(descr);
    return gen(descr);
}

core::control::Grapple*
GrappleItemBuilder::gen(int_t descriptor_id, int_t ob_id)
{
    core::GrappleDescr* descr = core::shortcuts::descriptors()->grapple(descriptor_id);
    core::control::Grapple* grapple = __genTemplate(descr, ob_id);
    __createInternals(grapple, descr);
    return grapple;
}

core::control::Grapple*
GrappleItemBuilder::gen(core::GrappleDescr* descr)
{
    core::control::Grapple* grapple = __genTemplate(descr);
    __createInternals(grapple, descr);
    return grapple;
} 

core::control::Grapple*
GrappleItemBuilder::__genTemplate(GrappleDescr* descriptor, int_t id)
{
    GrappleModel* model = new GrappleModel(descriptor->id(), id);
    assert(model);
    core::control::Grapple* grapple = new core::control::Grapple(descriptor, model);
    assert(grapple);
    return grapple;
}

void
GrappleItemBuilder::__createInternals(core::control::Grapple* grapple, core::GrappleDescr* descr)
{
    ItemBuilder::_createInternals(grapple, descr);
    EquipmentBuilder::_createInternals(grapple, descr);
    grapple->model()->setStrength(descr->strength());
    grapple->model()->setRadius(descr->radius());
    grapple->model()->setSpeed(descr->speed());
}

} // namespace core
