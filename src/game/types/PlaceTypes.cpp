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


std::string getPlaceStr(TYPE::PLACE place_id) 
{
    switch(place_id)
    {
        case TYPE::PLACE::NONE_ID:             { return "PLACE_NONE"; break; }
        
        case TYPE::PLACE::SPACE_ID:         { return "SPACE_ID"; break; }
        case TYPE::PLACE::HYPER_SPACE_ID:    { return "HYPER_SPACE_ID"; break; }
        case TYPE::PLACE::KOSMOPORT_ID:        { return "KOSMOPORT_ID"; break; }
        case TYPE::PLACE::NATURELAND_ID:    { return "NATURELAND_ID"; break; }

        default: { return "PLACE_UKNOWN"; break; }    
    }
} 

