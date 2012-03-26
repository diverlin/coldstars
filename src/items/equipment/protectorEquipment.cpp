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


ProtectorEquipment :: ProtectorEquipment(int protection_orig)
{
    	this->protection_orig = protection_orig;
}

ProtectorEquipment :: ~ProtectorEquipment() /* virtual */
{}


int ProtectorEquipment :: getProtection() const { return protection; }

/* virtual */		
void ProtectorEquipment :: updatePropetries()
{   	
        protection_add  = 0;
        
       	for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
    		protection_add += ((ProtectorModule*)modules_vec[i])->getProtectionAdd();     	
    	}
    	
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

/* virtual */
void ProtectorEquipment :: updateOwnerAbilities()
{
     	slot->getOwnerVehicle()->UpdateProtectionAbility();
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



ProtectorEquipment* getNewProtectorEquipment(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE::R0; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECH_LEVEL_0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.getRandomTexOb(PROTECTOR_ITEM_TEXTURE_ID);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(PROTECTOR_ITEM_TEXTURE_ID, revision_id) 

    	int protection_orig = getRandInt(PROTECTOR_PROTECTION_MIN, PROTECTOR_PROTECTION_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(PROTECTOR_MODULES_NUM_MIN, PROTECTOR_MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(PROTECTOR_MASS_MIN, PROTECTOR_MASS_MAX);
    	common_data.condition_max   = getRandInt(PROTECTOR_CONDITION_MIN, PROTECTOR_CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = EQUIPMENT_ID;
        data_id.subtype_id = PROTECTOR_EQUIPMENT_ID;
        
    	ProtectorEquipment* protector_equipment = new ProtectorEquipment(protection_orig);

        protector_equipment->setIdData(data_id);  
        protector_equipment->setTextureOb(texOb_item);    	
        protector_equipment->setFunctionalSlotSubTypeId(PROTECTOR_SLOT_ID);
        protector_equipment->setItemCommonData(common_data);
        
        protector_equipment->updatePropetries();
    	protector_equipment->countPrice();
    	
    	return protector_equipment;
}
