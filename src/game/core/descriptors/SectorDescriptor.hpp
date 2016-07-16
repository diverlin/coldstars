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

#include "Base.hpp"
#include <types/IdType.hpp>

#include <vector>

namespace descriptor {

struct Sector : public BBase
{
public:
    std::vector<id_type> starsystems;

    Sector() {}
    ~Sector() {}

    std::string info() const override final {
        std::string result = "Sector descriptor: " + BBase::info() + _str(" starsystems:", starsystems);
        return result;
    }
}; 

} // namespace descriptor





