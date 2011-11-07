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


#ifndef GRAPPLEEQUIPMENT_H
#define GRAPPLEEQUIPMENT_H


class GrappleEquipment : public CommonForEquipment
{
   	public:
      		GrappleEquipment();
      		GrappleEquipment(TextureOb* _texOb_item, 
      				 int _strength_orig, 
      				 int _radius_orig, 
      				 int _speed_orig, 
      				 int _maxNumItem_orig, 
				 EquipmentCommonData _common_data);   // joun strength and speed attributes into one
				 
      		~GrappleEquipment();

                void reshapeTargetObSlot(ItemSlot*);
                
		int getStrength()   const;
		int getRadius()     const;
		int getSpeed()      const;
		int getMaxNumItem() const;

      		bool insertModule(GrappleModule*);
                
                template <typename TARGET_TYPE>
                void add(TARGET_TYPE* target);
                
                void validationTargets();
                std::vector<TargetObject*> target_vec;
      		
      	private:
      		int strength_orig;
      		int strength_add;
      		int strength;

      		int radius_orig;
      		int radius_add;
      		int radius;

      		int speed_orig;
      		int speed_add;
      		int speed; 

      		int maxNumItem_orig;
      		int maxNumItem_add;
      		int maxNumItem;
      		
      	      	std::vector<GrappleModule*> modules_vec; 
      	      	
      	      	void countPrice();
      		void updatePropetries();      		
      		void virtual updateOwnerPropetries();
      		
     		void virtual addUniqueInfo();     		
           	std::string getStrengthStr();
           	std::string getRadiusStr();
           	std::string getSpeedStr();
           	std::string getMaxNumItemStr();
};

GrappleEquipment* grappleEquipmentGenerator(int race_id, int revision_id = -1);

#endif 
