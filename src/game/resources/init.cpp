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
#include "resources.hpp"
#include "TextureManager.hpp"

#include <struct/RaceInformationCollector.hpp>

#include "../ai/aiModel/AiModelCollector.hpp"
#include "../ai/aiModel/AiModelRanger.hpp"
#include "../ai/aiModel/AiModelConqueror.hpp"
#include "../ai/aiModel/AiModelTrader.hpp"

#include "../ai/scenarios/ScenarioCollector.hpp"

#include "../ai/scenarios/macro/MacroScenarioGoodsTrading.hpp"
#include "../ai/scenarios/macro/MacroScenarioStarSystemLiberation.hpp"
#include "../ai/scenarios/macro/MacroScenarioStarSystemDefence.hpp"
#include "../ai/scenarios/macro/MacroScenarioSelfSafety.hpp"

#include "../ai/scenarios/micro/MicroScenarioDestroy.hpp"
#include "../ai/scenarios/micro/MicroScenarioGrab.hpp" 
#include "../ai/scenarios/micro/MicroScenarioJump.hpp" 
#include "../ai/scenarios/micro/MicroScenarioDocking.hpp"
#include "../ai/scenarios/micro/MicroScenarioLaunching.hpp"
#include "../ai/scenarios/micro/MicroScenarioExploration.hpp"

void init()
{
    srand(time(0));
    
    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(TYPE::RACE::R0_ID);
    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(TYPE::RACE::R1_ID);
    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(TYPE::RACE::R2_ID);
    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(TYPE::RACE::R3_ID);
    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(TYPE::RACE::R4_ID);
    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(TYPE::RACE::R6_ID);
    RaceInformationCollector::Instance().RACES_ALL_vec.push_back(TYPE::RACE::R7_ID);
    
    RaceInformationCollector::Instance().RACES_GOOD_vec.push_back(TYPE::RACE::R0_ID);
    RaceInformationCollector::Instance().RACES_GOOD_vec.push_back(TYPE::RACE::R1_ID);
    RaceInformationCollector::Instance().RACES_GOOD_vec.push_back(TYPE::RACE::R2_ID);
    RaceInformationCollector::Instance().RACES_GOOD_vec.push_back(TYPE::RACE::R3_ID);
    RaceInformationCollector::Instance().RACES_GOOD_vec.push_back(TYPE::RACE::R4_ID);
    
    RaceInformationCollector::Instance().RACES_EVIL_vec.push_back(TYPE::RACE::R6_ID);
    RaceInformationCollector::Instance().RACES_EVIL_vec.push_back(TYPE::RACE::R7_ID);  
    
    RaceInformationCollector::Instance().SUBSUBTYPE_vec.push_back(TYPE::ENTITY::WARRIOR_ID);  
    RaceInformationCollector::Instance().SUBSUBTYPE_vec.push_back(TYPE::ENTITY::PIRAT_ID);  
    RaceInformationCollector::Instance().SUBSUBTYPE_vec.push_back(TYPE::ENTITY::TRADER_ID);  
    RaceInformationCollector::Instance().SUBSUBTYPE_vec.push_back(TYPE::ENTITY::DIPLOMAT_ID);  
    
    loadGameData();           
    TextureManager::Instance().FillShipSubTypeList();        
    	
    	
	/* create Macro Scenaries */
	ScenarioCollector::Instance().RegisterScenario(new MacroScenarioGoodsTrading());
	ScenarioCollector::Instance().RegisterScenario(new MacroScenarioStarSystemLiberation());
	ScenarioCollector::Instance().RegisterScenario(new MacroScenarioStarSystemDefence());
	ScenarioCollector::Instance().RegisterScenario(new MacroScenarioSelfSafety()); 	 	
	
	/* create Micro Scenaries */
	ScenarioCollector::Instance().RegisterScenario(new MicroScenarioDocking());
	ScenarioCollector::Instance().RegisterScenario(new MicroScenarioLaunching());
	ScenarioCollector::Instance().RegisterScenario(new MicroScenarioJump());
	ScenarioCollector::Instance().RegisterScenario(new MicroScenarioDestroy());
	ScenarioCollector::Instance().RegisterScenario(new MicroScenarioGrab());
	ScenarioCollector::Instance().RegisterScenario(new MicroScenarioExploration());
			
	/* create AI models */
	AiModelCollector::Instance().RegisterAiModel(new AiModelRanger());
	AiModelCollector::Instance().RegisterAiModel(new AiModelConqueror());  
	AiModelCollector::Instance().RegisterAiModel(new AiModelTrader());  
}



