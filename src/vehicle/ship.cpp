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


Ship :: Ship()
{}

Ship :: ~Ship()
{} 








Ship* shipGenerator(int race_id, int subtype_id, int size_id, int weapons_num)
{
    	TextureOb* texOb = g_TEXTURE_MANAGER.getRandomShipTexObWithFollowingAtrributes(race_id, subtype_id, size_id); 
       
       	int protection_rate = 1;
       	if (subtype_id == WARRIOR_ID)
        {
        	protection_rate = 3;
        }
        
        KorpusData data_korpus;
    	data_korpus.space       = size_id*150 + getRandInt(0, 100);
    	data_korpus.armor       = data_korpus.space;
    	data_korpus.protection  = size_id/2*protection_rate;
    	data_korpus.temperature = 100;
        data_korpus.price       = getRandInt(200, 400)*size_id;

        data_korpus.inhibit_GRAPPLE = false;
        data_korpus.weapon_slot_num = weapons_num;
            
            
        LifeData data_life;
        data_life.armor = data_korpus.armor;
        data_life.dying_time = 10*texOb->size_id;
       
        IdData data_id;
        data_id.id      = g_VEHICLE_ID_GENERATOR.getNextId(); 
    	data_id.type_id = SHIP_ID;
    	//subtype_id = ;       

        int size_threshold = 2; 
    	if (texOb->size_id > size_threshold)
       		data_korpus.render_TURRELS = true; 
    	else
       		data_korpus.render_TURRELS = false; 
                           
    	Ship* ship = new Ship();
    	ship->setKorpusData(data_korpus);
	ship->setTextureOb(texOb);
	ship->setIdData(data_id);
	ship->setLifeData(data_life);
    	
    	ship->postCreateInit();
    	    
    	return ship;
}




void equip(Vehicle* vehicle)
{
    	if (vehicle->data_korpus.weapon_slot_num >= 1)
    	{
       		//LazerEquipment* lazer_equipment = lazerEquipmentGenerator(RACE_0_ID);    
       		//vehicle->weapon_slot1.insertItem(lazer_equipment); 
    	       	RocketEquipment* rocket_equipment = rocketEquipmentGenerator(RACE_0_ID);    
       		vehicle->getWeaponComplex()->weapon_slot1.insertItem(rocket_equipment); 
    	
    	}   

    	if (vehicle->data_korpus.weapon_slot_num >= 2)
    	{
       		LazerEquipment* lazer_equipment = lazerEquipmentGenerator(RACE_0_ID);    
       		vehicle->getWeaponComplex()->weapon_slot2.insertItem(lazer_equipment); 
    	}   
    
    	if (vehicle->data_korpus.weapon_slot_num >= 3)
    	{
       		LazerEquipment* lazer_equipment = lazerEquipmentGenerator(RACE_0_ID);    
       		vehicle->getWeaponComplex()->weapon_slot3.insertItem(lazer_equipment); 
       		//RocketEquipment* rocket_equipment = rocketEquipmentGenerator(RACE_0_ID);    
       		//vehicle->weapon_slot3.insertItem(rocket_equipment); 
    	}   
        
    	if (vehicle->data_korpus.weapon_slot_num >= 4)
    	{
       		//LazerEquipment* lazer_equipment = lazerEquipmentGenerator(RACE_0_ID);    
       		//vehicle->weapon_slot4.insertItem(lazer_equipment);         
       		RocketEquipment* rocket_equipment = rocketEquipmentGenerator(RACE_0_ID);    
       		vehicle->getWeaponComplex()->weapon_slot4.insertItem(rocket_equipment); 
    	}   
    
    	if (vehicle->data_korpus.weapon_slot_num >= 5) 
    	{
       		//LazerEquipment* lazer_equipment = lazerEquipmentGenerator(RACE_0_ID);    
       		//vehicle->weapon_slot5.insertItem(lazer_equipment); 
       		RocketEquipment* rocket_equipment = rocketEquipmentGenerator(RACE_0_ID);    
       		vehicle->getWeaponComplex()->weapon_slot5.insertItem(rocket_equipment); 
    	}   
        
    
    
    	RadarEquipment* radar_equipment = radarEquipmentGenerator(RACE_0_ID);    
    	vehicle->radar_slot.insertItem(radar_equipment); 
    
   	DriveEquipment* drive_equipment = driveEquipmentGenerator(RACE_0_ID);    
    	vehicle->drive_slot.insertItem(drive_equipment); 

    	BakEquipment* bak_equipment = bakEquipmentGenerator(RACE_0_ID);    
    	vehicle->bak_slot.insertItem(bak_equipment); 
            
    	EnergizerEquipment* energizer_equipment = energizerEquipmentGenerator(RACE_0_ID);    
    	vehicle->energizer_slot.insertItem(energizer_equipment); 
    
    	ProtectorEquipment* protector_equipment = protectorEquipmentGenerator(RACE_0_ID);    
    	vehicle->protector_slot.insertItem(protector_equipment); 
        
    	DroidEquipment* droid_equipment = droidEquipmentGenerator(RACE_0_ID);    
    	vehicle->droid_slot.insertItem(droid_equipment); 
    
    
    	FreezerEquipment* freezer_equipment = freezerEquipmentGenerator(RACE_0_ID);    
    	vehicle->freezer_slot.insertItem(freezer_equipment);     

    	ScanerEquipment* scaner_equipment = scanerEquipmentGenerator(RACE_0_ID);    
    	vehicle->scaner_slot.insertItem(scaner_equipment); 
    
    	if (vehicle->data_korpus.inhibit_GRAPPLE == false) 
    	{
       		GrappleEquipment* grapple_equipment = grappleEquipmentGenerator(RACE_0_ID);    
       		vehicle->grapple_slot.insertItem(grapple_equipment); 
   	}
    
                             
    	for (unsigned int i = 0; i < 3; i++) 
    	{        
        	LazerEquipment* lazer_equipment = lazerEquipmentGenerator(RACE_0_ID);              
        	vehicle->slot_otsec_vec[i]->insertItem(lazer_equipment);
    	}


    	for (unsigned int i = 3; i < 6; i++) 
    	{        
        	RadarModule* radar_module = radarModuleGenerator();              
        	vehicle->slot_otsec_vec[i]->insertItem(radar_module);
    	}  
    	
    	for (unsigned int i = 6; i < 8; i++) 
    	{        
        	Bomb* bomb_item = getNewBomb();              
        	vehicle->slot_otsec_vec[i]->insertItem(bomb_item);
    	}   
}

