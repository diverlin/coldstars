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


#include "droidEquipment.h"

DroidEquipment :: DroidEquipment()
{}

DroidEquipment :: DroidEquipment(TextureOb* _itemTexOb, 
				 int _repair_orig, 
				 EquipmentCommonData _common_data)
{
    	CommonForEquipment_init(DROID_ID, _itemTexOb, _common_data);

    	repair_orig = _repair_orig;
    	repair_add  = 0;

    	updatePropetries();
    	countPrice();
}

DroidEquipment :: ~DroidEquipment()
{}


int DroidEquipment :: getRepair() const { return repair; }
		

void DroidEquipment :: updatePropetries()
{
     	repair = repair_orig + repair_add;
}

void DroidEquipment :: countPrice()
{
     	float repair_rate        = (float)repair_orig / DROID_REPAIR_MIN;
     	float modules_num_rate   = (float)common_data.modules_num_max / DROID_MODULES_NUM_MAX;

     	float effectiveness_rate = DROID_REPAIR_WEIGHT * repair_rate + DROID_MODULES_NUM_WEIGHT * modules_num_rate;

     	float mass_rate          = (float)common_data.mass / DROID_MASS_MIN;
     	float condition_rate     = (float)condition / common_data.condition_max;

     	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void DroidEquipment :: updateOwnerPropetries()
{
     	slot->getShip()->updateRepairAbility();
}


void DroidEquipment :: addUniqueInfo()
{
    	info.addTitleStr("DROID");
   	info.addNameStr("repair:");     info.addValueStr( getRepairStr() );
}
     		
     		
std::string DroidEquipment :: getRepairStr()
{
    	if (repair_add == 0)
        	return int2str(repair_orig);
    	else
        	return int2str(repair_orig) + "+" + int2str(repair_add);
}


bool DroidEquipment :: insertModule(DroidModule* _droid_module)
{
    	if (modules_pList.size() < common_data.modules_num_max)
    	{
        	repair_add += _droid_module->getRepairAdd();
    
        	updatePropetries();
         
        	texOb_modules_pList.push_back(_droid_module->getTexOb());
        	modules_pList.push_back(_droid_module);
        	return true;
    	}
   	else 
        	return false;    
}



DroidEquipment* droidEquipmentGenerator(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECH_LEVEL_0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* pTo_itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.DroidEquipment_texOb_pList);    
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(DROID_ITEM_TEXTURE_ID, revision_id)

    	int repair_orig     = randIntInRange(DROID_REPAIR_MIN, DROID_REPAIR_MAX);
    	
    	EquipmentCommonData common_data;
    	common_data.modules_num_max = randIntInRange(DROID_MODULES_NUM_MIN, DROID_MODULES_NUM_MAX);
    	common_data.mass          = randIntInRange(DROID_MASS_MIN, DROID_MASS_MAX);
    	common_data.condition_max = randIntInRange(DROID_CONDITION_MIN, DROID_CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

    	DroidEquipment* droid_equipment = new DroidEquipment(pTo_itemTexOb, repair_orig, common_data);
    	return droid_equipment;
}

