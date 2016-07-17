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

#include <builder/world/GalaxyBuilder.hpp>
#include <builder/spaceobjects/ContainerBuilder.hpp>

#include <pilots/Npc.hpp>
#include <pilots/Player.hpp>

#include <spaceobjects/Vehicle.hpp>

#include <ai/God.hpp>
#include <world/galaxy.hpp>
#include <world/Sector.hpp>
#include <world/starsystem.hpp>
#include <common/Global.hpp>

#include <descriptors/GalaxyDescriptor.hpp>
#include <jeti/particlesystem/ExplosionEffect.hpp>

#include <iostream>

    //std::cout<<0<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(0)<<std::endl;
    //std::cout<<5<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(5)<<std::endl;
    //std::cout<<10<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(10)<<std::endl;
    //std::cout<<150<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(150)<<std::endl;
    //std::cout<<250<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(250)<<std::endl;
    //std::cout<<350<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(350)<<std::endl;
    //std::cout<<500<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(500)<<std::endl;
    //std::cout<<1000<<" "<<CONVERTER::RADIUS2FORCE.GetEquivalent(1000)<<std::endl;
    
#include "TestParticlesRunScenario.hpp"

/* virtual */
void TestParticlesRunScenario::Init(Player* player)
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
//            starsystem_description.planet_num = 0;
//            starsystem_description.spacestation_num = 0;
//            starsystem_description.allow_satellites = false;
//            starsystem_description.allow_spacestations = false;
//            starsystem_description.allow_ships   = false;
                        
//            starsystem_description.allow_ship_ranger   = false;
//            starsystem_description.allow_ship_warrior  = false;
//            starsystem_description.allow_ship_trader   = false;
//            starsystem_description.allow_ship_pirat    = false;
//            starsystem_description.allow_ship_diplomat = false;
//            sector_description.starsystem_descriptions.push_back(starsystem_description);
//        }
        
//        galaxy_description.sector_descriptions.push_back(sector_description);
//    }
    
//    Galaxy* galaxy = GalaxyBuilder::Instance().GetNewGalaxy(galaxy_description);
//    God::Instance().SetGalaxy(galaxy);
        
//    glm::vec3 center(500, 500, DEFAULT_ENTITY_ZPOS);
//    glm::vec3 angle(0,0,0);
     
//    galaxy->GetRandomSector()->GetRandomStarSystem()->AddVehicle(player->GetNpc()->vehicle(), center, angle, nullptr);
        
//    Starsystem* starsystem = player->GetNpc()->vehicle()->starsystem(); // shortcut
//    for (int i=0; i<200; i++)
//    {
//        Container* container = ContainerBuilder::Instance().GetNewMineralContainer(4);

//        glm::vec3 center(10*i, 200+20, 0);
//        starsystem->AddContainer(container, center);
//    }

//    for (int i=0; i<200; i++)
//    {
//        Container* container = ContainerBuilder::Instance().GetNewMineralContainer(4);

//        glm::vec3 center(10*i, 200-20, 0);
//        starsystem->AddContainer(container, center);
//    }
}

/* virtual */
void TestParticlesRunScenario::Update_inDynamic(Player* player)
{
//    Starsystem* starsystem = player->GetNpc()->vehicle()->starsystem(); // shortcut
            
//    if (starsystem->IsAnyActiveParticlesEffectPresent(EFFECT::EXPLOSION_ID) == false)
//    {
//        float offset = 0;
//        for (int i=0; i<10; i++)
//        {
//            float radius = 20*i;
            
////            glm::vec3 center(offset, 200, 0);
////            jeti::ExplosionEffect* explosion = jeti::getNewExplosionEffect(radius);
////            starsystem->Add(explosion, center);
            
//            offset += 2.5*radius;
//        }

//    }
}

