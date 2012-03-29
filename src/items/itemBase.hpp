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


#ifndef ITEMBASE_H
#define ITEMBASE_H


class ItemBase
{
    	public:    				
      		ItemBase();
      		virtual ~ItemBase();
      		
                void setIdData(IdData);
                void setTextureOb(TextureOb*);
                void setFunctionalSlotSubTypeId(int);
                void setItemCommonData(ItemCommonData);
                void bindSlot(ItemSlot*);

    		TextureOb* GetTextureOb() const;                
      		unsigned int GetId()        const;
    		unsigned int GetTypeId()    const;
    		unsigned int GetSubTypeId() const;
    		unsigned int GetMass() const;

        	unsigned int getCondition() const; 
        	int getPrice() const; 
                int getFunctionalSlotSubTypeId() const;
     
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
                int mass;   
                int functional_slot_subtype_id;

     		bool is_DAMAGED;
                
                ItemCommonData common_data;
                
                ItemSlot* slot;
                
                InfoTable info;  
     		
     		virtual void addCommonInfo();
 		virtual void addUniqueInfo();                      
};

#endif
