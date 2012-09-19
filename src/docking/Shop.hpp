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

#ifndef SHOP_H
#define SHOP_H

#include "Room.hpp"
class Npc; 
class GoodsPack; 

class Shop : public Room
{
        public: 
                Shop(int id);
                ~Shop();      

                int GetMineralsAmount() 	const { return minerals_amount; };
        	int GetFoodAmount()		const { return food_amount; };    
        	int GetMedicineAmount() 	const { return medicine_amount; };  
        	int GetMilitaryAmount()		const { return military_amount; };  
        	int GetDrugAmount()		const { return drug_amount; };     
        	int GetExclusiveAmount() 	const { return exclusive_amount; };

                int GetMineralsPrice() 		const { return minerals_price; };
        	int GetFoodPrice() 		const { return food_price; };   
        	int GetMedicinePrice() 		const { return medicine_price; };  
        	int GetMilitaryPrice()		const { return military_price; };  
        	int GetDrugPrice() 		const { return drug_price; };     
        	int GetExclusivePrice()		const { return exclusive_price; };

                int GetAmount(int) const;    
                int GetPrice(int) const;
                        	                
        	void SellGoods(Npc*, int, int);
        	void BuyGoods(Npc*, GoodsPack*);
        	                
                void SaveData(boost::property_tree::ptree&) const;		
		void LoadData(const boost::property_tree::ptree&);
		void ResolveData();
		
        private:   
                int minerals_amount;
        	int food_amount;    
        	int medicine_amount;  
        	int military_amount;  
        	int drug_amount;     
        	int exclusive_amount;

                int minerals_price;
        	int food_price;    
        	int medicine_price;  
        	int military_price;  
        	int drug_price;     
        	int exclusive_price;
        	                   
        	void Deal(Npc*, int, int, int);
        	                     
        	void UpdateAllPrices();
        	void UpdateMineralPrice();
        	void UpdateFoodPrice();
        	void UpdateMedicinePrice();
        	void UpdateMilitaryPrice();
        	void UpdateDrugPrice();
        	void UpdateExclusivePrice();
    	
                void SaveDataUniqueShop(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueShop(const boost::property_tree::ptree&);
		void ResolveDataUniqueShop();
        
};

#endif

