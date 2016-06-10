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


std::string getTechLevelStr(type::TECH techlevel_id) 
{
    switch(techlevel_id)
    {
        case type::TECH::NONE_ID: { return "TECH_NONE"; break; }
        
        case type::TECH::L0_ID: { return "TECH0"; break; }
        case type::TECH::L1_ID: { return "TECH1"; break; }
        case type::TECH::L2_ID: { return "TECH2"; break; }
        case type::TECH::L3_ID: { return "TECH3"; break; }
        //case TYPE::TECH::L4_ID: { return "TECH4"; break; }
        //case TYPE::TECH::L5_ID: { return "TECH5"; break; }
        //case TYPE::TECH::L6_ID: { return "TECH6"; break; }
        //case TYPE::TECH::L7_ID: { return "TECH7"; break; }
        //case TYPE::TECH::L8_ID: { return "TECH8"; break; }
        //case TYPE::TECH::L9_ID: { return "TECH9"; break; }
    }
    
    return "TECH_UKNOWN";
}

