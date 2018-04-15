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

#include "Room.hpp"

namespace core {

class ShopModel : public RoomModel
{
public:
    ShopModel(int_t);
    ~ShopModel() = default;
    ShopModel(const std::string& data);
    std::string data() const;

    int mineralsAmount() const { return m_mineralsAmount; }
    int foodAmount() const { return m_foodAmount; }
    int medicineAmount() const { return m_medicineAmount; }
    int militaryAmount() const { return m_militaryAmount; }
    int drugAmount() const { return m_drugAmount; }
    int exclusiveAmount() const { return m_exclusiveAmount; }

    int mineralsPrice() const { return m_mineralsPrice; }
    int foodPrice() const { return m_foodPrice; }
    int medicinePrice() const { return m_medicinePrice; }
    int militaryPrice() const { return m_militaryPrice; }
    int drugPrice() const { return m_drugPrice; }
    int exclusivePrice() const { return m_exclusivePrice; }

    int amount(entity::Type) const;
    int price(entity::Type) const;

private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version) {
        ar & boost::serialization::base_object<RoomModel>(*this);
        ar & m_mineralsAmount;
        ar & m_foodAmount;
        ar & m_medicineAmount;
        ar & m_militaryAmount;
        ar & m_drugAmount;
        ar & m_exclusiveAmount;

        ar & m_mineralsPrice;
        ar & m_foodPrice;
        ar & m_medicinePrice;
        ar & m_militaryPrice;
        ar & m_drugPrice;
        ar & m_exclusivePrice;
    }

private:
    int m_mineralsAmount = 0;
    int m_foodAmount = 0;
    int m_medicineAmount = 0;
    int m_militaryAmount = 0;
    int m_drugAmount = 0;
    int m_exclusiveAmount = 0;

    int m_mineralsPrice = 0;
    int m_foodPrice = 0;
    int m_medicinePrice = 0;
    int m_militaryPrice = 0;
    int m_drugPrice = 0;
    int m_exclusivePrice = 0;
};

} // namespace core
