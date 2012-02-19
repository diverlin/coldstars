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


#ifndef DRIVEEQUIPMENT_H
#define DRIVEEQUIPMENT_H


class DriveEquipment :  public BaseEquipment
{
	public:
      		DriveEquipment(int speed_orig, 
      			       int hyper_orig);      			       
      		virtual ~DriveEquipment();

		int getSpeed() const;
		int getHyper() const;

      		bool insertModule(DriveModule*);
      		void virtual updateOwnerAbilities();
      		
      	private:
      	      	int speed_orig;
      		int speed_add;
      		int speed;

      		int hyper_orig;
      		int hyper_add;
      		int hyper;
      		
      		std::vector<DriveModule*> modules_vec;
      		
      		void countPrice();
      		void updatePropetries();
      		
     		void virtual addUniqueInfo();
           	std::string getSpeedStr();
           	std::string getHyperStr();      	
};

DriveEquipment* getNewDriveEquipment(int race_id, int revision_id = -1);

#endif 




