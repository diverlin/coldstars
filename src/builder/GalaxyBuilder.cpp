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


GalaxyBuilder& GalaxyBuilder::Instance()
{
	static GalaxyBuilder instance;
	return instance;
}

GalaxyBuilder::~GalaxyBuilder()
{}

void GalaxyBuilder::CreateNewGalaxy()
{
	int id = g_ID_GENERATOR.getNextId();
        galaxy = new Galaxy(id);
} 
        	
void GalaxyBuilder::CreateNewInternals()
{     	
    	int starsystem_num = getRandInt(ENTITY::GALAXY::STARSYSTEM_NUM_MIN, ENTITY::GALAXY::STARSYSTEM_NUM_MAX);
    	for(int i = 0; i < starsystem_num; i++)
    	{  
                StarSystemBuilder::Instance().CreateNewStarSystem();
                StarSystemBuilder::Instance().CreateNewInternals();
                
        	StarSystem* starsystem = StarSystemBuilder::Instance().GetStarSystem();
        	starsystem->SetGalaxy(galaxy);
        	galaxy->Add(starsystem);
 	}
}

void GalaxyBuilder::LoadGalaxy(const std::string& root)
{
	int id = SaveManager::Instance().Get<int>(root+"data_id.id");
	
}

