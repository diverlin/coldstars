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

#include <core/builder/pilot/NpcBuilder.hpp>
#include <builder/CommonBuilderHeaders.hpp>

#include <ceti/IdGenerator.hpp>
#include <ceti/Logger.hpp>
//#include <math/rand.hpp>
#include <meti/RandUtils.hpp>

#include <core/pilot/Npc.hpp>

#include <ai/aiModel/AiModelCollector.hpp>
#include <ai/aiModel/AiModelConqueror.hpp>
#include <ai/aiModel/AiModelRanger.hpp>
#include <ai/aiModel/AiModelTrader.hpp>

namespace builder {

control::Npc*
Npc::gen(race::Type race_id, entity::Type subtype_id, entity::Type subsubtype_id)
{
    control::Npc* npc = __createTemplate(subtype_id, subsubtype_id);
    __createInternals(npc, race_id, subtype_id, subsubtype_id);
    
    return npc;
}

control::Npc*
Npc::__createTemplate(entity::Type subtype_id, entity::Type subsubtype_id, int_t id)
{
    model::Npc* model = new model::Npc/*(id, subtype_id, subsubtype_id)*/;
    assert(false);
    //control::Npc* npc = new control::Npc(model);
    control::Npc* npc = new control::Npc(id, subtype_id, subsubtype_id);
    assert(npc);

    manager::EntityManager::get().add(npc);

    return npc;
}

void
Npc::__createInternals(control::Npc* npc, race::Type race_id, entity::Type subtype_id, entity::Type subsubtype_id)
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

    if ((race_id != race::Type::R6) && (race_id != race::Type::R7))
    {
        switch(subtype_id)
        {
        case entity::Type::RANGER:
        {
            assert(false);
//            npc->setAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::RANGER));

            break;
        }

        case entity::Type::WARRIOR:
        {
            assert(false);
//            npc->setAiModel(AiModelCollector::Instance().GetAiModel(AIMODEL::RANGER));

            break;
        }

        case entity::Type::TRADER:
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

    npc->model()->skills().addExpirience(meti::getRandInt(10000, 100000));
    while(npc->model()->skills().availablePoints()) {
        npc->model()->skills().manageAccordingToStrategy();
    }
}

} // namespace builder
