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


#include <client/run_scenario/NormalRunScenario.hpp>

#include <iostream>

#include <builder/world/GalaxyBuilder.hpp>

#include <core/pilot/Npc.hpp>
#include <client/pilot/Player.hpp>

#include <ai/God.hpp>
#include <core/world/galaxy.hpp>
#include <core/world/Sector.hpp>
#include <core/world/starsystem.hpp>
#include <common/Global.hpp>

#include <core/spaceobject/Planet.hpp>
#include <core/dock/Land.hpp>

#include <core/descriptor/world/GalaxyDescriptor.hpp>


/* virtual */
void NormalRunScenario::Init(client::Player* player)
{
//    GalaxyDescription galaxy_description;
//    galaxy_description.allow_invasion = false;
//    galaxy_description.sector_num = 1;
    
//    for (int i=0; i<galaxy_description.sector_num; i++)
//    {
//        SectorDescription sector_description;
//        sector_description.starsystem_num = 1;
        
//        for (int j=0; j<sector_description.starsystem_num; j++)
//        {
//            StarSystemDescription starsystem_description;
//            starsystem_description.planet_num = 5;
//            starsystem_description.spacestation_num = 3;
//            starsystem_description.asteroid_num = 3;
                       
//            starsystem_description.allow_ships         = false;
                        
//            starsystem_description.allow_ship_ranger   = false;
//            starsystem_description.allow_ship_warrior  = false;
//            starsystem_description.allow_ship_trader   = true;
//            starsystem_description.allow_ship_pirat    = false;
//            starsystem_description.allow_ship_diplomat = false;
//            sector_description.starsystem_descriptions.push_back(starsystem_description);
//        }
        
//        galaxy_description.sector_descriptions.push_back(sector_description);
//    }
    
//    Galaxy* galaxy = GalaxyBuilder::Instance().GetNewGalaxy(galaxy_description);
//    God::Instance().SetGalaxy(galaxy);
//    God::Instance().CreateLife(galaxy_description);
//    if (galaxy_description.allow_invasion == true)
//    {
//        God::Instance().CreateInvasion(galaxy_description);
//    }
    
//    bool player2space = true;
//    Starsystem* const starsystem = galaxy->GetRandomSector()->GetRandomStarSystem();
//    if (player2space == true)
//    {
//        glm::vec3 center(500, 500, DEFAULT_ENTITY_ZPOS);
//        glm::vec3 angle(0,0,0);
//        starsystem->AddVehicle(player->GetNpc()->vehicle(), center, angle, nullptr);
//    }
//    else
//    {
//        starsystem->GetRandomPlanet()->GetLand()->AddVehicle(player->GetNpc()->vehicle());
//    }

//    God::Instance().CreateShips(starsystem, /*ships_num=*/20, race::Type::R0);   // fake
}

