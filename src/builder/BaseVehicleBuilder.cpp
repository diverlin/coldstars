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


BaseVehicleBuilder::BaseVehicleBuilder() {}


BaseVehicleBuilder::~BaseVehicleBuilder() {}

	

void  BaseVehicleBuilder::CreateKorpusGeometry(Vehicle* vehicle)
{
	vehicle->RecalculateCollisionRadius();
	vehicle->createCenter();

    	vehicle->getPoints()->initMainQuadPoints(vehicle->getTexOb()->getFrameWidth(), vehicle->getTexOb()->getFrameHeight());
    	vehicle->getPoints()->addMainQuadPoints();
}

void BaseVehicleBuilder::CreateShieldGeometry(Vehicle* vehicle)
{
    	vehicle->getPoints()->initShieldQuadPoints();
    	vehicle->getPoints()->addShieldQuadPoints();
}
        	

void BaseVehicleBuilder::CreateTrailGeometry(Vehicle* vehicle)
{
    	vehicle->getPoints()->initMidLeftPoint();
    	vehicle->getPoints()->addMidLeftPoint();

    	vehicle->getPoints()->initMidFarLeftPoint();
    	vehicle->getPoints()->addMidFarLeftPoint();
}
        

void BaseVehicleBuilder::CreateGuiKontur(Vehicle* vehicle)
{
	vehicle->SetGuiTextureOb(vehicle->getTexOb());         	

    	float kontur_w, kontur_h;
    	if (vehicle->getTexOb()->getFrameWidth() > vehicle->getTexOb()->getFrameHeight())
    	{
        	kontur_w = 500; 
        	kontur_h = vehicle->getTexOb()->getFrameHeight() * kontur_w / (float)vehicle->getTexOb()->getFrameWidth();
    	}
    	else
    	{
        	kontur_h = 500; 
        	kontur_w = vehicle->getTexOb()->getFrameWidth() * kontur_h / (float)vehicle->getTexOb()->getFrameHeight();
    	}               

    	Rect kontur_rect(0, 0, kontur_w, kontur_h); 
    	kontur_rect.setCenter(SCREEN_WIDTH_MIN/2, SCREEN_HEIGHT_MIN/2); 
	vehicle->SetGuiRect(kontur_rect);
}
        
