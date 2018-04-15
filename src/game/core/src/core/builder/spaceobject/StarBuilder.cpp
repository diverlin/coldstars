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

#include "StarBuilder.hpp"
#include <builder/CommonBuilderHeaders.hpp>
#include <core/spaceobject/Star.hpp>

#include <common/constants.hpp>

#include <core/model/spaceobject/Star.hpp>
#include <core/spaceobject/Star.hpp>
#include <core/descriptor/Base.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/session/Shortcuts.hpp>

#include <core/generator/DescriptorGenerator.hpp>

#include <core/type/MeshType.hpp>
    
#include <meti/RandUtils.hpp>

namespace builder {

core::control::Star*
StarBuilder::gen()
{
    descriptor::Star* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::STAR)) {
        descr = descriptor::genStar();
    } else {
        descr = core::shortcuts::descriptors()->randStar();
    }
    assert(descr);
    return gen(descr);
} 

core::control::Star*
StarBuilder::gen(int_t descriptor_id, int_t id)
{
    descriptor::Star* descriptor = core::shortcuts::descriptors()->star(descriptor_id);
    return gen(descriptor, id);
}

core::control::Star*
StarBuilder::gen(descriptor::Star* descr, int_t id)
{
    core::control::Star* star = __genTemplate(descr, id);

    // Orientation
    star->setSize(descr->size());
    star->model()->setDirection(descr->direction());

    star->model()->setArmor(descr->armor());

    return star;
}

core::control::Star*
StarBuilder::__genTemplate(descriptor::Star* descr, int_t id)
{
    model::Star* model = new model::Star(descr->id(), id);
    assert(model);

    core::control::Star* star = new core::control::Star(descr, model);
    assert(star);

    return star;
}

} // namespace builder


