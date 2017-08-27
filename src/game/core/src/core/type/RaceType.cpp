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


#include "RaceType.hpp"

#include <cassert>

namespace race {

std::string to_string(race::Type race_id)
{
    switch(race_id)
    {
        case Type::NONE: { return "RACE_NONE"; }
        
        case Type::R0: { return "RACE0"; }
        case Type::R1:    { return "RACE1"; }
        case Type::R2:    { return "RACE2"; }
        case Type::R3:    { return "RACE3"; }
        case Type::R4:    { return "RACE4"; }

        case Type::R6:    { return "RACE6"; }
        case Type::R7:    { return "RACE7"; }

        default: {
        assert(false);
        return "RACE_UKNOWN";
    }
    }
}

} // namespace race
