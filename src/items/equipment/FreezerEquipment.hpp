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


#ifndef FREEZEREQUIPMENT_H
#define FREEZEREQUIPMENT_H

#include "BaseEquipment.hpp"

class FreezerEquipment : public BaseEquipment
{  
   	public:
      		FreezerEquipment(int);
      		virtual ~FreezerEquipment();

		void SetFreezeOrig(int freeze_orig) { this->freeze_orig = freeze_orig; };
                int GetFreeze() const { return freeze; };
    		
      		void CountPrice();
      		virtual void UpdatePropetries();  
      		
    		virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(const boost::property_tree::ptree&);
		virtual void ResolveData();
      		
      	private:
      	      	int freeze_orig;
      		int freeze_add;
      		int freeze;
      		
      		void virtual AddUniqueInfo();
       		std::string GetFreezeStr();
                
                void SaveDataUniqueFreezerEquipment(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueFreezerEquipment(const boost::property_tree::ptree&);
		void ResolveDataUniqueFreezerEquipment(); 
};


#endif 
