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


RocketEquipment :: RocketEquipment(int ammo_max_orig, 
				   int damage_orig, 
				   int radius_orig)
{
        this->ammo_max_orig = ammo_max_orig;
        this->damage_orig   = damage_orig;
        this->radius_orig   = radius_orig;
        
        ammo   = ammo_max_orig;
        damage = damage_orig;
        radius = radius_orig;
                
        data_bullet.texOb = g_TEXTURE_MANAGER.getRandomTexOb(ROCKET_BULLET_TEXTURE_ID);    
        data_bullet.damage        = damage;
        data_bullet.armor         = ROCKET_ARMOR;
        data_bullet.speed_init    = ROCKET_START_SPEED;
        data_bullet.speed_max     = ROCKET_SPEED_MAX;
        data_bullet.d_speed       = ROCKET_DELTA_SPEED;
        data_bullet.live_time     = ROCKET_EXISTANCE_TIME;
        data_bullet.angular_speed = ROCKET_ANGULAR_SPEED;
}


RocketEquipment :: ~RocketEquipment() /* virtual */
{}


int RocketEquipment :: getAmmo()   const { return ammo; }
int RocketEquipment :: getDamage() const { return damage; }
int RocketEquipment :: getRadius() const { return radius; }
		

/* virtual */
void RocketEquipment :: updatePropetries()
{
        ammo_max_add = 0;
        damage_add   = 0;
        radius_add   = 0;
        
    	for (unsigned int i = 0; i < modules_vec.size(); i++)
    	{
    		ammo_max_add += ((RocketModule*)modules_vec[i])->getAmmoMaxAdd();
        	damage_add   += ((RocketModule*)modules_vec[i])->getDamageAdd();
        	radius_add   += ((RocketModule*)modules_vec[i])->getRadiusAdd();        	
    	}
        	
    	ammo_max = ammo_max_orig + ammo_max_add;
    	damage   = damage_orig + damage_add;
    	radius   = radius_orig + radius_add;
}


void RocketEquipment :: countPrice()
{
    	float ammo_rate     = (float)ammo_max_orig / ROCKET_AMMO_MIN;
    	float damage_rate   = (float)damage_orig / ROCKET_DAMAGE_MIN;
    	float radius_rate   = (float)radius_orig / ROCKET_RADIUS_MIN;
    	float modules_num_rate   = (float)common_data.modules_num_max / ROCKET_MODULES_NUM_MAX;

    	float effectiveness_rate = ROCKET_AMMO_WEIGHT * ammo_rate + ROCKET_DAMAGE_WEIGHT * damage_rate + ROCKET_RADIUS_WEIGHT * radius_rate + ROCKET_MODULES_NUM_WEIGHT * modules_num_rate;

    	float mass_rate          = (float)common_data.mass / ROCKET_MASS_MIN;
    	float condition_rate     = (float)condition / common_data.condition_max;

    	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void RocketEquipment :: updateOwnerAbilities()
{      
    	slot->getOwnerVehicle()->UpdateFireAbility();
}


void RocketEquipment :: addUniqueInfo()
{
    	info.addTitleStr("ROCKET");
    	
    	info.addNameStr("ammo:");      info.addValueStr( getAmmoStr() );
    	info.addNameStr("damage:");    info.addValueStr( getDamageStr() );
    	info.addNameStr("radius:");    info.addValueStr( getRadiusStr() );
}
     		

std::string RocketEquipment :: getAmmoStr()
{
    	if (ammo_max_add == 0)
       		return int2str(ammo_max_orig) + "/" + int2str(ammo);
    	else
       		return int2str(ammo_max_orig) + "+" + int2str(ammo_max_add) + "/" + int2str(ammo);
}

std::string RocketEquipment :: getDamageStr()
{
    	if (damage_add == 0)
       		return int2str(damage_orig);
    	else
       		return int2str(damage_orig) + "+" + int2str(damage_add);
}

std::string RocketEquipment :: getRadiusStr()
{
    	if (radius_add == 0)
       		return int2str(radius_orig);
    	else
       		return int2str(radius_orig) + "+" + int2str(radius_add);
}


void RocketEquipment :: fireEvent()
{
	int num = 0;
    	RocketBullet* rocket1 = VehicleBuilder::Instance().GetNewRocket(data_bullet, slot, 0.0f);
    	slot->getOwnerVehicle()->getStarSystem()->addToSpace(rocket1);
    	num++;

    	//RocketBullet* rocket2 = getNewRocketBullet(data_bullet, slot, +2);
    	//slot->getOwnerShip()->getStarSystem()->add(rocket2);
    	//num++;


    	//rocketlaunch.play()
    	ammo -= num;

    	deterioration();
}



RocketEquipment* getNewRocketEquipment(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE_0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECH_LEVEL_0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.getRandomTexOb(ROCKET_ITEM_TEXTURE_ID);    
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(ROCKET_ITEM_TEXTURE_ID, revision_id)   
    
    	int ammo_max_orig = getRandInt(ROCKET_AMMO_MIN, ROCKET_AMMO_MAX);
    	int damage_orig   = getRandInt(ROCKET_DAMAGE_MIN, ROCKET_DAMAGE_MAX);
    	int radius_orig   = getRandInt(ROCKET_RADIUS_MIN, ROCKET_RADIUS_MAX);

	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(ROCKET_MODULES_NUM_MIN, ROCKET_MODULES_NUM_MAX);

    	common_data.mass = getRandInt(ROCKET_MASS_MIN, ROCKET_MASS_MAX);
    	common_data.condition_max = getRandInt(ROCKET_CONDITION_MIN, ROCKET_CONDITION_MAX) * tech_rate;

    	common_data.deterioration_rate = 1;
        
        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = EQUIPMENT_ID;
        data_id.subtype_id = ROCKET_EQUIPMENT_ID;        

    	RocketEquipment* rocket_equipment = new RocketEquipment(ammo_max_orig, damage_orig, radius_orig);

        rocket_equipment->setIdData(data_id);  
        rocket_equipment->setTextureOb(texOb_item);    	
        rocket_equipment->setFunctionalSlotSubTypeId(WEAPON_SLOT_ID);
        rocket_equipment->setItemCommonData(common_data);
                
        rocket_equipment->updatePropetries();
        rocket_equipment->countPrice();

        return rocket_equipment;
}






