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
#include "../spaceobjects/Planet.hpp"

#include "../common/id.hpp"
#include "../common/Logger.hpp"
#include "../managers/EntityManager.hpp"
#include "../common/rand.hpp"
#include "../resources/TextureManager.hpp"
#include "../resources/MeshCollector.hpp"

PlanetBuilder& PlanetBuilder::Instance()
{
	static PlanetBuilder instance;
	return instance;
}

PlanetBuilder::~PlanetBuilder()
{}

Planet* PlanetBuilder::GetNewPlanetTemplate(int id) const
{
	Planet* planet = NULL;
	
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
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
        LifeData data_life;
	data_life.armor = 100000;

	PlanetData planet_data;

	planet_data.orbit_center.Set(0, 0); 
	planet_data.radius_A      = orbit_radius;
	planet_data.radius_B      = orbit_radius; 
	planet_data.orbit_phi_inD = 0;
	planet_data.speed         = (float)getRandInt(ENTITY::PLANET::SPEED_MIN, ENTITY::PLANET::SPEED_MAX) / (float)orbit_radius;
    	planet_data.clockwise     = getRandBool();

        TextureOb* textureOb 	        = TextureManager::Instance().GetRandomTextureOb(TEXTURE::PLANET_ID); 
        TextureOb* textureOb_atmosphere = TextureManager::Instance().GetRandomTextureOb(TEXTURE::ATMOSPHERE_ID); 
        
        planet->SetPlanetData(planet_data);
	
	planet->SetTextureOb(textureOb);
	planet->SetLifeData(data_life);
	planet->SetMesh(MeshCollector::Instance().GetMeshByTypeId(MESH::SPHERE_NORMAL_ID));
	planet->SetScale(getRandInt(ENTITY::PLANET::SIZE_MIN_, ENTITY::PLANET::SIZE_MAX_));

	planet->CalcCollisionrRadius();
}

//void PlanetBuilder::CreateNewInternals2(Planet* planet)
//{    
        //int race_id = getRandIntFromVec(RaceInformationCollector::Instance().RACES_GOOD_vec);
        //int ship_num_max = getRandInt(2, 5);
        //int ship_count = 0;
        //while(ship_count < ship_num_max)
        //{        	
      		//int subtype_id = ENTITY::WARRIOR_ID;
      		//int size_id     = SIZE_4_ID;
      		//int weapons_num = 4;
        
        	//Npc* new_npc = NpcBuilder::Instance().GetNewNpc(race_id, subtype_id);
        	//Ship* new_ship = ShipBuilder::Instance().GetNewShip(race_id, subtype_id, size_id, weapons_num);
		//ShipBuilder::Instance().Equip(new_ship);   // improove
		
		//planet->AddVehicle(new_ship);
		
		//ship_count++;
        //}  
//}



