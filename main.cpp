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

#include "pureTest.cpp"

#include "src/resources/init.hpp"

#include "src/builder/GalaxyBuilder.hpp"
#include "src/builder/PlayerBuilder.hpp"
#include "src/config/config.hpp"
#include "src/managers/EntityManager.hpp"

#include "src/render/Screen.hpp"
#include "src/gui/UserInput.hpp"

#include "src/common/TurnTimer.hpp"
#include "src/pilots/Npc.hpp"
#include "src/spaceobjects/Planet.hpp"

#include "src/world/galaxy.hpp"
#include "src/world/starsystem.hpp"

#include "src/garbage/EntityGarbage.hpp"

#include "src/managers/God.hpp"

int main()
{          
	//pureTest2(); 

	init();  
        
	GameDate::Instance().SetDate(1,1,4000);

	Galaxy* galaxy = GalaxyBuilder::Instance().GetNewGalaxy();
	God::Instance().SetGalaxy(galaxy);
        God::Instance().CreateLife();
        God::Instance().InitiateInvasion();
	Player* player = PlayerBuilder::Instance().GetNewPlayer();

        bool player2space = false;
        if (player2space == true)
        {
                vec2f center(400, 400);
                float angle = 0;  
                galaxy->GetRandomStarSystem()->AddVehicle(player->GetNpc()->GetVehicle(), center, angle, NULL);
	}
        else
        {
                galaxy->GetRandomStarSystem()->GetRandomPlanet()->GetLand()->AddVehicle(player->GetNpc()->GetVehicle());
        }
        
        player->GetNpc()->GetVehicle()->SetGodMode(true);
        //player->GetNpc()->GetVehicle()->TEST_DamageAndLockRandItems(); // test

	//Screen::Instance().Resize(Config::Instance().SCREEN_WIDTH/1.5, Config::Instance().SCREEN_HEIGHT);

	// GAME LOOP
	while (Screen::Instance().GetWindow().IsOpened())
	{    
		/* server code start */
		TurnTimer::Instance().Update();

		God::Instance().Update(GameDate::Instance().GetDate());
		for (int i=0; i<Config::Instance().GAME_SPEED; i++)  // fake implementation (static ai should not be run several times at once)
		{
			galaxy->Update(player, TurnTimer::Instance().GetTurnTick());
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
				galaxy = player->GetNpc()->GetVehicle()->GetStarSystem()->GetGalaxy();
			}
		}
	}

	return EXIT_SUCCESS;
}

