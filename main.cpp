/*
	 Copyright (C) ColdStars, Aleksandr Pivovarov <<coldstars8@gmail.com>>

	 This program is free software; you can redistribute it and/or
	 modify it under the terms of the GNU General Public License
	 as published by the Free Software Foundation; either version 2
	 of the Licens-e, or (at your option) any later version.

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
#include "src/common/SaveLoadManager.hpp"

#include "src/render/Screen.hpp"
#include "src/gui/UserInput.hpp"

#include "src/common/TurnTimer.hpp"
#include "src/pilots/Npc.hpp"
#include "src/spaceobjects/Planet.hpp"

#include "src/garbage/EntityGarbage.hpp"

int main()
{           
	//runPureTest();

	init();  
        
	GameDate::Instance().SetDate(1,1,4000);

	Galaxy* galaxy = GalaxyBuilder::Instance().GetNewGalaxy();
	Player* player = PlayerBuilder::Instance().GetNewPlayer();

        bool player2space = true;
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
        player->GetNpc()->GetVehicle()->TEST_DamageAndLockRandItems(); // test

	//Screen::Instance().Resize(Config::Instance().SCREEN_WIDTH/1.5, Config::Instance().SCREEN_HEIGHT);

	// GAME LOOP
	while (Screen::Instance().GetWindow().IsOpened())
	{    
		/* server code start */
		TurnTimer::Instance().Update();

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
		player->RunSession(TurnTimer::Instance());
		player->UpdatePostTransactionEvent(TurnTimer::Instance());      
		
		if (TurnTimer::Instance().GetTurnEnded() == true)
		{	
			Player* loaded_player = SaveLoadManager::Instance().Update(player);
			if (loaded_player != NULL)
			{
				player = loaded_player;
				galaxy = loaded_player->GetNpc()->GetVehicle()->GetStarSystem()->GetGalaxy();
			}
		}
		/* client code end */
		
		if (TurnTimer::Instance().GetTurnTick() < 0)
		{
			EntityGarbage::Instance().Clear();
		}
	}

	return EXIT_SUCCESS;
}

//######################## UPRAVLENIE
//# 1,2,3...9 aktivacija oruzhija
//# a - aktivacija/deaktivacija vsex slotov oruzhija odnovremenno
//# g - aktivacija/deaktivacija zaxvata 
//# p - pokazat' podpisi planetam/asteroidam/mineralam
//# o - vkl/vykl otrisovku orbit vsex nebesnyx tel
//# SPACE - propusk xoda
//#################################################
