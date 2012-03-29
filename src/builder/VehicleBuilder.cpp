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


Ship* VehicleBuilder::GetNewShip(int race_id, int subtype_id, int size_id, int weapons_num)
{
    	TextureOb* texOb = g_TEXTURE_MANAGER.getRandomShipTexObWithFollowingAtrributes(race_id, subtype_id, size_id); 
       
       	int protection_rate = 1;
       	if (subtype_id == CLASS::WARRIOR_ID)
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
       
        IdData data_id;
        data_id.id         = g_ID_GENERATOR.getNextId(); 
    	data_id.type_id    = ENTITY::SHIP_ID;
    	data_id.subtype_id = subtype_id;       

        LifeData data_life;
        data_life.armor      = data_korpus.armor;
        data_life.dying_time = 10*texOb->size_id;
        
        int size_threshold = 2; 
    	if (texOb->size_id > size_threshold)
       		data_korpus.render_TURRELS = true; 
    	else
       		data_korpus.render_TURRELS = false; 
       		
	Ship* ship = new Ship();
	ship->SetKorpusData(data_korpus);
	ship->SetTextureOb(texOb);
	ship->SetIdData(data_id);
	ship->SetLifeData(data_life);
	
	CreateKorpusGeometry(ship);
        CreateKorpusGui(ship);
        CreateEquipmentSlots(ship);
        CreateDriveComplex(ship);
        CreateWeaponsComplex(ship);
        CreateProtectionComplex(ship);	
        
        GetEntityManager().RegisterEntity(ship);
        
        return ship;
}

Satellite* VehicleBuilder::GetNewSatellite()
{
	TextureOb* texOb = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::SATELLITE_ID);  
	
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

        data_korpus.inhibit_GRAPPLE = true;
        data_korpus.weapon_slot_num = 2;
       
        IdData data_id;
        data_id.id         = g_ID_GENERATOR.getNextId(); 
    	data_id.type_id    = ENTITY::SATELLITE_ID;
    	data_id.subtype_id = NONE_ID;       

        LifeData data_life;
        data_life.armor      = data_korpus.armor;
        data_life.dying_time = 10*texOb->size_id;
        
        int size_threshold = 2; 
	data_korpus.render_TURRELS = true;       

	Satellite* satellite = new Satellite();
	satellite->SetKorpusData(data_korpus);
	satellite->SetIdData(data_id);
	satellite->SetLifeData(data_life);
	satellite->SetTextureOb(texOb);
	
	CreateKorpusGeometry(satellite);
        CreateKorpusGui(satellite);
        CreateEquipmentSlots(satellite);
        CreateDriveComplex(satellite);
        CreateWeaponsComplex(satellite);
        CreateProtectionComplex(satellite);	
        
        GetEntityManager().RegisterEntity(satellite);
	
	return satellite;

}

SpaceStation* VehicleBuilder::GetNewSpaceStation()
{
	TextureOb* texOb = g_TEXTURE_MANAGER.getRandomTexOb(TEXTURE::SPACESTATION_ID); 
       
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

        data_korpus.inhibit_GRAPPLE = false;
        data_korpus.weapon_slot_num = 5;
       
        IdData data_id;
        data_id.id         = g_ID_GENERATOR.getNextId(); 
    	data_id.type_id    = ENTITY::SPACESTATION_ID;
    	data_id.subtype_id = SPACESTATION::MILITARY_ID;       

        LifeData data_life;
        data_life.armor      = data_korpus.armor;
        data_life.dying_time = 10*texOb->size_id;
        
        int size_threshold = 2; 
	data_korpus.render_TURRELS = true; 
                           
    	SpaceStation* spacestation = new SpaceStation(RACE::R0_ID);
    	spacestation->SetKorpusData(data_korpus);
	spacestation->SetTextureOb(texOb);
	spacestation->SetIdData(data_id);
	spacestation->SetLifeData(data_life);
    	
	CreateKorpusGeometry(spacestation);
        CreateKorpusGui(spacestation);
        CreateEquipmentSlots(spacestation);
        CreateDriveComplex(spacestation);
        CreateWeaponsComplex(spacestation);
        CreateProtectionComplex(spacestation);	
        
    	spacestation->createLand(RACE::R0_ID);
    	    
    	return spacestation;
}


RocketBullet* VehicleBuilder::GetNewRocket(BulletData data_bullet, ItemSlot* slot, float offset, bool force_center_start)
{
	IdData data_id;
	data_id.id         = g_ID_GENERATOR.getNextId(); 
	data_id.type_id    = ENTITY::ROCKET_ID;
	data_id.subtype_id = NONE_ID;

	LifeData data_life;	
	data_life.is_alive      = true;
        data_life.garbage_ready = false;
        data_life.armor = data_bullet.armor;        

    	RocketBullet* rocket = new RocketBullet(data_bullet, slot->GetTurrel()->getTarget(), slot->GetOwnerVehicle()->GetId());
         
        rocket->SetIdData(data_id);
        rocket->SetLifeData(data_life);
        rocket->SetTextureOb(data_bullet.texOb);
         
        CreateKorpusGeometry(rocket);
        //CreateShieldGeometry(rocket);
        //CreateGuiKontur(rocket);
        //CreateEquipmentSlots(rocket);
        CreateDriveComplex(rocket);
        //CreateWeaponsComplex(rocket);
        //CreateProtectionComplex(rocket);	
         
        if ( (slot->GetOwnerVehicle()->data_korpus.render_TURRELS == true) and (force_center_start == false))
    	{
        	rocket->place(slot->GetTurrel()->getPoints()->getCenter(), slot->GetTurrel()->getPoints()->getAngleDegree(), offset);
        }
        else
    	{
         	rocket->place(slot->GetOwnerVehicle()->GetPoints().getCenter(), slot->GetOwnerVehicle()->GetPoints().getAngleDegree(), offset);
    	}
        return rocket;
}
