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

#include <ceti/type/IdType.hpp>

#include <string>

namespace descriptor {
class BaseOLD;
} // namespace descriptor

namespace model {
namespace item {
class Bak;
} // namespace item
} // namespace model

namespace builder {
namespace item {

class Bak
{
public:
    Bak() = default;
    ~Bak() = default;

    static model::item::Bak* getNew();
    static model::item::Bak* getNew(const descriptor::BaseOLD&);
    static model::item::Bak* getNew(const std::string&);

private:
    static model::item::Bak* __createTemplate();
    static void __createInternals(model::item::Bak*, const descriptor::BaseOLD&);
}; 

} // namespace item
} // namespace builder




