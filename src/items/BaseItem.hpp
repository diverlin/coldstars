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


class BaseItem : public Base
{
    	public:    				
      		BaseItem();
      		virtual ~BaseItem();
      		
		void SetIdData(IdData data_id)       { this->data_id = data_id; };
		void SetTextureOb(TextureOb* texOb)  { this->texOb = texOb; };
		void SetFunctionalSlotSubTypeId(int functional_slot_subtype_id) { this->functional_slot_subtype_id = functional_slot_subtype_id; };
		void SetItemCommonData(ItemCommonData data_item) { this->data_item = data_item; };
                
            	TextureOb* GetTextureOb()   const { return texOb; };
		unsigned int GetMass()      const { return data_item.mass; };
		unsigned int GetCondition() const { return condition; };
		int GetPrice()              const { return price; };
		int GetFunctionalSlotSubTypeId() const { return functional_slot_subtype_id; };
    
                void BindSlot(ItemSlot*);
 
     		void Repair();

     		void Deterioration(); 
                
		void UpdateInfo();
			
      		virtual void Render(Rect);
      		void RenderInfo(Rect, float, float); 
     		
     		void virtual UpdateOwnerAbilities()=0;

	protected:
     		TextureOb* texOb;
                
                int race_id;
		unsigned int condition;
     		int price;

                int functional_slot_subtype_id;

     		bool is_DAMAGED;
                
                ItemCommonData data_item;
                
                ItemSlot* slot;
                
                InfoTable info;  
     		
     		virtual void AddCommonInfo()=0;
 		virtual void AddUniqueInfo()=0;                      
};

#endif
