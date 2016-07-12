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

#include "Game.hpp"

#include <iostream>

#include "common/TurnTimer.hpp"
#include <common/Global.hpp>
#include <common/GameDate.hpp>
#include <ceti/Logger.hpp>

#include <managers/EntityManager.hpp>
#include <ai/God.hpp>
#include <world/galaxy.hpp>
#include <descriptors/GalaxyDescriptor.hpp>
#include <descriptors/DescriptorGenerator.hpp>

//    galaxy_descriptor.allow_invasion = false;
//    galaxy_descriptor.sector_num = 1;
//    for (int i=0; i<galaxy_descriptor.sector_num; i++) {
//        SectorDescriptor sector_descriptor;
//        sector_descriptor.starsystem_num = 1;
//        for (int j=0; j<sector_descriptor.starsystem_num; j++) {
            //StarSystemDescriptor starsystem_descriptor;
//            starsystem_descriptor.planet_num = 5;
//            starsystem_descriptor.spacestation_num = 0;
//            starsystem_descriptor.asteroid_num = 3;

//            starsystem_descriptor.allow_satellites    = false;
//            starsystem_descriptor.allow_ships         = false;

//            starsystem_descriptor.allow_ship_ranger   = false;
//            starsystem_descriptor.allow_ship_warrior  = false;
//            starsystem_descriptor.allow_ship_trader   = true;
//            starsystem_descriptor.allow_ship_pirat    = false;
//            starsystem_descriptor.allow_ship_diplomat = false;
            //sector_descriptor.starsystem_descriptors.push_back(starsystem_descriptor);
//        }
//        galaxy_descriptor.sector_descriptors.push_back(sector_descriptor);
//    }

bool Game::run() const
{
    /// shortcuts
    God& god             = global::get().god();
    TurnTimer& turnTimer = global::get().turnTimer();
    GameDate& gameDate   = global::get().gameDate();

    /// create the world
    Galaxy* galaxy = god.createWorld(generator::getNewGalaxyDescriptor());

    /// game loop
    while (m_isRunning) {
        turnTimer.update();
        god.update(galaxy, gameDate);
        galaxy->Update(turnTimer.getStopTurnTimer());

        if (turnTimer.getTurnEnded() == true) {
            turnTimer.nextTurn();
            gameDate.dayPass();
        }
        
        if (turnTimer.getTurnEnded() == true) {
            global::get().entityManager().clearGarbage();

//            bool save_event = global::get().entityManager().UpdateSaveRequest();
//            bool load_event = global::get().entityManager().UpdateLoadRequest();
//            if (load_event == true) {
//                player = global::get().entityManager().GetPlayer();
//                galaxy = player->GetNpc()->GetVehicle()->starsystem()->GetSector()->GetGalaxy();
//            }
//            if (save_event == true) {
//                //..
//            }
        }
    }

    return EXIT_SUCCESS;
}
