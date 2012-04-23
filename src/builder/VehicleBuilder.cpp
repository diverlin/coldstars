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


VehicleBuilder& VehicleBuilder::Instance()
{	
	static VehicleBuilder instance;
	return instance;
}	


VehicleBuilder::~VehicleBuilder() {}


//Ship* VehicleBuilder::GetNewShip(int race_id, int subtype_id, int size_id, int weapons_num, int id) const
//{
	//if (id == NONE_ID)
	//{
		//id = g_ID_GENERATOR.getNextId();
	//}
        //Ship* ship = new Ship(id);
        //EntityManager::Instance().RegisterEntity(ship);
                
    	//TextureOb* texOb = g_TEXTURE_MANAGER.getRandomShipTexObWithFollowingAtrributes(race_id, subtype_id, size_id); 
       
       	//int protection_rate = 1;
       	//if (subtype_id == CLASS::WARRIOR_ID)
        //{
        	//protection_rate = 3;
        //}
        
        //KorpusData data_korpus;
    	//data_korpus.space       = size_id*150 + getRandInt(0, 100);
    	//data_korpus.armor       = data_korpus.space;
    	//data_korpus.protection  = size_id/2*protection_rate;
    	//data_korpus.temperature = 100;
        //data_korpus.price       = getRandInt(200, 400)*size_id;

        //data_korpus.slot_grapple_num = 1;
        //data_korpus.slot_weapon_num  = weapons_num;
       

    	
        //LifeData data_life;
        //data_life.armor      = data_korpus.armor;
        //data_life.dying_time = 10*texOb->size_id;
        
        //int size_threshold = 2; 
    	//if (texOb->size_id > size_threshold)
       		//data_korpus.render_TURRELS = true; 
    	//else
       		//data_korpus.render_TURRELS = false; 
	
	//ship->SetSubTypeId(subtype_id);
	//ship->SetKorpusData(data_korpus);
	//ship->SetTextureOb(texOb);
	//ship->SetLifeData(data_life);
	
	//CreateKorpusGeometry(ship);
        //CreateKorpusGui(ship);
        //CreateEquipmentSlots(ship);
        //CreateDriveComplex(ship);
        //CreateWeaponsComplex(ship);
        //CreateProtectionComplex(ship);
        
        //return ship;
//}

Satellite* VehicleBuilder::GetNewSatellite(int id) const
{
        if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
	}
        Satellite* satellite = new Satellite(id);
        EntityManager::Instance().RegisterEntity(satellite);
        
	TextureOb* texOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::SATELLITE_ID);  
	
       	int protection_rate = 1;
       	//if (subtype_id == CLASS::WARRIOR_ID)
        //{
        	protection_rate = 1;
        //}
        
        KorpusData data_korpus;
    	data_korpus.space       = 60 + getRandInt(0, 20);
    	data_korpus.armor       = 10*data_korpus.space;
    	data_korpus.protection  = 2*protection_rate;
    	data_korpus.temperature = 100;
        data_korpus.price       = 1000;

        data_korpus.slot_grapple_num = 1;
        data_korpus.slot_weapon_num  = 2;
 
        LifeData data_life;
        data_life.armor      = data_korpus.armor;
        data_life.dying_time = 10*texOb->size_id;
        
        int size_threshold = 2; 
	data_korpus.draw_turrels = true;       
	
	satellite->SetKorpusData(data_korpus);
	satellite->SetLifeData(data_life);
	satellite->SetTextureOb(texOb);
	
	CreateKorpusGeometry(satellite);
        CreateKorpusGui(satellite);
        CreateEquipmentSlots(satellite);
        CreateDriveComplex(satellite);
        CreateWeaponsComplex(satellite);
        CreateProtectionComplex(satellite);	
	
	return satellite;

}

SpaceStation* VehicleBuilder::GetNewSpaceStation(int id) const
{	
        if (id == NONE_ID)
	{
		id = g_ID_GENERATOR.getNextId();
	}
        SpaceStation* spacestation = new SpaceStation(id, RACE::R0_ID);
        EntityManager::Instance().RegisterEntity(spacestation);
                        
	TextureOb* texOb = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::SPACESTATION_ID); 
       
       	int protection_rate = 1;
       	//if (subtype_id == CLASS::WARRIOR_ID)
        //{
        	protection_rate = 5;
        //}
        
        KorpusData data_korpus;
    	data_korpus.space       = 2500 + getRandInt(0, 1000);
    	data_korpus.armor       = data_korpus.space;
    	data_korpus.protection  = 2*protection_rate;
    	data_korpus.temperature = 100;
        data_korpus.price       = 10000000;

        data_korpus.slot_grapple_num = 1;
        data_korpus.slot_weapon_num  = 5;
       
        LifeData data_life;
        data_life.armor      = data_korpus.armor;
        data_life.dying_time = 10*texOb->size_id;
        
        int size_threshold = 2; 
	data_korpus.draw_turrels = true; 
                           
    	spacestation->SetSubTypeId(SPACESTATION::MILITARY_ID);
    	spacestation->SetKorpusData(data_korpus);
	spacestation->SetTextureOb(texOb);
	spacestation->SetLifeData(data_life);
    	
	CreateKorpusGeometry(spacestation);
        CreateKorpusGui(spacestation);
        CreateEquipmentSlots(spacestation);
        CreateDriveComplex(spacestation);
        CreateWeaponsComplex(spacestation);
        CreateProtectionComplex(spacestation);	
        
    	spacestation->CreateLand(RACE::R0_ID);
    	    
    	return spacestation;
}


RocketBullet* VehicleBuilder::GetNewRocket(BulletData data_bullet, ItemSlot* slot, float offset, bool force_center_start) const
{
	IdData data_id;
	int id         = g_ID_GENERATOR.getNextId(); 

	LifeData data_life;	
	data_life.is_alive      = true;
        data_life.garbage_ready = false;
        data_life.armor = data_bullet.armor;        

    	RocketBullet* rocket = new RocketBullet(id, data_bullet, slot->GetTurrel()->GetTarget(), slot->GetOwnerVehicle()->GetId());
         
        rocket->SetLifeData(data_life);
        rocket->SetTextureOb(data_bullet.texOb);
         
        CreateKorpusGeometry(rocket);
        //CreateShieldGeometry(rocket);
        //CreateGuiKontur(rocket);
        //CreateEquipmentSlots(rocket);
        CreateDriveComplex(rocket);
        //CreateWeaponsComplex(rocket);
        //CreateProtectionComplex(rocket);	
         
        if ( (slot->GetOwnerVehicle()->data_korpus.draw_turrels == true) and (force_center_start == false))
    	{
        	rocket->place(slot->GetTurrel()->GetPoints().getCenter(), slot->GetTurrel()->GetPoints().getAngleDegree(), offset);
        }
        else
    	{
         	rocket->place(slot->GetOwnerVehicle()->GetPoints().getCenter(), slot->GetOwnerVehicle()->GetPoints().getAngleDegree(), offset);
    	}
        return rocket;
}
