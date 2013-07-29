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


#ifndef BASEVEHICLEBUILDER_HPP
#define BASEVEHICLEBUILDER_HPP

#include <types/TechLevelTypes.hpp>

class Vehicle;


class BaseVehicleBuilder
{
	public:
		static BaseVehicleBuilder& Instance();
		virtual ~BaseVehicleBuilder() {};

        void EquipEquipment(Vehicle*, TYPE::TECHLEVEL tech_leve = TYPE::TECHLEVEL::L0_ID) const; 
        void EquipModules(Vehicle*, TYPE::TECHLEVEL tech_leve = TYPE::TECHLEVEL::L0_ID) const; 
        void EquipArtefacts(Vehicle*, TYPE::TECHLEVEL tech_leve = TYPE::TECHLEVEL::L0_ID) const; 
        void EquipBomb(Vehicle*, TYPE::TECHLEVEL tech_leve = TYPE::TECHLEVEL::L0_ID) const; 
              
    protected:
		BaseVehicleBuilder() {};
		BaseVehicleBuilder(const BaseVehicleBuilder&) = delete;
		BaseVehicleBuilder& operator=(const BaseVehicleBuilder&) = delete;  
        
        void CreateItemSlots(Vehicle*) const;
}; 



#endif 
    

        


