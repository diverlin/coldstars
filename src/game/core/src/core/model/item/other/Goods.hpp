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

namespace model {
namespace item {

class Goods : public Item
{
public:
    Goods(int_t, int_t);
    ~Goods() = default;
    Goods(const std::string& data);
    std::string data() const;

    void setAmmount(int ammount) { m_ammount = ammount; assert(ammount>=0); }

    int ammount() const { return m_ammount; }

private:
    int m_ammount = 0;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<Item>(*this);
        ar & m_ammount;
    }
};

} // namespace item
} // namespace model

