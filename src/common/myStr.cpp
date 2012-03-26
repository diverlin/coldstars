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




std :: string returnRaceStringByRaceId(int id)  // replace by generator class
{
     	if (id == RACE::R0_ID)
        	return "RACE0";
     	if (id == RACE::R1_ID)
        	return "RACE1";
     	if (id == RACE::R2_ID)
        	return "RACE2";
     	if (id == RACE::R3_ID)
        	return "RACE3";
     	if (id == RACE::R4_ID)
        	return "RACE4";
     	if (id == RACE::R6_ID)
        	return "RACE6";
     	if (id == RACE::R7_ID)
        	return "RACE7";        
     	else
        	return "____";   
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




