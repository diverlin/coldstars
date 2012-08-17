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

#include "constants.hpp"

std::string getAiModelString(int id)
{
	switch(id)
	{
		case AIMODEL::CONQUEROR_ID: 	{ return "CONQUEROR_ID"; break; }
		case AIMODEL::RANGER_ID:	{ return "RANGER_ID"; break; }
		case AIMODEL::TRADER_ID:	{ return "TRADER_ID"; break; }
		
		default:			{ return "___"; break; }		
	}
}

std::string getClassString(int id)
{
	switch(id)
	{
		case CLASS::RANGER_ID: 	{ return "RANGER_ID"; break; }
		case CLASS::WARRIOR_ID:	{ return "WARRIOR_ID"; break; }
		case CLASS::PIRAT_ID:		{ return "PIRAT_ID"; break; }
		case CLASS::TRADER_ID:		{ return "TRADER_ID"; break; }
		case CLASS::DIPLOMAT_ID:	{ return "DIPLOMAT_ID"; break; }
		
		default:			{ return "___"; break; }		
	}
}

std::string getRaceString(int race_id) 
{
	switch(race_id)
	{
		case RACE::R0_ID: 	{ return "RACE0"; break; }
		case RACE::R1_ID:	{ return "RACE1"; break; }
		case RACE::R2_ID:	{ return "RACE2"; break; }
		case RACE::R3_ID:	{ return "RACE3"; break; }
		case RACE::R4_ID:	{ return "RACE4"; break; }	

		case RACE::R6_ID:	{ return "RACE6"; break; }
		case RACE::R7_ID:	{ return "RACE7"; break; }	
		
		default:		{ return "___"; break; }
	}
}



std::string int2str(int var) 
{
    	std::ostringstream stm;
    	stm << var;
    	return stm.str() ;
}

std::string bool2str(bool var) 
{
    	std::ostringstream stm;
    	if (var == true)
       		stm << "true";
    	else
       		stm << "false";   
    	return stm.str() ;
}




