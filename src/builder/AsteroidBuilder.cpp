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


AsteroidBuilder& AsteroidBuilder::Instance()
{
	static AsteroidBuilder instance;
	return instance;
}

AsteroidBuilder::~AsteroidBuilder()
{}

void AsteroidBuilder::CreateNewAsteroid(int id)
{
	if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
	}
        asteroid = new Asteroid(id);
        EntityManager::Instance().RegisterEntity(asteroid);
} 
        	
void AsteroidBuilder::CreateNewInternals()
{           
	LifeData data_life;   
	data_life.armor      = 10;
      	data_life.dying_time = 50;
      	
    	PlanetData planet_data;
	
	planet_data.scale         = getRandInt(ENTITY::ASTEROID::SIZE_MIN_, ENTITY::ASTEROID::SIZE_MAX_);  
    	planet_data.orbit_center  = vec2f(0, 0); 
    	planet_data.radius_A      = getRandInt(300, 1200);
    	planet_data.radius_B      = getRandInt(300, 1200); 
    	planet_data.orbit_phi_inD = getRandInt(0, 360);
    	planet_data.speed         = 0.1;

        TextureOb* texOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::ASTEROID_ID); 
        
        asteroid->SetPlanetData(planet_data);
	asteroid->SetTextureOb(texOb);
	asteroid->SetLifeData(data_life);
	asteroid->SetMesh(g_DEFORMED_SPHERE_MESH);	
       	
        asteroid->CalcCollisionrRadius();
}





