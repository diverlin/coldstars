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

#include "DriveEquipment.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../common/Logger.hpp"
#include "../../items//modules/DriveModule.hpp"

DriveEquipment::DriveEquipment(int id)
{
        data_id.id         = id;
        data_id.subtype_id = ENTITY::eTYPE::DRIVE_EQUIPMENT_ID;
        
     	speed_orig = 0;
     	hyper_orig = 0;
}

/* virtual */
DriveEquipment::~DriveEquipment() 
{}

/* virtual */
void DriveEquipment::UpdateProperties()
{     
     	speed_add        = 0;
     	hyper_add        = 0;
     
        for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
    		speed_add += ((DriveModule*)modules_vec[i])->GetSpeedAdd();
        	hyper_add += ((DriveModule*)modules_vec[i])->GetHyperAdd();  	
    	}
    	
     	speed = speed_orig + speed_add;
     	hyper = hyper_orig + hyper_add;
}
             
void DriveEquipment::CountPrice()
{
     	float speed_rate         = (float)speed_orig / EQUIPMENT::DRIVE::SPEED_MIN;
     	float hyper_rate         = (float)hyper_orig / EQUIPMENT::DRIVE::HYPER_MIN;
     	float modules_num_rate   = (float)data_item.modules_num_max / EQUIPMENT::DRIVE::MODULES_NUM_MAX;

     	float effectiveness_rate = EQUIPMENT::DRIVE::SPEED_WEIGHT * speed_rate + 
     				   EQUIPMENT::DRIVE::HYPER_WEIGHT * hyper_rate + 
     				   EQUIPMENT::DRIVE::MODULES_NUM_WEIGHT * modules_num_rate;

     	float mass_rate          = (float)data_item.mass / EQUIPMENT::DRIVE::MASS_MIN;
     	float condition_rate     = (float)condition / data_item.condition_max;

     	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void DriveEquipment::AddUniqueInfo()
{
    	info.addTitleStr("DRIVE");
    	info.addNameStr("speed:");     info.addValueStr(GetSpeedStr());
    	info.addNameStr("hyper:");     info.addValueStr(GetHyperStr());
}     		

std::string DriveEquipment::GetSpeedStr()
{
     	if (speed_add == 0)
        	return int2str(speed_orig);
     	else
        	return int2str(speed_orig) + "+" + int2str(speed_add);
}

std::string DriveEquipment::GetHyperStr()
{
     	if (hyper_add == 0)
        	return int2str(hyper_orig);
     	else
        	return int2str(hyper_orig) + "+" + int2str(hyper_add);
}


/*virtual*/
void DriveEquipment::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "drive_equipment." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseEquipment(save_ptree, root);
	SaveDataUniqueDriveEquipment(save_ptree, root);
}

/*virtual*/
void DriveEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseEquipment(load_ptree);
	LoadDataUniqueDriveEquipment(load_ptree);
}

/*virtual*/	
void DriveEquipment::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseEquipment();
	ResolveDataUniqueDriveEquipment();
}

void DriveEquipment::SaveDataUniqueDriveEquipment(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" SaveDataUniqueDriveEquipment()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
        save_ptree.put(root+"speed_orig", speed_orig);
        save_ptree.put(root+"hyper_orig", hyper_orig);
}
                
void DriveEquipment::LoadDataUniqueDriveEquipment(const boost::property_tree::ptree& load_ptree)
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" LoadDataUniqueDriveEquipment()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
	
        speed_orig = load_ptree.get<int>("speed_orig");
        hyper_orig = load_ptree.get<int>("hyper_orig");
}                

void DriveEquipment::ResolveDataUniqueDriveEquipment()
{
	#if SAVELOAD_LOG_ENABLED == 1
	Logger::Instance().Log(" ResolveDataUniqueDriveEquipment()  id=" + int2str(GetId()) + " START", SAVELOAD_LOG_DIP);
	#endif
}




