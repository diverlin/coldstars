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
#include "../../effects/Atmosphere.hpp"

#include <common/MeshTypes.hpp>

PlanetBuilder& PlanetBuilder::Instance()
{
	static PlanetBuilder instance;
	return instance;
}

PlanetBuilder::~PlanetBuilder()
{}

Planet* PlanetBuilder::GetNewPlanetTemplate(unsigned long int id) const
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

	planet_data.orbit_center.Set(0, 0, DEFAULT_ENTITY_ZPOS); 
	planet_data.radius_A      = orbit_radius;
	planet_data.radius_B      = orbit_radius; 
	planet_data.orbit_phi_inD = 0;
	planet_data.speed         = (float)getRandInt(ENTITY::PLANET::SPEED_MIN, ENTITY::PLANET::SPEED_MAX) / (float)orbit_radius;
    planet_data.clockwise     = getRandBool();

    TextureOb* textureOb 	        = TextureManager::Instance().GetRandomTextureOb(TEXTURE::PLANET_ID); 
    
    planet->SetPlanetData(planet_data);
	
	planet->SetLifeData(data_life);

	float scale_comp = getRandInt(ENTITY::PLANET::SCALE_MIN, ENTITY::PLANET::SCALE_MAX);
	Vec3<float> scale(scale_comp, scale_comp, scale_comp);
	planet->BindData3D(mesh, textureOb, scale);
	
	planet->SetAngle(Vec3<float>(-getRandInt(10, 40), -getRandInt(10, 40), 0));	
	float step = getRandInt(20, 60)*0.01;
	AnimationConstantRotationAxisZ* animation_program = new AnimationConstantRotationAxisZ(step);
	planet->SetRenderAnimation(animation_program);
	planet->SetZYX(false);
	
	//if (getRandBool()) 
	{
	        TextureOb* textureOb_atmosphere = TextureManager::Instance().GetRandomTextureOb(TEXTURE::ATMOSPHERE_ID); 
		Atmosphere* atmosphere = new Atmosphere(textureOb_atmosphere);
		planet->BindAtmosphere(atmosphere);
	}
}



