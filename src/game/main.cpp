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

#include <iostream>
#include "resources/init.hpp"

#include "builder/world/GalaxyBuilder.hpp"
#include "builder/PlayerBuilder.hpp"
#include "config/config.hpp"
#include "world/EntityManager.hpp"

#include "render/Screen.hpp"
#include "render/GlErrorHelper.hpp"
#include "gui/UserInput.hpp"

#include "common/TurnTimer.hpp"
#include "pilots/Npc.hpp"
#include "pilots/Player.hpp"
#include "spaceobjects/Planet.hpp"
#include "spaceobjects/Vehicle.hpp"

#include "world/galaxy.hpp"
#include "world/Sector.hpp"
#include "world/starsystem.hpp"

#include "garbage/EntityGarbage.hpp"

#include "world/God.hpp"

#include "struct/GalaxyDescription.hpp"
#include "docking/BaseLand.hpp"

#include "run_scenario/NormalRunScenario.hpp"
#include "run_scenario/TestParticlesRunScenario.hpp"
#include "run_scenario/TestTextRunScenario.hpp"

#include "gui/ButtonTrigger.hpp"
#include "gui/GuiActions.hpp"

#include "../pureTest/threadTest.cpp"

enum { NORMAL_RUNSCENARIO, TEST_PARTICLES_RUNSCENARIO, TEST_TEXT_RUNSCENARIO };

int main()
{
	//runThreadTest();
	
	init();        
	GameDate::Instance().SetDate(1,1,4000);
        
	Player* player = PlayerBuilder::Instance().GetNewPlayer();
	
	BaseRunScenario* run_scenario = nullptr;
	int scenario_type = NORMAL_RUNSCENARIO;
	switch(scenario_type)
	{
		case NORMAL_RUNSCENARIO: { run_scenario = new NormalRunScenario(); break; }
		case TEST_PARTICLES_RUNSCENARIO: { run_scenario = new TestParticlesRunScenario(); break; }	
		case TEST_TEXT_RUNSCENARIO: { run_scenario = new TestTextRunScenario(); break; }
		default: { std::cout<<"INVALID_RUNSCENARIO"<<std::endl; return EXIT_FAILURE; break; }	
	}
	run_scenario->Init(player);
	
	Galaxy* galaxy = player->GetNpc()->GetVehicle()->GetStarSystem()->GetSector()->GetGalaxy();       
        
	player->GetNpc()->GetVehicle()->SetGodMode(true);
	//player->GetNpc()->GetVehicle()->TEST_DamageAndLockRandItems(); // test

	//Screen::Instance().Resize(Config::Instance().SCREEN_WIDTH/1.5, Config::Instance().SCREEN_HEIGHT);
	
	/** */
	//ButtonTrigger* button = new ButtonTrigger(/*subtype_id=*/1, /*info*/"info", /*pAction=*/GuiActions::Test, /*textureOb*/NULL);
	//button->PressEvent(player);
	//button->PressEvent(player);

	//ButtonTrigger* button2 = new ButtonTrigger(/*subtype_id=*/2, /*info*/"info", /*pAction=*/GuiActions::Test2, /*textureOb*/NULL);
	//button2->PressEvent(player);
	
	////GuiActions::GalaxyMapGuiTransition(player);
	////player->GetGuiManager().EnterGuiSpace();
	////player->GetGuiManager().GetGuiSpace().EnterGalaxyMap();
	/** */
	
	// GAME LOOP
	while (Screen::Instance().GetWindow().isOpen())
	{    
		//std::cout<<player->GetNpc()->GetVehicle()->GetCenter().x<<std::endl;
		//std::cout<<player->GetNpc()->GetVehicle()->GetProperties().radar<<std::endl;
				
		/* server code start */
		TurnTimer::Instance().Update();

		God::Instance().Update(GameDate::Instance().GetDate());
		for (int i=0; i<Config::Instance().GAME_SPEED; i++)  // fake implementation (static ai should not be run several times at once)
		{
			galaxy->Update(TurnTimer::Instance().GetTurnTick());
		}

		if ((TurnTimer::Instance().GetTurnEnded() == true) and (UserInput::Instance().GetNextTurnReady()))
		{
			TurnTimer::Instance().NextTurn();
		} 
		/* server code end */

		/* client code start */
                player->UpdatePostTransaction();   
		player->RunSession(TurnTimer::Instance());  
                player->UpdatePostTransactionEvent(TurnTimer::Instance()); 
		/* client code end */
		
		if (TurnTimer::Instance().GetTurnEnded() == true)
		{
			EntityGarbage::Instance().Clear();

			bool save_event = EntityManager::Instance().UpdateSaveRequest();
			bool load_event = EntityManager::Instance().UpdateLoadRequest();
			if (load_event == true)
			{
				player = EntityManager::Instance().GetPlayer();
				galaxy = player->GetNpc()->GetVehicle()->GetStarSystem()->GetSector()->GetGalaxy();
			}
		}

		if (TurnTimer::Instance().GetTurnTick() > 1) // hack
		{
			run_scenario->Update_inDynamic(player);
		}
		else
		{
			run_scenario->Update_inStatic(player);		
		}
		
		checkOpenglErrors(__FILE__,__LINE__);
	}

	return EXIT_SUCCESS;
}

