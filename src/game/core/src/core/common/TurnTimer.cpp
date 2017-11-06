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
//       manager::EntityManager::get().SaveRequest();
//    }

//    if (core::global::get().config().GetAutoLoadMode() == true) {
//        LOG("*** AUTO (LoadRequest)");
//       manager::EntityManager::get().LoadRequest();
//    }
                
    m_ticksLeft = TURN_TICKS;
    m_turnEnded = false;
    m_turnCount++;
}
                        
void TurnTimer::update(int threshold)
{
    //std::cout<<"tick tack"<<m_stopTurnTimer<<std::endl;
    m_ticksLeft--;
    //std::cout<<"tick="<<m_ticksLeft<<std::endl;

    /////////// AUTO-TURN /////////////
    if (m_ticksLeft < threshold) {
        LOG("*** AUTO_TURN_MODE proceed END TURN");
        //nextTurn();
    }
        
    if (m_ticksLeft < 0) {
        m_turnEnded = true;
    }
}




