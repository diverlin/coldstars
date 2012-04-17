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


BaseVehicleBuilder::~BaseVehicleBuilder() {}

	

void  BaseVehicleBuilder::CreateKorpusGeometry(Vehicle* vehicle) const
{
	vehicle->RecalculateCollisionRadius();
	vehicle->GetPoints().CreateCenter();

    	vehicle->GetPoints().initMainQuadPoints(vehicle->GetTextureOb()->getFrameWidth(), vehicle->GetTextureOb()->getFrameHeight());
    	vehicle->GetPoints().addMainQuadPoints();
}


void BaseVehicleBuilder::CreateKorpusGui(Vehicle* vehicle) const
{
	vehicle->SetGuiTextureOb(vehicle->GetTextureOb());         	

    	float kontur_w, kontur_h;
    	if (vehicle->GetTextureOb()->getFrameWidth() > vehicle->GetTextureOb()->getFrameHeight())
    	{
        	kontur_w = 500; 
        	kontur_h = vehicle->GetTextureOb()->getFrameHeight() * kontur_w / (float)vehicle->GetTextureOb()->getFrameWidth();
    	}
    	else
    	{
        	kontur_h = 500; 
        	kontur_w = vehicle->GetTextureOb()->getFrameWidth() * kontur_h / (float)vehicle->GetTextureOb()->getFrameHeight();
    	}               

    	Rect kontur_rect(0, 0, kontur_w, kontur_h); 
    	kontur_rect.setCenter(Config::Instance().SCREEN_WIDTH/2, Config::Instance().SCREEN_HEIGHT/2); 
	vehicle->SetGuiRect(kontur_rect);
}
        
