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

namespace descriptor {
class LazerDescr;
} // namespace descriptor

namespace core {
namespace control {
class Lazer;
} // namespace control
}

namespace core {

class LazerItemBuilder : public EquipmentBuilder
{
public:
    static core::control::Lazer* gen();
    static core::control::Lazer* gen(int_t, int_t ob_id = NONE);
    static core::control::Lazer* gen(descriptor::LazerDescr*);

private:
    LazerItemBuilder() = delete;
    ~LazerItemBuilder() = delete;

    static core::control::Lazer* __genTemplate(descriptor::LazerDescr*, int_t ob_id = NONE);
    static void __createInternals(core::control::Lazer*, descriptor::LazerDescr*);
}; 

} // namespace core

