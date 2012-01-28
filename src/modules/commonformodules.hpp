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


#ifndef COMMONFORMODULES_H
#define COMMONFORMODULES_H


class CommonForModules
{
    	public:    				
      		CommonForModules();
      		void CommonForModules_init(int _subtype_id, TextureOb* _texOb);
      		~CommonForModules();
      		
      		// accessors
      		unsigned int getId()      const;
    		unsigned int getTypeId()    const;
    		unsigned int getSubTypeId() const;
    		unsigned int getMass() const;
    		TextureOb* getTexOb() const;

		// other methods	
		void updateInfo();
			
      		void render(Rect slot_rect);
      		void renderInfo(Rect slot_rect, float, float); 
      		
      		// not relevant for this cals but is needed for interface
      		int getFunctionalSlotSubTypeId();
      		void bindSlot(ItemSlot*);
      		void updateOwnerPropetries();
      		//
      		
      	private:
      	      	int id, type_id, subtype_id;
      	      		
     		TextureOb* texOb;
     		int w, h;  
         	
	protected:
                int mass;   
                
                InfoTable info;  	
     		
     		void addCommonInfo();
 		void virtual addUniqueInfo();              
                
};

#endif
