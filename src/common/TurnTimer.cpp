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
#include "../config/config.hpp"

TurnTimer::TurnTimer():
turn_tick(-1),
turn_ended(true)
{}

TurnTimer::~TurnTimer()
{}

void TurnTimer::NextTurn() 
{
	turn_tick = TURN_TIME;
        //day++;
        //printf("        *** turn END was activated, day = %i\n", day); 
}
						
void TurnTimer::Update(GameDate& game_date)
{
        turn_tick -= Config::Instance().GAMESPEED;        
        
       	/////////// AUTO-TURN /////////////
       	if ( (turn_tick < -50) and (Config::Instance().AUTOTURN_MODE == true) )
       	{  
       		turn_tick = TURN_TIME;
        	game_date.NextDay();
        	printf("        *** auto turn END was activated\n");
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
		
	

