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

class GoodsPack; 

namespace core {
class ShopDescr;
} // namespace core

namespace model {
class Shop;
} // namespace model

namespace core {
namespace control {

class Npc;

class Shop : public Room
{
public:
    Shop(ShopDescr*, model::Shop*);
    ~Shop();

    int mineralsAmount()     const { return m_mineralsAmount; }
    int foodAmount()        const { return m_foodAmount; }
    int medicineAmount()     const { return m_medicineAmount; }
    int militaryAmount()        const { return m_militaryAmount; }
    int drugAmount()        const { return m_drugAmount; }
    int exclusiveAmount()     const { return m_exclusiveAmount; }

    int mineralsPrice()         const { return m_mineralsPrice; }
    int foodPrice()         const { return m_foodPrice; }
    int medicinePrice()         const { return m_medicinePrice; }
    int militaryPrice()        const { return m_militaryPrice; }
    int drugPrice()         const { return m_drugPrice; }
    int exclusivePrice()        const { return m_exclusivePrice; }

    int amount(entity::Type) const;
    int price(entity::Type) const;

    bool sellGoods(Npc*, entity::Type, int);
    int buyGoods(GoodsPack*);

//    void Save(boost::property_tree::ptree&) const;
//    void Load(const boost::property_tree::ptree&);
//    void Resolve();

private:
    ShopDescr* m_descriptor_shop = nullptr;
    model::Shop* m_model_shop = nullptr;

    ShopDescr* descriptor() const { return m_descriptor_shop; }
    model::Shop* model() const { return m_model_shop; }

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

    int __deal(int, entity::Type, int);

    void __updateAllPrices();
    void __updateMineralPrice();
    void __updateFoodPrice();
    void __updateMedicinePrice();
    void __updateMilitaryPrice();
    void __updateDrugPrice();
    void __updateExclusivePrice();

//    void SaveData(boost::property_tree::ptree&, const std::string&) const;
//    void LoadData(const boost::property_tree::ptree&);
//    void ResolveData();

};

} // namespace control
} // namespace core
