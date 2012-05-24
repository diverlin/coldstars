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


StarBuilder& StarBuilder::Instance()
{
	static StarBuilder instance;
	return instance;
}

StarBuilder::~StarBuilder()
{}

void StarBuilder::CreateNewStar(int id)
{
	if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
	}
        star = new Star(id);
        EntityManager::Instance().RegisterEntity(star);
} 
        	
void StarBuilder::CreateNewInternals()
{     
        LifeData data_life;

 	PlanetData star_data;
	star_data.scale         = getRandInt(ENTITY::STAR::SIZE_MIN_, ENTITY::STAR::SIZE_MAX_);  
    	star_data.orbit_center  = vec2f(0, 0); 
    	star_data.radius_A      = 50;
    	star_data.radius_B      = 50; 
    	star_data.orbit_phi_inD = 0;
    	star_data.speed         = 1.8;

    	TextureOb* texOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::STAR_ID);

    	star->SetPlanetData(star_data);
	star->SetTextureOb(texOb);
	star->SetLifeData(data_life);
	star->SetMesh(g_SPHERE_MESH);	
        	
        star->CalcCollisionrRadius();
 
	star->CalcColor();
}


