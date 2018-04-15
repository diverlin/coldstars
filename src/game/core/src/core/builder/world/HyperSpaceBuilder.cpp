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

#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>
#include <core/manager/EntityManager.hpp>

namespace core {

core::control::HyperSpace*
HyperSpaceBuilder::gen()
{
    core::HyperSpaceDescr* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(core::Type::HYPERSPACE)) {
        descr = core::genHyperSpace();
    } else {
        descr = core::shortcuts::descriptors()->randHyperSpace();
    }
    assert(descr);
    return gen(descr);
}

core::control::HyperSpace*
HyperSpaceBuilder::gen(core::HyperSpaceDescr* descr)
{
    core::control::HyperSpace* hyperspace = __genTemplate(descr);
    return hyperspace;
} 

core::control::HyperSpace*
HyperSpaceBuilder::gen(int_t descriptor_id, int_t ob_id)
{
    core::HyperSpaceDescr* descr = core::shortcuts::descriptors()->hyperSpace(descriptor_id);
    core::control::HyperSpace* hyperspace = __genTemplate(descr, ob_id);
    return hyperspace;
}

core::control::HyperSpace*
HyperSpaceBuilder::__genTemplate(core::HyperSpaceDescr* descr, int_t ob_id)
{
    HyperSpaceModel* model = new HyperSpaceModel(descr->id(), ob_id);
    assert(model);

    core::control::HyperSpace* hyperspace = new core::control::HyperSpace(descr, model);
    assert(hyperspace);

    core::shortcuts::entities()->setHyperSpace(hyperspace);
    return hyperspace;
}

} // namespace core
