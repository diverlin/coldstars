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


#include <run_scenario/NormalRunScenario.hpp>

#include <iostream>

#include <builder/world/GalaxyBuilder.hpp>

#include <pilots/Npc.hpp>
#include <pilots/Player.hpp>

#include <world/God.hpp>
#include <world/galaxy.hpp>
#include <world/Sector.hpp>
#include <world/starsystem.hpp>
#include <world/EntityManager.hpp>

#include <spaceobjects/Planet.hpp>
#include <dock/BaseLand.hpp>

#include <garbage/EntityGarbage.hpp>

#include <struct/GalaxyDescription.hpp>


/* virtual */
void NormalRunScenario::Init(Player* player)
{
	GalaxyDescription galaxy_description;
	galaxy_description.allow_invasion = true;
	galaxy_description.sector_num = 10;
	
	for (int i=0; i<galaxy_description.sector_num; i++)
	{
		SectorDescription sector_description;
		sector_description.starsystem_num = 3;
		
		for (int j=0; j<sector_description.starsystem_num; j++)		
		{
			StarSystemDescription starsystem_description;
			starsystem_description.planet_num = 10;
			starsystem_description.spacestation_num = 3;
			starsystem_description.asteroid_num = 3;
						
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
	God::Instance().SetGalaxy(galaxy);        
	God::Instance().CreateLife(galaxy_description);
	if (galaxy_description.allow_invasion == true)
	{
		God::Instance().CreateInvasion(galaxy_description);
	}
	
 	bool player2space = true;
 	StarSystem* const starsystem = galaxy->GetRandomSector()->GetRandomStarSystem();
	if (player2space == true)
	{
		Vec3<float> center(500, 500, DEFAULT_ENTITY_ZPOS);
		Vec3<float> angle(0,0,0);  
		starsystem->AddVehicle(player->GetNpc()->GetVehicle(), center, angle, nullptr);
	}
	else
	{
		starsystem->GetRandomPlanet()->GetLand()->AddVehicle(player->GetNpc()->GetVehicle());
	}

	God::Instance().CreateShips(starsystem, /*ships_num=*/50, TYPE::RACE::R0_ID);
}

