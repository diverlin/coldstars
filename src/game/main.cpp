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

#include "builder/world/GalaxyBuilder.hpp"
#include "builder/PlayerBuilder.hpp"
#include "config/config.hpp"
#include "world/EntityManager.hpp"

#include "render/Screen.hpp"
#include "render/GlErrorHelper.hpp"
#include "gui/UserInput.hpp"

#include "common/TurnTimer.hpp"
#include "pilots/Npc.hpp"
#include "spaceobjects/Planet.hpp"

#include "world/galaxy.hpp"
#include "world/Sector.hpp"
#include "world/starsystem.hpp"

#include "garbage/EntityGarbage.hpp"

#include "world/God.hpp"

#include "struct/GalaxyDescription.hpp"
#include "docking/BaseLand.hpp"

#include <iostream>

int main()
{
	//std::cout<<0<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(0)<<std::endl;
	//std::cout<<5<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(5)<<std::endl;
	//std::cout<<10<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(10)<<std::endl;
	//std::cout<<150<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(150)<<std::endl;
	//std::cout<<250<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(250)<<std::endl;
	//std::cout<<350<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(350)<<std::endl;
	//std::cout<<500<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(500)<<std::endl;
	//std::cout<<1000<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(1000)<<std::endl;
					
	init();  
        
	GameDate::Instance().SetDate(1,1,4000);

	GalaxyDescription galaxy_description;
	galaxy_description.allow_invasion = false;
	galaxy_description.sector_num = 2;
	
	for (unsigned int i=0; i<galaxy_description.sector_num; i++)
	{
		SectorDescription sector_description;
		sector_description.starsystem_num = 2;
		
		for (unsigned int j=0; j<sector_description.starsystem_num; j++)		
		{
			StarSystemDescription starsystem_description;
			starsystem_description.planet_num = 5;
					
			starsystem_description.spacestation_num_min = 10;
			starsystem_description.spacestation_num_max = 10;
			starsystem_description.allow_satellites = false;
			starsystem_description.allow_spacestations = true;
			
			starsystem_description.allow_ship_ranger   = false;
			starsystem_description.allow_ship_warrior  = false;
			starsystem_description.allow_ship_trader   = true;
			starsystem_description.allow_ship_pirat    = false;
			starsystem_description.allow_ship_diplomat = false;
			sector_description.starsystem_descriptions.push_back(starsystem_description);
		}
	
		
		galaxy_description.sector_descriptions.push_back(sector_description);			
	}
	
	Galaxy* galaxy = GalaxyBuilder::Instance().GetNewGalaxy(galaxy_description);
	God::Instance().Init(galaxy, galaxy_description);
        
	Player* player = PlayerBuilder::Instance().GetNewPlayer();

        bool player2space = true;
        if (player2space == true)
        {
                Vec3<float> center(500, 500, DEFAULT_ENTITY_ZPOS);
                Vec3<float> angle(0,0,0);  
                galaxy->GetRandomSector()->GetRandomStarSystem()->AddVehicle(player->GetNpc()->GetVehicle(), center, angle, NULL);
	}
        else
        {
                galaxy->GetRandomSector()->GetRandomStarSystem()->GetRandomPlanet()->GetLand()->AddVehicle(player->GetNpc()->GetVehicle());
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

		checkOpenglErrors(__FILE__,__LINE__);
	}

	return EXIT_SUCCESS;
}

