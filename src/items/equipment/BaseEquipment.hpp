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

#ifndef BASEEQUIPMENT_H
#define BASEEQUIPMENT_H

#include "../modules/BaseModule.hpp"

struct UnresolvedDataUniqueBaseEquipment
{
        std::vector<int> modules_id;
};

class BaseEquipment : public BaseItem
{
        public:
     		BaseEquipment();
     		virtual ~BaseEquipment();

      		bool InsertModule(BaseModule*);
      		virtual void UpdatePropetries() = 0;
      		
      		virtual void Render(const Rect&);
      		      		
     	protected:
		std::vector<BaseModule*> modules_vec;    // needs for inserted modules drawing
                
                virtual void AddCommonInfo();
                
                UnresolvedDataUniqueBaseEquipment data_unresolved_BaseEquipment;
                void SaveDataUniqueBaseEquipment(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueBaseEquipment(const boost::property_tree::ptree&);
		void ResolveDataUniqueBaseEquipment();   
};

#endif 
