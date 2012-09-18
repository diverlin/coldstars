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
#include "../common/myStr.hpp"
#include "../common/rand.hpp"
#include "../common/EntityManager.hpp"
#include "../spaceobjects/Vehicle.hpp"

Shop::Shop(int id)
{
	data_id.id = id;
	data_id.type_id = ENTITY::SHOP_ID;
	data_id.subtype_id = ENTITY::SHOP_ID;
	
	minerals_amount  = getRandInt(MINERALS_STARTAMOUNT_MIN, MINERALS_STARTAMOUNT_MAX);
        food_amount      = getRandInt(FOOD_STARTAMOUNT_MIN, FOOD_STARTAMOUNT_MAX);
        medicine_amount  = getRandInt(MEDICINE_STARTAMOUNT_MIN, MEDICINE_STARTAMOUNT_MAX);
        military_amount  = getRandInt(MILITARY_STARTAMOUNT_MIN, MILITARY_STARTAMOUNT_MAX);
        drug_amount      = getRandInt(DRUG_STARTAMOUNT_MIN, DRUG_STARTAMOUNT_MAX);
        exclusive_amount = getRandInt(EXCLUSIVE_STARTAMOUNT_MIN, EXCLUSIVE_STARTAMOUNT_MAX);
        
        UpdateAllPrices();
}

Shop::~Shop()
{
	EntityManager::Instance().RemoveEntity(this);
}                


int Shop::GetAmount(int subtype_id) const
{
	switch(subtype_id)
	{
		case ENTITY::MINERALS_ID: 	{ return minerals_amount; break; }
		case ENTITY::FOOD_ID: 		{ return food_amount; break; }
		case ENTITY::MEDICINE_ID: 	{ return medicine_amount; break; }
		case ENTITY::MILITARY_ID: 	{ return military_amount; break; }		
		case ENTITY::DRUG_ID:		{ return drug_amount; break; }
		case ENTITY::EXCLUSIVE_ID: 	{ return exclusive_amount; break; }
	}
}    
                
int Shop::GetPrice(int subtype_id) const
{
	switch(subtype_id)
	{
		case ENTITY::MINERALS_ID: 	{ return minerals_price; break; }
		case ENTITY::FOOD_ID: 		{ return food_price; break; }
		case ENTITY::MEDICINE_ID: 	{ return medicine_price; break; }
		case ENTITY::MILITARY_ID: 	{ return military_price; break; }		
		case ENTITY::DRUG_ID:		{ return drug_price; break; }
		case ENTITY::EXCLUSIVE_ID: 	{ return exclusive_price; break; }
	}
}

                
void Shop::SellGoods(Npc* npc, int subtype_id, int amount)
{    
	int sign = -1;
	Deal(npc, sign, subtype_id, amount);	   		

	GoodsPack* goods_pack = GetNewGoodsPack(subtype_id);
        goods_pack->Increase(amount);	
	npc->GetVehicle()->AddItemToCargoSlot(goods_pack);
}
    
        	
void Shop::BuyGoods(Npc* npc, GoodsPack* goods_pack)
{
	int sign = 1;
 	
	Deal(npc, sign, goods_pack->GetSubTypeId(), goods_pack->GetMass());	
	goods_pack->GetItemSlot()->RemoveItem();
	//delete goods_pack; // dangerrr
}
       
void Shop::Deal(Npc* npc, int sign, int subtype_id, int amount)
{
 	float skill_rate = 1.0f + sign*0.1*npc->GetSkill().GetTrader();
	switch(subtype_id)
	{
		case ENTITY::MINERALS_ID:
		{		
			minerals_amount += sign*amount;
			npc->IncreaseCredits(sign*amount*skill_rate*minerals_price);
			
			UpdateMineralPrice();
			
			break;
		}

		case ENTITY::FOOD_ID:
		{        					
			food_amount += sign*amount;
			npc->IncreaseCredits(sign*amount*skill_rate*food_price);
						
			UpdateFoodPrice();
			
			break;
		}

		case ENTITY::MEDICINE_ID:
		{        					
			medicine_amount += sign*amount;
			npc->IncreaseCredits(sign*amount*skill_rate*medicine_price);
			
			UpdateMedicinePrice();
			
			break;
		}			

		case ENTITY::MILITARY_ID:
		{        					
			military_amount += sign*amount;
			npc->IncreaseCredits(sign*amount*skill_rate*military_price);	
		
			UpdateMilitaryPrice();
			
			break;
		}	

		case ENTITY::DRUG_ID:
		{        					
			drug_amount += sign*amount;
			npc->IncreaseCredits(sign*amount*skill_rate*drug_price);
						
			UpdateDrugPrice();
			
			break;
		}	

		case ENTITY::EXCLUSIVE_ID:
		{        					
			exclusive_amount += sign*amount;
			npc->IncreaseCredits(sign*amount*skill_rate*exclusive_price);
						
			UpdateExclusivePrice();
			
			break;
		}	
	}
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
        medicine_price	= PRICE::MEDICINE_MAX  * (1.0 - atan((float)medicine_amount/MEDICINE_AMOUNT_MAX)/1.6); 
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

void Shop::SaveDataUniqueShop(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"minerals_amount", minerals_amount);
	save_ptree.put(root+"food_amount", 	food_amount);
	save_ptree.put(root+"medicine_amount", medicine_amount);
	save_ptree.put(root+"military_amount", military_amount);
	save_ptree.put(root+"drug_amount", 	drug_amount);
	save_ptree.put(root+"exclusive_amount", exclusive_amount);
}

void Shop::LoadDataUniqueShop(const boost::property_tree::ptree& load_ptree)
{
	minerals_amount = load_ptree.get<int>("minerals_amount");
	food_amount	 = load_ptree.get<int>("food_amount");
	medicine_amount = load_ptree.get<int>("medicine_amount");
	military_amount = load_ptree.get<int>("military_amount");
	drug_amount 	 = load_ptree.get<int>("drug_amount");
	exclusive_amount = load_ptree.get<int>("exclusive_amount");
}

void Shop::ResolveDataUniqueShop()
{
	UpdateAllPrices();
	((Kosmoport*)EntityManager::Instance().GetEntityById(data_unresolved_Room.owner_kosmoport_id))->BindShop(this); 
}

void Shop::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "shop." + int2str(GetId())+".";
	SaveDataUniqueBase(save_ptree, root);
	SaveDataUniqueRoom(save_ptree, root);
	SaveDataUniqueShop(save_ptree, root);
}

void Shop::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
	LoadDataUniqueRoom(load_ptree);
	LoadDataUniqueShop(load_ptree);
}

void Shop::ResolveData()
{
	ResolveDataUniqueBase();
	ResolveDataUniqueRoom();
	ResolveDataUniqueShop();
}



