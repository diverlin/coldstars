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

#include <builder/pilots/NpcBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <common/IdGenerator.hpp>
#include <ceti/Logger.hpp>
//#include <math/rand.hpp>
#include <meti/RandUtils.hpp>

#include <pilots/Npc.hpp>

#include <ai/aiModel/AiModelCollector.hpp>
#include <ai/aiModel/AiModelConqueror.hpp>
#include <ai/aiModel/AiModelRanger.hpp>
#include <ai/aiModel/AiModelTrader.hpp>


NpcBuilder::NpcBuilder()
{}

NpcBuilder::~NpcBuilder()
{}

Npc* NpcBuilder::createTemplate(type::ENTITY subtype_id, type::ENTITY subsubtype_id, id_type id) const
{
    Npc* npc = new Npc(id, subtype_id, subsubtype_id);
    assert(npc);

    global::get().entityManager().reg(npc);
    
    return npc;
}

Npc* NpcBuilder::create(type::race race_id, type::ENTITY subtype_id, type::ENTITY subsubtype_id) const
{
    Npc* npc = createTemplate(subtype_id, subsubtype_id);
    createInternals(npc, race_id, subtype_id, subsubtype_id);
    
    return npc;
}
            
void NpcBuilder::createInternals(Npc* npc, type::race race_id, type::ENTITY subtype_id, type::ENTITY subsubtype_id) const
{        
    //LifeData data_life;
    
    //TextureOb* texOb_face  = TextureCollector::Instance().getRandomFaceTexObWithFolloingAttributes(race_id);
        
    npc->SetRaceId(race_id);
    //npc->SetTextureOb(texOb_face);
    //npc->setSubTypeId(subtype_id);
    //npc->setSubSubTypeId(subsubtype_id);
    //npc->setLifeData(data_life);
    
    npc->ApplySkillsStrategy();
        
       if ((race_id != type::race::R6_ID) and (race_id != type::race::R7_ID))
       {
        switch(subtype_id)
        {
            case type::ENTITY::RANGER_ID:
               {
                   npc->SetAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::RANGER_ID));            
                               
                break;    
               }
                        
               case type::ENTITY::WARRIOR_ID:
               {
                   npc->SetAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::RANGER_ID));                        
                                
                break;    
               }
                       
                  case type::ENTITY::TRADER_ID: 
                  {
                      npc->SetAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::TRADER_ID)); 
                      
                      break;
                  }
                  
                        //case ENTITY::DIPLOMAT_ID:     {}
                  //case ENTITY::PIRAT_ID:     {}
                        
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
        
    npc->GetSkills().AddExpirience(meti::getRandInt(10000, 100000));
    while(npc->GetSkills().GetAvailablePoints() != 0)
    {
        npc->GetSkills().ManageAccordingToStrategy();
    }
}
