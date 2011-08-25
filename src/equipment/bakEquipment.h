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


#ifndef BAKEQUIPMENT_H
#define BAKEQUIPMENT_H

class BakEquipment : public CommonForEquipment
{
	public:
   		BakEquipment();
     		BakEquipment(TextureOb* _pTo_itemTexOb, int _fuel_max_orig, int _modules_num_max, int _mass, int _condition_max, int _deterioration_rate);
     		~BakEquipment();

		int getFuel() const;
		
		void fill();
		
     		void countPrice();
     		void updatePropetries();
     		void updateOwnerPropetries();

     		void updateInfo();
          		std::string returnFuelStr();
          
     		bool insertModule(BakModule* pTo_bakModule);
     		
     	private:
     	     	int fuel_max_orig;
     		int fuel_max_add;
     		int fuel_max;
     		int fuel;
     		
     	     	VEC_pBakModule_type modules_pList; 
     	     		
     	     	// INFO 
     		std::string info_title_0;
     		std::string info_title_1;   std::string info_value_1;
    		std::string info_title_2;   std::string info_value_2; 
     		std::string info_title_3;   std::string info_value_3;
     		std::string info_title_4;   std::string info_value_4;
     		std::string info_title_5;   std::string info_value_5;
     	
};

BakEquipment* bakEquipmentGenerator(int race_id, int revision_id = -1);

#endif 
