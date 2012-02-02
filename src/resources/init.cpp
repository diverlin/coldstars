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
    	g_APP.SetFramerateLimit(g_FPS_LIMIT); 
    	g_APP.PreserveOpenGLStates(true);
    	g_APP.UseVerticalSync(g_VERT_SYNC);

    	initGL(g_VIEW_WIDTH, g_VIEW_HEIGHT); 

	prepearGlobalVecs();    	
    	loadGameData();
    	
    	if (g_USE_MODERN_HW == true)
	{
		initPostProcess();
	}
	
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
	
	
	/* create galaxy */
    	g_GALAXY = new Galaxy();
    	
   
        
        /* create player */
        pPLAYER   = new Player();    
	pPLAYER->setStarSystem(g_GALAXY->getRandomStarSystem());      
      		
      	int prace_id = RACE_7_ID;
      	int psubtype_id = WARRIOR_ID;
      	int size_id = 5;
      	int weapons_num = 5;
    	Npc* pnpc = getNewNpc(prace_id, psubtype_id);   
    	Ship* pship = shipGenerator(prace_id, psubtype_id, size_id, weapons_num);
	
    	equip((Vehicle*)pship);            		// improove
        pship->updateAllStuff(); 		// improove
        
        pnpc->bind(pship);

	vec2f center(-400, 400);
	float angle = 0;  
		
        pPLAYER->getStarSystem()->addToSpace(pship, center, angle);
        pPLAYER->getStarSystem()->addToSpace(pnpc);
        	
    	pship->getPoints()->setCenter(-400, -400);
    	pship->getPoints()->setAngle(0);
    	pship->getPoints()->update();

   	pPLAYER->bindNpc(pnpc);
   	    	
    	/* create GUI */
    	g_GUI_VEHICLE = new GuiVehicle();
        g_GUI_VEHICLE->createControlSkillButtons();
        
        g_GUI_SPACE = new GuiSpace();
        g_GUI_KOSMOPORT = new GuiKosmoport();   
            	
    	g_GUI_MAP = new GuiMap();
    	g_GUI_MAP->bindGalaxy(g_GALAXY);
    	
    	g_KEYEVENTS = new KeyEvents(); 
    	
    	g_FPS = new Fps();
    	g_TIMER = new GameTimer();
}





void initGL(int width, int height)
{   
  	// Set color and depth clear value
  	//glClearDepth(1.f);
  	glClearColor(0.f, 0.f, 0.f, 0.f);

  	// Enable Z-buffer read and write
  	//glEnable(GL_DEPTH_TEST);
  	//glDepthMask(GL_TRUE);

  	// Setup a perspective projection
  	glMatrixMode(GL_PROJECTION);
  	glLoadIdentity();
  	//gluPerspective(90.f, 1.f, 1.f, 500.f);
  	glOrtho(0, width, 0, height, 0.1f, 1000.0f);
  	glMatrixMode(GL_MODELVIEW);
            
  	glEnable(GL_TEXTURE_2D);
  	glEnable(GL_BLEND);
  	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);
  
      	glShadeModel(GL_SMOOTH);
      	//glDisable(GL_LIGHTING);  
}   


void initPostProcess()
{
	int w = g_VIEW_WIDTH;
	int h = g_VIEW_HEIGHT;

	g_FBO0 = new FBO(w,h);
	g_FBO1 = new FBO(w,h);	
	g_FBO2 = new FBO(w,h);
	g_FBO3 = new FBO(w,h);
	g_BLOOM = new BloomEffect(w, h, g_BLUR_PROGRAM, g_EXTRACT_BRIGHT_PROGRAM, g_COMBINE_PROGRAM, 1, 1);
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


