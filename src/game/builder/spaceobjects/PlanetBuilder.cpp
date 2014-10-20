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

#include "PlanetBuilder.hpp"
#include "../CommonBuilderHeaders.hpp"
#include "../../spaceobjects/Planet.hpp"

#include <effects/Atmosphere.hpp>
#include <effects/Ring.hpp>

#include <types/MeshTypes.hpp>

PlanetBuilder& PlanetBuilder::Instance()
{
    static PlanetBuilder instance;
    return instance;
}

PlanetBuilder::~PlanetBuilder()
{}

Planet* PlanetBuilder::GetNewPlanetTemplate(INTLONGEST id) const
{
    Planet* planet = nullptr;
    
    if (id == NONE_ID)
    {
        id = EntityIdGenerator::Instance().GetNextId();
    }

    try 
    { 
        planet = new Planet(id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
    
    EntityManager::Instance().RegisterEntity(planet);
    
    return planet;
} 
       
Planet* PlanetBuilder::GetNewPlanet(float orbit_radius) const
{
    Planet* planet = GetNewPlanetTemplate();
    CreateNewInternals(planet, orbit_radius);
    
    return planet;
} 
     
void PlanetBuilder::CreateNewInternals(Planet* planet, float orbit_radius) const
{     
    Mesh* mesh = MeshCollector::Instance().GetMeshByTypeId(TYPE::MESH::SPHERE_ID);
      
    LifeData data_life;
    data_life.armor = 100000;

    PlanetData planet_data;

    planet_data.orbit_center  = glm::vec3(0, 0, DEFAULT_ENTITY_ZPOS); 
    planet_data.radius_A      = orbit_radius;
    planet_data.radius_B      = orbit_radius; 
    planet_data.orbit_phi_inD = 0;
    planet_data.speed         = (float)getRandInt(ENTITY::PLANET::SPEED_MIN, ENTITY::PLANET::SPEED_MAX) / (float)orbit_radius;
    planet_data.clockwise     = getRandBool();

    TextureOb* textureOb      = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::PLANET_ID); 
    
    planet->SetPlanetData(planet_data);
    
    planet->SetLifeData(data_life);

    float scale_comp = getRandInt(ENTITY::PLANET::SCALE_MIN, ENTITY::PLANET::SCALE_MAX);
    glm::vec3 scale(scale_comp, scale_comp, scale_comp);
    //alpitodorender planet->SetRenderData(mesh, textureOb, scale);
 
    float delta_angle = 0.0001*getRandInt(20, 60);
    AnimationConstantRotation* animation_rotation = new AnimationConstantRotation(delta_angle);
    //alpitodorender planet->SetAnimationRotation(animation_rotation);
    
    //if (getRandBool()) 
    {
        TextureOb* textureOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::ATMOSPHERE_ID); 
        Atmosphere* atmosphere = new Atmosphere();
        //alpitodorender atmosphere->SetRenderData(mesh, textureOb, 1.04f*scale);
        planet->AddDecoration(atmosphere);
    }

   /* 
   {
        Mesh* mesh_plane = MeshCollector::Instance().GetMeshByTypeId(TYPE::MESH::PLANE_ID);
        
        TextureOb* textureOb = TextureManager::Instance().GetRandomTextureOb(TYPE::TEXTURE::RING_ID); 
        Ring* ring = new Ring();
        ring->BindData3D(mesh_plane, textureOb, 1.5f*scale);
        //ring->SetDirection(glm::normalize(glm::vec3(1.0f)));
        ring->SetDirection(glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
        planet->AddDecoration(ring);
    }
    */
    
}



