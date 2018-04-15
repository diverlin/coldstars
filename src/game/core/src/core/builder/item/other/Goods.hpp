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

#include <core/builder/item/ItemBuilder.hpp>

#include <ceti/type/IdType.hpp>

#include <string>

namespace core {
class GoodsDescr;
} // namespace descriptor

namespace core {
namespace control {
class Goods;
} // namespace control
}

namespace core {

class GoodsBuilder : public ItemBuilder
{
public:
    static core::control::Goods* gen(core::GoodsDescr*);
    static core::control::Goods* gen(int_t, int_t object_id = NONE);
    static core::control::Goods* gen();

private:
    GoodsBuilder() = delete;
    ~GoodsBuilder() = delete;

    static core::control::Goods* __genTemplate(core::GoodsDescr*, int_t object_id = NONE);
    static void __createInternals(core::control::Goods*, core::GoodsDescr*);
}; 

} // namespace core




