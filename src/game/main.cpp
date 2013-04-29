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

#include "resources/init.hpp"

#include "builder/GalaxyBuilder.hpp"
#include "builder/PlayerBuilder.hpp"
#include "config/config.hpp"
#include "world/EntityManager.hpp"

#include "render/Screen.hpp"
#include "gui/UserInput.hpp"

#include "common/TurnTimer.hpp"
#include "pilots/Npc.hpp"
#include "spaceobjects/Planet.hpp"

#include "world/galaxy.hpp"
#include "world/starsystem.hpp"

#include "garbage/EntityGarbage.hpp"

#include "world/God.hpp"

#include "world/GalaxyDescription.hpp"
#include "docking/BaseLand.hpp"

#include <iostream>

int main()
{          
	init();  
        
	GameDate::Instance().SetDate(1,1,4000);

	GalaxyDescription galaxy_description;
	galaxy_description.allow_invasion = false;
	galaxy_description.starsystem_num = 2;
	
	for (unsigned int i=0; i<galaxy_description.starsystem_num; i++)
	{
		StarSystemDescription starsystem_description;
		starsystem_description.spacestation_num_min = 50;
		starsystem_description.spacestation_num_max = 50;
		starsystem_description.allow_satellites = false;
		starsystem_description.allow_spacestations = true;
		
		starsystem_description.allow_ship_ranger   = false;
		starsystem_description.allow_ship_warrior  = false;
		starsystem_description.allow_ship_trader   = true;
		starsystem_description.allow_ship_pirat    = false;
		starsystem_description.allow_ship_diplomat = false;
		galaxy_description.starsystems.push_back(starsystem_description);
	}
	
	Galaxy* galaxy = GalaxyBuilder::Instance().GetNewGalaxy(galaxy_description);
	God::Instance().Init(galaxy, galaxy_description);
        
	Player* player = PlayerBuilder::Instance().GetNewPlayer();

        bool player2space = true;
        if (player2space == true)
        {
                vec2f center(1400, 1400);
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
	while (Screen::Instance().GetWindow().isOpen())
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

		int glErr = glGetError();
		if (glErr != 0)
		{
			std::cout<<"GL_ERROR="<<glErr<<std::endl;
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}

