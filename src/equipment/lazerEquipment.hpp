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


class LazerEquipment : public CommonForEquipment
{
    	public:
      		LazerEquipment(TextureOb* _pTo_itemTexOb, 
      			       int _damage_orig, 
      			       int _radius_orig, 
			       EquipmentCommonData _common_data);
      			       
      		~LazerEquipment();

		int getDamage() const;
		int getRadius() const;
		
      		void fireEvent(Turrel* _turrel);
      
      		bool insertModule(LazerModule* pTo_lazerModule);
      		
      	private:
      	      	int damage_orig;
      		int damage_add;
      		int damage;

      		int radius_orig;
      		int radius_add;
      		int radius;
      		
      		int particle_Size;
      		TextureOb* texOb_turrel;
      		TextureOb* texOb_lazerEffect;
      		TextureOb* texOb_particle;
      		
      	      	std::vector<LazerModule*> modules_pList;
      	      	
      	      	void updatePropetries();
      		void countPrice();
      		void virtual updateOwnerPropetries();

     		void virtual addUniqueInfo();
           	std::string getDamageStr();
           	std::string getRadiusStr();      	
};

LazerEquipment* lazerEquipmentGenerator(int race_id, int revision_id = -1);

#endif 
