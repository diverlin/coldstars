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

#ifndef GUISTORE_H
#define GUISTORE_H

#include "BaseGuiElement.hpp"
#include "GuiPair.hpp"
class Store;
class ItemSlot;
class VehicleSlot;
#include "../common/rect.hpp"
#include "MouseData.hpp"

class GuiStore : public BaseGuiElement
{
        public:
                GuiStore();                      
                ~GuiStore();
		
		void BindStore(Store*);
		void UnbindStore();
                
                Store* GetStore() const { return store; };
                
                bool UpdateMouseInteraction(const MouseData&);

        	void RenderSlots(int) const;                
                
        private:
                Store* store;
        
              	std::vector<GuiPair<Rect, ItemSlot*>> rect_itemslot_vec;          
              	std::vector<GuiPair<Rect, VehicleSlot*>> rect_vehicleslot_vec;
};

#endif




