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
    	Gui::GetWindow().SetFramerateLimit(g_FPS_LIMIT); 
    	Gui::GetWindow().PreserveOpenGLStates(true);
    	Gui::GetWindow().UseVerticalSync(g_VERT_SYNC);

	prepearGlobalVecs();    	
    	loadGameData();
    	
	/* create Macro Scenaries */
	g_MACROSCENARIO_STARSYSTEMLIBERATION = new MacroScenarioStarSystemLiberation();    // make as singlenton
	g_MACROSCENARIO_STARSYSTEMDEFENCE    = new MacroScenarioStarSystemDefence();       // make as singlenton
	g_MACROSCENARIO_SELFSAFETY           = new MacroScenarioSelfSafety();	 	   // make as singlenton
	
	/* create Micro Scenaries */
	g_MICROSCENARIO_DOCKING = new MicroScenarioDocking();    	 // make as singlenton
	g_MICROSCENARIO_JUMP    = new MicroScenarioJump();       	 // make as singlenton
	g_MICROSCENARIO_DESTROY = new MicroScenarioDestroy();	 	 // make as singlenton
	//g_STATE_EXPLORE = new StateExplore();	 	 // make as singlenton
	
	/* create AI models */
 	g_AIMODEL_RANGER    = new AiModelRanger();     // make as singlenton
	g_AIMODEL_CONQUEROR = new AiModelConqueror();  // make as singlenton
}


Galaxy* getNewGalaxy()
{
	Galaxy* galaxy = new Galaxy();
    	return galaxy;
}



Player* getNewPlayer(Galaxy* galaxy)
{
	Player* player   = new Player();

      	int prace_id = RACE_7_ID;
      	int psubtype_id = WARRIOR_ID;
      	int size_id = 5;
      	int weapons_num = 5;
    	Npc* pnpc = getNewNpc(prace_id, psubtype_id);   
    	Ship* pship = VehicleBuilder::Instance().GetNewShip(prace_id, psubtype_id, size_id, weapons_num);
	
    	equip((Vehicle*)pship);   		// improove
        pship->UpdateAllPropertiesAndAbilities(); 		// improove
        
        pnpc->bind(pship);
   	player->bindNpc(pnpc);
   	
	vec2f center(-400, 400);
	float angle = 0;  
		
	StarSystem* starsystem = galaxy->getRandomStarSystem();
	starsystem->addToSpace(pship, center, angle, NULL);
        starsystem->addToSpace(pnpc);
        
    	return player;
}




void prepearGlobalVecs()
{
    	RACES_ALL_LIST.push_back(RACE_0_ID);
    	RACES_ALL_LIST.push_back(RACE_1_ID);
    	RACES_ALL_LIST.push_back(RACE_2_ID);
    	RACES_ALL_LIST.push_back(RACE_3_ID);
    	RACES_ALL_LIST.push_back(RACE_4_ID);
   	RACES_ALL_LIST.push_back(RACE_6_ID);
    	RACES_ALL_LIST.push_back(RACE_7_ID);

    	RACES_GOOD_LIST.push_back(RACE_0_ID);
    	RACES_GOOD_LIST.push_back(RACE_1_ID);
   	RACES_GOOD_LIST.push_back(RACE_2_ID);
    	RACES_GOOD_LIST.push_back(RACE_3_ID);
    	RACES_GOOD_LIST.push_back(RACE_4_ID);

    	RACES_EVIL_LIST.push_back(RACE_6_ID);
    	RACES_EVIL_LIST.push_back(RACE_7_ID);

    	SHIP_SUBTYPE_LIST.push_back(RANGER_ID);
    	SHIP_SUBTYPE_LIST.push_back(WARRIOR_ID);
    	SHIP_SUBTYPE_LIST.push_back(PIRAT_ID);
    	SHIP_SUBTYPE_LIST.push_back(TRADER_ID);
   	SHIP_SUBTYPE_LIST.push_back(DIPLOMAT_ID);
            
    	RACE4_ALLOWED_SUBTYPE_LIST.push_back(WARRIOR_ID);
    	RACE4_ALLOWED_SUBTYPE_LIST.push_back(TRADER_ID);
    	RACE4_ALLOWED_SUBTYPE_LIST.push_back(DIPLOMAT_ID);    	
}


