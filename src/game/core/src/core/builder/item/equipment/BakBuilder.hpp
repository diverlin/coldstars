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
namespace item {
class Bak;
} // namespace item
} // namespace descriptor

namespace control {
namespace item {
class Bak;
} // namespace item
} // namespace control

namespace builder {
namespace item {

class Bak : public Equipment
{
public:
    static control::item::Bak* gen(descriptor::item::Bak*);
    static control::item::Bak* gen(int_t, int_t ob_id = NONE);
    static control::item::Bak* gen();

private:
    Bak() = delete;
    ~Bak() = delete;

    static control::item::Bak* __genTemplate(descriptor::item::Bak*, int_t ob_id = NONE);
    static void __createInternals(control::item::Bak*, descriptor::item::Bak*);
}; 

} // namespace item
} // namespace builder




