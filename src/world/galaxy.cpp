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

#include "../common/constants.hpp"

Galaxy::Galaxy()
{ 
	data_id.id         = g_ID_GENERATOR.getNextId();
    	data_id.type_id    = ENTITY::GALAXY_ID;
    	data_id.subtype_id = NONE_ID;
}

void Galaxy::CreateNewInternals()
{
    	int starsystem_num = getRandInt(ENTITY::GALAXY::STARSYSTEM_NUM_MIN, ENTITY::GALAXY::STARSYSTEM_NUM_MAX);
    	for(int i = 0; i < starsystem_num; i++)
    	{  
                int id = g_ID_GENERATOR.getNextId();
                StarSystemBuilder::Instance().CreateNewStarSystem(id);
                StarSystemBuilder::Instance().CreateNewInternals();
                
        	StarSystem* starsystem = StarSystemBuilder::Instance().GetStarSystem();
        	starsystem->SetGalaxy(this);
        	this->Add(starsystem);
    	}
}

////ugly
StarSystem* Galaxy::GetRandomStarSystem()
{
	return STARSYSTEM_vec[getRandInt(0, STARSYSTEM_vec.size())];
}

StarSystem* Galaxy::GetRandomCapturedStarSystem()
{
	std::vector<StarSystem*> ss_vec;
	
	for (unsigned int i = 0; i<STARSYSTEM_vec.size(); i++)
	{
		if (STARSYSTEM_vec[i]->GetCaptured() == true)
		{
			ss_vec.push_back(STARSYSTEM_vec[i]);
		}
	}
	
	return ss_vec[getRandInt(0, ss_vec.size())];
}
//ugly
     		
void Galaxy::Update(int time)
{
	for (unsigned int i = 0; i < STARSYSTEM_vec.size(); i++)
     	{
		STARSYSTEM_vec[i]->Update(time, true); 
     	}
}

void Galaxy::SaveEvent() const
{
	for (unsigned int i = 0; i < STARSYSTEM_vec.size(); i++)
     	{
		STARSYSTEM_vec[i]->SaveEvent(); 
     	}
}

void Galaxy::LoadEvent() const
{}


Galaxy* GetNewGalaxy()
{
        Galaxy* galaxy = new Galaxy();
	return galaxy;
}

  
         
/*
void generateNumEnemyNPC(StarSystem* starsystem, int ship_per_system)
{
	int npc_subtype_id;
    	int npc_race_id = RACES_EVIL_LIST[getRandInt(0, RACES_EVIL_LIST.size())];
        
    	for (int i=0; i<ship_per_system; i++)
    	{     
       		//npc_subtype_id = SHIP_SUBTYPE_LIST[getRandInt(0, RACES_EVIL_LIST.size())];
                npc_subtype_id = CLASS::WARRIOR_ID;

        	Npc* npc = getNewNpc(npc_race_id, npc_subtype_id);

        	int ship_race_id = npc_race_id;         // RACES_ALL_LIST[getRandInt(0, RACES_ALL_LIST.size())];
        	int ship_subtype_id = npc_subtype_id;   // SHIP_SUBTYPE_LIST[getRandInt(0, SHIP_SUBTYPE_LIST.size())];
        	int ship_size_id = getRandInt(1, 9);
        	int weapons_num = getRandInt(1, 5);
        	Ship* ship = VehicleBuilder::Instance().GetNewShip(ship_race_id, ship_subtype_id, ship_size_id, weapons_num);
       
        	VehicleBuilder::Instance().Equip(ship);            // improove
        	ship->UpdateAllPropertiesAndAbilities(); 	  // improove
        
        	npc->Bind(ship);

		vec2f center(getRandInt(0, 800), getRandInt(0, 800));
		float angle = getRandInt(0, 360);  
		
        	starsystem->AddToSpace(ship, center, angle, NULL);
        	
        	Satellite* satellite = VehicleBuilder::Instance().GetNewSatellite();
                VehicleBuilder::Instance().Equip(satellite);           		// improove
                        	
                starsystem->AddToSpace((Vehicle*)satellite, vec2f(0, 0), 0, ship);
    	}
}
*/

