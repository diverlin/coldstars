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


#include "TechLevelTypes.hpp"


std::string getRaceStr(TYPE::TECHLEVEL techlevel_id) 
{
	switch(techlevel_id)
	{
		case TYPE::TECHLEVEL::NONE_ID: { return "TECHLEVEL_NONE"; break; }
		
		case TYPE::TECHLEVEL::L0_ID: { return "TECHLEVEL0"; break; }
		case TYPE::TECHLEVEL::L1_ID: { return "TECHLEVEL1"; break; }
		case TYPE::TECHLEVEL::L2_ID: { return "TECHLEVEL2"; break; }
		case TYPE::TECHLEVEL::L3_ID: { return "TECHLEVEL3"; break; }
		//case TYPE::TECHLEVEL::L4_ID: { return "TECHLEVEL4"; break; }	
		//case TYPE::TECHLEVEL::L5_ID: { return "TECHLEVEL5"; break; }
		//case TYPE::TECHLEVEL::L6_ID: { return "TECHLEVEL6"; break; }
		//case TYPE::TECHLEVEL::L7_ID: { return "TECHLEVEL7"; break; }	
		//case TYPE::TECHLEVEL::L8_ID: { return "TECHLEVEL8"; break; }			
		//case TYPE::TECHLEVEL::L9_ID: { return "TECHLEVEL9"; break; }	
	}
	
	return "TECHLEVEL_UKNOWN";
}

