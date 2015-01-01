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

#pragma once

#include <string>
//#include <ceti/StringUtils.hpp>

struct StarSystemsConditionData
{
      public:
             StarSystemsConditionData():safe_num(0), war_num(0), captured_num(0) {};
             ~StarSystemsConditionData() {};

             int safe_num;
             int war_num;
             int captured_num;
                          
             void Reset() { safe_num = 0; war_num = 0; captured_num = 0; };
        std::string GetStr() const { return "safe_num="+std::to_string(safe_num)+" war_num="+std::to_string(war_num)+" captured_num="+std::to_string(captured_num); }
};

