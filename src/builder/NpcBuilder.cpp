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


NpcBuilder& NpcBuilder::Instance()
{
	static NpcBuilder instance;
	return instance;
}

NpcBuilder::~NpcBuilder()
{}

void NpcBuilder::CreateNewNpc(int id)
{
	if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
	}

        try 
        { 
		npc = new Npc(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
	EntityManager::Instance().RegisterEntity(npc);
} 
        	
void NpcBuilder::CreateNewInternals(int race_id, int subtype_id)
{    	
    	LifeData data_life;
    	
       	TextureOb* texOb_face  = g_TEXTURE_MANAGER.getRandomFaceTexObWithFolloingAttributes(race_id);
       	    
       	npc->SetRaceId(race_id);
        npc->SetTextureOb(texOb_face);
        npc->SetSubTypeId(subtype_id);
        npc->SetLifeData(data_life);
        
   
        if (( race_id == RACE::R6_ID) or ( race_id == RACE::R7_ID) )
        {
                npc->SetModelAi(AIMODEL_CONQUEROR);
        }
        else
        {
       		npc->SetModelAi(AIMODEL_RANGER);        
        }
}
