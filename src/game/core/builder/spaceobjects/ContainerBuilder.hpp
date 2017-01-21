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

#include <string>

namespace descriptor {
//class Container;
class BaseOLD;
} // namespace descriptor

namespace item {
class Base;
} // namespace item

namespace model {
class Container;
}

namespace builder {

class Container
{
public:
    Container();
    ~Container();

    static model::Container* create();
    static model::Container* create(const std::string& data);
    static model::Container* create(const descriptor::BaseOLD&);
    //        Container* create(jeti::control::TextureOb*, BaseItem*) const;
    //        Container* create(item::BaseItem*) const;
    //        Container* create(int mineral_ammount = 0) const;

private:
    static model::Container* __getNewTemplate();
    static void __createInternals(model::Container*, const descriptor::BaseOLD&);
    //        void createInternals(Container*, jeti::control::TextureOb*, BaseItem*) const;
    //        void createInternals(Container*, BaseItem*) const;
}; 

} // namespace builder
