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
#include <vector>

namespace tech {

enum class Type {
    NONE=0,
    //
    LEVEL0,
    LEVEL1,
    LEVEL2,
    LEVEL3
};

std::string to_string(Type);

const std::vector<Type> TECH_TYPES = {
    Type::LEVEL0,
    Type::LEVEL1,
    Type::LEVEL2,
    Type::LEVEL3
};

} // namespace tech






