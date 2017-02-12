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


std::string to_string(tech::type techlevel_id) 
{
    switch(techlevel_id)
    {
        case tech::type::NONE: { return "NONE"; break; }
        
        case tech::type::LEVEL0: { return "TECH0"; break; }
        case tech::type::LEVEL1: { return "TECH1"; break; }
        case tech::type::LEVEL2: { return "TECH2"; break; }
        case tech::type::LEVEL3: { return "TECH3"; break; }
        //case tech::type::L4: { return "TECH4"; break; }
        //case tech::type::L5: { return "TECH5"; break; }
        //case tech::type::L6: { return "TECH6"; break; }
        //case tech::type::L7: { return "TECH7"; break; }
        //case tech::type::L8: { return "TECH8"; break; }
        //case tech::type::L9: { return "TECH9"; break; }
    }
    
    return "TECH_UKNOWN";
}

