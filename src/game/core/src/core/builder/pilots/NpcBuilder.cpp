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

#include <ceti/IdGenerator.hpp>
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

model::Npc*
NpcBuilder::createTemplate(entity::type subtype_id, entity::type subsubtype_id, int_t id) const
{
    model::Npc* npc = new model::Npc/*(id, subtype_id, subsubtype_id)*/;
    assert(npc);

    core::global::get().entityManager().reg(npc);
    
    return npc;
}

model::Npc*
NpcBuilder::create(race::type race_id, entity::type subtype_id, entity::type subsubtype_id) const
{
    model::Npc* npc = createTemplate(subtype_id, subsubtype_id);
    createInternals(npc, race_id, subtype_id, subsubtype_id);
    
    return npc;
}

void
NpcBuilder::createInternals(model::Npc* npc, race::type race_id, entity::type subtype_id, entity::type subsubtype_id) const
{        
    //LifeData data_life;
    
    //TextureOb* texOb_face  = TextureCollector::Instance().getRandomFaceTexObWithFolloingAttributes(race_id);

    assert(false);
//    npc->setRaceId(race_id);

    //npc->SetTextureOb(texOb_face);
    //npc->setSubTypeId(subtype_id);
    //npc->setSubSubTypeId(subsubtype_id);
    //npc->setLifeData(data_life);
    
    assert(false);
//    npc->applySkillsStrategy();

    if ((race_id != race::type::R6) && (race_id != race::type::R7))
    {
        switch(subtype_id)
        {
        case entity::type::RANGER:
        {
            assert(false);
//            npc->setAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::RANGER));

            break;
        }

        case entity::type::WARRIOR:
        {
            assert(false);
//            npc->setAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::RANGER));

            break;
        }

        case entity::type::TRADER:
        {
            assert(false);
//            npc->setAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::TRADER));

            break;
        }

            //case ENTITY::DIPLOMAT:     {}
            //case ENTITY::PIRAT:     {}

        default:
        {
            assert(false);
//            npc->setAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::RANGER));

            break;
        }
        }
    }
    else
    {
        assert(false);
//        npc->setAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::CONQUEROR));
    }

    npc->skills().addExpirience(meti::getRandInt(10000, 100000));
    while(npc->skills().availablePoints()) {
        npc->skills().manageAccordingToStrategy();
    }
}
