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

#include <ai/aiModel/AiModelCollector.hpp>
#include <ai/aiModel/AiModelRanger.hpp>
#include <ai/aiModel/AiModelConqueror.hpp>
#include <ai/aiModel/AiModelTrader.hpp>

#include <ai/scenarios/ScenarioCollector.hpp>

#include <ai/scenarios/macro/MacroScenarioGoodsTrading.hpp>
#include <ai/scenarios/macro/MacroScenarioStarSystemLiberation.hpp>
#include <ai/scenarios/macro/MacroScenarioStarSystemDefence.hpp>
#include <ai/scenarios/macro/MacroScenarioSelfSafety.hpp>

#include <ai/scenarios/micro/MicroScenarioDestroy.hpp>
#include <ai/scenarios/micro/MicroScenarioGrab.hpp>
#include <ai/scenarios/micro/MicroScenarioJump.hpp>
#include <ai/scenarios/micro/MicroScenarioDocking.hpp>
#include <ai/scenarios/micro/MicroScenarioLaunching.hpp>
#include <ai/scenarios/micro/MicroScenarioExploration.hpp>

#include <common/TurnTimer.hpp>
#include <descriptor/RaceDescriptors.hpp>

void initGameStuff()
{
    srand(time(0));
    //GameDate::Instance().SetDate(1,1,4000);
    
//    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(race::type::R0);
//    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(race::type::R1);
//    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(race::type::R2);
//    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(race::type::R3);
//    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(race::type::R4);
//    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(race::type::R6);
//    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(race::type::R7);
    
//    RaceInformationCollector::Instance().RACES_GOOD_vec.push_back(race::type::R0);
//    RaceInformationCollector::Instance().RACES_GOOD_vec.push_back(race::type::R1);
//    RaceInformationCollector::Instance().RACES_GOOD_vec.push_back(race::type::R2);
//    RaceInformationCollector::Instance().RACES_GOOD_vec.push_back(race::type::R3);
//    RaceInformationCollector::Instance().RACES_GOOD_vec.push_back(race::type::R4);
    
//    RaceInformationCollector::Instance().RACES_EVIL_vec.push_back(race::type::R6);
//    RaceInformationCollector::Instance().RACES_EVIL_vec.push_back(race::type::R7);
    
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



