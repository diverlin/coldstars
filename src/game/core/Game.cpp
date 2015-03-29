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
#include <common/Logger.hpp>
#include <managers/EntitiesManager.hpp>
#include <ai/God.hpp>
#include <world/galaxy.hpp>


bool Game::run() const
{
    God::Instance().createWorld();
    
    // GAME LOOP
    while (m_isRunning)
    {                   
        TurnTimer& turnTimer = global::get().turnTimer();
        GameDate& gameDate   = global::get().gameDate();

        turnTimer.Update();
        God::Instance().Update(gameDate);
        God::Instance().galaxy()->Update(turnTimer.GetTurnTick());

        if ((turnTimer.GetTurnEnded() == true) /*&& (UserInputManagerInSpace::Instance().GetNextTurnReady())*/) {
            turnTimer.NextTurn();
            gameDate++;
            Logger::Instance().Log("*** NEXT TURN, date:"+gameDate.str());
        }
        
        if (turnTimer.GetTurnEnded() == true) {
            global::get().entitiesManager().ClearGarbage();

//            bool save_event = global::get().entitiesManager().UpdateSaveRequest();
//            bool load_event = global::get().entitiesManager().UpdateLoadRequest();
//            if (load_event == true) {
//                player = global::get().entitiesManager().GetPlayer();
//                galaxy = player->GetNpc()->GetVehicle()->starsystem()->GetSector()->GetGalaxy();
//            }
//            if (save_event == true) {
//                //..
//            }
        }
    }

    return EXIT_SUCCESS;
}
