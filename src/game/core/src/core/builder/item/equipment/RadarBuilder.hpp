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
class Radar;
} // namespace item
} // namespace descriptor

namespace control {
namespace item {
class Radar;
} // namespace item
} // namespace control

namespace builder {
namespace item {

class Radar : public Equipment
{
public:
    static control::item::Radar* gen();
    static control::item::Radar* gen(int_t, int_t ob_id = NONE);
    static control::item::Radar* gen(descriptor::item::Radar*);

private:
    Radar() = delete;
    ~Radar() = delete;

    static control::item::Radar* __genTemplate(descriptor::item::Radar*, int_t ob_id = NONE);
    static void __createInternals(control::item::Radar*, descriptor::item::Radar*);
}; 

} // namespace item
} // namespace builder
