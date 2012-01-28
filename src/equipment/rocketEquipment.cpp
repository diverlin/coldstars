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


RocketEquipment :: RocketEquipment()
{}

RocketEquipment :: RocketEquipment(TextureOb* _texOb_item, 
				   int _ammo_max_orig, 
				   int _damage_orig, 
				   int _radius_orig, 
				   EquipmentCommonData _common_data)
{
	CommonForEquipment_init(ROCKET_EQUIPMENT_ID, WEAPON_SLOT_ID, _texOb_item, _common_data);

        ammo_max_orig = _ammo_max_orig;
        ammo_max_add = 0;
        ammo = ammo_max_orig;
        
        damage_orig = _damage_orig;
        damage_add = 0;
        damage = 0;

        radius_orig = _radius_orig;
        radius_add = 0;
        radius = 0;
  
        updatePropetries();
        countPrice();
        updateInfo();
                
        data_bullet.texOb = g_TEXTURE_MANAGER.getRandomTexOb(ROCKET_BULLET_TEXTURE_ID);    
        data_bullet.damage        = damage;
        data_bullet.armor         = ROCKET_ARMOR;
        data_bullet.speed_init    = ROCKET_START_SPEED;
        data_bullet.speed_max     = ROCKET_SPEED_MAX;
        data_bullet.d_speed       = ROCKET_DELTA_SPEED;
        data_bullet.live_time     = ROCKET_EXISTANCE_TIME;
        data_bullet.angular_speed = ROCKET_ANGULAR_SPEED;
}


RocketEquipment :: ~RocketEquipment()
{
	for (unsigned int mi = 0; mi<modules_vec.size(); mi++)
	{
		delete modules_vec[mi];
	}
}


int RocketEquipment :: getAmmo()   const { return ammo; }
int RocketEquipment :: getDamage() const { return damage; }
int RocketEquipment :: getRadius() const { return radius; }
		

void RocketEquipment :: updatePropetries()
{
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


void RocketEquipment :: updateOwnerPropetries()
{      
    	slot->getOwnerShip()->updateFireAbility();
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


void RocketEquipment :: fireEvent_TRUE()
{
	int num;
    	RocketBullet* rocket1 = rocketBulletGenerator(data_bullet, slot, 0.0f);
    	slot->getOwnerShip()->getStarSystem()->add(rocket1);
    	num++;

    	//RocketBullet* rocket2 = rocketBulletGenerator(data_bullet, slot, +2);
    	//slot->getOwnerShip()->getStarSystem()->add(rocket2);
    	//num++;


    	//rocketlaunch.play()
    	ammo -= num;

    	deterioration();
}


void RocketEquipment :: fireEvent_FALSE()
{
	bool force_center_start = true;
    	RocketBullet* rocket1 = rocketBulletGenerator(data_bullet, slot, -2, force_center_start);
    	slot->getOwnerShip()->getStarSystem()->add(rocket1);

    	RocketBullet* rocket2 = rocketBulletGenerator(data_bullet, slot, +2, force_center_start);
    	slot->getOwnerShip()->getStarSystem()->add(rocket2);

    	ammo -= 2;

    	deterioration();
}


bool RocketEquipment :: insertModule(RocketModule* _rocket_module)
{
    	if (modules_vec.size() < common_data.modules_num_max)
    	{
        	ammo_max_add += _rocket_module->getAmmoMaxAdd();
        	damage_add   += _rocket_module->getDamageAdd();
        	radius_add   += _rocket_module->getRadiusAdd();
        
        	updatePropetries();
        
        	texOb_modules_pList.push_back(_rocket_module->getTexOb());
        	modules_vec.push_back(_rocket_module);
        	return true;
    	}
    	else
        	return false;     
}
    



RocketEquipment* rocketEquipmentGenerator(int race_id, int revision_id)
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

	EquipmentCommonData common_data;
    	common_data.modules_num_max = getRandInt(ROCKET_MODULES_NUM_MIN, ROCKET_MODULES_NUM_MAX);

    	common_data.mass = getRandInt(ROCKET_MASS_MIN, ROCKET_MASS_MAX);
    	common_data.condition_max = getRandInt(ROCKET_CONDITION_MIN, ROCKET_CONDITION_MAX) * tech_rate;

    	common_data.deterioration_rate = 1;

    	RocketEquipment* rocket_equipment = new RocketEquipment(texOb_item,  ammo_max_orig, damage_orig, radius_orig, common_data);
    	return rocket_equipment;
}






