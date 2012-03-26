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


DroidEquipment :: DroidEquipment(int repair_orig)
{
    	this->repair_orig = repair_orig;
}

DroidEquipment :: ~DroidEquipment() /* virtual */
{}


int DroidEquipment :: getRepair() const { return repair; }
		

/* virtual */
void DroidEquipment :: updatePropetries()
{
    	repair_add        = 0;
        
        for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
    		repair_add += ((DroidModule*)modules_vec[i])->getRepairAdd();    	
    	}
    	
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

/* virtual */
void DroidEquipment :: updateOwnerAbilities()
{
     	slot->getOwnerVehicle()->UpdateRepairAbility();
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


		

DroidEquipment* getNewDroidEquipment(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE::R0; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECH_LEVEL_0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.getRandomTexOb(DROID_ITEM_TEXTURE_ID);    
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(DROID_ITEM_TEXTURE_ID, revision_id)

    	int repair_orig     = getRandInt(DROID_REPAIR_MIN, DROID_REPAIR_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(DROID_MODULES_NUM_MIN, DROID_MODULES_NUM_MAX);
    	common_data.mass          = getRandInt(DROID_MASS_MIN, DROID_MASS_MAX);
    	common_data.condition_max = getRandInt(DROID_CONDITION_MIN, DROID_CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = EQUIPMENT_ID;
        data_id.subtype_id = DROID_EQUIPMENT_ID;  
        
    	DroidEquipment* droid_equipment = new DroidEquipment(repair_orig);
        
        droid_equipment->setIdData(data_id);  
        droid_equipment->setTextureOb(texOb_item);    	
        droid_equipment->setFunctionalSlotSubTypeId(SLOT::DROID);
        droid_equipment->setItemCommonData(common_data);
                
                
    	droid_equipment->updatePropetries();
    	droid_equipment->countPrice();
    	
    	return droid_equipment;
}

