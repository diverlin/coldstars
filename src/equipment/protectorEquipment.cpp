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


#include "protectorEquipment.hpp"

ProtectorEquipment :: ProtectorEquipment(TextureOb* _itemTexOb, 
					 int _protection_orig, 
					 EquipmentCommonData _common_data)
{
    	CommonForEquipment_init(PROTECTOR_ID, _itemTexOb, _common_data);

    	protection_orig = _protection_orig;
    	protection_add  = 0;

    	updatePropetries();
    	countPrice();
}

ProtectorEquipment :: ~ProtectorEquipment()
{}


int ProtectorEquipment :: getProtection() const { return protection; }

		
void ProtectorEquipment :: updatePropetries()
{
      	protection = protection_orig + protection_add;
}

void ProtectorEquipment :: countPrice()
{
      	float protection_rate    = (float)protection_orig / PROTECTOR_PROTECTION_MIN;
      	float modules_num_rate   = (float)common_data.modules_num_max / PROTECTOR_MODULES_NUM_MAX;

      	float effectiveness_rate = PROTECTOR_PROTECTION_WEIGHT * protection_rate + PROTECTOR_MODULES_NUM_WEIGHT * modules_num_rate;

      	float mass_rate          = (float)common_data.mass / PROTECTOR_MASS_MIN;
      	float condition_rate     = (float)condition / common_data.condition_max;

      	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

void ProtectorEquipment :: updateOwnerPropetries()
{
     	slot->getShip()->updateProtectionAbility();
}



void ProtectorEquipment :: addUniqueInfo()
{
    	info.addTitleStr("PROTECTOR");
    	info.addNameStr("protection:");     info.addValueStr( getProtectionStr() );
}
     		

std::string ProtectorEquipment :: getProtectionStr()
{
     	if (protection_add == 0)
         	return int2str(protection_orig);
     	else
         	return int2str(protection_orig) + "+" + int2str(protection_add);
}



bool ProtectorEquipment :: insertModule(ProtectorModule* _protector_module)
{
    	if (modules_pList.size() < common_data.modules_num_max)
    	{
        	protection_add += _protector_module->getProtectionAdd();
    
        	updatePropetries();
        
        	texOb_modules_pList.push_back(_protector_module->getTexOb());
        	modules_pList.push_back(_protector_module);
        	return true;
    	}
    	else
        	return false;    
}
    


ProtectorEquipment* protectorEquipmentGenerator(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECH_LEVEL_0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.ProtectorEquipment_texOb_pList);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(PROTECTOR_ITEM_TEXTURE_ID, revision_id) 

    	int protection_orig = randIntInRange(PROTECTOR_PROTECTION_MIN, PROTECTOR_PROTECTION_MAX);
    	
    	EquipmentCommonData common_data;
    	common_data.modules_num_max = randIntInRange(PROTECTOR_MODULES_NUM_MIN, PROTECTOR_MODULES_NUM_MAX);
    	common_data.mass            = randIntInRange(PROTECTOR_MASS_MIN, PROTECTOR_MASS_MAX);
    	common_data.condition_max   = randIntInRange(PROTECTOR_CONDITION_MIN, PROTECTOR_CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

    	ProtectorEquipment* protector_equipment = new ProtectorEquipment(itemTexOb, protection_orig, common_data);

    	return protector_equipment;
}
