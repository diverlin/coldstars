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


#ifndef ENERGIZEREQUIPMENT_H
#define ENERGIZEREQUIPMENT_H


class EnergizerEquipment : public CommonForEquipment
{
	public:
      		EnergizerEquipment();
      		EnergizerEquipment(TextureOb* _pTo_itemTexOb, int _energy_max_orig, int _restoration_orig, int _modules_num_max, int _mass, int _condition_max, int _deterioration_rate);
      		~EnergizerEquipment();
      
      		int getEnergy() const;
      		
      		void countPrice();
      		void updatePropetries();
      		void updateOwnerPropetries();

      		void updateInfo();
           		std::string returnEnergyStr();
           		std::string returnRestorationStr();

      		bool insertModule(EnergizerModule* pTo_energizerModule);
      		
      	private:
      		int energy_max_orig;
      		int energy_max_add;
      		int energy_max;
      		int energy;

      		int restoration_orig;
      		int restoration_add;
      		int restoration;

      	      	VEC_pEnergizerModule_type modules_pList;

      		// INFO 
      		std::string info_title_0;
      		std::string info_title_1;   std::string info_value_1;
      		std::string info_title_2;   std::string info_value_2; 
      		std::string info_title_3;   std::string info_value_3;
      		std::string info_title_4;   std::string info_value_4;
      		std::string info_title_5;   std::string info_value_5;
      		std::string info_title_6;   std::string info_value_6;
      	
};

EnergizerEquipment* energizerEquipmentGenerator(int race_id, int revision_id = -1);

#endif 
