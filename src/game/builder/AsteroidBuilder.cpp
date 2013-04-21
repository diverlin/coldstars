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

#include "AsteroidBuilder.hpp"
#include "../spaceobjects/Asteroid.hpp"
#include "../common/IdGenerator.hpp"
#include "../common/Logger.hpp"
#include "../world/EntityManager.hpp"
#include "../common/rand.hpp"
#include "../resources/TextureManager.hpp"
#include "../resources/MeshCollector.hpp"

#include "../animations/AnimationConstantRotationAxisZ.hpp"
	
AsteroidBuilder& AsteroidBuilder::Instance()
{
	static AsteroidBuilder instance;
	return instance;
}

AsteroidBuilder::~AsteroidBuilder()
{}

Asteroid* AsteroidBuilder::GetNewAsteroidTemplate(unsigned long int id) const
{
	Asteroid* asteroid = NULL;
	
	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	asteroid = new Asteroid(id); 
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        EntityManager::Instance().RegisterEntity(asteroid);
        
        return asteroid;
} 

Asteroid* AsteroidBuilder::GetNewAsteroid() const
{
	Asteroid* asteroid = GetNewAsteroidTemplate();
	CreateNewInternals(asteroid);
        
        return asteroid;
} 
       	
void AsteroidBuilder::CreateNewInternals(Asteroid* asteroid) const
{           
	Mesh* mesh = MeshCollector::Instance().GetMeshByTypeId(MESH::SPHERE_DEFORMED_ID);
	
	LifeData data_life;   
	data_life.armor      = 10;
      	data_life.dying_time = 50;
      	
    	PlanetData planet_data;
	
    	planet_data.orbit_center  = vec2f(0, 0); 
    	planet_data.radius_A      = getRandInt(300, 1200);
    	planet_data.radius_B      = getRandInt(300, 1200); 
    	planet_data.orbit_phi_inD = getRandInt(0, 360);
    	planet_data.speed         = 0.1;
    	planet_data.clockwise     = getRandBool();
    	
        TextureOb* texOb = TextureManager::Instance().GetRandomTextureOb(TEXTURE::ASTEROID_ID); 
        
        asteroid->SetPlanetData(planet_data);
	asteroid->SetTextureOb(texOb);
	asteroid->SetLifeData(data_life);

        
        asteroid->SetAngle(vec3f(getRandInt(10, 40), getRandInt(10, 40), 0));	        
	float step = getRandInt(10, 100)*0.01;
	AnimationConstantRotationAxisZ* animation_program = new AnimationConstantRotationAxisZ(step);
	asteroid->SetMesh(mesh, animation_program);
	asteroid->SetZYX(false);
				
	asteroid->SetScale(getRandInt(ENTITY::ASTEROID::SCALE_MIN, ENTITY::ASTEROID::SCALE_MAX));	
       	asteroid->SetGivenExpirience(ENTITY::ASTEROID::GIVEN_EXPIRIENCE);
	
        asteroid->CalculateCollisionRadius();
}





