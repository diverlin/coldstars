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


class LazerEquipment : public EquipmentBase
{
    	public:
      		LazerEquipment(int damage_orig, 
      			       int radius_orig);      			       
      		virtual ~LazerEquipment();

		int getDamage() const;
		int getRadius() const;
		
      		void fireEvent_TRUE();
      		void fireEvent_FALSE();
      		      
      		void virtual UpdateOwnerAbilities();
      		
       	      	virtual void updatePropetries();
      		void countPrice();
    		
    		virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(boost::property_tree::ptree&);
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
           	std::string getDamageStr();
           	std::string getRadiusStr();      	
};

LazerEquipment* getNewLazerEquipment(int race_id, int revision_id = -1);

#endif 
