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


#ifndef BASEITEM_H
#define BASEITEM_H

#include "../common/Base.hpp"
#include "../text/textstuff.hpp"
class ItemSlot; //#include "../spaceobjects/ItemSlot.hpp"

struct ItemCommonData 
{
	ItemCommonData();

	unsigned int modules_num_max; 
	unsigned int condition_max; 
	unsigned int deterioration_rate;
	unsigned int mass; 
};

struct UnresolvedDataUniqueBaseItem
{
        std::string textureOb_path;
        int item_slot_id;
};

class BaseItem : public Base
{
    	public:    				
      		BaseItem();
      		virtual ~BaseItem();

		void SetTextureOb(TextureOb* textureOb)  { this->textureOb = textureOb; };
		void SetFunctionalSlotSubTypeId(int functional_slot_subtype_id) { this->functional_slot_subtype_id = functional_slot_subtype_id; };
		void SetItemCommonData(const ItemCommonData& data_item) { this->data_item = data_item; };
                void SetItemSlot(ItemSlot* item_slot)  { this->item_slot = item_slot; };

                ItemSlot* GetItemSlot() const { return item_slot; };
                                                
            	TextureOb* GetTextureOb()   	const { return textureOb; };
		unsigned int GetMass()      	const { return data_item.mass; };
		unsigned int GetCondition() 	const { return condition; };
		int GetPrice()              	const { return price; };
		int GetFunctionalSlotSubTypeId() const { return functional_slot_subtype_id; };
 
     		void Repair();

     		void Deterioration(); 
                
		void UpdateInfo();
			
		virtual void UpdatePropetries() {};
			
      		virtual void Render(const Rect&);
      		void RenderInfo(const Rect&, float, float); 

	protected:
     		TextureOb* textureOb;
                
                int race_id;
		unsigned int condition;
     		int price;

                int functional_slot_subtype_id;

     		bool is_DAMAGED;
                
                ItemCommonData data_item;
                
                ItemSlot* item_slot;
                
                InfoTable info;  
     		
                UnresolvedDataUniqueBaseItem data_unresolved_BaseItem;
                
     		virtual void AddCommonInfo()=0;
 		virtual void AddUniqueInfo()=0;   
                
                void SaveDataUniqueBaseItem(boost::property_tree::ptree&, const std::string&) const; 
                void LoadDataUniqueBaseItem(const boost::property_tree::ptree&); 
                void ResolveDataUniqueBaseItem();                   
};

#endif
