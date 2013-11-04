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
#include "../../world/Sector.hpp"
#include "../../world/starsystem.hpp"

#include "../../config/config.hpp"

#include "../../struct/GalaxyDescription.hpp"

SectorBuilder& SectorBuilder::Instance()
{
    static SectorBuilder instance;
    return instance;
}

SectorBuilder::~SectorBuilder()
{}

Sector* SectorBuilder::GetNewSectorTemplate(INTLONGEST id) const
{
    Sector* sector = nullptr;
    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }
    
    try 
    { 
        sector = new Sector(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    EntityManager::Instance().RegisterEntity(sector);
    
    return sector;
} 

Sector* SectorBuilder::GetNewSector(const SectorDescription& sector_description) const
{
    Sector* sector = GetNewSectorTemplate();
    CreateNewInternals(sector, sector_description);
    
    return sector;
} 
        
void SectorBuilder::CreateNewInternals(Sector* sector, const SectorDescription& sector_description) const
{
    for(unsigned int i=0; i<sector_description.starsystem_descriptions.size(); i++)
    {  
        glm::vec3 center(getRandXYVec3f(3, 8, DEFAULT_ENTITY_ZPOS));                                    
        
        StarSystem* starsystem = StarSystemBuilder::Instance().GetNewStarSystem(sector_description.starsystem_descriptions[i]);
        sector->Add(starsystem, center); 
    }
}

                


                


