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


#ifndef BAKEQUIPMENT_H
#define BAKEQUIPMENT_H


class BakEquipment : public BaseEquipment
{
	public:
     		BakEquipment(int);
     		virtual ~BakEquipment();
		
                void SetFuelMaxOrig(int fuel_max_orig) { this->fuel_max_orig = fuel_max_orig; };
                void SetFuel(int fuel)                 { this->fuel = fuel; };
                void IncreaseFuel(int fuel);	
                int GetFuelMiss() const { return (fuel_max - fuel); };	
                                
		int GetFuel() const    { return fuel; };
		int GetFuelMax() const { return fuel_max; };
     	
     	     	virtual void UpdatePropetries();

     	     	void CountPrice();
                     	     		
     	     	virtual void SaveData(boost::property_tree::ptree&) const;
		virtual void LoadData(const boost::property_tree::ptree&);
		virtual void ResolveData();
		
     	private:
     	     	int fuel_max_orig;
     		int fuel_max_add;
     		int fuel_max;
     		int fuel;

     		void virtual AddUniqueInfo();
          	std::string GetFuelStr();
                
                void SaveDataUniqueBakEquipment(boost::property_tree::ptree&, const std::string&) const;
		void LoadDataUniqueBakEquipment(const boost::property_tree::ptree&);
		void ResolveDataUniqueBakEquipment();
};

#endif 
