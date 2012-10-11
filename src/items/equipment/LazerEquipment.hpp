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

#ifndef LAZEREQUIPMENT_H
#define LAZEREQUIPMENT_H

#include "BaseEquipment.hpp"

class LazerEquipment : public BaseEquipment
{
    	public:
      		LazerEquipment(int);      
      		virtual ~LazerEquipment();

		void SetDamageOrig(int damage_orig) { this->damage_orig = damage_orig; };
		void SetRadiusOrig(int radius_orig) { this->radius_orig = radius_orig; };
                
		int GetDamage() const { return damage; };
		int GetRadius() const { return radius; };
		
      		void FireEvent(bool);
      		
       	      	virtual void UpdatePropetries();
                
      		void CountPrice();
    		
    		virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(const boost::property_tree::ptree&);
		virtual void ResolveData();
		
      	private:
      	      	int damage_orig;
      		int damage_add;
      		int damage;

      		int radius_orig;
      		int radius_add;
      		int radius;
      		
      		TextureOb* texOb_turrel;
      		TextureOb* texOb_lazerEffect;

     		void virtual AddUniqueInfo();
           	std::string GetDamageStr();
           	std::string GetRadiusStr();   
                
                void SaveDataUniqueLazerEquipment(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueLazerEquipment(const boost::property_tree::ptree&);
		void ResolveDataUniqueLazerEquipment();  	
};

#endif 