void BaseVehicleBuilder::CreateEquipmentSlots(Vehicle* vehicle)
{
    	TextureOb* texOb_slot   = g_TEXTURE_MANAGER.getRandomTexOb(SLOT_TEXTURE_ID);  

	ItemSlot* radar_slot       = new ItemSlot(RADAR_SLOT_ID, vehicle, texOb_slot);
				 
	radar_slot->setRect( vehicle->GetGuiRect().getCenter().x + 4*SHIP_SLOT_WIDTH, 
			     vehicle->GetGuiRect().getCenter().y - SHIP_SLOT_HEIGHT/2 + 1.1*SHIP_SLOT_HEIGHT/2,
			     SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
	vehicle->Add(radar_slot);	
	
	
	ItemSlot* scaner_slot      = new ItemSlot(SCANER_SLOT_ID, vehicle, texOb_slot); 

	scaner_slot->setRect(  vehicle->GetGuiRect().getCenter().x + 4*SHIP_SLOT_WIDTH, 
			       vehicle->GetGuiRect().getCenter().y - SHIP_SLOT_HEIGHT/2 - 1.1*SHIP_SLOT_HEIGHT/2,
			       SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
	vehicle->Add(scaner_slot);
	
	
	ItemSlot* energizer_slot   = new ItemSlot(ENERGIZER_SLOT_ID, vehicle, texOb_slot);
	
	energizer_slot->setRect(  vehicle->GetGuiRect().getCenter().x - 2*SHIP_SLOT_WIDTH, 
				  vehicle->GetGuiRect().getCenter().y - SHIP_SLOT_HEIGHT/2,
				  SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
    	vehicle->Add(energizer_slot);
    		
    		
	if (vehicle->data_korpus.inhibit_GRAPPLE == false)
	{
		ItemSlot* grapple_slot  = new ItemSlot(GRAPPLE_SLOT_ID, vehicle, texOb_slot);
				
		grapple_slot->setRect(  vehicle->GetGuiRect().getCenter().x - 3*SHIP_SLOT_WIDTH, 
					vehicle->GetGuiRect().getCenter().y - SHIP_SLOT_HEIGHT/2 + 1.1*SHIP_SLOT_HEIGHT,
					SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
					 
    		vehicle->Add(grapple_slot); 
    	}
    	
    	
	ItemSlot* protector_slot   = new ItemSlot(PROTECTOR_SLOT_ID, vehicle, texOb_slot);
			
	protector_slot->setRect(  vehicle->GetGuiRect().getCenter().x - 3*SHIP_SLOT_WIDTH, 
				  vehicle->GetGuiRect().getCenter().y - SHIP_SLOT_HEIGHT/2 - 1.1*SHIP_SLOT_HEIGHT,
				  SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
    	vehicle->Add(protector_slot); 
	
	
	ItemSlot* droid_slot       = new ItemSlot(DROID_SLOT_ID, vehicle, texOb_slot);
				    
	droid_slot->setRect(  vehicle->GetGuiRect().getCenter().x - 1*SHIP_SLOT_WIDTH, 
			      vehicle->GetGuiRect().getCenter().y - SHIP_SLOT_HEIGHT/2 + 1.1*SHIP_SLOT_HEIGHT,
			      SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
				    
    	vehicle->Add(droid_slot); 
    	
    	
	ItemSlot* freezer_slot     = new ItemSlot(FREEZER_SLOT_ID, vehicle, texOb_slot);
				    
	freezer_slot->setRect( vehicle->GetGuiRect().getCenter().x - 1*SHIP_SLOT_WIDTH, 
			       vehicle->GetGuiRect().getCenter().y - SHIP_SLOT_HEIGHT/2 - 1.1*SHIP_SLOT_HEIGHT,
			       SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
	
	vehicle->Add(freezer_slot);   
	////////////////////////////////////////////////////


    	//////// OTSEC SLOT ////////////////////////////////
    	for (int i = 0; i <= 10; i++)
    	{
         	ItemSlot* otsec_slot = new ItemSlot(CARGO_SLOT_ID, vehicle, texOb_slot);
         		
         	otsec_slot->setRect( vehicle->GetGuiRect().getCenter().x + (i-6) * SHIP_SLOT_WIDTH, 
         			     vehicle->GetGuiRect().getCenter().y - 3*SHIP_SLOT_HEIGHT,
         			     SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
         					
         	vehicle->Add(otsec_slot);         
    	}
    	////////////////////////////////////////////////////


    	//////////// GATE SLOT /////////////////////////////
    	ItemSlot* gate_slot = new ItemSlot(GATE_SLOT_ID, vehicle, texOb_slot);
    			     
    	gate_slot->setRect(  vehicle->GetGuiRect().getCenter().x - 5*SHIP_SLOT_WIDTH, 
    			     vehicle->GetGuiRect().getCenter().y + 3*SHIP_SLOT_HEIGHT,
    			     SHIP_SLOT_WIDTH, SHIP_SLOT_HEIGHT);
    			
    	vehicle->Add(gate_slot);
}	


void BaseVehicleBuilder::CreateDriveComplex(Vehicle* vehicle)
{
    	DriveComplex* drive_complex = new DriveComplex(vehicle);  
    	vehicle->SetDriveComplex(drive_complex);
}

void BaseVehicleBuilder::CreateWeaponsComplex(Vehicle* vehicle)
{
 	WeaponComplex* weapon_complex = new WeaponComplex(vehicle);
 	weapon_complex->postCreateInit(vehicle->data_korpus.weapon_slot_num, vehicle->data_korpus.render_TURRELS);
 	vehicle->SetWeaponComplex(weapon_complex);
}

void BaseVehicleBuilder::CreateProtectionComplex(Vehicle* vehicle)
{
      	TextureOb* texOb_shield = g_TEXTURE_MANAGER.getRandomTexOb(SHIELD_EFFECT_TEXTURE_ID); 
 	ShieldEffect* shield = new ShieldEffect(vehicle, texOb_shield);
 	
 	vehicle->SetShieldEffect(shield);
}
        	
