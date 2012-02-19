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


class EnergizerEquipment : public BaseEquipment
{
	public:
      		EnergizerEquipment(int energy_max_orig, 
      				   int restoration_orig);         
      		virtual ~EnergizerEquipment();
      
      		int getEnergy() const;
      		
      		bool insertModule(EnergizerModule*);
      		void virtual updateOwnerAbilities();
      		
      	private:
      		int energy_max_orig;
      		int energy_max_add;
      		int energy_max;
      		int energy;

      		int restoration_orig;
      		int restoration_add;
      		int restoration;

      	      	std::vector<EnergizerModule*> modules_vec;

      		void countPrice();
      		void updatePropetries();
      		
     		void virtual addUniqueInfo();
           	std::string getEnergyStr();
           	std::string getRestorationStr();
};

EnergizerEquipment* getNewEnergizerEquipment(int race_id, int revision_id = -1);

#endif 
