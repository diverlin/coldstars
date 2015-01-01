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
#include "../world/EntityManager.hpp"
#include "../spaceobjects/Vehicle.hpp"
#include "../items/others/GoodsPack.hpp"
#include "../slots/ItemSlot.hpp"
#include "../pilots/Npc.hpp"

#include "../garbage/EntityGarbage.hpp"

Shop::Shop(int id)
{
    SetId(id);
    SetTypeId(TYPE::ENTITY::SHOP_ID);
    SetSubTypeId(TYPE::ENTITY::SHOP_ID);    
    
    minerals_amount  = meti::getRandInt(MINERALS_STARTAMOUNT_MIN, MINERALS_STARTAMOUNT_MAX);
    food_amount      = meti::getRandInt(FOOD_STARTAMOUNT_MIN, FOOD_STARTAMOUNT_MAX);
    medicine_amount  = meti::getRandInt(MEDICINE_STARTAMOUNT_MIN, MEDICINE_STARTAMOUNT_MAX);
    military_amount  = meti::getRandInt(MILITARY_STARTAMOUNT_MIN, MILITARY_STARTAMOUNT_MAX);
    drug_amount      = meti::getRandInt(DRUG_STARTAMOUNT_MIN, DRUG_STARTAMOUNT_MAX);
    exclusive_amount = meti::getRandInt(EXCLUSIVE_STARTAMOUNT_MIN, EXCLUSIVE_STARTAMOUNT_MAX);
    
    UpdateAllPrices();
}

Shop::~Shop()
{}                


int Shop::GetAmount(TYPE::ENTITY subtype_id) const
{
    switch(subtype_id)
    {
        case TYPE::ENTITY::MINERALS_ID:     { return minerals_amount; break; }
        case TYPE::ENTITY::FOOD_ID:         { return food_amount; break; }
        case TYPE::ENTITY::MEDICINE_ID:     { return medicine_amount; break; }
        case TYPE::ENTITY::MILITARY_ID:     { return military_amount; break; }        
        case TYPE::ENTITY::DRUG_ID:        { return drug_amount; break; }
        case TYPE::ENTITY::EXCLUSIVE_ID:     { return exclusive_amount; break; }
    }
    
    return 0;
}    
                
int Shop::GetPrice(TYPE::ENTITY subtype_id) const
{
    switch(subtype_id)
    {
        case TYPE::ENTITY::MINERALS_ID:     { return minerals_price; break; }
        case TYPE::ENTITY::FOOD_ID:         { return food_price; break; }
        case TYPE::ENTITY::MEDICINE_ID:     { return medicine_price; break; }
        case TYPE::ENTITY::MILITARY_ID:     { return military_price; break; }        
        case TYPE::ENTITY::DRUG_ID:            { return drug_price; break; }
        case TYPE::ENTITY::EXCLUSIVE_ID:     { return exclusive_price; break; }
    }
    
    return 0;
}

                
bool Shop::SellGoods(Npc* npc, TYPE::ENTITY subtype_id, int amount)
{    
    int sign = -1;
    int price = Deal(sign, subtype_id, amount);
    
    if (price > 0)
    {        
        if (npc->WithdrawCredits(price) == true)
        {
            GoodsPack* goods_pack = GetNewGoodsPack(subtype_id);
            goods_pack->Increase(amount);    
        
            npc->GetVehicle()->AddItemToCargoSlot(goods_pack);
                
            return true;
        }
    }      
    
    return false;
}
    
            
int Shop::BuyGoods(GoodsPack* goods_pack)
{     
    int sign = 1;    
    int price = Deal(sign, goods_pack->GetSubTypeId(), goods_pack->GetMass());    
    if (price > 0)
    {
        goods_pack->GetItemSlot()->RemoveItem(); 
        EntityGarbage::Instance().Add(goods_pack);
    }
    
    return price;
}
       
