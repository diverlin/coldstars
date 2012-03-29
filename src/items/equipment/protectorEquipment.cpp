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
      	float protection_rate    = (float)protection_orig / EQUIPMENT::PROTECTOR::PROTECTION_MIN;
      	float modules_num_rate   = (float)data_item.modules_num_max / EQUIPMENT::PROTECTOR::MODULES_NUM_MAX;

      	float effectiveness_rate = EQUIPMENT::PROTECTOR::PROTECTION_WEIGHT * protection_rate + 
      				   EQUIPMENT::PROTECTOR::MODULES_NUM_WEIGHT * modules_num_rate;

      	float mass_rate          = (float)data_item.mass / EQUIPMENT::PROTECTOR::MASS_MIN;
      	float condition_rate     = (float)condition / data_item.condition_max;

      	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

/* virtual */
void ProtectorEquipment :: UpdateOwnerAbilities()
{
     	slot->GetOwnerVehicle()->UpdateProtectionAbility();
}



void ProtectorEquipment :: AddUniqueInfo()
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
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::PROTECTOR_EQUIPMENT_ID);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::PROTECTOR_EQUIPMENT_ID, revision_id) 

    	int protection_orig = getRandInt(EQUIPMENT::PROTECTOR::PROTECTION_MIN, EQUIPMENT::PROTECTOR::PROTECTION_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::PROTECTOR::MODULES_NUM_MIN, EQUIPMENT::PROTECTOR::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::PROTECTOR::MASS_MIN, EQUIPMENT::PROTECTOR::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::PROTECTOR::CONDITION_MIN, EQUIPMENT::PROTECTOR::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = EQUIPMENT::EQUIPMENT_ID;
        data_id.subtype_id = EQUIPMENT::PROTECTOR_ID;
        
    	ProtectorEquipment* protector_equipment = new ProtectorEquipment(protection_orig);

        protector_equipment->SetIdData(data_id);  
        protector_equipment->SetTextureOb(texOb_item);    	
        protector_equipment->SetFunctionalSlotSubTypeId(SLOT::PROTECTOR_ID);
        protector_equipment->SetItemCommonData(common_data);
        
        protector_equipment->updatePropetries();
    	protector_equipment->countPrice();
    	
    	return protector_equipment;
}
