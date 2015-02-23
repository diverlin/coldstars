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

#include <struct/GalaxyDescription.hpp>

#include <meti/RandUtils.hpp>


GalaxyBuilder& GalaxyBuilder::Instance()
{
    static GalaxyBuilder instance;
    return instance;
}

GalaxyBuilder::~GalaxyBuilder()
{}

Galaxy* GalaxyBuilder::GetNewGalaxyTemplate(INTLONGEST id) const
{
    Galaxy* galaxy = nullptr;
    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    try 
    { 
        galaxy = new Galaxy(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    global::get().entitiesManager().RegisterEntity(galaxy);
    
    return galaxy;
} 

Galaxy* GalaxyBuilder::GetNewGalaxy(const GalaxyDescription& galaxy_description) const
{
    Galaxy* galaxy = GetNewGalaxyTemplate();
    CreateNewInternals(galaxy, galaxy_description);
    
    return galaxy;
} 
            
void GalaxyBuilder::CreateNewInternals(Galaxy* galaxy, const GalaxyDescription& galaxy_description) const
{     
    for(unsigned int i=0; i<galaxy_description.sector_descriptions.size(); i++)
    {  
        glm::vec3 center = meti::getRandXYVec3f(0, ENTITY::GALAXY::PARSEC/2, GUI::POS_Z);
        
        Sector* sector = SectorBuilder::Instance().GetNewSector(galaxy_description.sector_descriptions[i]);
        galaxy->Add(sector, center); 
    }
}

