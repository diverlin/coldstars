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


#include "PlaceTypes.hpp"


std::string getPlaceStr(type::place place_id) 
{
    switch(place_id)
    {
        case type::place::NONE:             { return "PLACE_NONE"; break; }
        
        case type::place::KOSMOS:         { return "SPACE_ID"; break; }
        case type::place::HYPER:    { return "HYPER_SPACE_ID"; break; }
        case type::place::KOSMOPORT:        { return "KOSMOPORT_ID"; break; }
        case type::place::LAND:    { return "NATURELAND_ID"; break; }

        default: { return "PLACE_UKNOWN"; break; }    
    }
} 

