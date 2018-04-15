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

#include "TurrelBuilder.hpp"
#include <core/builder/CommonBuilderHeaders.hpp>
#include <core/model/spaceobject/Asteroid.hpp>
#include <core/part/Turrel.hpp>
#include <core/descriptor/part/Turrel.hpp>

#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <core/generator/DescriptorGenerator.hpp>

namespace GovermentBuilder {

core::control::Turrel*
TurrelBuilder::gen()
{
    descriptor::Turrel* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::TURREL)) {
        descr = descriptor::genTurrel();
    } else {
        descr = core::shortcuts::descriptors()->randTurrel();
    }
    assert(descr);
    return gen(descr);
}

core::control::Turrel*
TurrelBuilder::gen(descriptor::Turrel* descr)
{
    core::control::Turrel* turrel = __genTemplate(descr);

    /// Base

    /// Orientation
    turrel->setSize(descr->size());
    turrel->model()->setDirection(descr->direction());

    return turrel;
} 

core::control::Turrel*
TurrelBuilder::__genTemplate(descriptor::Turrel* descr)
{
    model::Turrel* model = new model::Turrel(descr->id());
    assert(model);

    core::control::Turrel* turrel = new core::control::Turrel(descr, model);
    assert(turrel);

    //manager::Entities::get().add(turrel);

    return turrel;
}

} // namespace builder



