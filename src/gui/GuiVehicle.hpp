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

class GuiVehicle : public BaseGui
{
   	public:
      		GuiVehicle();
      		~GuiVehicle();

     		bool UpdateMouseInteraction(const MouseData&, Vehicle*, Store* store = NULL);   
     				
      		void RenderVehicle(const MouseData&, Vehicle*, int) const;
		void RenderFocusedItemInfo(const MouseData&, Vehicle*) const;
      		
      	private:  		
      		void RenderSlotsAndItems(Vehicle*) const;
      		void RenderMarksForEmptySlots(const MouseData&, Vehicle*, int) const;  
};



#endif
