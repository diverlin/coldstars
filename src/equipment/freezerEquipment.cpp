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


#include "freezerEquipment.h"

FreezerEquipment :: FreezerEquipment()
{}



FreezerEquipment :: FreezerEquipment(TextureOb* _itemTexOb, 
				     int _freeze_orig, 
				     EquipmentCommonData _common_data)
{
    	CommonForEquipment_init(FREEZER_ID, _itemTexOb, _common_data);

    	freeze_orig = _freeze_orig;
    	freeze_add  = 0;

    	updatePropetries();
    	countPrice();
}


FreezerEquipment :: ~FreezerEquipment()
{}


int FreezerEquipment :: getFreeze() const { return freeze; }
		

void FreezerEquipment :: updatePropetries()
{
     	freeze = freeze_orig + freeze_add;
}


void FreezerEquipment :: countPrice()
{
     	float freeze_rate          = (float)freeze_orig / FREEZER_FREEZE_MIN;
     	float modules_num_rate     = (float)common_data.modules_num_max / FREEZER_MODULES_NUM_MAX;

     	float effectiveness_rate = FREEZER_FREEZE_WEIGHT * freeze_rate + FREEZER_MODULES_NUM_WEIGHT * modules_num_rate;

     	float mass_rate          = (float)common_data.mass / FREEZER_MASS_MIN;
     	float condition_rate     = (float)condition / common_data.condition_max;

     	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void FreezerEquipment :: updateOwnerPropetries()
{
    	slot->getShip()->updateFreezeAbility();
}

      
void FreezerEquipment :: addUniqueInfo()
{
    	info.addTitleStr("FREEZER");
    	info.addNameStr("freeze:");     info.addValueStr( getFreezeStr() );
}
           		
           		
std::string FreezerEquipment :: getFreezeStr()
{
     	if (freeze_add == 0)
         	return int2str(freeze_orig);
     	else
         	return int2str(freeze_orig) + "+" + int2str(freeze_add);
}


bool FreezerEquipment :: insertModule(FreezerModule* _freezer_module)
{
    	if (modules_pList.size() < common_data.modules_num_max)
    	{
        	freeze_add += _freezer_module->getFreezeAdd();
    
        	updatePropetries();
        
        	texOb_modules_pList.push_back(_freezer_module->getTexOb());
        	modules_pList.push_back(_freezer_module);
        	return true;
    	}
    	else
        	return false;    
}
      

FreezerEquipment* freezerEquipmentGenerator(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECH_LEVEL_0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* pTo_itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.FreezerEquipment_texOb_pList);    // FAKE TEXTURE OB LIST IS USED HERE
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(RADAR_ITEM_TEXTURE_ID, revision_id) 

    	int freeze_orig     = randIntInRange(FREEZER_FREEZE_MIN, FREEZER_FREEZE_MAX);
    	
    	EquipmentCommonData common_data;
    	common_data.modules_num_max = randIntInRange(FREEZER_MODULES_NUM_MIN, FREEZER_MODULES_NUM_MAX);
    	common_data.mass            = randIntInRange(FREEZER_MASS_MIN, FREEZER_MASS_MAX);
    	common_data.condition_max   = randIntInRange(FREEZER_CONDITION_MIN, FREEZER_CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

    	FreezerEquipment* freezer_module = new FreezerEquipment(pTo_itemTexOb, freeze_orig, common_data);
    	return freezer_module;
}
