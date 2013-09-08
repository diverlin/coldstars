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

#include "StarBuilder.hpp"
#include "../CommonBuilderHeaders.hpp"
#include "../../spaceobjects/Star.hpp"

#include <types/MeshTypes.hpp>
    
StarBuilder& StarBuilder::Instance()
{
    static StarBuilder instance;
    return instance;
}

StarBuilder::~StarBuilder()
{}

Star* StarBuilder::GetNewStarTemplate(INTLONGEST id) const
{
    Star* star = nullptr;
    
    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    try 
    { 
        star = new Star(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    EntityManager::Instance().RegisterEntity(star);
    
    return star;
} 
 
Star* StarBuilder::GetNewStar() const
{
    Star* star = GetNewStarTemplate();
    CreateNewInternals(star);
        
    return star;
} 
          
void StarBuilder::CreateNewInternals(Star* star) const
{     
    Mesh* mesh = MeshCollector::Instance().GetMeshByTypeId(TYPE::MESH::SPHERE_ID);
    
    LifeData data_life;
    data_life.armor = 1000000; 
    
    PlanetData star_data;
    star_data.orbit_center  = glm::vec3(0, 0, DEFAULT_ENTITY_ZPOS); 
    star_data.radius_A      = 50;
    star_data.radius_B      = 50; 
    star_data.orbit_phi_inD = 0;
    star_data.speed         = 1.8;
    
    TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::STAR_ID);
    
    star->SetPlanetData(star_data);
    star->SetLifeData(data_life);
    float scale_comp = getRandInt(ENTITY::STAR::SCALE_MIN, ENTITY::STAR::SCALE_MAX); 
    glm::vec3 scale(scale_comp, scale_comp, scale_comp);
    star->BindData3D(mesh, texOb, scale);    
 
    star->CalcColor();
}


