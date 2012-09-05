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


#ifndef GRAPPLEEQUIPMENTBUILDER_H
#define GRAPPLEEQUIPMENTBUILDER_H

#include "../../../items/equipment/GrappleEquipment.hpp"
#include "../../../common/constants.hpp"

class GrappleEquipmentBuilder
{
	public:
		static GrappleEquipmentBuilder& Instance();
		~GrappleEquipmentBuilder();

        	void CreateNewGrappleEquipment(int id = NONE_ID); 
                void CreateNewInternals(int race_id, int revision_id = -1);
                GrappleEquipment* GetGrappleEquipment() const { return grapple_equipment; };
        	 		                
        private:
                GrappleEquipment* grapple_equipment;
                
		GrappleEquipmentBuilder() {};
		GrappleEquipmentBuilder(const GrappleEquipmentBuilder&) = delete;
		GrappleEquipmentBuilder& operator=(const GrappleEquipmentBuilder&) = delete;
}; 

#endif 
    

        


