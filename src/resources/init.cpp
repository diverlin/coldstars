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


void init()
{
        RACES_ALL_LIST.push_back(RACE::R0_ID);
    	RACES_ALL_LIST.push_back(RACE::R1_ID);
    	RACES_ALL_LIST.push_back(RACE::R2_ID);
    	RACES_ALL_LIST.push_back(RACE::R3_ID);
    	RACES_ALL_LIST.push_back(RACE::R4_ID);
   	RACES_ALL_LIST.push_back(RACE::R6_ID);
    	RACES_ALL_LIST.push_back(RACE::R7_ID);

    	RACES_GOOD_LIST.push_back(RACE::R0_ID);
    	RACES_GOOD_LIST.push_back(RACE::R1_ID);
   	RACES_GOOD_LIST.push_back(RACE::R2_ID);
    	RACES_GOOD_LIST.push_back(RACE::R3_ID);
    	RACES_GOOD_LIST.push_back(RACE::R4_ID);

    	RACES_EVIL_LIST.push_back(RACE::R6_ID);
    	RACES_EVIL_LIST.push_back(RACE::R7_ID);  
        
    	loadGameData();           
        TextureManager::Instance().FillShipSubTypeList();        
    	
    	
	/* create Macro Scenaries */
	ScenarioCollector::Instance().RegisterScenario(new MacroScenarioStarSystemLiberation());
	ScenarioCollector::Instance().RegisterScenario(new MacroScenarioStarSystemDefence());
	ScenarioCollector::Instance().RegisterScenario(new MacroScenarioSelfSafety()); 	 	   // make as singlenton
	
	/* create Micro Scenaries */
	ScenarioCollector::Instance().RegisterScenario(new MicroScenarioDocking());
	ScenarioCollector::Instance().RegisterScenario(new MicroScenarioLaunching());
	ScenarioCollector::Instance().RegisterScenario(new MicroScenarioJump());
	ScenarioCollector::Instance().RegisterScenario(new MicroScenarioDestroy());
	
	/* create AI models */
 	AIMODEL_RANGER    = new AiModelRanger();     // make as singlenton
	AIMODEL_CONQUEROR = new AiModelConqueror();  // make as singlenton
}



