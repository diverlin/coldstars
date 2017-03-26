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

#include <world/starsystem.hpp>

#include <common/Config.hpp>

#include <meti/RandUtils.hpp>


namespace builder {

control::Sector*
Sector::__genTemplate()
{   
    model::Sector* model = new model::Sector;
    assert(model);

    descriptor::Sector* descr = nullptr;
    assert(descr);

    control::Sector* sector = new control::Sector(model, descr);
    assert(sector);

    EntityManager::get().reg(sector);
    
    return sector;
} 

control::Sector*
Sector::create(descriptor::Sector* descr)
{
    control::Sector* sector = __genTemplate();
    Sector::__createInternals(sector, descr);
    return sector;
} 

void
Sector::__createInternals(control::Sector* sector, descriptor::Sector* descr)
{
    for(const auto& id: descr->starsystems) {
        glm::vec3 center(meti::getRandXYVec3f(3, 8, DEFAULT_ENTITY_ZPOS));
        
        control::StarSystem* starsystem = builder::StarSystem::gen(descriptor::Manager::get().starSystem(id));
//        sector->add(starsystem, center);
    }
}

} // namespace builder





