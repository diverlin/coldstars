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

#include <world/galaxy.hpp>
#include <world/Sector.hpp>

#include <descriptor/GalaxyDescriptor.hpp>
#include <descriptor/DescriptorManager.hpp>

#include <meti/RandUtils.hpp>

namespace builder {

model::Galaxy*
Galaxy::__createTemplate()
{
    model::Galaxy* galaxy = new model::Galaxy;
    assert(galaxy);

    core::global::get().entityManager().reg(galaxy);
    
    return galaxy;
} 

model::Galaxy*
Galaxy::create(descriptor::Galaxy* descr)
{
    model::Galaxy* model = __createTemplate();
    __createInternals(model, descr);
    return model;
} 

void Galaxy::__createInternals(model::Galaxy* model, descriptor::Galaxy* descr)
{     
    assert(false);
    //    for(const auto& id: descriptor.sectors) {
    //        glm::vec3 center = meti::getRandXYVec3f(0, ENTITY::GALAXY::PARSEC/2, GUI::POS_Z);
    //        Sector* sector = core::global::get().sectorBuilder().create(descriptor::Manager::get().sector().get(id));
    //        galaxy->add(sector, center);
    //    }
}

} // namespace builder
