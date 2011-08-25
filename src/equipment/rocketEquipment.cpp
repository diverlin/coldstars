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


#include "rocketEquipment.h"

RocketEquipment :: RocketEquipment()
{}

RocketEquipment :: RocketEquipment(TextureOb* _pTo_itemTexOb, 
				   int _ammo_max_orig, 
				   int _damage_orig, 
				   int _radius_orig, 
				   int _modules_num_max, 
				   int _mass, 
				   int _condition_max, 
				   int _deterioration_rate)
{
	CommonForEquipment_init(ROCKET_ID, _pTo_itemTexOb, _modules_num_max, _mass, _condition_max, _deterioration_rate);

        ammo_max_orig = _ammo_max_orig;
        ammo_max_add = 0;
        ammo = ammo_max_orig;
        
        damage_orig = _damage_orig;
        damage_add = 0;

        radius_orig = _radius_orig;
        radius_add = 0;


        pTo_bulletTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.rocketBullet_texOb_pList);    
        bullet_size          = returnObjectSize((*pTo_bulletTexOb).w, (*pTo_bulletTexOb).h); 
        bullet_armor         = ROCKET_ARMOR;
        bullet_speed_init    = ROCKET_START_SPEED;
        bullet_speed_max     = ROCKET_SPEED_MAX;
        bullet_d_speed       = ROCKET_DELTA_SPEED;
        bullet_live_time     = ROCKET_EXISTANCE_TIME;
        bullet_angular_speed = ROCKET_ANGULAR_SPEED;

        turrelTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.turrel_texOb_pList); 
   
        updatePropetries();
        countPrice();
        updateInfo();
}


RocketEquipment :: ~RocketEquipment()
{}


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
    	float modules_num_rate   = (float)modules_num_max / ROCKET_MODULES_NUM_MAX;

    	float effectiveness_rate = ROCKET_AMMO_WEIGHT * ammo_rate + ROCKET_DAMAGE_WEIGHT * damage_rate + ROCKET_RADIUS_WEIGHT * radius_rate + ROCKET_MODULES_NUM_WEIGHT * modules_num_rate;

    	float mass_rate          = (float)mass / ROCKET_MASS_MIN;
    	float condition_rate     = (float)condition / condition_max;

    	price = (3 * effectiveness_rate - mass_rate - condition_rate) * 100;
}


void RocketEquipment :: updateOwnerPropetries()
{      
    	slot->getShip()->updateFireAbility();
}

std::string RocketEquipment :: returnAmmoStr()
{
    	if (ammo_max_add == 0)
       		return int2str(ammo_max_orig) + "/" + int2str(ammo);
    	else
       		return int2str(ammo_max_orig) + "+" + int2str(ammo_max_add) + "/" + int2str(ammo);
}

std::string RocketEquipment :: returnDamageStr()
{
    	if (damage_add == 0)
       		return int2str(damage_orig);
    	else
       		return int2str(damage_orig) + "+" + int2str(damage_add);
}

std::string RocketEquipment :: returnRadiusStr()
{
    	if (radius_add == 0)
       		return int2str(radius_orig);
    	else
       		return int2str(radius_orig) + "+" + int2str(radius_add);
}

void RocketEquipment :: updateInfo()
{
    	info_title_pList.clear();
    	info_value_pList.clear();

    	info_title_0 = "ROCKET";
    	info_title_1 = "ammo:";       info_value_1 = returnAmmoStr();
    	info_title_2 = "damage:";     info_value_2 = returnDamageStr();
    	info_title_3 = "radius:";     info_value_3 = returnRadiusStr();

    	info_title_4 = "modules:";    info_value_4 = int2str(modules_num_max);
    	info_title_5 = "condition:";  info_value_5 = int2str(condition) + "/" + int2str(condition_max);
    	info_title_6 = "mass:";       info_value_6 = int2str(mass);
    	info_title_7 = "price:";      info_value_7 = int2str(price);

    	info_title_pList.push_back(&info_title_0);  
    	info_title_pList.push_back(&info_title_1);   info_value_pList.push_back(&info_value_1);
    	info_title_pList.push_back(&info_title_2);   info_value_pList.push_back(&info_value_2);
    	info_title_pList.push_back(&info_title_3);   info_value_pList.push_back(&info_value_3);
    	info_title_pList.push_back(&info_title_4);   info_value_pList.push_back(&info_value_4);
    	info_title_pList.push_back(&info_title_5);   info_value_pList.push_back(&info_value_5); 
    	info_title_pList.push_back(&info_title_6);   info_value_pList.push_back(&info_value_6);
    	info_title_pList.push_back(&info_title_7);   info_value_pList.push_back(&info_value_7);
}

