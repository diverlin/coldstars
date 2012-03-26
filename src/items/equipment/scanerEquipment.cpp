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


ScanerEquipment :: ScanerEquipment(int scan_orig)
{
    	this->scan_orig = scan_orig;
}

ScanerEquipment :: ~ScanerEquipment() /* virtual */
{}

int ScanerEquipment :: getScan() const { return scan; }
		
	
/* virtual */	
void ScanerEquipment :: updatePropetries()
{    	
        scan_add = 0;
        
        for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
    		scan_add += ((ScanerModule*)modules_vec[i])->getScanAdd();      	
    	}
    	
     	scan = scan_orig + scan_add;
}


void ScanerEquipment :: countPrice()
{
     	float scan_rate          = (float)scan_orig / SCANER_SCAN_MIN;
     	float modules_num_rate   = (float)common_data.modules_num_max / SCANER_MODULES_NUM_MAX;

     	float effectiveness_rate = SCANER_SCAN_WEIGHT * scan_rate + SCANER_MODULES_NUM_WEIGHT * modules_num_rate;

     	float mass_rate          = (float)common_data.mass / SCANER_MASS_MIN;
     	float condition_rate     = (float)condition / common_data.condition_max;

     	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

/* virtual */
void ScanerEquipment :: updateOwnerAbilities()
{
    	slot->getOwnerVehicle()->UpdateScanAbility();
}


void ScanerEquipment :: addUniqueInfo()
{
    	info.addTitleStr("SCANER");
    	info.addNameStr("scan:");     info.addValueStr( getScanStr() );
}
     		

std::string ScanerEquipment :: getScanStr()
{
     	if (scan_add == 0)
         	return int2str(scan_orig);
     	else
         	return int2str(scan_orig) + "+" + int2str(scan_add);
}



ScanerEquipment* getNewScanerEquipment(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.getRandomTexOb(SCANER_ITEM_TEXTURE_ID);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(SCANER_ITEM_TEXTURE_ID, revision_id)


    	int scan_orig       = getRandInt(SCANER_SCAN_MIN, SCANER_SCAN_MAX);
    	
    	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(SCANER_MODULES_NUM_MIN, SCANER_MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(SCANER_MASS_MIN, SCANER_MASS_MAX);
    	common_data.condition_max   = getRandInt(SCANER_CONDITION_MIN, SCANER_CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = EQUIPMENT::EQUIPMENT_ID;
        data_id.subtype_id = EQUIPMENT::SCANER_ID; 
        
    	ScanerEquipment* scaner_equipment = new ScanerEquipment(scan_orig);
        
        scaner_equipment->setIdData(data_id);  
        scaner_equipment->setTextureOb(texOb_item);    	
        scaner_equipment->setFunctionalSlotSubTypeId(SLOT::SCANER_ID);
        scaner_equipment->setItemCommonData(common_data);
           
    	scaner_equipment->updatePropetries();
    	scaner_equipment->countPrice();
    	     
    	return scaner_equipment;
}
