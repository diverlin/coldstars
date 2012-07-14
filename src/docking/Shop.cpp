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


Shop::Shop(int id)
{
	data_id.id = id;
	data_id.type_id = ENTITY::SHOP_ID;
	data_id.subtype_id = ENTITY::SHOP_ID;
	
	minerals_ammount  = getRandInt(MINERALS_AMOUNT_MIN, MINERALS_AMOUNT_MAX);
        food_ammount      = getRandInt(FOOD_AMOUNT_MIN, FOOD_AMOUNT_MAX);
        medicine_ammount  = getRandInt(MEDICINE_AMOUNT_MIN, MEDICINE_AMOUNT_MAX);
        military_ammount  = getRandInt(MILITARY_AMOUNT_MIN, MILITARY_AMOUNT_MAX);
        drug_ammount      = getRandInt(DRUG_AMOUNT_MIN, DRUG_AMOUNT_MAX);
        exclusive_ammount = getRandInt(EXCLUSIVE_AMOUNT_MIN, EXCLUSIVE_AMOUNT_MAX);
        
        UpdatePrices();
}

Shop::~Shop()
{
	EntityManager::Instance().RemoveEntity(this);
}                


void Shop::UpdatePrices()
{
	minerals_price 	= PRICE::MINERALS_MAX * (1.0f - exp(-1.0f/minerals_ammount));
        //food_price 	= PRICE::FOOD_MAX      - PRICE::FOOD_RATE * food_ammount;    
        //medicine_price	= PRICE::MEDICINE_MAX  - PRICE::MEDICINE_RATE * medicine_ammount; 
        //military_price  = PRICE::MILITARY_MAX  - PRICE::MILITARY_RATE * military_ammount;   
        //drug_price      = PRICE::DRUG_MAX      - PRICE::DRUG_RATE * drug_ammount;     
        //exclusive_price = PRICE::EXCLUSIVE_MAX - PRICE::EXCLUSIVE_RATE * exclusive_ammount;   ;
}


void Shop::SaveDataUniqueShop(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	save_ptree.put(root+"minerals_ammount", minerals_ammount);
	save_ptree.put(root+"food_ammount", food_ammount);
	save_ptree.put(root+"medicine_ammount", medicine_ammount);
	save_ptree.put(root+"military_ammount", military_ammount);
	save_ptree.put(root+"drug_ammount", drug_ammount);
	save_ptree.put(root+"exclusive_ammount", exclusive_ammount);
}

void Shop::LoadDataUniqueShop(const boost::property_tree::ptree& load_ptree)
{
	minerals_ammount = load_ptree.get<int>("minerals_ammount");
	food_ammount = load_ptree.get<int>("food_ammount");
	medicine_ammount = load_ptree.get<int>("medicine_ammount");
	military_ammount = load_ptree.get<int>("military_ammount");
	drug_ammount = load_ptree.get<int>("drug_ammount");
	exclusive_ammount = load_ptree.get<int>("exclusive_ammount");
}

void Shop::ResolveDataUniqueShop()
{
	UpdatePrices();
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