int Shop::Deal(int sign, TYPE::ENTITY subtype_id, int amount)
{
    int money = 0;
    switch(subtype_id)
    {
        case TYPE::ENTITY::MINERALS_ID:
        {        
            minerals_amount += sign*amount;
            money = amount*minerals_price;
            
            UpdateMineralPrice();
            
            break;
        }

        case TYPE::ENTITY::FOOD_ID:
        {                            
            food_amount += sign*amount;
            money = amount*food_price;
                        
            UpdateFoodPrice();
            
            break;
        }

        case TYPE::ENTITY::MEDICINE_ID:
        {                            
            medicine_amount += sign*amount;
            money = amount*medicine_price;
            
            UpdateMedicinePrice();
            
            break;
        }            

        case TYPE::ENTITY::MILITARY_ID:
        {                            
            military_amount += sign*amount;
            money = amount*military_price;    
        
            UpdateMilitaryPrice();
            
            break;
        }    

        case TYPE::ENTITY::DRUG_ID:
        {                            
            drug_amount += sign*amount;
            money = amount*drug_price;    
                        
            UpdateDrugPrice();
            
            break;
        }    

        case TYPE::ENTITY::EXCLUSIVE_ID:
        {                            
            exclusive_amount += sign*amount;
            money = amount*exclusive_price;
                        
            UpdateExclusivePrice();
            
            break;
        }    
    }
    
    return money;
}
            
void Shop::UpdateAllPrices()
{
        UpdateMineralPrice();
        UpdateFoodPrice();
        UpdateMedicinePrice();
        UpdateMilitaryPrice();
        UpdateDrugPrice();
        UpdateExclusivePrice();
}

void Shop::UpdateMineralPrice()
{
    minerals_price = PRICE::MINERALS_MAX * (1.0 - atan((float)minerals_amount/MINERALS_AMOUNT_MAX)/1.6);
}
 
void Shop::UpdateFoodPrice()
{
        food_price = PRICE::FOOD_MAX * (1.0 - atan((float)food_amount/FOOD_AMOUNT_MAX)/1.6);    
}

void Shop::UpdateMedicinePrice()
{
        medicine_price    = PRICE::MEDICINE_MAX  * (1.0 - atan((float)medicine_amount/MEDICINE_AMOUNT_MAX)/1.6); 
}

void Shop::UpdateMilitaryPrice()
{
        military_price  = PRICE::MILITARY_MAX * (1.0 - atan((float)military_amount/MILITARY_AMOUNT_MAX)/1.6);   
}

void Shop::UpdateDrugPrice()
{
        drug_price = PRICE::DRUG_MAX * (1.0 - atan((float)drug_amount/DRUG_AMOUNT_MAX)/1.6);  
}

void Shop::UpdateExclusivePrice()
{
        exclusive_price = PRICE::EXCLUSIVE_MAX * (1.0 - atan((float)exclusive_amount/EXCLUSIVE_AMOUNT_MAX)/1.6);   
}            

void Shop::SaveData(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
    save_ptree.put(root+"minerals_amount", minerals_amount);
    save_ptree.put(root+"food_amount",     food_amount);
    save_ptree.put(root+"medicine_amount", medicine_amount);
    save_ptree.put(root+"military_amount", military_amount);
    save_ptree.put(root+"drug_amount",     drug_amount);
    save_ptree.put(root+"exclusive_amount", exclusive_amount);
}

void Shop::LoadData(const boost::property_tree::ptree& load_ptree)
{
    minerals_amount = load_ptree.get<int>("minerals_amount");
    food_amount     = load_ptree.get<int>("food_amount");
    medicine_amount = load_ptree.get<int>("medicine_amount");
    military_amount = load_ptree.get<int>("military_amount");
    drug_amount      = load_ptree.get<int>("drug_amount");
    exclusive_amount = load_ptree.get<int>("exclusive_amount");
}

void Shop::ResolveData()
{
    UpdateAllPrices();
    ((Kosmoport*)EntityManager::Instance().GetEntityById(data_unresolved_Room.owner_kosmoport_id))->BindShop(this); 
}

void Shop::Save(boost::property_tree::ptree& save_ptree) const
{
    std::string root = "shop." + std::to_string(GetId())+".";
    Base::SaveData(save_ptree, root);
    Room::SaveData(save_ptree, root);
    Shop::SaveData(save_ptree, root);
}

void Shop::Load(const boost::property_tree::ptree& load_ptree)
{
    Base::LoadData(load_ptree);
    Room::LoadData(load_ptree);
    Shop::LoadData(load_ptree);
}

void Shop::Resolve()
{
    Base::ResolveData();
    Room::ResolveData();
    Shop::ResolveData();
}



