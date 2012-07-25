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


#ifndef LAZERMODULE_H
#define LAZERMODULE_H

#include "BaseModule.hpp"

class LazerModule : public BaseModule
{
    	public:
	       	LazerModule(int);
        	virtual ~LazerModule();

		void SetDamageAdd(int damage_add) { this->damage_add = damage_add; };
		void SetRadiusAdd(int radius_add) { this->radius_add = radius_add; };
                
		int GetDamageAdd() const { return damage_add; };
		int GetRadiusAdd() const { return radius_add; };
		
		virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(const boost::property_tree::ptree&);
		virtual void ResolveData();
		
        private:
                int damage_add;
        	int radius_add; 
        	
        	void virtual AddUniqueInfo();   
        	
        	void SaveDataUniqueLazerModule(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueLazerModule(const boost::property_tree::ptree&);
		void ResolveDataUniqueLazerModule();    
};

LazerModule* GetNewLazerModule();

#endif




