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


class DriveEquipment : public BaseEquipment
{
	public:
      		DriveEquipment(int);      			       
      		virtual ~DriveEquipment();

		void SetSpeedOrig(int speed_orig) { this->speed_orig = speed_orig; };
		void SetHyperOrig(int hyper_orig) { this->hyper_orig = hyper_orig; };

		int GetSpeed() const { return speed; };
		int GetHyper() const { return hyper; };
      		
      		virtual void UpdatePropetries();
                virtual void UpdateVehicleAbility(Vehicle*, int sign = 1);

      		void CountPrice();
                      		      		
      		virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(const boost::property_tree::ptree&);
		virtual void ResolveData();
		
      	private:
      	      	int speed_orig;
      		int speed_add;
      		int speed;

      		int hyper_orig;
      		int hyper_add;
      		int hyper;
      		
     		void virtual AddUniqueInfo();
           	std::string GetSpeedStr();
           	std::string GetHyperStr();   
                
                void SaveDataUniqueDriveEquipment(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueDriveEquipment(const boost::property_tree::ptree&);
		void ResolveDataUniqueDriveEquipment();  
};


#endif 




