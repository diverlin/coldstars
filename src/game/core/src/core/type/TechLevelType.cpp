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


#include "TechLevelType.hpp"

#include <cassert>

namespace tech {

std::string to_string(tech::Type techlevel_id)
{
    switch(techlevel_id)
    {
    case tech::Type::NONE: { return "NONE"; }
        
    case tech::Type::LEVEL0: { return "TECH0"; }
    case tech::Type::LEVEL1: { return "TECH1"; }
    case tech::Type::LEVEL2: { return "TECH2"; }
    case tech::Type::LEVEL3: { return "TECH3"; }
        //case tech::Type::L4: { return "TECH4"; }
        //case tech::Type::L5: { return "TECH5"; }
        //case tech::Type::L6: { return "TECH6"; }
        //case tech::Type::L7: { return "TECH7"; }
        //case tech::Type::L8: { return "TECH8"; }
        //case tech::Type::L9: { return "TECH9"; }
    }
    
    assert(false);
    return "TECH_UKNOWN";
}

} // namespace tech
