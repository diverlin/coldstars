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


class BaseItem
{
    	public:    				
      		BaseItem();
      		virtual ~BaseItem();
      		
		void setIdData(IdData data_id)       { this->data_id = data_id; };
		void setTextureOb(TextureOb* texOb)  { this->texOb = texOb; };
		void setFunctionalSlotSubTypeId(int functional_slot_subtype_id) { this->functional_slot_subtype_id = functional_slot_subtype_id; };
		void setItemCommonData(ItemCommonData data_item) { this->data_item = data_item; };
                
            	TextureOb* GetTextureOb()     const { return texOb; };
		unsigned int GetId()        const { return data_id.id; };
		unsigned int GetTypeId()    const { return data_id.type_id; };
		unsigned int GetSubTypeId() const { return data_id.subtype_id; };
		unsigned int GetMass()    const { return data_item.mass; };
		unsigned int getCondition() const { return condition; };
		int getPrice()     const { return price; };
		int getFunctionalSlotSubTypeId() const { return functional_slot_subtype_id; };
    
                void bindSlot(ItemSlot*);
 
     		void repair();

     		void deterioration(); 
                
		void updateInfo();
			
      		virtual void render(Rect);
      		void renderInfo(Rect, float, float); 
     		
     		void virtual updateOwnerAbilities() = 0;

	protected:
      	      	IdData data_id;
     		TextureOb* texOb;
                
                int race_id;
		unsigned int condition;
     		int price;

                int functional_slot_subtype_id;

     		bool is_DAMAGED;
                
                ItemCommonData data_item;
                
                ItemSlot* slot;
                
                InfoTable info;  
     		
     		virtual void addCommonInfo()=0;
 		virtual void addUniqueInfo()=0;                      
};

#endif
