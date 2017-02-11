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


#include "RaceTypes.hpp"

std::string to_string(race::type race_id)
{
    switch(race_id)
    {
        case race::type::NONE: { return "RACE_NONE"; break; }
        
        case race::type::R0_ID: { return "RACE0"; break; }
        case race::type::R1_ID:    { return "RACE1"; break; }
        case race::type::R2_ID:    { return "RACE2"; break; }
        case race::type::R3_ID:    { return "RACE3"; break; }
        case race::type::R4_ID:    { return "RACE4"; break; }

        case race::type::R6_ID:    { return "RACE6"; break; }
        case race::type::R7_ID:    { return "RACE7"; break; }

        default: { return "RACE_UKNOWN"; break; }    
    }
}

