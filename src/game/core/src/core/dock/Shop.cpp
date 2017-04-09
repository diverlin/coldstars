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


#include "Shop.hpp"
#include "Kosmoport.hpp"
#include "../common/constants.hpp"
//#include <ceti/StringUtils.hpp>
#include <meti/RandUtils.hpp>

#include <common/Global.hpp>
#include <core/manager/EntityManager.hpp>

#include <core/spaceobject/Vehicle.hpp>
#include <core/item/other/GoodsPack.hpp>
#include <core/slot/ItemSlot.hpp>
#include <core/pilot/Npc.hpp>

#include <core/descriptor/dock/Shop.hpp>
#include <core/model/dock/Shop.hpp>

namespace control {

Shop::Shop(descriptor::Shop* descr, model::Shop* model)
    :
      Room(descr, model)
    , m_descriptor_shop(descr)
    , m_model_shop(model)
{
    m_mineralsAmount  = meti::getRandInt(MINERALS_STARTAMOUNT_MIN, MINERALS_STARTAMOUNT_MAX);
    m_foodAmount      = meti::getRandInt(FOOD_STARTAMOUNT_MIN, FOOD_STARTAMOUNT_MAX);
    m_medicineAmount  = meti::getRandInt(MEDICINE_STARTAMOUNT_MIN, MEDICINE_STARTAMOUNT_MAX);
    m_militaryAmount  = meti::getRandInt(MILITARY_STARTAMOUNT_MIN, MILITARY_STARTAMOUNT_MAX);
    m_drugAmount      = meti::getRandInt(DRUG_STARTAMOUNT_MIN, DRUG_STARTAMOUNT_MAX);
    m_exclusiveAmount = meti::getRandInt(EXCLUSIVE_STARTAMOUNT_MIN, EXCLUSIVE_STARTAMOUNT_MAX);
    
    __updateAllPrices();
}

Shop::~Shop()
{}                


int Shop::amount(entity::Type subtype_id) const
{
    switch(subtype_id)
    {
    case entity::Type::MINERALS:     { return m_mineralsAmount; break; }
    case entity::Type::FOOD:         { return m_foodAmount; break; }
    case entity::Type::MEDICINE:     { return m_medicineAmount; break; }
    case entity::Type::MILITARY:     { return m_militaryAmount; break; }
    case entity::Type::DRUG:         { return m_drugAmount; break; }
    case entity::Type::EXCLUSIVE:    { return m_exclusiveAmount; break; }
    }
    
    return 0;
}    

int Shop::price(entity::Type subtype_id) const
{
    switch(subtype_id)
    {
    case entity::Type::MINERALS:     { return m_mineralsPrice; break; }
    case entity::Type::FOOD:         { return m_foodPrice; break; }
    case entity::Type::MEDICINE:     { return m_medicinePrice; break; }
    case entity::Type::MILITARY:     { return m_militaryPrice; break; }
    case entity::Type::DRUG:         { return m_drugPrice; break; }
    case entity::Type::EXCLUSIVE:    { return m_exclusivePrice; break; }
    }
    
    return 0;
}


bool Shop::sellGoods(Npc* npc, entity::Type subtype_id, int amount)
{    
    int sign = -1;
    int price = __deal(sign, subtype_id, amount);
    
    if (price > 0) {
        assert(false);
        //        if (npc->withdrawCredits(price)) {
        //            GoodsPack* goods_pack = GetNewGoodsPack(subtype_id);
        //            goods_pack->Increase(amount);
        
        //            assert(false);
        //            //npc->vehicle()->addItemToCargoSlot(goods_pack);

        //            return true;
        //        }
    }
    
    return false;
}


int
Shop::buyGoods(GoodsPack* goods_pack)
{
    assert(false);
    //    int sign = 1;
    //    int price = Deal(sign, goods_pack->subtype(), goods_pack->mass());
    //    if (price > 0)
    //    {
    //        goods_pack->slot()->removeItem();
    //       manager::EntityManager::get().addToGarbage(goods_pack);
    //    }
    
    //    return price;
}

int
Shop::__deal(int sign, entity::Type subtype_id, int amount)
{
    int money = 0;
    switch(subtype_id)
    {
    case entity::Type::MINERALS:
    {
        m_mineralsAmount += sign*amount;
        money = amount*m_mineralsPrice;

        __updateMineralPrice();

        break;
    }

    case entity::Type::FOOD:
    {
        m_foodAmount += sign*amount;
        money = amount*m_foodPrice;

        __updateFoodPrice();

        break;
    }

    case entity::Type::MEDICINE:
    {
        m_medicineAmount += sign*amount;
        money = amount*m_medicinePrice;

        __updateMedicinePrice();

        break;
    }

    case entity::Type::MILITARY:
    {
        m_militaryAmount += sign*amount;
        money = amount*m_militaryPrice;
        
        __updateMilitaryPrice();

        break;
    }

    case entity::Type::DRUG:
    {
        m_drugAmount += sign*amount;
        money = amount*m_drugPrice;

        __updateDrugPrice();

        break;
    }

    case entity::Type::EXCLUSIVE:
    {
        m_exclusiveAmount += sign*amount;
        money = amount*m_exclusivePrice;

        __updateExclusivePrice();

        break;
    }
    }
    
    return money;
}

void Shop::__updateAllPrices()
{
    __updateMineralPrice();
    __updateFoodPrice();
    __updateMedicinePrice();
    __updateMilitaryPrice();
    __updateDrugPrice();
    __updateExclusivePrice();
}

void Shop::__updateMineralPrice()
{
    m_mineralsPrice = PRICE::MINERALS_MAX * (1.0 - atan((float)m_mineralsAmount/MINERALS_AMOUNT_MAX)/1.6);
}

void Shop::__updateFoodPrice()
{
    m_foodPrice = PRICE::FOOD_MAX * (1.0 - atan((float)m_foodAmount/FOOD_AMOUNT_MAX)/1.6);
}

void Shop::__updateMedicinePrice()
{
    m_medicinePrice    = PRICE::MEDICINE_MAX  * (1.0 - atan((float)m_medicineAmount/MEDICINE_AMOUNT_MAX)/1.6);
}

void Shop::__updateMilitaryPrice()
{
    m_militaryPrice  = PRICE::MILITARY_MAX * (1.0 - atan((float)m_militaryAmount/MILITARY_AMOUNT_MAX)/1.6);
}

void Shop::__updateDrugPrice()
{
    m_drugPrice = PRICE::DRUG_MAX * (1.0 - atan((float)m_drugAmount/DRUG_AMOUNT_MAX)/1.6);
}

void Shop::__updateExclusivePrice()
{
    m_exclusivePrice = PRICE::EXCLUSIVE_MAX * (1.0 - atan((float)m_exclusiveAmount/EXCLUSIVE_AMOUNT_MAX)/1.6);
}            

//void Shop::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
//{
//    save_ptree.put(root+"minerals_amount", minerals_amount);
//    save_ptree.put(root+"food_amount",     food_amount);
//    save_ptree.put(root+"medicine_amount", medicine_amount);
//    save_ptree.put(root+"military_amount", military_amount);
//    save_ptree.put(root+"drug_amount",     drug_amount);
//    save_ptree.put(root+"exclusive_amount", exclusive_amount);
//}

//void Shop::LoadData(const boost::property_tree::ptree& load_ptree)
//{
//    minerals_amount = load_ptree.get<int>("minerals_amount");
//    food_amount     = load_ptree.get<int>("food_amount");
//    medicine_amount = load_ptree.get<int>("medicine_amount");
//    military_amount = load_ptree.get<int>("military_amount");
//    drug_amount      = load_ptree.get<int>("drug_amount");
//    exclusive_amount = load_ptree.get<int>("exclusive_amount");
//}

//void Shop::ResolveData()
//{
////    UpdateAllPrices();
////    ((Kosmoport*)manager::EntityManager::get().getEntity(data_unresolved_Room.owner_kosmoport_id))->BindShop(this);
//}

//void Shop::Save(boost::property_tree::ptree& save_ptree) const
//{
////    std::string root = "shop." + std::to_string(id())+".";
////    Base::SaveData(save_ptree, root);
////    Room::SaveData(save_ptree, root);
////    Shop::SaveData(save_ptree, root);
//}

//void Shop::Load(const boost::property_tree::ptree& load_ptree)
//{
////    Base::LoadData(load_ptree);
////    Room::LoadData(load_ptree);
////    Shop::LoadData(load_ptree);
//}

//void Shop::Resolve()
//{
////    Base::ResolveData();
////    Room::ResolveData();
////    Shop::ResolveData();
//}

} // namespace control

