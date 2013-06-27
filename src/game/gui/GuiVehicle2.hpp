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

#ifndef GUIVEHICLE2_H
#define GUIVEHICLE2_H

#include "BaseGuiElement.hpp"
#include "BaseButton.hpp"
#include "../docking/Store.hpp"
#include "GuiPair.hpp"
class Vehicle;
#include "MouseData.hpp"

class GuiVehicle2 : public BaseGuiElement
{
   	public:
      		GuiVehicle2();
      		~GuiVehicle2();
      		
      		Vehicle* GetVehicle() const { return vehicle; }

		void Reset();
		void BindVehicle(Vehicle*, float scale = 1.0f);        	
      		void UpdateEquipmentIcons() const;
      		void ButtonsAction(Player*) const;
      		
      		ItemSlot* GetInreactedItemSlot(const MouseData&);   
      		
      		void UpdateOffset();
      		
      	private:
      		std::vector<GuiPair<BaseButton*, ItemSlot*>> button_slot_vec;

        	void CreateFunctionalItemSlotsCircleGeometry(Vehicle*, float);
        	
        	Vehicle* vehicle;
};

#endif
