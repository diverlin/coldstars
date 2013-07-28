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


#ifndef NATURELAND_H
#define NATURELAND_H

#include "BaseLand.hpp"
class ItemSlot;
class BaseItem;

struct UnresolvedDataUniqueNatureLand
{
	std::string textureOb_background_path;
};

class NatureLand : public BaseLand
{
        public:
                NatureLand(int);
                virtual ~NatureLand();

		virtual void PutChildsToGarbage() const;
		
		void SetTextureObBackground(TextureOb* textureOb_background) { this->textureOb_background = textureOb_background; };
		
		TextureOb* GetBackgroundTextureOb() const { return textureOb_background; };

		void AddItemSlot(ItemSlot*);

                bool AddItem(BaseItem*);
                bool CanAcceptNewItem() const;
                          
                virtual bool AddVehicle(Vehicle*);
                virtual bool RemoveVehicle(Vehicle*);
                
                virtual bool GetPermissionToLand() const;
                                
                virtual void UpdateInStatic();      
                
                virtual std::string GetDockVehicleStr() const;
                                
                void SaveData(boost::property_tree::ptree&) const;
    		void LoadData(const boost::property_tree::ptree&);
    		void ResolveData(); 
    	
    	private:
    		TextureOb* textureOb_background;
    		
    		std::vector<Vehicle*> VEHICLE_vec;
    		std::vector<ItemSlot*> item_slot_vec;

		UnresolvedDataUniqueNatureLand data_unresolved_NatureLand;
		void SaveDataUniqueNatureLand(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueNatureLand(const boost::property_tree::ptree&);
		void ResolveDataUniqueNatureLand();
		
		friend class GuiNatureLand;
};

#endif
