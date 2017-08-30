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
#include <core/world/Sector.hpp>

#include <core/descriptor/world/GalaxyDescriptor.hpp>
#include <core/manager/Session.hpp>
#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

namespace builder {

control::Galaxy*
Galaxy::gen()
{
    descriptor::Galaxy* descr = nullptr;
    if (!core::shortcuts::descriptors()->hasType(descriptor::Type::GALAXY)) {
        descr = descriptor::genGalaxy({0});
    } else {
        descr = core::shortcuts::descriptors()->randGalaxy();
    }
    return gen(descr);
}

control::Galaxy*
Galaxy::gen(descriptor::Galaxy* descr)
{
    control::Galaxy* galaxy = __genTemplate(descr);
    __createInternals(galaxy, descr);
    return galaxy;
} 

control::Galaxy*
Galaxy::__genTemplate(descriptor::Galaxy* descr)
{
    model::Galaxy* model = new model::Galaxy(descr->id());
    assert(model);

    control::Galaxy* galaxy = new control::Galaxy(descr, model);
    assert(galaxy);

    core::shortcuts::entities()->add(galaxy);

    return galaxy;
}

void Galaxy::genLife(control::Galaxy* galaxy)
{
    for(control::Sector* sector: galaxy->sectors()) {
        builder::Sector::genLife(sector);
    }
}

void Galaxy::__createInternals(control::Galaxy* galaxy, descriptor::Galaxy* descr)
{     
    for(int_t id: descr->sectors) {
        glm::vec3 position = meti::rand::gen_vec3xy(0, ENTITY::GALAXY::PARSEC/2);
        descriptor::Sector* descr_sector = core::shortcuts::descriptors()->sector(id);
        control::Sector* sector = builder::Sector::gen(descr_sector);
        galaxy->add(sector, position);
    }
}

} // namespace builder
