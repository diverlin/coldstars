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

#include <common/GameDate.hpp>
#include <types/IdType.hpp>

struct AgressorData
{
    IDTYPE npc_id;
    GameDate last_date;
    int counter;
    
    AgressorData(const IDTYPE& npc_id, const GameDate& last_date, int counter)
        :
          npc_id(npc_id)
        , last_date(last_date)
        , counter(counter)
    {}
   
    bool operator<(const AgressorData& rhs) 
    { 
        if (counter < rhs.counter)  { return true; }
        else                        { return false; }
    }
};

struct AgressorDataComparator
{
    bool operator() (const AgressorData& lhs, const AgressorData& rhs) const
    {
        if (lhs.counter < rhs.counter) { return true; }
        else                           { return false; }
    }
};    


