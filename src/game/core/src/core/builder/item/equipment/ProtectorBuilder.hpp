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

#include <vector>
#include <string>

namespace descriptor {
namespace item {
class Protector;
} // namespace item
} // namespace descriptor

namespace model {
namespace item {
class Protector;
} // namespace item
} // namespace model

namespace builder {
namespace item {

class Protector : public Equipment
{
public:
    static model::item::Protector* gen();
    static std::vector<model::item::Protector*> gen(int);
    static model::item::Protector* gen(descriptor::item::Protector*);

private:
    Protector() = delete;
    ~Protector() = delete;

    static model::item::Protector* __genTemplate(int_t);
    static void __createInternals(model::item::Protector*, descriptor::item::Protector*);
}; 

} // namespace item
} // namespace builder
