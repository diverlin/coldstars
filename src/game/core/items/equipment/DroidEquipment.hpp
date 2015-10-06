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


#ifndef DROIDEQUIPMENT_H
#define DROIDEQUIPMENT_H

#include "BaseEquipment.hpp"

class DroidEquipment : public BaseEquipment
{
       public: 
             DroidEquipment(const ID& id);
             virtual ~DroidEquipment();

        void SetRepairOrig(int repair_orig) { this->repair_orig = repair_orig; };
        int GetRepair() const { return repair; };

              virtual void updateProperties();
              virtual void updateInStatic();
                
              void CountPrice();
              
              virtual void Save(boost::property_tree::ptree&) const;
        virtual void Load(const boost::property_tree::ptree&);
        virtual void Resolve();
        
          private:
              int repair_orig;
              int repair_add;
              int repair;
              
             void virtual AddUniqueInfo();
               std::string GetRepairStr();
                
                void SaveData(boost::property_tree::ptree&, const std::string&) const;
        void LoadData(const boost::property_tree::ptree&);
        void ResolveData();  
};

#endif 
