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


#include <builder/world/GalaxyBuilder.hpp>
#include <builder/world/SectorBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <core/world/galaxy.hpp>
#include <core/model/world/galaxy.hpp>
//#include <core/world/Sector.hpp>

#include <common/constants.hpp>
#include <core/descriptor/world/GalaxyDescriptor.hpp>
#include <core/session/Shortcuts.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace core {

core::control::Galaxy*
GalaxyBuilder::gen()
{
    descriptor::Galaxy* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::GALAXY)) {
        descr = descriptor::genGalaxy({0});
    } else {
        descr = core::shortcuts::descriptors()->randGalaxy();
    }
    return gen(descr);
}

core::control::Galaxy*
GalaxyBuilder::gen(int_t descriptor_id, int_t object_id)
{
    descriptor::Galaxy* descriptor = core::shortcuts::descriptors()->galaxy(descriptor_id);
    core::control::Galaxy* sector = __genTemplate(descriptor, object_id);
    __createInternals(sector, descriptor);
    return sector;
}

core::control::Galaxy*
GalaxyBuilder::gen(descriptor::Galaxy* descriptor)
{
    core::control::Galaxy* galaxy = __genTemplate(descriptor);
    __createInternals(galaxy, descriptor);
    return galaxy;
} 

core::control::Galaxy*
GalaxyBuilder::__genTemplate(descriptor::Galaxy* descriptor, int_t object_id)
{
    model::Galaxy* model = new model::Galaxy(descriptor->id(), object_id);
    assert(model);

    core::control::Galaxy* galaxy = new core::control::Galaxy(descriptor, model);
    assert(galaxy);

    return galaxy;
}

void GalaxyBuilder::__createInternals(core::control::Galaxy* galaxy, descriptor::Galaxy* descr)
{
     // see composer, all logic there
}

} // namespace core
