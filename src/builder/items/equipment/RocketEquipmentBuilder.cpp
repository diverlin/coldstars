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


RocketEquipmentBuilder& RocketEquipmentBuilder::Instance()
{
	static RocketEquipmentBuilder instance;
	return instance;
}

RocketEquipmentBuilder::~RocketEquipmentBuilder()
{}

void RocketEquipmentBuilder::CreateNewRocketEquipment(int id)
{
	if (id == NONE_ID)
	{


		id = SimpleIdGenerator::Instance().GetNextId();
	}

 	try 
        { 
        	rocket_equipment = new RocketEquipment(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        EntityManager::Instance().RegisterEntity(rocket_equipment);
} 
        	
void RocketEquipmentBuilder::CreateNewInternals(int race_id, int revision_id)
{     
    	if (race_id == -1)
       		race_id = RACE::R0_ID; //RACES_GOOD_LIST[randint(0, len(RACES_GOOD_LIST) - 1)]

    	if (revision_id == -1)
       		revision_id = TECHLEVEL::L0_ID; 

    	int tech_rate = 1; //int tech_rate = returnRaceTechRate(race_id);  
        
    	TextureOb* texOb_item = TextureManager::Instance().GetRandomTextureOb(TEXTURE::ROCKET_EQUIPMENT_ID);    
    	//item_texOb = TEXTURE_MANAGER.returnItemTexOb(TEXTURE::ROCKET_EQUIPMENT_ID, revision_id)   
    
    	int ammo_max_orig = getRandInt(EQUIPMENT::ROCKET::AMMO_MIN, EQUIPMENT::ROCKET::AMMO_MAX);
    	int damage_orig   = getRandInt(EQUIPMENT::ROCKET::DAMAGE_MIN, EQUIPMENT::ROCKET::DAMAGE_MAX);
    	int radius_orig   = getRandInt(EQUIPMENT::ROCKET::RADIUS_MIN, EQUIPMENT::ROCKET::RADIUS_MAX);

	ItemCommonData common_data;
    	common_data.modules_num_max = getRandInt(EQUIPMENT::ROCKET::MODULES_NUM_MIN, EQUIPMENT::ROCKET::MODULES_NUM_MAX);

    	common_data.mass = getRandInt(EQUIPMENT::ROCKET::MASS_MIN, EQUIPMENT::ROCKET::MASS_MAX);
    	common_data.condition_max = getRandInt(EQUIPMENT::ROCKET::CONDITION_MIN, EQUIPMENT::ROCKET::CONDITION_MAX) * tech_rate;

    	common_data.deterioration_rate = 1;

        BulletData data_bullet;
        data_bullet.damage        = damage_orig;
        data_bullet.armor         = ENTITY::ROCKET::ARMOR;
        data_bullet.speed_init    = ENTITY::ROCKET::START_SPEED;
        data_bullet.speed_max     = ENTITY::ROCKET::SPEED_MAX;
        data_bullet.d_speed       = ENTITY::ROCKET::DELTA_SPEED;
        data_bullet.live_time     = ENTITY::ROCKET::LIFE_TIME;
        data_bullet.angular_speed = ENTITY::ROCKET::ANGULAR_SPEED;
        
        rocket_equipment->SetAmmoMaxOrig(ammo_max_orig);
	rocket_equipment->SetDamageOrig(damage_orig);
	rocket_equipment->SetRadiusOrig(radius_orig);   
        rocket_equipment->SetBulletData(data_bullet); 
    	rocket_equipment->SetAmmo(ammo_max_orig);                
        rocket_equipment->SetTextureOb(texOb_item);    	
        rocket_equipment->SetFunctionalSlotSubTypeId(ITEMSLOT::WEAPON_ID);
        rocket_equipment->SetItemCommonData(common_data);
                
        rocket_equipment->UpdatePropetries();
        rocket_equipment->CountPrice();
}


