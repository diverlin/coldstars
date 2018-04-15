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


#include <builder/world/StarSystemBuilder.hpp>
#include <core/builder/spaceobject/ALL>
#include <core/builder/pilot/NpcBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <core/spaceobject/ALL>

#include <world/starsystem.hpp>

#include <descriptor/Base.hpp>
#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/model/world/starsystem.hpp>

#include <core/generator/DescriptorGenerator.hpp>

#include <meti/RandUtils.hpp>

namespace core {

core::control::StarSystem*
StarSystemBuilder::gen()
{
    descriptor::StarSystem* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::STARSYSTEM)) {
        descr = descriptor::genStarSystem();
    } else {
        descr = core::shortcuts::descriptors()->randStarSystem();
    }
    assert(descr);
    return gen(descr);
}

core::control::StarSystem*
StarSystemBuilder::gen(descriptor::StarSystem* descr)
{
    core::control::StarSystem* starsystem = __genTemplate(descr);
    __createInternals(starsystem, descr);
    return starsystem;
} 

core::control::StarSystem*
StarSystemBuilder::gen(int_t descriptor_id, int_t object_id)
{
    descriptor::StarSystem* descriptor = core::shortcuts::descriptors()->starSystem(descriptor_id);
    core::control::StarSystem* starsystem = __genTemplate(descriptor, object_id);
    __createInternals(starsystem, descriptor);
    return starsystem;
}

core::control::StarSystem*
StarSystemBuilder::__genTemplate(descriptor::StarSystem* descr, int_t ob_id)
{
    model::StarSystem* model = new model::StarSystem(descr->id(), ob_id);
    assert(model);

    core::control::StarSystem* starsystem = new core::control::StarSystem(descr, model);
    assert(starsystem);

    return starsystem;
}

void StarSystemBuilder::__createInternals(core::control::StarSystem* starsystem, descriptor::StarSystem* descr)
{
}

} // namespace builder
