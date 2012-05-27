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


#ifndef STORE_H
#define STORE_H


class Store : public Base
{
        public:
                Store(int);                      
                ~Store();

                void SetOwnerKosmoport(Kosmoport* owner_kosmoport) { this->owner_kosmoport = owner_kosmoport; }
        	void SetTextureObBackground(TextureOb* textureOb_background) { this->textureOb_background = textureOb_background; };
		
		Kosmoport* GetOwnerKosmoport() { return owner_kosmoport; }
		                
		void AddSlot(ItemSlot* slot, const Rect& rect);                
                bool AddItem(BaseItem*);

                ItemSlot* GetEmptySlot();
                                     	
                bool SellItemFromSlot(Npc*, ItemSlot*);		
                bool BuyItemFromSlot(Npc*, ItemSlot*); 

                void Render() const;
                
                void SaveData(boost::property_tree::ptree&) const;		
		void LoadData(const boost::property_tree::ptree&);
		void ResolveData();
		
        public:
                Kosmoport* owner_kosmoport;
                        
                TextureOb* textureOb_background; 
              
                std::vector<ItemSlot*> slot_total_vec;
                
                void SaveDataUniqueStore(boost::property_tree::ptree&, const std::string&) const;		
		void LoadDataUniqueStore(const boost::property_tree::ptree&);
		void ResolveDataUniqueStore();
};
        
#endif




