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

#include <core/model/item/Item.hpp>

#include <ceti/type/IdType.hpp>

#include <string>
#include <cassert>

namespace core {

class GoodsPackModel : public ItemModel
{
public:
    GoodsPackModel(int_t, int_t);
    ~GoodsPackModel() = default;
    GoodsPackModel(const std::string& data);
    std::string data() const;

    void setAmount(int amount) { m_amount = amount; assert(amount>=0); }

    int amount() const { return m_amount; }

private:
    int m_amount = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<ItemModel>(*this);
        ar & m_amount;
    }
};

} // namespace core

