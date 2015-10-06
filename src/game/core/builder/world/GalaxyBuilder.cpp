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

#include <descriptors/GalaxyDescriptor.hpp>

#include <meti/RandUtils.hpp>


GalaxyBuilder::GalaxyBuilder()
{}

GalaxyBuilder::~GalaxyBuilder()
{}

Galaxy* GalaxyBuilder::createTemplate(ID id) const
{
    Galaxy* galaxy = new Galaxy(id);
    assert(galaxy);

    global::get().entitiesManager().reg(galaxy);
    
    return galaxy;
} 

Galaxy* GalaxyBuilder::create(const GalaxyDescriptor& galaxy_descriptor) const
{
    Galaxy* galaxy = createTemplate();
    createInternals(galaxy, galaxy_descriptor);
    
    return galaxy;
} 
            
void GalaxyBuilder::createInternals(Galaxy* galaxy, const GalaxyDescriptor& galaxy_descriptor) const
{     
    for(const auto& sector_descriptor: galaxy_descriptor.sector_descriptors) {
        glm::vec3 center = meti::getRandXYVec3f(0, ENTITY::GALAXY::PARSEC/2, GUI::POS_Z);
        Sector* sector = global::get().sectorBuilder().create(sector_descriptor);
        galaxy->Add(sector, center); 
    }
}

