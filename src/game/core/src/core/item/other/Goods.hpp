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

#include <core/item/Item.hpp>

namespace descriptor {
namespace item {
class Goods;
} // namespace item
} // namespace descriptor

namespace model {
namespace item {
class Goods;
} // namespace item
} // namespace model

namespace control {
namespace item {

class Goods : public Item
{
public:
    Goods(descriptor::item::Goods*, model::item::Goods*);
    virtual ~Goods();

    void increase(int amount);
    void decrease(int amount);

    virtual void updateOwnerAbilities() {}

private:
    descriptor::item::Goods* m_descriptor_goods = nullptr;
    model::item::Goods* m_model_goods = nullptr;
};

} // namespace item
} // namespace control

//control::GoodsPack* GetNewGoodsPack(entity::Type, int_t id = NONE);

