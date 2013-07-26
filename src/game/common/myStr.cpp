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
#include <sstream>
#include "Base.hpp"

std::string int2str(long long int val) 
{
	if (val >= 0)
	{
    		std::ostringstream stm;
    		stm<<val;
    		return stm.str();
	}    	
    	else
    	{
    		std::ostringstream stm;
    		stm<<abs(val);
    		return "-"+stm.str();
    	}
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

std::string getAiModelStr(int id)
{
	switch(id)
	{
		case AIMODEL::CONQUEROR_ID: 	{ return "CONQUEROR_ID"; break; }
		case AIMODEL::RANGER_ID:	{ return "RANGER_ID"; break; }
		case AIMODEL::TRADER_ID:	{ return "TRADER_ID"; break; }
		
		default:			{ return "UKNOWN ID"; break; }		
	}
}

std::string getNavigatorActionStr(int type_id)
{
	switch(type_id)
	{
		case NAVIGATOR_ACTION::NONE_ID: 	{ return "NONE_ID"; break; }
		case NAVIGATOR_ACTION::DOCKING_ID:	{ return "DOCKING_ID"; break; }
		case NAVIGATOR_ACTION::COLLECTING_ID:	{ return "COLLECTING_ID"; break; }
		case NAVIGATOR_ACTION::KEEP_FIRE_DISTANCE_ID:	{ return "KEEP_FIRE_DISTANCE_ID"; break; }
		case NAVIGATOR_ACTION::KEEP_CLOSE_ID:	{ return "KEEP_CLOSE_ID"; break; }
		case NAVIGATOR_ACTION::KEEP_MIDDLE_ID:	{ return "KEEP_MIDDLE_ID"; break; }
		case NAVIGATOR_ACTION::KEEP_FAR_ID: 	{ return "KEEP_FAR_ID"; break; }
		
		default: { return "UNKNOWN ID"; }
	}
}






std::string getPlaceTypeStr(PLACE::TYPE type_id)
{
	switch(type_id)
	{
	    switch(type_id)
	    {
		    case PLACE::TYPE::SPACE_ID: 		{ return "SPACE_ID"; break; }
		    case PLACE::TYPE::HYPER_SPACE_ID: 	{ return "HYPER_SPACE_ID"; break; }
            case PLACE::TYPE::KOSMOPORT_ID: 	{ return "KOSMOPORT_ID"; break; }
		    case PLACE::TYPE::NATURELAND_ID: 	{ return "NATURELAND_ID"; break; }
							
		    default: { return "UNKNOWN ID"; }
	    }
    }
}