void BaseVehicleBuilder::CreateEquipmentSlots(Vehicle* vehicle) const
{
    	TextureOb* texOb_slot   = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::SLOT_ID);  

	ItemSlot* radar_slot = new ItemSlot();
	radar_slot->SetSubTypeId(SLOT::RADAR_ID);
	radar_slot->SetTextureOb(texOb_slot);
	radar_slot->SetOwnerVehicle(vehicle);				 
	radar_slot->SetRect( vehicle->GetGuiRect().getCenter().x + 4*GUI::SLOT::WIDTH_FOR_SHIP, 
			     vehicle->GetGuiRect().getCenter().y - GUI::SLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::SLOT::HEIGHT_FOR_SHIP/2,
			     GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
	vehicle->Add(radar_slot);	
	
	
	ItemSlot* scaner_slot = new ItemSlot();
	scaner_slot->SetSubTypeId(SLOT::SCANER_ID); 
	scaner_slot->SetTextureOb(texOb_slot);
	scaner_slot->SetOwnerVehicle(vehicle);
	scaner_slot->SetRect(  vehicle->GetGuiRect().getCenter().x + 4*GUI::SLOT::WIDTH_FOR_SHIP, 
			       vehicle->GetGuiRect().getCenter().y - GUI::SLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::SLOT::HEIGHT_FOR_SHIP/2,
			       GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
	vehicle->Add(scaner_slot);
	
	
	ItemSlot* energizer_slot = new ItemSlot();
	energizer_slot->SetSubTypeId(SLOT::ENERGIZER_ID); 
	energizer_slot->SetTextureOb(texOb_slot);
	energizer_slot->SetOwnerVehicle(vehicle);
	energizer_slot->SetRect(  vehicle->GetGuiRect().getCenter().x - 2*GUI::SLOT::WIDTH_FOR_SHIP, 
				  vehicle->GetGuiRect().getCenter().y - GUI::SLOT::HEIGHT_FOR_SHIP/2,
				  GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
	vehicle->Add(energizer_slot);
    		
    		
	if (vehicle->data_korpus.inhibit_GRAPPLE == false)
	{
		ItemSlot* grapple_slot = new ItemSlot();
		grapple_slot->SetSubTypeId(SLOT::GRAPPLE_ID);
		grapple_slot->SetTextureOb(texOb_slot);
		grapple_slot->SetOwnerVehicle(vehicle);
		grapple_slot->SetRect(  vehicle->GetGuiRect().getCenter().x - 3*GUI::SLOT::WIDTH_FOR_SHIP, 
					vehicle->GetGuiRect().getCenter().y - GUI::SLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::SLOT::HEIGHT_FOR_SHIP,
					GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);					 
    		vehicle->Add(grapple_slot); 
    	}
    	
    	
	
	ItemSlot* droid_slot = new ItemSlot();
	droid_slot->SetSubTypeId(SLOT::DROID_ID);
	droid_slot->SetTextureOb(texOb_slot);
	droid_slot->SetOwnerVehicle(vehicle);			    
	droid_slot->SetRect(  vehicle->GetGuiRect().getCenter().x - 1*GUI::SLOT::WIDTH_FOR_SHIP, 
			      vehicle->GetGuiRect().getCenter().y - GUI::SLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::SLOT::HEIGHT_FOR_SHIP,
			      GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);				    
    	vehicle->Add(droid_slot); 
    	
    	
	ItemSlot* freezer_slot     = new ItemSlot();
	freezer_slot->SetSubTypeId(SLOT::FREEZER_ID);
	freezer_slot->SetTextureOb(texOb_slot);
	freezer_slot->SetOwnerVehicle(vehicle);			    
	freezer_slot->SetRect( vehicle->GetGuiRect().getCenter().x - 1*GUI::SLOT::WIDTH_FOR_SHIP, 
			       vehicle->GetGuiRect().getCenter().y - GUI::SLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::SLOT::HEIGHT_FOR_SHIP,
			       GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);	
	vehicle->Add(freezer_slot);   
	////////////////////////////////////////////////////


    	//////// OTSEC SLOT ////////////////////////////////
    	for (int i = 0; i <= 10; i++)
    	{
         	ItemSlot* otsec_slot = new ItemSlot();
         	otsec_slot->SetSubTypeId(SLOT::CARGO_ID);
         	otsec_slot->SetTextureOb(texOb_slot);
         	otsec_slot->SetOwnerVehicle(vehicle);
         	otsec_slot->SetRect( vehicle->GetGuiRect().getCenter().x + (i-6) * GUI::SLOT::WIDTH_FOR_SHIP, 
         			     vehicle->GetGuiRect().getCenter().y - 3*GUI::SLOT::HEIGHT_FOR_SHIP,
         			     GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);         					
         	vehicle->Add(otsec_slot);         
    	}
    	////////////////////////////////////////////////////


    	//////////// GATE SLOT /////////////////////////////
    	ItemSlot* gate_slot = new ItemSlot();
    	gate_slot->SetSubTypeId(SLOT::GATE_ID);
    	gate_slot->SetTextureOb(texOb_slot);
        gate_slot->SetOwnerVehicle(vehicle);    			     
    	gate_slot->SetRect(  vehicle->GetGuiRect().getCenter().x - 5*GUI::SLOT::WIDTH_FOR_SHIP, 
    			     vehicle->GetGuiRect().getCenter().y + 3*GUI::SLOT::HEIGHT_FOR_SHIP,
    			     GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
    			
    	vehicle->Add(gate_slot);
}	


void BaseVehicleBuilder::CreateDriveComplex(Vehicle* vehicle) const
{
    	vehicle->GetPoints().initMidLeftPoint();
    	vehicle->GetPoints().addMidLeftPoint();

    	vehicle->GetPoints().initMidFarLeftPoint();
    	vehicle->GetPoints().addMidFarLeftPoint();
    	
    	DriveComplex* drive_complex = new DriveComplex(vehicle);  
    	vehicle->SetDriveComplex(drive_complex);
}

void BaseVehicleBuilder::CreateWeaponsComplex(Vehicle* vehicle) const
{
 	WeaponComplex* weapon_complex = new WeaponComplex(vehicle);
 	weapon_complex->PostCreateInit(vehicle->data_korpus.weapon_slot_num, vehicle->data_korpus.render_TURRELS);
 	vehicle->SetWeaponComplex(weapon_complex);
}

void BaseVehicleBuilder::CreateProtectionComplex(Vehicle* vehicle) const
{
    	vehicle->GetPoints().initShieldQuadPoints();
    	vehicle->GetPoints().addShieldQuadPoints();
    	
	ProtectionComplex* protection_complex = new ProtectionComplex(vehicle); 	
 	vehicle->SetProtectionComplex(protection_complex);
}
        	


void BaseVehicleBuilder::Equip(Vehicle* vehicle) const
{
    	if (vehicle->data_korpus.weapon_slot_num >= 1)
    	{
       		//vehicle->weapon_slot1.InsertItem(lazerEquipmentGenerator(RACE_0_ID)); 
       		vehicle->GetWeaponComplex()->GetWeaponSlot1().InsertItem(GetNewRocketEquipment(RACE::R0_ID));     	
    	}   

    	if (vehicle->data_korpus.weapon_slot_num >= 2)
    	{
       		vehicle->GetWeaponComplex()->GetWeaponSlot2().InsertItem(GetNewLazerEquipment(RACE::R0_ID)); 
    	}   
    
    	if (vehicle->data_korpus.weapon_slot_num >= 3)
    	{
       		vehicle->GetWeaponComplex()->GetWeaponSlot3().InsertItem(GetNewLazerEquipment(RACE::R0_ID)); 
       		//vehicle->weapon_slot3.InsertItem(rocketEquipmentGenerator(RACE_0_ID)); 
    	}   
        
    	if (vehicle->data_korpus.weapon_slot_num >= 4)
    	{
       		//vehicle->weapon_slot4.InsertItem(lazerEquipmentGenerator(RACE_0_ID));         
       		vehicle->GetWeaponComplex()->GetWeaponSlot4().InsertItem(GetNewRocketEquipment(RACE::R0_ID)); 
    	}   
    
    	if (vehicle->data_korpus.weapon_slot_num >= 5) 
    	{
       		//vehicle->weapon_slot5.InsertItem(lazerEquipmentGenerator(RACE_0_ID)); 
       		vehicle->GetWeaponComplex()->GetWeaponSlot5().InsertItem(GetNewRocketEquipment(RACE::R0_ID)); 
    	}   
        
    	vehicle->GetRadarSlot()->InsertItem(GetNewRadarEquipment(RACE::R0_ID)); 
 
    	vehicle->GetDriveComplex()->GetDriveSlot().InsertItem(GetNewDriveEquipment(RACE::R0_ID)); 
    	vehicle->GetDriveComplex()->GetBakSlot().InsertItem(GetNewBakEquipment(RACE::R0_ID)); 
    	vehicle->GetEnergizerSlot()->InsertItem(GetNewEnergizerEquipment(RACE::R0_ID));     
    	vehicle->GetProtectionComplex()->GetProtectorSlot().InsertItem(GetNewProtectorEquipment(RACE::R0_ID)); 
   	vehicle->GetDroidSlot()->InsertItem(GetNewDroidEquipment(RACE::R0_ID)); 
   	vehicle->GetFreezerSlot()->InsertItem(GetNewFreezerEquipment(RACE::R0_ID));  
   	vehicle->GetScanerSlot()->InsertItem(GetNewScanerEquipment(RACE::R0_ID)); 
    
    	if (vehicle->data_korpus.inhibit_GRAPPLE == false) 
    	{
      		vehicle->GetGrappleSlot()->InsertItem(GetNewGrappleEquipment(RACE::R0_ID)); 
   	}
    
                             
    	for (unsigned int i = 0; i < 3; i++) 
    	{        
                vehicle->AddItemToOtsec(GetNewLazerEquipment(RACE::R0_ID));
    	}


    	for (unsigned int i = 0; i < 3; i++) 
    	{        
        	vehicle->AddItemToOtsec(GetNewRadarModule());
    	}  
    	
    	for (unsigned int i = 0; i < 3; i++) 
    	{        
                vehicle->AddItemToOtsec(GetNewBomb());
    	}   
    	
    	vehicle->UpdateAllPropertiesAndAbilities(); 
}







