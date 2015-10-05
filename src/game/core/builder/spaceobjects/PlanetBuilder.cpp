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

#include <common/constants.hpp>

//#include <effects/Atmosphere.hpp>
//#include <effects/Ring.hpp>

#include <types/MeshTypes.hpp>

#include <meti/RandUtils.hpp>


PlanetBuilder::PlanetBuilder()
{}

PlanetBuilder::~PlanetBuilder()
{}

Planet* PlanetBuilder::createTemplate(INTLONGEST id) const
{
    Planet* planet = new Planet(id);
    assert(planet);

    global::get().entitiesManager().RegisterEntity(planet);
    
    return planet;
} 
       
Planet* PlanetBuilder::create(float orbit_radius) const
{
    Planet* planet = createTemplate();
    createInternals(planet, orbit_radius);
    
    return planet;
} 
     
void PlanetBuilder::createInternals(Planet* planet, float orbit_radius) const
{     
    //jeti::Mesh* mesh = MeshCollector::Instance().getMesh(TYPE::MESH::SPHERE_ID);
      
    LifeData data_life;
    data_life.armor = 100000;

    PlanetDescriptor planet_data;

    planet_data.orbit_center  = glm::vec3(0, 0, DEFAULT_ENTITY_ZPOS); 
    planet_data.radius_A      = orbit_radius;
    planet_data.radius_B      = orbit_radius; 
    planet_data.orbit_phi_inD = 0;
    planet_data.speed         = (float)meti::getRandInt(ENTITY::PLANET::SPEED_MIN, ENTITY::PLANET::SPEED_MAX) / (float)orbit_radius;
    planet_data.clockwise     = meti::getRandBool();

    //jeti::TextureOb* textureOb      = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::PLANET_ID);
    
    planet->SetPlanetDescriptor(planet_data);
    
    planet->setLifeData(data_life);

    float scale_comp = meti::getRandInt(ENTITY::PLANET::SCALE_MIN, ENTITY::PLANET::SCALE_MAX);
    glm::vec3 scale(scale_comp, scale_comp, scale_comp);
    //alpitodorender planet->SetRenderData(mesh, textureOb, scale);
 
    float delta_angle = 0.0001*meti::getRandInt(20, 60);
    //jeti::AnimationConstantRotation* animation_rotation = new jeti::AnimationConstantRotation(delta_angle);
    //alpitodorender planet->SetAnimationRotation(animation_rotation);
    
    //if (getRandBool()) 
    {
        //jeti::TextureOb* textureOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::ATMOSPHERE_ID);
        //Atmosphere* atmosphere = new Atmosphere();
        //alpitodorender atmosphere->SetRenderData(mesh, textureOb, 1.04f*scale);
        //alpitodorender planet->AddDecoration(atmosphere);
    }

   /* 
   {
        Mesh* mesh_plane = MeshCollector::Instance().getMesh(TYPE::MESH::PLANE_ID);
        
        TextureOb* textureOb = TextureCollector::Instance().getTextureByTypeId(TYPE::TEXTURE::RING_ID);
        Ring* ring = new Ring();
        ring->BindData3D(mesh_plane, textureOb, 1.5f*scale);
        //ring->setDirection(glm::normalize(glm::vec3(1.0f)));
        ring->setDirection(glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f)));
        planet->AddDecoration(ring);
    }
    */
    
}



