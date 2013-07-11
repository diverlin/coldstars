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

#ifndef GUIVEHICLE2_HPP
#define GUIVEHICLE2_HPP

#include "BaseGuiElement.hpp"
class Vehicle;

class GuiVehicle2 : public BaseGuiElement
{
   	public:
        GuiVehicle2(int subtype_id):BaseGuiElement(subtype_id), m_Vehicle(nullptr) {}
        ~GuiVehicle2() {}
        
        virtual void UpdateUnique(Player*) final;
      		
    private:
        Vehicle* m_Vehicle;

		void Reset();
		void BindVehicle(Vehicle*, float scale = 1.0f); 
        void CreateFunctionalItemSlotsWithCircleGeometry(Vehicle*, float);
};

#endif
