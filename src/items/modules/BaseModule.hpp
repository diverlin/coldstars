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


#ifndef MODULEBASE_H
#define MODULEBASE_H

#include "../BaseItem.hpp"
class BaseEquipment; //#include "../equipment/BaseEquipment.hpp"


struct UnresolvedDataUniqueBaseModule
{
        int equipment_owner_id;
};

class BaseModule : public BaseItem
{
    	public:
      		BaseModule();
      		virtual ~BaseModule();
      		
      		void SetEquipmentOwner(BaseEquipment* equipment_owner) { this->equipment_owner = equipment_owner; };

	protected:     	
		BaseEquipment* equipment_owner;
		
		UnresolvedDataUniqueBaseModule data_unresolved_BaseModule;
		
     		void AddCommonInfo();   
     		
     		void SaveDataUniqueBaseModule(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueBaseModule(const boost::property_tree::ptree&);
		void ResolveDataUniqueBaseModule();                
};

#endif
