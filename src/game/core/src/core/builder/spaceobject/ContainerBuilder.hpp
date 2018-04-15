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

//namespace item {
//class Base;
//} // namespace item

namespace core {

namespace control {
class Container;
} // namespace control

class ContainerBuilder
{
public:
    static core::control::Container* gen();
//    static model::Container* gen(const std::string& data);
    static core::control::Container* gen(descriptor::Container*);
    static core::control::Container* gen(int_t, int_t);
    static core::control::Container* gen(int_t, int_t, int_t);
    //        Container* create(jeti::control::TextureOb*, BaseItem*) const;
    //        Container* create(Base*) const;
    //        Container* create(int mineral_ammount = 0) const;

private:
    ContainerBuilder() = default;
    ~ContainerBuilder() = default;

    static core::control::Container* __genTemplate(descriptor::Container*, int_t obId = NONE);
    static void __createInternals(core::control::Container*, descriptor::Container*);
    //        void createInternals(Container*, jeti::control::TextureOb*, BaseItem*) const;
    //        void createInternals(Container*, BaseItem*) const;
}; 

} // namespace core
