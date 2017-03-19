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


#include "StatusType.hpp"


std::string getTargetStatusStr(STATUS status)
{
    switch(status)
    {
        case STATUS::TARGET_DEAD:               { return "STATUS::TARGET_DEAD"; break; }
        case STATUS::TARGET_NOTIN_SPACE:        { return "STATUS::TARGET_NOTIN_SPACE"; break; }
        case STATUS::TARGET_NOTIN_STARSYSTEM:   { return "STATUS::TARGET_NOTIN_STARSYSTEM"; break; }
        case STATUS::TARGET_OUTOF_RANGE:        { return "STATUS::TARGET_OUTOF_RANGE"; break; }
        case STATUS::TARGET_OK:                 { return "STATUS::TARGET_OK"; break; }
           
        case STATUS::ITEMSLOT_EMPTY:            { return "STATUS::ITEMSLOT_EMPTY"; break; }

        case STATUS::ITEM_DAMAGED:              { return "STATUS::ITEM_DAMAGED"; break; }   
        case STATUS::ITEM_LOCKED:               { return "STATUS::ITEM_LOCKED"; break; }           
        case STATUS::ITEM_OK:                   { return "STATUS::ITEM_OK"; break; }   

        case STATUS::OK:                        { return "STATUS::OK"; break; }  
                                     
        default: { return "STATUS::UNKNOWN"; break; }
    }
}
