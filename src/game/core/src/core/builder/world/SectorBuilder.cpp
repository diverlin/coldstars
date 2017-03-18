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

#include <descriptor/SectorDescriptor.hpp>
#include <core/manager/DescriptorManager.hpp>

#include <world/starsystem.hpp>

#include <common/Config.hpp>

#include <meti/RandUtils.hpp>


namespace builder {

model::Sector*
Sector::__genTemplate()
{   
    model::Sector* sector = new model::Sector;
    assert(sector);

    core::global::get().entityManager().reg(sector);
    
    return sector;
} 

model::Sector*
Sector::create(descriptor::Sector* descr)
{
    model::Sector* model = __genTemplate();
    Sector::__createInternals(model, descr);
    return model;
} 

void Sector::__createInternals(model::Sector* model, descriptor::Sector* descr)
{
    for(const auto& id: descr->starsystems) {
        glm::vec3 center(meti::getRandXYVec3f(3, 8, DEFAULT_ENTITY_ZPOS));
        
        model::StarSystem* model = builder::StarSystem::gen(descriptor::Manager::get().starSystem(id));
//        sector->add(starsystem, center);
    }
}

} // namespace builder





