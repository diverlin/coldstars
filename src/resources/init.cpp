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
	prepearGlobalVecs();    	
    	loadGameData();
    	
	/* create Macro Scenaries */
	MACROSCENARIO_STARSYSTEMLIBERATION = new MacroScenarioStarSystemLiberation();    // make as singlenton
	MACROSCENARIO_STARSYSTEMDEFENCE    = new MacroScenarioStarSystemDefence();       // make as singlenton
	MACROSCENARIO_SELFSAFETY           = new MacroScenarioSelfSafety();	 	   // make as singlenton
	
	/* create Micro Scenaries */
	MICROSCENARIO_DOCKING = new MicroScenarioDocking();    	 // make as singlenton
	MICROSCENARIO_JUMP    = new MicroScenarioJump();       	 // make as singlenton
	MICROSCENARIO_DESTROY = new MicroScenarioDestroy();	 	 // make as singlenton
	//g_STATE_EXPLORE = new StateExplore();	 	 // make as singlenton
	
	/* create AI models */
 	AIMODEL_RANGER    = new AiModelRanger();     // make as singlenton
	AIMODEL_CONQUEROR = new AiModelConqueror();  // make as singlenton
}



void prepearGlobalVecs()
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

    	SHIP_SUBTYPE_LIST.push_back(CLASS::RANGER_ID);
    	SHIP_SUBTYPE_LIST.push_back(CLASS::WARRIOR_ID);
    	SHIP_SUBTYPE_LIST.push_back(CLASS::PIRAT_ID);
    	SHIP_SUBTYPE_LIST.push_back(CLASS::TRADER_ID);
   	SHIP_SUBTYPE_LIST.push_back(CLASS::DIPLOMAT_ID);
            
    	RACE4_ALLOWED_SUBTYPE_LIST.push_back(CLASS::WARRIOR_ID);
    	RACE4_ALLOWED_SUBTYPE_LIST.push_back(CLASS::TRADER_ID);
    	RACE4_ALLOWED_SUBTYPE_LIST.push_back(CLASS::DIPLOMAT_ID);    	
}


