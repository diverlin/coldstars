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


#ifndef TECHLEVELTYPES_HPP
#define TECHLEVELTYPES_HPP

#include <string>
#include <vector>


namespace TYPE
{
    enum class TECHLEVEL 
    {
        NONE_ID=0, L0_ID, L1_ID, L2_ID, L3_ID/*, L4_ID, L5_ID, L6_ID, L7_ID, L8_ID, L9_ID*/
    };
}

const std::vector<TYPE::TECHLEVEL> TECHLEVEL_TYPES =
{
TYPE::TECHLEVEL::L0_ID,
TYPE::TECHLEVEL::L1_ID,
TYPE::TECHLEVEL::L2_ID,
TYPE::TECHLEVEL::L3_ID
};

std::string getTechLevelStr(TYPE::TECHLEVEL); 

#endif

