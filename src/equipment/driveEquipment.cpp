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


#include "driveEquipment.hpp"

DriveEquipment :: DriveEquipment()
{}

DriveEquipment :: DriveEquipment(TextureOb* _itemTexOb, 
				 int _speed_orig, 
				 int _hyper_orig, 
				 EquipmentCommonData _common_data)
{
     CommonForEquipment_init(DRIVE_ID, _itemTexOb, _common_data);

     speed_orig = _speed_orig;
     speed_add  = 0;

     hyper_orig = _hyper_orig;
     hyper_add  = 0;


     updatePropetries();
     countPrice();
     
     
     // particle system settings
     pTo_particleTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.particles_texOb_pList); ;
     particle_num = 5;
     particle_size = 6;
     particle_velocity = 1.2;
     particle_alpha_start = 1.0;
     particle_alpha_end = 0.0;
     particle_d_alpha = 0.05;
}

DriveEquipment :: ~DriveEquipment()
{}


int DriveEquipment :: getSpeed() const { return speed; }
int DriveEquipment :: getHyper() const { return hyper; }
		
		
void DriveEquipment :: updatePropetries()
{
     speed = speed_orig + speed_add;
     hyper = hyper_orig + hyper_add;
}


void DriveEquipment :: countPrice()
{
     float speed_rate         = (float)speed_orig / DRIVE_SPEED_MIN;
     float hyper_rate         = (float)hyper_orig / DRIVE_HYPER_MIN;
     float modules_num_rate   = (float)common_data.modules_num_max / DRIVE_MODULES_NUM_MAX;

     float effectiveness_rate = DRIVE_SPEED_WEIGHT * speed_rate + DRIVE_HYPER_WEIGHT * hyper_rate + DRIVE_MODULES_NUM_WEIGHT * modules_num_rate;

     float mass_rate          = (float)common_data.mass / DRIVE_MASS_MIN;
     float condition_rate     = (float)condition / common_data.condition_max;

     price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void DriveEquipment :: updateOwnerPropetries()
{
    	slot->getShip()->updateDriveAbility();
}


void DriveEquipment :: addUniqueInfo()
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

bool DriveEquipment :: insertModule(DriveModule* _drive_module)
{
    	if (modules_pList.size() < common_data.modules_num_max)
    	{
        	speed_add += _drive_module->getSpeedAdd();
        	hyper_add += _drive_module->getHyperAdd();
     
        	updatePropetries();
         
        	texOb_modules_pList.push_back(_drive_module->getTexOb());
        	modules_pList.push_back(_drive_module);
        	return true;
    	}
    	else    
        	return false;
} 


DriveEquipment* driveEquipmentGenerator(int race_id, int revision_id)
{
    if (race_id == -1)
       race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    if (revision_id == -1)
       revision_id = TECH_LEVEL_0_ID; 

    int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    TextureOb* pTo_itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.DriveEquipment_texOb_pList);   
    //item_texOb = TEXTURE_MANAGER.returnItemTexOb(DRIVE_ITEM_TEXTURE_ID, revision_id) 

    int speed_orig      = getRandInt(DRIVE_SPEED_MIN, DRIVE_SPEED_MAX);
    int hyper_orig      = getRandInt(DRIVE_HYPER_MIN, DRIVE_HYPER_MAX);
    
    EquipmentCommonData common_data;
    common_data.modules_num_max = getRandInt(DRIVE_MODULES_NUM_MIN, DRIVE_MODULES_NUM_MAX);
    common_data.mass            = getRandInt(DRIVE_MASS_MIN, DRIVE_MASS_MAX);
    common_data.condition_max   = getRandInt(DRIVE_CONDITION_MIN, DRIVE_CONDITION_MAX) * tech_rate;
    common_data.deterioration_rate = 1;

    DriveEquipment* pTo_drive = new DriveEquipment(pTo_itemTexOb, speed_orig, hyper_orig, common_data);
    return pTo_drive;
}

