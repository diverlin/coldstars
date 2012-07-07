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

class GuiVehicle
{
   	public:
      		GuiVehicle(Player*);
      		~GuiVehicle();

		void SetOffset(const vec2i& offset) { this->offset = offset; };
     		bool UpdateMouseInteraction(int, int, int, int, Vehicle*, Store* store = NULL);   
     				
      		void RenderVehicle(Vehicle*, int, int, int) const;
		void RenderFocusedItemInfo(Vehicle*, int, int) const;
      		
      	private: 		
      		Player* player;
      		
      		vec2i offset;
  		
      		void RenderSlotsAndItems(Vehicle*) const;
      		void RenderMarksForEmptySlots(Vehicle*, int, int, int) const;  
};



#endif
