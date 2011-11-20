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

#ifndef COMMONFOREQUIPMENT_H
#define COMMONFOREQUIPMENT_H


class CommonForEquipment
{
        public:
     		CommonForEquipment();
     		virtual ~CommonForEquipment();
     		
     		int getTypeId()    const;
        	int getSubTypeId() const;
        	unsigned int getMass() const; 
        	unsigned int getCondition() const; 
        	int getPrice() const; 
                TextureOb* getTexOb() const;
                int getFunctionalSlotSubTypeId() const;
     
     		void bindSlot(ItemSlot*);
     		void repair();

     		void render(Rect slot_rect);
     		void renderInfo(Rect slot_rect, float offset_x, float offset_y); 
     		
     		void updateInfo();
     		
     		void virtual updateOwnerPropetries();
     		
     	private:
     	        int id;
     	        int type_id, subtype_id;
     	        
     	        TextureOb* itemTexOb;
     		int w, h;
	
 		void (CommonForEquipment::*pToFunc_render)(Rect slot_rect);
          	void _renderFrame(Rect slot_rect);
          	void _renderFrames(Rect slot_rect);
          	
          	
     	protected:
     	     	ItemSlot* slot;
     		EquipmentCommonData common_data;
     		int functional_slot_subtype_id;
		
		int race_id;
		unsigned int condition;
     		unsigned int price;			// unsigned is not used to debug the formula of price calc

     		bool in_SPACE;                 		// this flag is needed for grap function to check if the item was already collected or not
     		bool is_DAMAGED;
     		
		VEC_pTexOb_type texOb_modules_pList;      // needs for inserted modules drawing

		InfoTable info;
						
		void addCommonInfo();
 		void virtual addUniqueInfo();
 		
		void CommonForEquipment_init(int _subtype_id, int _functional_slot_subtype_id, TextureOb* _pTo_itemTexOb, EquipmentCommonData _common_data);
      		void deterioration();     	
     		
};

#endif 
