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

#include "gameStruct.hpp"

	
VisionStatus :: VisionStatus()
{
   	ASTEROID  = false;
	CONTAINER = false;
   	MINERAL   = false;

   	RANGER   = false;
   	WARRIOR  = false;
   	TRADER   = false;  
   	PIRAT    = false;
   	DIPLOMAT = false;
}



NeedsToDo :: NeedsToDo()
{
  	REPAIR_KORPUS    = false;
  	REPAIR_EQUIPMENT = false;
        
  	GET_FUEL    = false;
   	GET_BULLETS = false;
        GET_CREDITS = false;
        
   	BUY         = false;
   	SELL        = false;
}


AbilitiesStatus :: AbilitiesStatus()
{
        RADAR    = false;
   	DRIVE    = false;
   	HJUMP    = false;
   	ENERGIZE = false;
   	PROTECT  = false;
   	REPAIR   = false;
   	FREEZE   = false;
   	GRAB     = false;
   	SCAN     = false;
   	//FIRE     = false;
}





IdData :: IdData()
{
	id            = NONE_ID;
	type_id       = NONE_ID;
	subtype_id    = NONE_ID;
	subsubtype_id = NONE_ID;
}


ParticleData :: ParticleData()
{	
      	size_start = 0.0;
      	size_end   = 0.0;
        d_size     = 0.0;

      	velocity_start = 0.0;
      	velocity_end   = 0.0;
	d_velocity     = 0.0;
        
        frame = 0;
}
	



AngleData :: AngleData()
{}
