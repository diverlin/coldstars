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

#include "EquipmentBuilder.hpp"

#include <ceti/type/IdType.hpp>

#include <string>

namespace core {
class RadarDescr;
} // namespace core

namespace core {
namespace control {
class Radar;
} // namespace control
}

namespace core {

class RadarItemBuilder : public EquipmentBuilder
{
public:
    static core::control::Radar* gen();
    static core::control::Radar* gen(int_t, int_t ob_id = NONE);
    static core::control::Radar* gen(core::RadarDescr*);

private:
    RadarItemBuilder() = delete;
    ~RadarItemBuilder() = delete;

    static core::control::Radar* __genTemplate(core::RadarDescr*, int_t ob_id = NONE);
    static void __createInternals(core::control::Radar*, core::RadarDescr*);
}; 

} // namespace core
