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
class Lazer;
} // namespace item
} // namespace descriptor

namespace model {
namespace item {
class Lazer;
} // namespace item
} // namespace model

namespace builder {
namespace item {

class Lazer : public Equipment
{
public:
    static model::item::Lazer* gen();
//    static model::item::Lazer* gen(const std::string&);
    static model::item::Lazer* gen(descriptor::item::Lazer*);

private:
    Lazer() = delete;
    ~Lazer() = delete;

    static model::item::Lazer* __genTemplate(int_t);
    static void __createInternals(model::item::Lazer*, descriptor::item::Lazer*);
}; 

} // namespace item
} // namespace builder

