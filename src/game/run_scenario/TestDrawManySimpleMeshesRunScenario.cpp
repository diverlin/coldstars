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

#include "../builder/world/GalaxyBuilder.hpp"
#include "../builder/spaceobjects/ContainerBuilder.hpp"

#include "../pilots/Npc.hpp"
#include "../pilots/Player.hpp"

#include "../spaceobjects/Vehicle.hpp"

#include "../world/God.hpp"
#include "../world/galaxy.hpp"
#include "../world/Sector.hpp"
#include "../world/starsystem.hpp"
#include "../world/EntityManager.hpp"

#include "../garbage/EntityGarbage.hpp"

#include "../struct/GalaxyDescription.hpp"
#include <render/particlesystem/ExplosionEffect.hpp>

#include <iostream>
    
#include "TestDrawManySimpleMeshesRunScenario.hpp"

#include <math/rand.hpp>

/* virtual */
void TestDrawManySimpleMeshesRunScenario::Init(Player* player)
{
    GalaxyDescription galaxy_description;
    galaxy_description.allow_invasion = false;
    galaxy_description.sector_num = 1;
    
    for (int i=0; i<galaxy_description.sector_num; i++)
    {
        SectorDescription sector_description;
        sector_description.starsystem_num = 1;
        
        for (int j=0; j<sector_description.starsystem_num; j++)        
        {
            StarSystemDescription starsystem_description;
            starsystem_description.planet_num = 0;                    
            starsystem_description.spacestation_num = 0;
            starsystem_description.allow_satellites = false;
            starsystem_description.allow_spacestations = false;
            starsystem_description.allow_ships   = false;
                        
            starsystem_description.allow_ship_ranger   = false;
            starsystem_description.allow_ship_warrior  = false;
            starsystem_description.allow_ship_trader   = false;
            starsystem_description.allow_ship_pirat    = false;
            starsystem_description.allow_ship_diplomat = false;
            sector_description.starsystem_descriptions.push_back(starsystem_description);
        }    
        
        galaxy_description.sector_descriptions.push_back(sector_description);            
    }
    
    Galaxy* galaxy = GalaxyBuilder::Instance().GetNewGalaxy(galaxy_description);
    God::Instance().SetGalaxy(galaxy);
        
    glm::vec3 center(500, 500, DEFAULT_ENTITY_ZPOS);
    glm::vec3 angle(0,0,0); 
     
    galaxy->GetRandomSector()->GetRandomStarSystem()->AddVehicle(player->GetNpc()->GetVehicle(), center, angle, nullptr);
        
    StarSystem* starsystem = player->GetNpc()->GetVehicle()->GetStarSystem(); // shortcut        
    for (int i=0; i<2000; i++)
    {
        Container* container = ContainerBuilder::Instance().GetNewMineralContainer(4);

        glm::vec3 center = getRandXYVec3f(10.0f, 500.0f, DEFAULT_ENTITY_ZPOS);        
        starsystem->AddContainer(container, center);
    }
}

/* virtual */
void TestDrawManySimpleMeshesRunScenario::Update_inDynamic(Player* player)
{
   
}

