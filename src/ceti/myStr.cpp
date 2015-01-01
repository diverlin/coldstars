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

#include <sstream>

namespace ceti {

std::string int2str(long long int val) 
{
    if (val >= 0) {
        std::ostringstream stm;
        stm<<val;
        return stm.str();
    } else {
        std::ostringstream stm;
        stm<<abs(val);
        return "-"+stm.str();
    }
}

std::string bool2str(bool var) 
{
    std::ostringstream stm;
    if (var == true) {
        stm << "true";
    } else {
        stm << "false";
    }
    return stm.str() ;
}

} // namespace ceti
