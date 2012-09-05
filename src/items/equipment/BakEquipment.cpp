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

#include "BakEquipment.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../items//modules/BakModule.hpp"

BakEquipment::BakEquipment(int id)
{
        data_id.id         = id;
        data_id.subtype_id = ENTITY::BAK_EQUIPMENT_ID;
        
    	fuel_max_orig = 0;  
    	fuel          = 0;
}
   
/* virtual */
BakEquipment::~BakEquipment() 
{}
		
void BakEquipment::IncreaseFuel(int fuel)		
{
	this->fuel += fuel; 
        if (this->fuel > fuel_max)
        { 
        	this->fuel = fuel_max; // not sure if it's needed
        }       					
}	
                					
/* virtual */			
void BakEquipment::UpdatePropetries()
{
    	fuel_max_add = 0;
    	
    	for (unsigned int i = 0; i<modules_vec.size(); i++)
    	{
    		fuel_max_add += ((BakModule*)modules_vec[i])->GetFuelMaxAdd();
    	}
    	
    	fuel_max = fuel_max_orig + fuel_max_add;    	
}

void BakEquipment::CountPrice()
{
    	float fuel_rate          = (float)fuel_max_orig / EQUIPMENT::BAK::FUEL_MIN;
    	float modules_num_rate   = (float)data_item.modules_num_max / EQUIPMENT::BAK::MODULES_NUM_MAX;

    	float effectiveness_rate = EQUIPMENT::BAK::FUEL_WEIGHT * fuel_rate + 
    				   EQUIPMENT::BAK::MODULES_NUM_WEIGHT * modules_num_rate;

    	float mass_rate          = (float)data_item.mass / EQUIPMENT::BAK::MASS_MIN;
    	float condition_rate     = (float)condition / data_item.condition_max;

   	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void BakEquipment::AddUniqueInfo()
{
    	info.addTitleStr("BAK");
    	info.addNameStr("fuel:");      info.addValueStr( GetFuelStr() );
}


std::string BakEquipment::GetFuelStr()
{
     	if (fuel_max_add == 0)
        	return int2str(fuel_max_orig) + "/" + int2str(fuel);
     	else
        	return int2str(fuel_max_orig) + "+" + int2str(fuel_max_add) + "/" + int2str(fuel);
}

/*virtual*/
void BakEquipment::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "bak_equipment." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseEquipment(save_ptree, root);
	SaveDataUniqueBakEquipment(save_ptree, root);
}

/*virtual*/
void BakEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseEquipment(load_ptree);
	LoadDataUniqueBakEquipment(load_ptree);
}

/*virtual*/
void BakEquipment::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseEquipment();
	ResolveDataUniqueBakEquipment();
}

void BakEquipment::SaveDataUniqueBakEquipment(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
        save_ptree.put(root+"fuel_max_orig", fuel_max_orig);
        save_ptree.put(root+"fuel", fuel);
}
                
void BakEquipment::LoadDataUniqueBakEquipment(const boost::property_tree::ptree& load_ptree)
{
        fuel_max_orig = load_ptree.get<int>("fuel_max_orig");
        fuel = load_ptree.get<int>("fuel");
}                

void BakEquipment::ResolveDataUniqueBakEquipment()
{}

