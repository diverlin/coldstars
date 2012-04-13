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


#ifndef PROTECTOREQUIPMENT_H
#define PROTECTOREQUIPMENT_H


class ProtectorEquipment  : public EquipmentBase
{
	public:
      		ProtectorEquipment(int protection_orig);
      		virtual ~ProtectorEquipment();

		int getProtection() const;

      		void virtual UpdateOwnerAbilities();
      		
      		void countPrice();
      		virtual void updatePropetries();
      		
      		virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(boost::property_tree::ptree&);
		virtual void ResolveData();
		
      	private:
      	      	int protection_orig;
      		int protection_add;
      		int protection;

     		void virtual AddUniqueInfo();
           	std::string getProtectionStr();
};

ProtectorEquipment* getNewProtectorEquipment(int race_id, int revision_id = -1);

#endif 
