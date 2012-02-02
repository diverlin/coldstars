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
        data_id.id      = g_SHIP_ID_GENERATOR.getNextId(); 
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
    	
    	ship->getPoints()->setCenter(getRandInt(0, 800), getRandInt(0, 800)); 
    	ship->getPoints()->setAngle(getRandInt(0, 360));   
    	ship->getPoints()->update();   
    	    	 	
    	ship->getNavigator()->setStaticTargetCoords(vec2f(getRandInt(0, 1200), getRandInt(0, 1200)));    	
    	    
    	return ship;
}




void equip(Ship* ship)
{
    	if (ship->data_korpus.weapon_slot_num >= 1)
    	{
       		//LazerEquipment* pTo_lazer1 = lazerEquipmentGenerator(RACE_0_ID);    
       		//ship->weapon_slot1.insertItem(pTo_lazer1); 
    	       	RocketEquipment* rocket1 = rocketEquipmentGenerator(RACE_0_ID);    
       		ship->getWeaponComplex()->weapon_slot1.insertItem(rocket1); 
    	
    	}   

    	if (ship->data_korpus.weapon_slot_num >= 2)
    	{
       		LazerEquipment* pTo_lazer2 = lazerEquipmentGenerator(RACE_0_ID);    
       		ship->getWeaponComplex()->weapon_slot2.insertItem(pTo_lazer2); 
    	}   
    
    	if (ship->data_korpus.weapon_slot_num >= 3)
    	{
       		LazerEquipment* pTo_lazer3 = lazerEquipmentGenerator(RACE_0_ID);    
       		ship->getWeaponComplex()->weapon_slot3.insertItem(pTo_lazer3); 
       		//RocketEquipment* rocket3 = rocketEquipmentGenerator(RACE_0_ID);    
       		//ship->weapon_slot3.insertItem(rocket3); 
    	}   
        
    	if (ship->data_korpus.weapon_slot_num >= 4)
    	{
       		//LazerEquipment* pTo_lazer4 = lazerEquipmentGenerator(RACE_0_ID);    
       		//ship->weapon_slot4.insertItem(pTo_lazer4);         
       		RocketEquipment* rocket4 = rocketEquipmentGenerator(RACE_0_ID);    
       		ship->getWeaponComplex()->weapon_slot4.insertItem(rocket4); 
    	}   
    
    	if (ship->data_korpus.weapon_slot_num >= 5) 
    	{
       		//LazerEquipment* pTo_lazer5 = lazerEquipmentGenerator(RACE_0_ID);    
       		//ship->weapon_slot5.insertItem(pTo_lazer5); 
       		RocketEquipment* rocket5 = rocketEquipmentGenerator(RACE_0_ID);    
       		ship->getWeaponComplex()->weapon_slot5.insertItem(rocket5); 
    	}   
        
    
    
    	RadarEquipment* pTo_radar = radarEquipmentGenerator(RACE_0_ID);    
    	ship->radar_slot.insertItem(pTo_radar); 
    
   	DriveEquipment* pTo_drive = driveEquipmentGenerator(RACE_0_ID);    
    	ship->drive_slot.insertItem(pTo_drive); 

    	BakEquipment* pTo_bak = bakEquipmentGenerator(RACE_0_ID);    
    	ship->bak_slot.insertItem(pTo_bak); 
            
    	EnergizerEquipment* pTo_energizer = energizerEquipmentGenerator(RACE_0_ID);    
    	ship->energizer_slot.insertItem(pTo_energizer); 
    
    	ProtectorEquipment* pTo_protector = protectorEquipmentGenerator(RACE_0_ID);    
    	ship->protector_slot.insertItem(pTo_protector); 
        
    	DroidEquipment* pTo_droid = droidEquipmentGenerator(RACE_0_ID);    
    	ship->droid_slot.insertItem(pTo_droid); 
    
    
    	FreezerEquipment* pTo_freezer = freezerEquipmentGenerator(RACE_0_ID);    
    	ship->freezer_slot.insertItem(pTo_freezer);     

    	ScanerEquipment* pTo_scaner = scanerEquipmentGenerator(RACE_0_ID);    
    	ship->scaner_slot.insertItem(pTo_scaner); 
    
    	if (ship->data_korpus.inhibit_GRAPPLE == false) 
    	{
       		GrappleEquipment* pTo_grapple = grappleEquipmentGenerator(RACE_0_ID);    
       		ship->grapple_slot.insertItem(pTo_grapple); 
   	}
    
                             
    	for (unsigned int i = 0; i < 3; i++) 
    	{        
        	LazerEquipment* lazer_equipment = lazerEquipmentGenerator(RACE_0_ID);              
        	ship->slot_otsec_vec[i]->insertItem(lazer_equipment);
    	}


    	for (unsigned int i = 3; i < 6; i++) 
    	{        
        	RadarModule* radar_module = radarModuleGenerator();              
        	ship->slot_otsec_vec[i]->insertItem(radar_module);
    	}  
    	
    	for (unsigned int i = 6; i < 8; i++) 
    	{        
        	Bomb* bomb = getNewBomb();              
        	ship->slot_otsec_vec[i]->insertItem(bomb);
    	}   
}

