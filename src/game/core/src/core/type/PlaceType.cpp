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


#include "PlaceType.hpp"
#include <ceti/StringUtils.hpp>

#include <cassert>

namespace place {

std::string to_string(place::Type place)
{
    switch(place) {
        case place::Type::NONE: { return "place::Type::NONE"; }        
        case place::Type::SPACE: { return "place::Type::SPACE"; }
        case place::Type::HYPERSPACE: { return "place::Type::HYPERSPACE"; }
        case place::Type::KOSMOPORT: { return "place::Type::KOSMOPORT"; }
        case place::Type::NATURELAND: { return "place::Type::NATURELAND"; }
        case place::Type::SHIP: { return "place::Type::SHIP"; }
    }
    assert(false);
} 

std::string strip(const std::string& str) {
    return ceti::replace(str, "place::Type::", "");
}

} // namespace place
