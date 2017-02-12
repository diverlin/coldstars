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
class Scaner;
} // namespace item
} // namespace descriptor

namespace model {
namespace item {
class Scaner;
} // namespace item
} // namespace model

namespace builder {
namespace item {

class Scaner : public Equipment
{
public:
    Scaner() = default;
    ~Scaner() = default;

    static model::item::Scaner* getNew();
    static model::item::Scaner* getNew(const std::string&);
    static model::item::Scaner* getNew(const descriptor::item::Scaner&);

private:
    static model::item::Scaner* __createTemplate(int_t);
    static void __createInternals(model::item::Scaner*, const descriptor::item::Scaner&);
}; 

} // namespace item
} // namespace builder
