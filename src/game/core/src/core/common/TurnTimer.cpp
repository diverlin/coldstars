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
{}

TurnTimer::~TurnTimer()
{}

void TurnTimer::nextTurn()
{
//    if (core::global::get().config().GetAutoSaveMode() == true) {
//        LOG("*** AUTO (SaveRequest)");
//       EntityManager::get().SaveRequest();
//    }

//    if (core::global::get().config().GetAutoLoadMode() == true) {
//        LOG("*** AUTO (LoadRequest)");
//       EntityManager::get().LoadRequest();
//    }
                
    m_stopTurnTimer = TURN_TIME;
    m_turnEnded = false;
    m_turnCounter++;
}
                        
void TurnTimer::update(int threshold)
{
    m_stopTurnTimer--;

    /////////// AUTO-TURN /////////////
    if (m_stopTurnTimer < threshold) {
        LOG("*** AUTO_TURN_MODE proceed END TURN");
        nextTurn();
    }
        
    if (m_stopTurnTimer < 0) {
        m_turnEnded = true;
    } else {
        m_turnEnded = false;
    }
}




