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


#include "HyperSpaceBuilder.hpp"

#include <core/type/DescriptorType.hpp>

#include <core/descriptor/world/HyperSpace.hpp>
#include <core/model/world/HyperSpace.hpp>
#include <core/world/HyperSpace.hpp>

#include <core/manager/Session.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>
#include <core/manager/EntityManager.hpp>

namespace builder {

control::HyperSpace*
HyperSpace::gen()
{
    descriptor::HyperSpace* descr = nullptr;
    if (!core::Sessions::get().session()->descriptor()->hasType(descriptor::Type::HYPERSPACE)) {
        descr = descriptor::genHyperSpace();
    } else {
        descr = core::Sessions::get().session()->descriptor()->randHyperSpace();
    }
    assert(descr);
    return gen(descr);
}

control::HyperSpace*
HyperSpace::gen(descriptor::HyperSpace* descr)
{
    control::HyperSpace* hyperspace = __genTemplate(descr);
    return hyperspace;
} 

control::HyperSpace*
HyperSpace::gen(int_t descriptor_id, int_t ob_id)
{
    descriptor::HyperSpace* descr = core::Sessions::get().session()->descriptor()->hyperSpace(descriptor_id);
    control::HyperSpace* hyperspace = __genTemplate(descr, ob_id);
    return hyperspace;
}

control::HyperSpace*
HyperSpace::__genTemplate(descriptor::HyperSpace* descr, int_t ob_id)
{
    model::HyperSpace* model = new model::HyperSpace(descr->id(), ob_id);
    assert(model);

    control::HyperSpace* hyperspace = new control::HyperSpace(descr, model);
    assert(hyperspace);

    core::shortcuts::entities()->setHyperSpace(hyperspace);
    return hyperspace;
}

} // namespace builder
