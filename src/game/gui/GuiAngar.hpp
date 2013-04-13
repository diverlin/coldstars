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

#ifndef GUIANGAR_H
#define GUIANGAR_H

#include "BaseGui.hpp"
class Angar;
class ItemSlot;
class VehicleSlot;
#include "GuiPair.hpp"

class GuiAngar : public BaseGui
{
    	public:
       		GuiAngar();
       		~GuiAngar();
		
		void BindAngar(Angar*);
		void UnbindAngar();
				
		Angar* GetAngar() const { return angar; };
		
       		bool UpdateMouseInteractionWithVehicleSlots(const MouseData&);

		void CheckButtonsLock();
       		void ButtonsAction() const;   

       		void RenderVehicleAndItemSlots() const;      
       	
       	private:
       	        Angar* angar;
       	        
       	        ItemSlot* repair_slot;
                ItemSlot* charge_slot;
                
       	      	std::vector<GuiPair<Rect, VehicleSlot*>> rect_vehicleslot_vec;
       	      	std::vector<GuiPair<Rect, ItemSlot*>> rect_itemslot_vec;
};


#endif 