void RocketEquipment :: fireEvent()
{
    	RocketBullet* pTo_r1; 
    	if (slot->getShip()->render_TURRELS == true)
    	{
        	pTo_r1 = new RocketBullet(slot->getShip()->pTo_starsystem, 
                                  	  pTo_bulletTexOb, 
                                  	  slot->getTurrel()->getCenterX(), 
                                  	  slot->getTurrel()->getCenterY(), 
                                  	  slot->getTurrel()->getAngle(), 
                                  	  slot->getTurrel()->getTarget_pCenterX(), 
                                  	  slot->getTurrel()->getTarget_pCenterY(), 
                                  	  slot->getTurrel()->getTarget_pAliveStatus(), 
                                  	  slot->getShip()->id, 
                                  	  damage, 
                                  	  bullet_size, 
                                  	  bullet_armor, 
                                  	  bullet_speed_init, 
                                  	  bullet_speed_max, 
                                  	  bullet_d_speed, 
                                  	  bullet_angular_speed, 
                                  	  bullet_live_time);
        }
    	else
    	{
        	pTo_r1 = new RocketBullet(slot->getShip()->pTo_starsystem, 
                                 	  pTo_bulletTexOb, 
                                  	  slot->getShip()->points.center_x, 
                                  	  slot->getShip()->points.center_y, 
                                  	  slot->getTurrel()->getAngle(), 
                                  	  slot->getTurrel()->getTarget_pCenterX(), 
                                  	  slot->getTurrel()->getTarget_pCenterY(), 
                                  	  slot->getTurrel()->getTarget_pAliveStatus(), 
                                  	  slot->getShip()->id, 
                                  	  damage, 
                                  	  bullet_size, 
                                  	  bullet_armor, 
                                  	  bullet_speed_init, 
                                  	  bullet_speed_max, 
                                  	  bullet_d_speed, 
                                  	  bullet_angular_speed, 
                                  	  bullet_live_time);
         }

    	//if (pTo_wslot->target_type_id == SHIP_ID)
        	//pTo_r1->setShipAsTarget(pTo_wslot->pTo_shipTarget);
    	//if (pTo_wslot->target_type_id == ASTEROID_ID)
        	//pTo_r1->setAsteroidAsTarget(pTo_wslot->pTo_asteroidTarget); 
    	//if (pTo_wslot->target_type_id == MINERAL_ID)
        	//pTo_r1->setMineralAsTarget(pTo_wslot->pTo_mineralTarget); 
    	//if (pTo_wslot->target_type_id == CONTAINER_ID)
        	//pTo_r1->setContainerAsTarget(pTo_wslot->pTo_containerTarget); 
           
    	//r1.points.setCenter(l_owner.points.center[0]+15, l_owner.points.center[1])
    	pTo_r1->pTo_starsystem->ROCKET_pList.push_back(pTo_r1);

    	//r2 = rocketBulletInstance(self.bullet_texOb, l_owner, l_target, self.damage,  self.bullet_size, self.bullet_armor, self.bullet_speed_init, self.bullet_speed_max, self.bullet_d_speed, self.bullet_live_time, self.bullet_angular_speed)
    	//r2.points.setCenter(l_owner.points.center[0]-15, l_owner.points.center[1])
    	//r2.starsystem.ROCKET_list.append(r2)

    	//rocketlaunch.play()
    	ammo -= 2;

    	deterioration();
}



bool RocketEquipment :: insertModule(RocketModule* _rocket_module)
{
    	if (modules_pList.size() < modules_num_max)
    	{
        	ammo_max_add += _rocket_module->getAmmoMaxAdd();
        	damage_add   += _rocket_module->getDamageAdd();
        	radius_add   += _rocket_module->getRadiusAdd();
        
        	updatePropetries();
        
        	texOb_modules_pList.push_back(_rocket_module->getTexOb());
        	modules_pList.push_back(_rocket_module);
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

    	TextureOb* pTo_itemTexOb = g_TEXTURE_MANAGER.returnPointerToRandomTexObFromList(&g_TEXTURE_MANAGER.RocketEquipment_texOb_pList);    
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(ROCKET_ITEM_TEXTURE_ID, revision_id)   
    
    	int ammo_max_orig = randIntInRange(ROCKET_AMMO_MIN, ROCKET_AMMO_MAX);
    	int damage_orig   = randIntInRange(ROCKET_DAMAGE_MIN, ROCKET_DAMAGE_MAX);
    	int radius_orig   = randIntInRange(ROCKET_RADIUS_MIN, ROCKET_RADIUS_MAX);

    	int modules_num_max = randIntInRange(ROCKET_MODULES_NUM_MIN, ROCKET_MODULES_NUM_MAX);

    	int mass = randIntInRange(ROCKET_MASS_MIN, ROCKET_MASS_MAX);
    	int condition_max = randIntInRange(ROCKET_CONDITION_MIN, ROCKET_CONDITION_MAX) * tech_rate;

    	int deterioration_rate = 1;

    	RocketEquipment* _rocket_equipment = new RocketEquipment(pTo_itemTexOb,  ammo_max_orig, damage_orig, radius_orig, modules_num_max, mass, condition_max, deterioration_rate);
    	return _rocket_equipment;
}






