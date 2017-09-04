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

#include "SectorBuilder.hpp"
#include "StarSystemBuilder.hpp"
#include "../CommonBuilderHeaders.hpp"
#include <core/world/Sector.hpp>
#include <core/model/world/Sector.hpp>

#include <core/descriptor/world/SectorDescriptor.hpp>

#include <core/manager/Session.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

//#include <world/starsystem.hpp>

//#include <common/Config.hpp>

namespace builder {

control::Sector*
Sector::gen()
{
    descriptor::Sector* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::SECTOR)) {
        descr = descriptor::genSector({0});
    } else {
        descr = core::shortcuts::descriptors()->randSector();
    }
    return gen(descr);
}

control::Sector*
Sector::gen(int_t descriptor_id, int_t object_id)
{
    descriptor::Sector* descriptor = core::shortcuts::descriptors()->sector(descriptor_id);
    control::Sector* sector = __genTemplate(descriptor, object_id);
    __createInternals(sector, descriptor);
    return sector;
}

control::Sector*
Sector::gen(descriptor::Sector* descriptor)
{
    control::Sector* sector = __genTemplate(descriptor);
    __createInternals(sector, descriptor);
    return sector;
} 

control::Sector*
Sector::__genTemplate(descriptor::Sector* descriptor, int_t object_id)
{
    model::Sector* model = new model::Sector(descriptor->id(), object_id);
    assert(model);

    control::Sector* sector = new control::Sector(descriptor, model);
    assert(sector);

    return sector;
}

void
Sector::__createInternals(control::Sector* sector, descriptor::Sector* descriptor)
{
    assert(false);
//    for(const auto& id: descr->starsystems) {
//        glm::vec3 position(meti::rand::gen_vec3xy(3, 8));
//        descriptor::StarSystem* descr_starsystem = core::shortcuts::descriptors()->starSystem(id);
//        control::StarSystem* starsystem = builder::StarSystem::gen(descr_starsystem);
//        sector->add(starsystem, position);
//    }
}

} // namespace builder





