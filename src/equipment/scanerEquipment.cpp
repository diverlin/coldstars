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


ScanerEquipment :: ScanerEquipment()
{}

ScanerEquipment :: ScanerEquipment(TextureOb* _texOb_item, 
				   int _scan_orig, 
				   EquipmentCommonData _common_data)
{
    	CommonForEquipment_init(SCANER_EQUIPMENT_ID, SCANER_SLOT_ID, _texOb_item, _common_data);

    	scan_orig = _scan_orig;
    	scan_add = 0;

    	updatePropetries();
    	countPrice();
}

ScanerEquipment :: ~ScanerEquipment()
{
	for (unsigned int mi = 0; mi<modules_vec.size(); mi++)
	{
		delete modules_vec[mi];
	}
}

int ScanerEquipment :: getScan() const { return scan; }
		
		
void ScanerEquipment :: updatePropetries()
{
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

void ScanerEquipment :: updateOwnerPropetries()
{
    	slot->getOwnerShip()->updateScanAbility();
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

bool ScanerEquipment :: insertModule(ScanerModule* _scaner_module)
{
    	if (modules_vec.size() < common_data.modules_num_max)
    	{
        	scan_add += _scaner_module->getScanAdd();
    
        	updatePropetries();
        
        	texOb_modules_pList.push_back(_scaner_module->getTexOb());
        	modules_vec.push_back(_scaner_module);
        	return true;
    	}
    	else
        	return false;     
}


ScanerEquipment* scanerEquipmentGenerator(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECH_LEVEL_0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.ScanerEquipment_texOb_pList);   
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(SCANER_ITEM_TEXTURE_ID, revision_id)


    	int scan_orig       = getRandInt(SCANER_SCAN_MIN, SCANER_SCAN_MAX);
    	
    	EquipmentCommonData common_data;
    	common_data.modules_num_max = getRandInt(SCANER_MODULES_NUM_MIN, SCANER_MODULES_NUM_MAX);
    	common_data.mass            = getRandInt(SCANER_MASS_MIN, SCANER_MASS_MAX);
    	common_data.condition_max   = getRandInt(SCANER_CONDITION_MIN, SCANER_CONDITION_MAX) * tech_rate;
    	common_data.deterioration_rate = 1;

    	ScanerEquipment* scaner_equipment = new ScanerEquipment(texOb_item, scan_orig, common_data);
    	return scaner_equipment;
}
