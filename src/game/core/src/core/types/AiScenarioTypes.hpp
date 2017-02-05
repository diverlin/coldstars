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

namespace ai
{
    enum class type
    {
        NONE_ID = 0,
        
        MACRO_WARRIORRECRUTE_ID, 
        MACRO_STARSYSTEMDEFENCE_ID, 
        MACRO_STARSYSTEMLIBERATION_ID, 
        MACRO_SELFSAFETY_ID, // replace selfsafety to survival        
        MACRO_GOODSTRADING_ID,
        
        MICRO_DESTROY_ID,
        MICRO_DOCKING_ID,        
        MICRO_LAUNCHING_ID,
        MICRO_GRAB_ID,
        MICRO_JUMP_ID,
        MICRO_EXPLORATION_ID
    };    
} // namespace ai



