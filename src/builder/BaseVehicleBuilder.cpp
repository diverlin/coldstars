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


void BaseVehicleBuilder::CreateKorpusGeometry(Vehicle* vehicle) const
{
	vehicle->RecalculateCollisionRadius();

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
    		vehicle->data_korpus.gui_scale = (float)kontur_w/vehicle->GetTextureOb()->getFrameWidth();
        	kontur_h = vehicle->GetTextureOb()->getFrameHeight() * kontur_w / (float)vehicle->GetTextureOb()->getFrameWidth();
    	}
    	else
    	{
        	kontur_h = 500; 
    		vehicle->data_korpus.gui_scale = (float)kontur_h/vehicle->GetTextureOb()->getFrameHeight();
        	kontur_w = vehicle->GetTextureOb()->getFrameWidth() * kontur_h / (float)vehicle->GetTextureOb()->getFrameHeight();
    	}               

    	Rect kontur_rect(0, 0, kontur_w, kontur_h); 
    	kontur_rect.SetCenter(Config::Instance().SCREEN_WIDTH/2, Config::Instance().SCREEN_HEIGHT/2); 
	vehicle->SetGuiRect(kontur_rect);
}
        
void BaseVehicleBuilder::CreateEquipmentSlots(Vehicle* vehicle) const
{        
	Rect rect;

        // WEAPON SLOTS
        for (unsigned int i = 0; i<vehicle->data_korpus.slot_weapon_num; i++)
        {
        	ItemSlot* weapon_slot = GetNewItemSlot(SLOT::WEAPON_ID);
        	rect = Rect(vehicle->GetGuiRect().GetBottomLeft().x + 1.1*i*GUI::SLOT::WIDTH_FOR_SHIP, 
                             	  vehicle->GetGuiRect().GetBottomLeft().y -1*GUI::SLOT::HEIGHT_FOR_SHIP/2,
       			     	  GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);        
        	vehicle->AddSlot(weapon_slot, rect);
        }
        //
                
	ItemSlot* radar_slot = GetNewItemSlot(SLOT::RADAR_ID);
        rect = Rect(vehicle->GetGuiRect().GetCenter().x+4*GUI::SLOT::WIDTH_FOR_SHIP, 
			  vehicle->GetGuiRect().GetCenter().y-1*GUI::SLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::SLOT::HEIGHT_FOR_SHIP/2,
			  GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
	vehicle->AddSlot(radar_slot, rect);
	
	
	ItemSlot* scaner_slot = GetNewItemSlot(SLOT::SCANER_ID); 
	rect = Rect(vehicle->GetGuiRect().GetCenter().x+4*GUI::SLOT::WIDTH_FOR_SHIP, 
			  vehicle->GetGuiRect().GetCenter().y-1*GUI::SLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::SLOT::HEIGHT_FOR_SHIP/2,
			  GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
	vehicle->AddSlot(scaner_slot, rect);
	
	
	ItemSlot* energizer_slot = GetNewItemSlot(SLOT::ENERGIZER_ID); 
	rect = Rect(vehicle->GetGuiRect().GetCenter().x-2*GUI::SLOT::WIDTH_FOR_SHIP, 
			  vehicle->GetGuiRect().GetCenter().y-1*GUI::SLOT::HEIGHT_FOR_SHIP/2,
			  GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
	vehicle->AddSlot(energizer_slot, rect);
    		
    		
	if (vehicle->data_korpus.slot_grapple_num != 0)
	{
		ItemSlot* grapple_slot = GetNewItemSlot(SLOT::GRAPPLE_ID);
		rect = Rect(vehicle->GetGuiRect().GetCenter().x-3*GUI::SLOT::WIDTH_FOR_SHIP, 
                                  vehicle->GetGuiRect().GetCenter().y-GUI::SLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::SLOT::HEIGHT_FOR_SHIP,
                                  GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);					 
    		vehicle->AddSlot(grapple_slot, rect); 
    	}
    	
	ItemSlot* droid_slot = GetNewItemSlot(SLOT::DROID_ID);
	rect = Rect(vehicle->GetGuiRect().GetCenter().x-1*GUI::SLOT::WIDTH_FOR_SHIP, 
			  vehicle->GetGuiRect().GetCenter().y-1*GUI::SLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::SLOT::HEIGHT_FOR_SHIP,
			  GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);				    
    	vehicle->AddSlot(droid_slot, rect); 
    	
    	
	ItemSlot* freezer_slot = GetNewItemSlot(SLOT::FREEZER_ID);
	rect = Rect(vehicle->GetGuiRect().GetCenter().x-1*GUI::SLOT::WIDTH_FOR_SHIP, 
			  vehicle->GetGuiRect().GetCenter().y-1*GUI::SLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::SLOT::HEIGHT_FOR_SHIP,
			  GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);	
	vehicle->AddSlot(freezer_slot, rect);   
        
        
        ItemSlot* protector_slot = GetNewItemSlot(SLOT::PROTECTOR_ID); 
	rect = Rect(vehicle->GetGuiRect().GetCenter().x-3*GUI::SLOT::WIDTH_FOR_SHIP, 
			  vehicle->GetGuiRect().GetCenter().y-1*GUI::SLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::SLOT::HEIGHT_FOR_SHIP,
			  GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);	    
    	vehicle->AddSlot(protector_slot, rect); 
        
        
        ItemSlot* drive_slot = GetNewItemSlot(SLOT::DRIVE_ID); 
	rect = Rect(vehicle->GetGuiRect().GetCenter().x-5*GUI::SLOT::WIDTH_FOR_SHIP, 
			  vehicle->GetGuiRect().GetCenter().y-1*GUI::SLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::SLOT::HEIGHT_FOR_SHIP/2,
                          GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
	vehicle->AddSlot(drive_slot, rect);
	
	
        ItemSlot* bak_slot = GetNewItemSlot(SLOT::BAK_ID);  
	rect = Rect(vehicle->GetGuiRect().GetCenter().x-5*GUI::SLOT::WIDTH_FOR_SHIP, 
			  vehicle->GetGuiRect().GetCenter().y-1*GUI::SLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::SLOT::HEIGHT_FOR_SHIP/2,
			  GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
	vehicle->AddSlot(bak_slot, rect);
	////////////////////////////////////////////////////


    	//////// OTSEC SLOT ////////////////////////////////
    	for (int i = 0; i <= 10; i++)
    	{
         	ItemSlot* otsec_slot = GetNewItemSlot(SLOT::CARGO_ID);
         	rect = Rect(vehicle->GetGuiRect().GetCenter().x+(i-6)*GUI::SLOT::WIDTH_FOR_SHIP, 
         			  vehicle->GetGuiRect().GetCenter().y    -3*GUI::SLOT::HEIGHT_FOR_SHIP,
         			  GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);         					
         	vehicle->AddSlot(otsec_slot, rect);         
    	}
    	////////////////////////////////////////////////////


    	//////////// GATE SLOT /////////////////////////////
    	ItemSlot* gate_slot = GetNewItemSlot(SLOT::GATE_ID);
   	rect = Rect(vehicle->GetGuiRect().GetCenter().x-5*GUI::SLOT::WIDTH_FOR_SHIP, 
    			  vehicle->GetGuiRect().GetCenter().y+3*GUI::SLOT::HEIGHT_FOR_SHIP,
    			  GUI::SLOT::WIDTH_FOR_SHIP, GUI::SLOT::HEIGHT_FOR_SHIP);
    	vehicle->AddSlot(gate_slot, rect);
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
 	weapon_complex->PostCreateInit(vehicle->data_korpus.slot_weapon_num, vehicle->data_korpus.draw_turrels);
 	vehicle->SetWeaponComplex(weapon_complex);
}

void BaseVehicleBuilder::CreateProtectionComplex(Vehicle* vehicle) const
{
	ProtectionComplex* protection_complex = new ProtectionComplex(vehicle); 	
 	vehicle->SetProtectionComplex(protection_complex);
}

void BaseVehicleBuilder::Equip(Vehicle* vehicle) const
{
    	for (unsigned int i = 0; i<vehicle->data_korpus.slot_weapon_num; i++)
    	{
    	    	//RocketEquipmentBuilder::Instance().CreateNewRocketEquipment();
        	//RocketEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID); 
       		//vehicle->GetWeaponComplex()->Add(RocketEquipmentBuilder::Instance().GetRocketEquipment());

    	        LazerEquipmentBuilder::Instance().CreateNewLazerEquipment();
        	LazerEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID); 
       		vehicle->GetWeaponComplex()->Add(LazerEquipmentBuilder::Instance().GetLazerEquipment()); 
    	}   
           
        RadarEquipmentBuilder::Instance().CreateNewRadarEquipment();
        RadarEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID); 
    	vehicle->GetRadarSlot()->InsertItem(RadarEquipmentBuilder::Instance().GetRadarEquipment()); 

        DriveEquipmentBuilder::Instance().CreateNewDriveEquipment();
        DriveEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID); 
    	vehicle->GetDriveComplex()->GetDriveSlot()->InsertItem(DriveEquipmentBuilder::Instance().GetDriveEquipment()); 
        
        BakEquipmentBuilder::Instance().CreateNewBakEquipment();
        BakEquipmentBuilder::Instance().CreateNewInternals();
    	vehicle->GetDriveComplex()->GetBakSlot()->InsertItem(BakEquipmentBuilder::Instance().GetBakEquipment()); 
        
        EnergizerEquipmentBuilder::Instance().CreateNewEnergizerEquipment();
        EnergizerEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
    	vehicle->GetEnergizerSlot()->InsertItem(EnergizerEquipmentBuilder::Instance().GetEnergizerEquipment());     

   	ProtectorEquipmentBuilder::Instance().CreateNewProtectorEquipment();
        ProtectorEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
   	vehicle->GetProtectionComplex()->GetProtectorSlot()->InsertItem(ProtectorEquipmentBuilder::Instance().GetProtectorEquipment()); 
   	
   	DroidEquipmentBuilder::Instance().CreateNewDroidEquipment();
        DroidEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
   	vehicle->GetDroidSlot()->InsertItem(DroidEquipmentBuilder::Instance().GetDroidEquipment()); 

   	FreezerEquipmentBuilder::Instance().CreateNewFreezerEquipment();
        FreezerEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
   	vehicle->GetFreezerSlot()->InsertItem(FreezerEquipmentBuilder::Instance().GetFreezerEquipment());  

   	ScanerEquipmentBuilder::Instance().CreateNewScanerEquipment();
        ScanerEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
   	vehicle->GetScanerSlot()->InsertItem(ScanerEquipmentBuilder::Instance().GetScanerEquipment()); 
    
    	if (vehicle->data_korpus.slot_grapple_num != 0) 
    	{
    	   	GrappleEquipmentBuilder::Instance().CreateNewGrappleEquipment();
        	GrappleEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
      		vehicle->GetGrappleSlot()->InsertItem(GrappleEquipmentBuilder::Instance().GetGrappleEquipment()); 
   	}

    	for (unsigned int i = 0; i < 3; i++) 
    	{        
    	    	RadarModuleBuilder::Instance().CreateNewRadarModule();
        	RadarModuleBuilder::Instance().CreateNewInternals();
        	vehicle->AddItemToOtsec(RadarModuleBuilder::Instance().GetRadarModule());
    	}  
    	
    	for (unsigned int i = 0; i < 3; i++) 
    	{        
    	    	BombBuilder::Instance().CreateNewBomb();
        	BombBuilder::Instance().CreateNewInternals();
        	vehicle->AddItemToOtsec(BombBuilder::Instance().GetBomb());
    	}   
    	
    	vehicle->UpdateAllPropertiesAndAbilities(); 
}






