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
#include "constants.hpp"
#include "GameDate.hpp"
#include "Logger.hpp"
#include "../config/config.hpp"
#include "EntityManager.hpp"

TurnTimer& TurnTimer::Instance()
{
	static TurnTimer instance;
	return instance;
}

TurnTimer::TurnTimer():
turn_tick(-1),
turn_ended(true),
turn_counter(0)
{}

TurnTimer::~TurnTimer()
{}

void TurnTimer::NextTurn() 
{
	if (Config::Instance().AUTO_SAVE_MODE == true)
	{
	        Logger::Instance().Log("*** proceeding autosave(AUTO_SAVE_MODE=ON)");
		EntityManager::Instance().SaveRequest();
	}
			
	turn_tick = TURN_TIME;
	turn_ended = false;
	
	turn_counter++;
	
	GameDate::Instance().NextDay();
	Logger::Instance().Log("*** NEXT TURN, date:"+GameDate::Instance().GetDate().GetStr());
}
						
void TurnTimer::Update()
{
        turn_tick -= Config::Instance().GAME_SPEED;        
        
       	/////////// AUTO-TURN /////////////
       	if ( (turn_tick < -50) and (Config::Instance().AUTO_TURN_MODE == true) )
       	{  
        	Logger::Instance().Log("*** AUTO_TURN_MODE proceed END TURN");
       		NextTurn();
        }     
        
        if (turn_tick < 0)
        {
        	turn_ended = true;
        }   
        else
        {
        	turn_ended = false;
        }
}

void TurnTimer::Draw() const
{}
		
	

