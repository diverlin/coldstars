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

#include "init.hpp"

#include <core/ai/aiModel/AiModelCollector.hpp>
#include <core/ai/aiModel/AiModelRanger.hpp>
#include <core/ai/aiModel/AiModelConqueror.hpp>
#include <core/ai/aiModel/AiModelTrader.hpp>

#include <core/ai/scenary/ScenarioCollector.hpp>

#include <core/ai/scenary/macro/MacroScenarioGoodsTrading.hpp>
#include <core/ai/scenary/macro/MacroScenarioStarSystemLiberation.hpp>
#include <core/ai/scenary/macro/MacroScenarioStarSystemDefence.hpp>
#include <core/ai/scenary/macro/MacroScenarioSelfSafety.hpp>

#include <core/ai/scenary/micro/MicroScenarioDestroy.hpp>
#include <core/ai/scenary/micro/MicroScenarioGrab.hpp>
#include <core/ai/scenary/micro/MicroScenarioJump.hpp>
#include <core/ai/scenary/micro/MicroScenarioDocking.hpp>
#include <core/ai/scenary/micro/MicroScenarioLaunching.hpp>
#include <core/ai/scenary/micro/MicroScenarioExploration.hpp>

#include <common/TurnTimer.hpp>
#include <descriptor/RaceDescriptors.hpp>

void initGameStuff()
{
    srand(time(0));
    //GameDate::Instance().SetDate(1,1,4000);
    
//    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(race::Type::R0);
//    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(race::Type::R1);
//    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(race::Type::R2);
//    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(race::Type::R3);
//    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(race::Type::R4);
//    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(race::Type::R6);
//    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(race::Type::R7);
    
//    RaceInformationCollector::Instance().RACES_GOOD_vec.push_back(race::Type::R0);
//    RaceInformationCollector::Instance().RACES_GOOD_vec.push_back(race::Type::R1);
//    RaceInformationCollector::Instance().RACES_GOOD_vec.push_back(race::Type::R2);
//    RaceInformationCollector::Instance().RACES_GOOD_vec.push_back(race::Type::R3);
//    RaceInformationCollector::Instance().RACES_GOOD_vec.push_back(race::Type::R4);
    
//    RaceInformationCollector::Instance().RACES_EVIL_vec.push_back(race::Type::R6);
//    RaceInformationCollector::Instance().RACES_EVIL_vec.push_back(race::Type::R7);
    
//    RaceInformationCollector::Instance().SUBSUBTYPE_vec.push_back(entity::Type::WARRIOR);
//    RaceInformationCollector::Instance().SUBSUBTYPE_vec.push_back(entity::Type::PIRAT);
//    RaceInformationCollector::Instance().SUBSUBTYPE_vec.push_back(entity::Type::TRADER);
//    RaceInformationCollector::Instance().SUBSUBTYPE_vec.push_back(entity::Type::DIPLOMAT);

    /* create Macro Scenaries */
    ScenarioCollector::Instance().add(new MacroScenarioGoodsTrading());
    ScenarioCollector::Instance().add(new MacroScenarioStarSystemLiberation());
    ScenarioCollector::Instance().add(new MacroScenarioStarSystemDefence());
    ScenarioCollector::Instance().add(new MacroScenarioSelfSafety());          
    
    /* create Micro Scenaries */
    ScenarioCollector::Instance().add(new MicroScenarioDocking());
    ScenarioCollector::Instance().add(new MicroScenarioLaunching());
    ScenarioCollector::Instance().add(new MicroScenarioJump());
    ScenarioCollector::Instance().add(new MicroScenarioDestroy());
    ScenarioCollector::Instance().add(new MicroScenarioGrab());
    ScenarioCollector::Instance().add(new MicroScenarioExploration());
            
    /* create AI models */
    AiModelCollector::Instance().RegisterAiModel(new AiModelRanger());
    AiModelCollector::Instance().RegisterAiModel(new AiModelConqueror());  
    AiModelCollector::Instance().RegisterAiModel(new AiModelTrader());  
}



