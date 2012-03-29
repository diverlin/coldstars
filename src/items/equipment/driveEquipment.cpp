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


DriveEquipment :: DriveEquipment(int speed_orig, 
				 int hyper_orig)
{
     	this->speed_orig = speed_orig;
     	this->hyper_orig = hyper_orig;
}

DriveEquipment :: ~DriveEquipment() /* virtual */
{}


int DriveEquipment :: getSpeed() const { return speed; }
int DriveEquipment :: getHyper() const { return hyper; }
		
	
/* virtual */	
void DriveEquipment :: updatePropetries()
{     
     	speed_add        = 0;
     	hyper_add        = 0;
     
        for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
    		speed_add += ((DriveModule*)modules_vec[i])->getSpeedAdd();
        	hyper_add += ((DriveModule*)modules_vec[i])->getHyperAdd();  	
    	}
    	
     	speed = speed_orig + speed_add;
     	hyper = hyper_orig + hyper_add;
}


void DriveEquipment :: countPrice()
{
     	float speed_rate         = (float)speed_orig / EQUIPMENT::DRIVE::SPEED_MIN;
     	float hyper_rate         = (float)hyper_orig / EQUIPMENT::DRIVE::HYPER_MIN;
     	float modules_num_rate   = (float)data_item.modules_num_max / EQUIPMENT::DRIVE::MODULES_NUM_MAX;

     	float effectiveness_rate = EQUIPMENT::DRIVE::SPEED_WEIGHT * speed_rate + 
     				   EQUIPMENT::DRIVE::HYPER_WEIGHT * hyper_rate + 
     				   EQUIPMENT::DRIVE::MODULES_NUM_WEIGHT * modules_num_rate;

     	float mass_rate          = (float)data_item.mass / EQUIPMENT::DRIVE::MASS_MIN;
     	float condition_rate     = (float)condition / data_item.condition_max;

     	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}

/* virtual */
void DriveEquipment :: UpdateOwnerAbilities()
{
    	slot->GetOwnerVehicle()->UpdateDriveAbility();
    	slot->GetOwnerVehicle()->UpdateJumpAbility();    	
}


void DriveEquipment :: AddUniqueInfo()
{
    	info.addTitleStr("DRIVE");
    	info.addNameStr("speed:");     info.addValueStr( getSpeedStr() );
    	info.addNameStr("hyper:");     info.addValueStr( getHyperStr() );
}     		

std::string DriveEquipment :: getSpeedStr()
{
     	if (speed_add == 0)
        	return int2str(speed_orig);
     	else
        	return int2str(speed_orig) + "+" + int2str(speed_add);
}

std::string DriveEquipment :: getHyperStr()
{
     	if (hyper_add == 0)
        	return int2str(hyper_orig);
     	else
        	return int2str(hyper_orig) + "+" + int2str(hyper_add);
}


DriveEquipment* getNewDriveEquipment(int race_id, int revision_id)
{
        if (race_id == -1)
                race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

        if (revision_id == -1)
                revision_id = TECHLEVEL::L0_ID; 

        int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

        TextureOb* texOb_item = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::DRIVE_EQUIPMENT_ID);   
        //item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::DRIVE_EQUIPMENT_ID, revision_id) 

        int speed_orig      = getRandInt(EQUIPMENT::DRIVE::SPEED_MIN, EQUIPMENT::DRIVE::SPEED_MAX);
        int hyper_orig      = getRandInt(EQUIPMENT::DRIVE::HYPER_MIN, EQUIPMENT::DRIVE::HYPER_MAX);
    
        ItemCommonData common_data;
        common_data.modules_num_max = getRandInt(EQUIPMENT::DRIVE::MODULES_NUM_MIN, EQUIPMENT::DRIVE::MODULES_NUM_MAX);
        common_data.mass            = getRandInt(EQUIPMENT::DRIVE::MASS_MIN, EQUIPMENT::DRIVE::MASS_MAX);
        common_data.condition_max   = getRandInt(EQUIPMENT::DRIVE::CONDITION_MIN, EQUIPMENT::DRIVE::CONDITION_MAX) * tech_rate;
        common_data.deterioration_rate = 1;

        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = EQUIPMENT::EQUIPMENT_ID;
        data_id.subtype_id = EQUIPMENT::DRIVE_ID;
        
        DriveEquipment* drive_equipment = new DriveEquipment(speed_orig, hyper_orig);
    
        drive_equipment->SetIdData(data_id);  
        drive_equipment->SetTextureOb(texOb_item);    	
        drive_equipment->SetFunctionalSlotSubTypeId(SLOT::DRIVE_ID);
        drive_equipment->SetItemCommonData(common_data);
         
        drive_equipment->updatePropetries();
     	drive_equipment->countPrice();
     
        return drive_equipment;
}

