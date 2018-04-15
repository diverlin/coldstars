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
class Scaner;
} // namespace descriptor

namespace core {
namespace control {
class Scaner;
} // namespace control
}

namespace core {

class ScanerItemBuilder : public EquipmentBuilder
{
public:
    static core::control::item::Scaner* gen();
    static core::control::item::Scaner* gen(int_t, int_t ob_id = NONE);
    static core::control::item::Scaner* gen(descriptor::item::Scaner*);

private:
    ScanerItemBuilder() = delete;
    ~ScanerItemBuilder() = delete;

    static core::control::item::Scaner* __genTemplate(descriptor::item::Scaner*, int_t ob_id = NONE);
    static void __createInternals(core::control::item::Scaner*, descriptor::item::Scaner*);
}; 

} // namespace builder
