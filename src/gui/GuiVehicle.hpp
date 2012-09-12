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


#ifndef GUIVEHICLE_H
#define GUIVEHICLE_H

#include "../docking/Store.hpp"
#include "GuiPair.hpp"

class GuiVehicle : public BaseGui
{
   	public:
      		GuiVehicle();
      		~GuiVehicle();

		void BindVehicle(Vehicle*, float scale = 1.0f);
        	
     		bool UpdateMouseInteractionInSpace(const MouseData&);   
                bool UpdateMouseInteractionInStore(const MouseData&, Vehicle*, Store*); 
                        			
      		void RenderVehicle(const MouseData&, int mark_slot_subtype_id = NONE_ID) const;
		void RenderFocusedItemInfo(const MouseData&) const;
      		
      	private:
      	        Rect rect_korpus; 
                TextureOb* textureOb_korpus;
                	
      		std::vector<GuiPair<Rect, ItemSlot*>> rect_slot_vec;
      		      	
      		void RenderSlots() const;
      		void RenderMarksForEmptySlots(const MouseData&, int) const;  

        	void CreateKorpusGui(Vehicle*, float);
        	void CreateItemSlotsGeometry(Vehicle*, float);
        	void CreateFunctionalItemSlotsCircleGeometry(Vehicle*, float);
};



#endif
