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

#include "NpcBuilder.hpp"
#include "../pilots/Npc.hpp"

#include "../ai/aiModel/AiModelCollector.hpp"
#include "../ai/aiModel/AiModelConqueror.hpp"
#include "../ai/aiModel/AiModelRanger.hpp"
#include "../ai/aiModel/AiModelTrader.hpp"

#include "../common/id.hpp"
#include "../common/Logger.hpp"
#include "../common/EntityManager.hpp"
#include "../resources/textureManager.hpp"


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
		id = SimpleIdGenerator::Instance().GetNextId();
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
    	//LifeData data_life;
    	
       	//TextureOb* texOb_face  = TextureManager::Instance().getRandomFaceTexObWithFolloingAttributes(race_id);
       	    
       	npc->SetRaceId(race_id);
        //npc->SetTextureOb(texOb_face);
        npc->SetSubTypeId(subtype_id);
        //npc->SetLifeData(data_life);
        
   	if ((race_id != RACE::R6_ID) and (race_id != RACE::R7_ID))
   	{
		switch(subtype_id)
		{
   		   	//case CLASS::DIPLOMAT_ID: 	{}
   		   	//case CLASS::PIRAT_ID: 	{}
   			//case CLASS::WARRIOR_ID: 	{}
   			case CLASS::RANGER_ID:
   			{
   				npc->SetAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::RANGER_ID));    					
   				break;    
   			}
   		   	case CLASS::TRADER_ID: 
   		   	{
   		   		npc->SetAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::TRADER_ID)); 
   		   		
   		   		for (int i=0; i<6; i++)
   		   		{
   		   			npc->GetSkill().IncrementTrader();
   		   		}
   		   		npc->GetSkill().Acknowledge();
   		   		
   		   		break;
   		   	}
   		   	
   		   	default: 
   		   	{
   				npc->SetAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::RANGER_ID));    					
   				break;    
   			}
   		}
   	}
   	else
   	{
		npc->SetAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::CONQUEROR_ID));    			
   	}
}
