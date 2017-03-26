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
class Container;
} // namespace descriptor

namespace control {
class Container;
} // namespace control

namespace item {
class Base;
} // namespace item

namespace builder {

class Container
{
public:
    static control::Container* gen();
//    static model::Container* gen(const std::string& data);
    static control::Container* gen(descriptor::Container*);
    //        Container* create(jeti::control::TextureOb*, BaseItem*) const;
    //        Container* create(item::Base*) const;
    //        Container* create(int mineral_ammount = 0) const;

private:
    Container() = default;
    ~Container() = default;

    static control::Container* __genTemplate(int_t);
    static void __createInternals(control::Container*, descriptor::Container*);
    //        void createInternals(Container*, jeti::control::TextureOb*, BaseItem*) const;
    //        void createInternals(Container*, BaseItem*) const;
}; 

} // namespace builder
