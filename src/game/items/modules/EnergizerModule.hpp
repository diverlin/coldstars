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


#ifndef ENERGIZERMODULE_H
#define ENERGIZERMODULE_H

#include "BaseModule.hpp"

class EnergizerModule : public BaseModule
{
   	public:   
      		EnergizerModule(int);
      		virtual ~EnergizerModule();

		void SetEnergyMaxAdd(int energy_max_add)    { this->energy_max_add = energy_max_add; };
		void SetRestorationAdd(int restoration_add) { this->restoration_add = restoration_add; };
                
		int GetEnergyMaxAdd()   const { return energy_max_add; };
		int GetRestorationAdd() const { return restoration_add; };
      		
      		virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(const boost::property_tree::ptree&);
		virtual void ResolveData();
		
      	private:
      	      	int energy_max_add;
      		int restoration_add;
      		
      		void virtual AddUniqueInfo();
      		
      		void SaveDataUniqueEnergizerModule(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueEnergizerModule(const boost::property_tree::ptree&);
		void ResolveDataUniqueEnergizerModule();
};

#endif
