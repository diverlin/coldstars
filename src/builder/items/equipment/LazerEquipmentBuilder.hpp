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


#ifndef LAZEREQUIPMENTBUILDER_H
#define LAZEREQUIPMENTBUILDER_H


class LazerEquipmentBuilder
{
	public:
		static LazerEquipmentBuilder& Instance();
		~LazerEquipmentBuilder();

        	void CreateNewLazerEquipment(int id = NONE_ID); 
                void CreateNewInternals(int race_id, int revision_id = -1);
                LazerEquipment* GetLazerEquipment() const { return lazer_equipment; };
        	 		                
        private:
                LazerEquipment* lazer_equipment;
                
		LazerEquipmentBuilder() {};
		LazerEquipmentBuilder(const LazerEquipmentBuilder&) = delete;
		LazerEquipmentBuilder& operator=(const LazerEquipmentBuilder&) = delete;
}; 

#endif 
    

        


