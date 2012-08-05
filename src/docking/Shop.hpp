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
#include "../pilots/Npc.hpp"
#include "../items/others/GoodsPack.hpp"

class Shop : public Room
{
        public: 
                Shop(int id);
                ~Shop();                

                int GetMineralsAmmount() 	const { return minerals_ammount; };
        	int GetFoodAmmount()		const { return food_ammount; };    
        	int GetMedicineAmmount() 	const { return medicine_ammount; };  
        	int GetMilitaryAmmount()	const { return military_ammount; };  
        	int GetDrugAmmount()		const { return drug_ammount; };     
        	int GetExclusiveAmmount() 	const { return exclusive_ammount; };

                int GetMineralsPrice() 		const { return minerals_price; };
        	int GetFoodPrice() 		const { return food_price; };   
        	int GetMedicinePrice() 		const { return medicine_price; };  
        	int GetMilitaryPrice()		const { return military_price; };  
        	int GetDrugPrice() 		const { return drug_price; };     
        	int GetExclusivePrice()		const { return exclusive_price; };
        	                
        	void SellGoods(Npc*, int, int);
        	void BuyGoods(Npc*, GoodsPack*);
        	                
                void SaveData(boost::property_tree::ptree&) const;		
		void LoadData(const boost::property_tree::ptree&);
		void ResolveData();
		
        private:   
                int minerals_ammount;
        	int food_ammount;    
        	int medicine_ammount;  
        	int military_ammount;  
        	int drug_ammount;     
        	int exclusive_ammount;

                int minerals_price;
        	int food_price;    
        	int medicine_price;  
        	int military_price;  
        	int drug_price;     
        	int exclusive_price;
        	                     
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

