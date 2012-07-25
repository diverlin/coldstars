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


PlanetBuilder& PlanetBuilder::Instance()
{
	static PlanetBuilder instance;
	return instance;
}

PlanetBuilder::~PlanetBuilder()
{}

void PlanetBuilder::CreateNewPlanet(int id)
{
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
} 
        	
void PlanetBuilder::CreateNewInternals(float orbit_radius)
{           
        LifeData data_life;

	PlanetData planet_data;

	planet_data.orbit_center  = vec2f(0, 0); 
	planet_data.radius_A      = orbit_radius;
	planet_data.radius_B      = orbit_radius; 
	planet_data.orbit_phi_inD = 0;
	planet_data.speed         = (float)getRandInt(ENTITY::PLANET::SPEED_MIN, ENTITY::PLANET::SPEED_MAX) / (float)orbit_radius;


        TextureOb* textureOb 	        = TextureManager::Instance().GetRandomTextureOb(TEXTURE::PLANET_ID); 
        TextureOb* textureOb_atmosphere = TextureManager::Instance().GetRandomTextureOb(TEXTURE::ATMOSPHERE_ID); 
        
        planet->SetPlanetData(planet_data);

        unsigned long int population = getRandInt(1000, 4000);
	//unsigned long int population = 0;
	BaseLand* land;
	if (population > 0) 
	{ 
		KosmoportBuilder::Instance().CreateNewKosmoport();
		KosmoportBuilder::Instance().CreateNewInternals();
		land = KosmoportBuilder::Instance().GetKosmoport();
	}
        else                
        { 
        	land = new NatureLand(); 
        }
        	
	planet->BindLand(land);
	
	planet->SetTextureOb(textureOb);
	planet->SetSubTypeId(ENTITY::KOSMOPORT_ID);
	planet->SetLifeData(data_life);
	planet->SetMesh(g_SPHERE_MESH);	
	planet->SetScale(getRandInt(ENTITY::PLANET::SIZE_MIN_, ENTITY::PLANET::SIZE_MAX_));

	planet->CalcCollisionrRadius();
}





