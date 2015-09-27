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
#include <struct/SectorDescriptor.hpp>
#include <world/starsystem.hpp>

#include <common/Config.hpp>

#include <meti/RandUtils.hpp>

SectorBuilder::SectorBuilder()
{}

SectorBuilder::~SectorBuilder()
{}

Sector* SectorBuilder::createTemplate(INTLONGEST id) const
{
    Sector* sector = nullptr;
    if (id == NONE_ID) {
        id = EntityIdGenerator::Instance().GetNextId();
    }
    
    try {
        sector = new Sector(id);
    } catch(std::bad_alloc) {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    global::get().entitiesManager().RegisterEntity(sector);
    
    return sector;
} 

Sector* SectorBuilder::create(const SectorDescriptor& sector_descriptor) const
{
    Sector* sector = createTemplate();
    createInternals(sector, sector_descriptor);
    
    return sector;
} 
        
void SectorBuilder::createInternals(Sector* sector, const SectorDescriptor& sector_descriptor) const
{
    for(const auto& starsystem_descriptor: sector_descriptor.starsystem_descriptors)
    {  
        glm::vec3 center(meti::getRandXYVec3f(3, 8, DEFAULT_ENTITY_ZPOS));
        
        StarSystem* starsystem = global::get().starSystemBuilder().create(starsystem_descriptor);
        sector->Add(starsystem, center); 
    }
}

                


                


