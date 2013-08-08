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


#ifndef STATUSTYPES_HPP
#define STATUSTYPES_HPP

#include <string>


enum class STATUS 
{ 
    TARGET_DEAD, TARGET_NOTIN_SPACE, TARGET_NOTIN_STARSYSTEM, TARGET_OUTOF_RANGE, TARGET_OK,
    ITEMSLOT_EMPTY,
    ITEM_DAMAGED, ITEM_LOCKED, ITEM_OK,
    
    OK
};

std::string getTargetStatusStr(STATUS);


#endif
