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
                
        data_bullet.texOb = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::ROCKET_BULLET_ID);    
        data_bullet.damage        = damage;
        data_bullet.armor         = ENTITY::ROCKET::ARMOR;
        data_bullet.speed_init    = ENTITY::ROCKET::START_SPEED;
        data_bullet.speed_max     = ENTITY::ROCKET::SPEED_MAX;
        data_bullet.d_speed       = ENTITY::ROCKET::DELTA_SPEED;
        data_bullet.live_time     = ENTITY::ROCKET::LIFE_TIME;
        data_bullet.angular_speed = ENTITY::ROCKET::ANGULAR_SPEED;
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
    	float ammo_rate     = (float)ammo_max_orig / EQUIPMENT::ROCKET::AMMO_MIN;
    	float damage_rate   = (float)damage_orig / EQUIPMENT::ROCKET::DAMAGE_MIN;
    	float radius_rate   = (float)radius_orig / EQUIPMENT::ROCKET::RADIUS_MIN;
    	float modules_num_rate   = (float)data_item.modules_num_max / EQUIPMENT::ROCKET::MODULES_NUM_MAX;

    	float effectiveness_rate = EQUIPMENT::ROCKET::AMMO_WEIGHT * ammo_rate + 
    				   EQUIPMENT::ROCKET::DAMAGE_WEIGHT * damage_rate + 
    				   EQUIPMENT::ROCKET::RADIUS_WEIGHT * radius_rate + 
    				   EQUIPMENT::ROCKET::MODULES_NUM_WEIGHT * modules_num_rate;

    	float mass_rate          = (float)data_item.mass / EQUIPMENT::ROCKET::MASS_MIN;
    	float condition_rate     = (float)condition / data_item.condition_max;

    	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void RocketEquipment :: UpdateOwnerAbilities()
{      
    	slot->getOwnerVehicle()->UpdateFireAbility();
}


void RocketEquipment :: AddUniqueInfo()
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
    	slot->getOwnerVehicle()->GetStarSystem()->addToSpace(rocket1);
    	num++;

    	//RocketBullet* rocket2 = getNewRocketBullet(data_bullet, slot, +2);
    	//slot->getOwnerShip()->GetStarSystem()->add(rocket2);
    	//num++;


    	//rocketlaunch.play()
    	ammo -= num;

    	Deterioration();
}



RocketEquipment* getNewRocketEquipment(int race_id, int revision_id)
{
    	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  

    	TextureOb* texOb_item = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::ROCKET_EQUIPMENT_ID);    
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::ROCKET_EQUIPMENT_ID, revision_id)   
    
    	int ammo_max_orig = getRandInt(EQUIPMENT::ROCKET::AMMO_MIN, EQUIPMENT::ROCKET::AMMO_MAX);
    	int damage_orig   = getRandInt(EQUIPMENT::ROCKET::DAMAGE_MIN, EQUIPMENT::ROCKET::DAMAGE_MAX);
    	int radius_orig   = getRandInt(EQUIPMENT::ROCKET::RADIUS_MIN, EQUIPMENT::ROCKET::RADIUS_MAX);

	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::ROCKET::MODULES_NUM_MIN, EQUIPMENT::ROCKET::MODULES_NUM_MAX);

    	common_data.mass = getRandInt(EQUIPMENT::ROCKET::MASS_MIN, EQUIPMENT::ROCKET::MASS_MAX);
    	common_data.condition_max = getRandInt(EQUIPMENT::ROCKET::CONDITION_MIN, EQUIPMENT::ROCKET::CONDITION_MAX) * tech_rate;

    	common_data.deterioration_rate = 1;
        
        IdData data_id;
        data_id.type_id    = g_ID_GENERATOR.getNextId();
        data_id.type_id    = EQUIPMENT::EQUIPMENT_ID;
        data_id.subtype_id = EQUIPMENT::ROCKET_ID;        

    	RocketEquipment* rocket_equipment = new RocketEquipment(ammo_max_orig, damage_orig, radius_orig);

        rocket_equipment->SetIdData(data_id);  
        rocket_equipment->SetTextureOb(texOb_item);    	
        rocket_equipment->SetFunctionalSlotSubTypeId(SLOT::WEAPON_ID);
        rocket_equipment->SetItemCommonData(common_data);
                
        rocket_equipment->updatePropetries();
        rocket_equipment->countPrice();

        return rocket_equipment;
}






