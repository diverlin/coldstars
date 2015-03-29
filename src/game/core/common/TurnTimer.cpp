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

#include "TurnTimer.hpp"
#include "Logger.hpp"

TurnTimer::TurnTimer()
    :
      turn_tick(2)
    , turn_counter(0)
{}

TurnTimer::~TurnTimer()
{}

void TurnTimer::NextTurn() 
{
//    if (global::get().config().GetAutoSaveMode() == true) {
//        Logger::Instance().Log("*** AUTO (SaveRequest)");
//        global::get().entitiesManager().SaveRequest();
//    }

//    if (global::get().config().GetAutoLoadMode() == true) {
//        Logger::Instance().Log("*** AUTO (LoadRequest)");
//        global::get().entitiesManager().LoadRequest();
//    }
                
    turn_tick = TURN_TIME;
    turn_ended = false;
    
    turn_counter++;
}
                        
void TurnTimer::Update(bool auto_turn)
{        
    turn_tick--;

    /////////// AUTO-TURN /////////////
    if ( (turn_tick < -50) && (auto_turn == true) ) {
        Logger::Instance().Log("*** AUTO_TURN_MODE proceed END TURN");
        NextTurn();
    }
        
    if (turn_tick < 0) {
        turn_ended = true;
    } else {
        turn_ended = false;
    }
}




