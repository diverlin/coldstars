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

#include <core/descriptor/Base.hpp>

#include <ceti/StringUtils.hpp>
#include <ceti/type/IdType.hpp>

#include <vector>

namespace descriptor {

struct SectorDescr : public BaseDescr
{
public:
    std::vector<int_t> starsystems;

    SectorDescr();
    ~SectorDescr() = default;

    ceti::InfoTable info() const override final {
        ceti::InfoTable result = BaseDescr::info();
        result.add("descriptor::Sector");
        result.add("starsystems", ceti::to_string(starsystems));
        return result;
    }
}; 

} // namespace descriptor





