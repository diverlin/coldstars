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


#ifndef GRAPPLEMODULE_H
#define GRAPPLEMODULE_H


class GrappleModule : public BaseModule
{
    	public:     
      		GrappleModule(int strength_add, 
                              int radius_add, 
                              int speed_add, 
                              int maxNumItem_add);
      		virtual ~GrappleModule();

		int GetStrengthAdd()   const { return strength_add; };
		int GetRadiusAdd()     const { return radius_add; };
		int GetSpeedAdd()      const { return speed_add; };
		int GetMaxNumItemAdd() const { return maxNumItem_add; };
      		
      		virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(boost::property_tree::ptree&);
		virtual void ResolveData();
		
      	private: 
      	       	int strength_add;
       		int radius_add;
       		int speed_add;
       		int maxNumItem_add;
       		
       		void virtual AddUniqueInfo();
       		
       		void SaveDataUniqueGrappleModule(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueGrappleModule(const boost::property_tree::ptree&);
		void ResolveDataUniqueGrappleModule();
};

GrappleModule* GetNewGrappleModule();


#endif
