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

#include "../common/IdGenerator.hpp"
#include "../common/Logger.hpp"
#include "../common/rand.hpp"

#include "../world/EntityManager.hpp"
#include "../resources/TextureManager.hpp"

NpcBuilder& NpcBuilder::Instance()
{
	static NpcBuilder instance;
	return instance;
}

NpcBuilder::~NpcBuilder()
{}

Npc* NpcBuilder::GetNewNpcTemplate(ENTITY::eTYPE subtype_id, ENTITY::eTYPE subsubtype_id, unsigned long int id) const
{
	Npc* npc = nullptr;
	
	if (id == NONE_ID)
	{
		id = EntityIdGenerator::Instance().GetNextId();
	}

    try 
    { 
        npc = new Npc(id, subtype_id, subsubtype_id);
    }
    catch(std::bad_alloc)
    {
        Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
    }
	EntityManager::Instance().RegisterEntity(npc);
	
	return npc;
} 


Npc* NpcBuilder::GetNewNpc(int race_id, ENTITY::eTYPE subtype_id, ENTITY::eTYPE subsubtype_id) const
{
    Npc* npc = GetNewNpcTemplate(subtype_id, subsubtype_id);
    CreateNewInternals(npc, race_id, subtype_id, subsubtype_id);  
    
    return npc;
}
        	
void NpcBuilder::CreateNewInternals(Npc* npc, int race_id, ENTITY::eTYPE subtype_id, ENTITY::eTYPE subsubtype_id) const
{    	
    //LifeData data_life;
    
    //TextureOb* texOb_face  = TextureManager::Instance().getRandomFaceTexObWithFolloingAttributes(race_id);
        
    npc->SetRaceId(race_id);
    //npc->SetTextureOb(texOb_face);
    //npc->SetSubTypeId(subtype_id);
    //npc->SetSubSubTypeId(subsubtype_id);
    //npc->SetLifeData(data_life);
    
    npc->ApplySkillsStrategy();
        
   	if ((race_id != RACE::R6_ID) and (race_id != RACE::R7_ID))
   	{
		switch(subtype_id)
		{
                        case ENTITY::eTYPE::RANGER_ID:
   			{
   				npc->SetAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::RANGER_ID));    					
                               
                                break;    
   			}
                        
   			case ENTITY::eTYPE::WARRIOR_ID:
   			{
   				npc->SetAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::RANGER_ID));    					
                                
                                break;    
   			}
                       
   		   	case ENTITY::eTYPE::TRADER_ID: 
   		   	{
   		   		npc->SetAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::TRADER_ID)); 
   		   		
   		   		break;
   		   	}
   		   	
                        //case ENTITY::DIPLOMAT_ID: 	{}
   		   	//case ENTITY::PIRAT_ID: 	{}
                        
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
        
        npc->GetSkills().AddExpirience(getRandInt(10000, 100000));
        while(npc->GetSkills().GetAvailablePoints() != 0)
        {
                npc->GetSkills().ManageAccordingToStrategy();
        }
}
