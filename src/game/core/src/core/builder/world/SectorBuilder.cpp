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
#include <world/Sector.hpp>

#include <core/descriptor/world/SectorDescriptor.hpp>

#include <core/manager/DescriptorManager.hpp>
#include <core/generator/DescriptorGenerator.hpp>

#include <world/starsystem.hpp>

#include <common/Config.hpp>

namespace builder {

control::Sector*
Sector::gen()
{
    descriptor::Sector* descr = nullptr;
    if (!descriptor::Manager::get().hasType(descriptor::Type::SECTOR)) {
        descr = descriptor::genSector({0});
    } else {
        descr = descriptor::Manager::get().randSector();
    }
    return gen(descr);
}

control::Sector*
Sector::gen(descriptor::Sector* descr)
{
    control::Sector* sector = __genTemplate(descr);
    __createInternals(sector, descr);
    return sector;
} 

void
Sector::genLife(control::Sector* sector)
{
    for(control::StarSystem* starsystem: sector->starSystems()) {
        builder::StarSystem::genLife(starsystem);
    }
}

control::Sector*
Sector::__genTemplate(descriptor::Sector* descr)
{
    model::Sector* model = new model::Sector(descr->id());
    assert(model);

    control::Sector* sector = new control::Sector(descr, model);
    assert(sector);

    manager::Entities::get().add(sector);

    return sector;
}

void
Sector::__createInternals(control::Sector* sector, descriptor::Sector* descr)
{
    for(const auto& id: descr->starsystems) {
        glm::vec3 position(meti::rand::gen_vec3xy(3, 8));
        descriptor::StarSystem* descr_starsystem = descriptor::Manager::get().starSystem(id);
        control::StarSystem* starsystem = builder::StarSystem::gen(descr_starsystem);
        sector->add(starsystem, position);
    }
}

} // namespace builder





