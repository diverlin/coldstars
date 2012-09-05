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

#include "FreezerEquipment.hpp"
#include "../../common/constants.hpp"
#include "../../common/myStr.hpp"
#include "../../items/modules/FreezerModule.hpp"

FreezerEquipment::FreezerEquipment(int id)
{
        data_id.id         = id;
        data_id.subtype_id = ENTITY::FREEZER_EQUIPMENT_ID; 
         
    	freeze_orig = 0;
}

/* virtual */
FreezerEquipment::~FreezerEquipment() 
{}

/* virtual */
void FreezerEquipment::UpdatePropetries()
{
    	freeze_add  = 0;
        
        for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
    		freeze_add += ((FreezerModule*)modules_vec[i])->GetFreezeAdd();   	
    	}
    	
     	freeze = freeze_orig + freeze_add;
}

void FreezerEquipment::CountPrice()
{
     	float freeze_rate          = (float)freeze_orig / EQUIPMENT::FREEZER::FREEZE_MIN;
     	float modules_num_rate     = (float)data_item.modules_num_max / EQUIPMENT::FREEZER::MODULES_NUM_MAX;

     	float effectiveness_rate = EQUIPMENT::FREEZER::FREEZE_WEIGHT * freeze_rate + EQUIPMENT::FREEZER::MODULES_NUM_WEIGHT * modules_num_rate;

     	float mass_rate          = (float)data_item.mass / EQUIPMENT::FREEZER::MASS_MIN;
     	float condition_rate     = (float)condition / data_item.condition_max;

     	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void FreezerEquipment::AddUniqueInfo()
{
    	info.addTitleStr("FREEZER");
    	info.addNameStr("freeze:");     info.addValueStr(GetFreezeStr());
}

std::string FreezerEquipment::GetFreezeStr()
{
     	if (freeze_add == 0)
         	return int2str(freeze_orig);
     	else
         	return int2str(freeze_orig) + "+" + int2str(freeze_add);
}


/*virtual*/
void FreezerEquipment::SaveData(boost::property_tree::ptree& save_ptree) const
{
	std::string root = "freezer_equipment." + int2str(GetId()) + ".";
	SaveDataUniqueBase(save_ptree, root);
        SaveDataUniqueBaseItem(save_ptree, root);
	SaveDataUniqueBaseEquipment(save_ptree, root);
	SaveDataUniqueFreezerEquipment(save_ptree, root);
}

/*virtual*/
void FreezerEquipment::LoadData(const boost::property_tree::ptree& load_ptree)
{
	LoadDataUniqueBase(load_ptree);
        LoadDataUniqueBaseItem(load_ptree);
	LoadDataUniqueBaseEquipment(load_ptree);
	LoadDataUniqueFreezerEquipment(load_ptree);
}

/*virtual*/
void FreezerEquipment::ResolveData()
{
	ResolveDataUniqueBase();
        ResolveDataUniqueBaseItem();
	ResolveDataUniqueBaseEquipment();
	ResolveDataUniqueFreezerEquipment();
}

void FreezerEquipment::SaveDataUniqueFreezerEquipment(boost::property_tree::ptree& save_ptree, const std::string& root) const
{
        save_ptree.put(root+"freeze_orig", freeze_orig);
}
                
void FreezerEquipment::LoadDataUniqueFreezerEquipment(const boost::property_tree::ptree& load_ptree)
{
        freeze_orig = load_ptree.get<int>("freeze_orig");     
}                

void FreezerEquipment::ResolveDataUniqueFreezerEquipment()
{}

