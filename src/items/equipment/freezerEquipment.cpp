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


FreezerEquipment :: FreezerEquipment(int freeze_orig)
{
    	this->freeze_orig = freeze_orig;
}

FreezerEquipment :: ~FreezerEquipment() /* virtual */
{}


int FreezerEquipment :: getFreeze() const { return freeze; }
		
/* virtual */
void FreezerEquipment :: updatePropetries()
{
    	freeze_add  = 0;
        
        for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
    		freeze_add += ((FreezerModule*)modules_vec[i])->getFreezeAdd();   	
    	}
    	
     	freeze = freeze_orig + freeze_add;
}


void FreezerEquipment :: countPrice()
{
     	float freeze_rate          = (float)freeze_orig / EQUIPMENT::FREEZER::FREEZE_MIN;
     	float modules_num_rate     = (float)data_item.modules_num_max / EQUIPMENT::FREEZER::MODULES_NUM_MAX;

     	float effectiveness_rate = EQUIPMENT::FREEZER::FREEZE_WEIGHT * freeze_rate + EQUIPMENT::FREEZER::MODULES_NUM_WEIGHT * modules_num_rate;

     	float mass_rate          = (float)data_item.mass / EQUIPMENT::FREEZER::MASS_MIN;
     	float condition_rate     = (float)condition / data_item.condition_max;

     	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

/* virtual */
void FreezerEquipment :: UpdateOwnerAbilities()
{
    	slot->GetOwnerVehicle()->UpdateFreezeAbility();
}

      
void FreezerEquipment :: AddUniqueInfo()
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

      

FreezerEquipment* getNewFreezerEquipment(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::FREEZER_EQUIPMENT_ID);    
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::RADAR_EQUIPMENT_ID, revision_id) 

    	int freeze_orig     = getRandInt(EQUIPMENT::FREEZER::FREEZE_MIN, EQUIPMENT::FREEZER::FREEZE_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::FREEZER::MODULES_NUM_MIN, EQUIPMENT::FREEZER::MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(EQUIPMENT::FREEZER::MASS_MIN, EQUIPMENT::FREEZER::MASS_MAX);
    	common_data.condition_max   = getRandInt(EQUIPMENT::FREEZER::CONDITION_MIN, EQUIPMENT::FREEZER::CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = EQUIPMENT::EQUIPMENT_ID;
        data_id.subtype_id = EQUIPMENT::FREEZER_ID;   
        
    	FreezerEquipment* freezer_equipment = new FreezerEquipment(freeze_orig);
        
        freezer_equipment->SetIdData(data_id);  
        freezer_equipment->SetTextureOb(texOb_item);    	
        freezer_equipment->SetFunctionalSlotSubTypeId(SLOT::FREEZER_ID);
        freezer_equipment->SetItemCommonData(common_data);
  
      	freezer_equipment->updatePropetries();
    	freezer_equipment->countPrice();
    	              
    	return freezer_equipment;
}
