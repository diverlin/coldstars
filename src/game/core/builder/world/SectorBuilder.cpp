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

#include <descriptors/SectorDescriptor.hpp>
#include <descriptors/DescriptorManager.hpp>

#include <world/starsystem.hpp>

#include <common/Config.hpp>

#include <meti/RandUtils.hpp>


namespace builder {

model::Sector*
Sector::__createTemplate()
{   
    model::Sector* sector = new model::Sector;
    assert(sector);

    core::global::get().entityManager().reg(sector);
    
    return sector;
} 

model::Sector*
Sector::create(const descriptor::Sector& descriptor)
{
    model::Sector* sector = __createTemplate();
    Sector::__createInternals(sector, descriptor);
    
    return sector;
} 

void Sector::__createInternals(model::Sector* sector, const descriptor::Sector& descriptor)
{
    for(const auto& id: descriptor.starsystems) {
        glm::vec3 center(meti::getRandXYVec3f(3, 8, DEFAULT_ENTITY_ZPOS));
        
        model::Starsystem* starsystem = builder::Starsystem::create(core::global::get().descriptors().starsystem().get(id));
//        sector->add(starsystem, center);
    }
}

} // namespace builder





