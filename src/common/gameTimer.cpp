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


GameTimer :: GameTimer() : year(4000), month(1), day(0), turn_tick(-1), turn_ended(true)
{}

GameTimer :: ~GameTimer()
{}
	
bool GameTimer :: getTurnEnded() const { return turn_ended; }
int GameTimer :: getTurnTick() const { return turn_tick; }


void GameTimer :: nextTurn() 
{
	turn_tick = TURN_TIME;
        day++;
        printf("        *** turn END was activated, day = %i\n", day); 
}
						
void GameTimer :: update()
{
        turn_tick -= g_GAMESPEED;
        
        
       	/////////// AUTO-TURN /////////////
       	if ( (turn_tick < -50) and (g_AUTOTURN_ENABLE == true) )
       	{  
       		turn_tick = TURN_TIME;
        	day++;
        	printf("        *** auto turn END was activated, day = %i\n", day);
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

void GameTimer :: draw() const
{}
		
	

