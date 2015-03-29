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


#ifndef RACETYPES_HPP
#define RACETYPES_HPP

#include <string>


namespace TYPE
{
    enum class RACE 
    {
        NONE_ID=0, R0_ID, R1_ID, R2_ID, R3_ID, R4_ID, R6_ID, R7_ID, LAST_ID
    };
}

std::string getRaceStr(TYPE::RACE); 

#endif
