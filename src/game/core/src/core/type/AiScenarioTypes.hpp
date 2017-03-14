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
        NONE = 0,
        
        MACRO_WARRIORRECRUTE, 
        MACRO_STARSYSTEMDEFENCE, 
        MACRO_STARSYSTEMLIBERATION, 
        MACRO_SELFSAFETY, // replace selfsafety to survival        
        MACRO_GOODSTRADING,
        
        MICRO_DESTROY,
        MICRO_DOCKING,        
        MICRO_LAUNCHING,
        MICRO_GRAB,
        MICRO_JUMP,
        MICRO_EXPLORATION
    };    
} // namespace ai



