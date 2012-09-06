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

#include "items/artefacts/GravityArtefactBuilder.hpp"
#include "BaseVehicleBuilder.hpp"

BaseVehicleBuilder& BaseVehicleBuilder::Instance()
{	
	static BaseVehicleBuilder instance;
	return instance;
}	

void BaseVehicleBuilder::CreateKorpusGeometry(Vehicle* vehicle) const
{
	vehicle->RecalculateCollisionRadius();

    	vehicle->GetPoints().initMainQuadPoints(vehicle->GetTextureOb()->GetFrameWidth(), vehicle->GetTextureOb()->GetFrameHeight());
    	vehicle->GetPoints().addMainQuadPoints();
}


void BaseVehicleBuilder::CreateKorpusGui(Vehicle* vehicle) const
{
	vehicle->SetGuiTextureOb(vehicle->GetTextureOb());         	

    	float kontur_w, kontur_h;
    	if (vehicle->GetTextureOb()->GetFrameWidth() > vehicle->GetTextureOb()->GetFrameHeight())
    	{
        	kontur_w = 500; 
    		vehicle->GetKorpusData().gui_scale = (float)kontur_w/vehicle->GetTextureOb()->GetFrameWidth();
        	kontur_h = vehicle->GetTextureOb()->GetFrameHeight() * kontur_w / (float)vehicle->GetTextureOb()->GetFrameWidth();
    	}
    	else
    	{
        	kontur_h = 500; 
    		vehicle->GetKorpusData().gui_scale = (float)kontur_h/vehicle->GetTextureOb()->GetFrameHeight();
        	kontur_w = vehicle->GetTextureOb()->GetFrameWidth() * kontur_h / (float)vehicle->GetTextureOb()->GetFrameHeight();
    	}               

    	Rect kontur_rect(-kontur_w/2, -kontur_h/2, kontur_w, kontur_h); 
	vehicle->SetGuiRect(kontur_rect);
}
        
void BaseVehicleBuilder::CreateEquipmentSlots(Vehicle* vehicle) const
{        
	Rect rect;

        // WEAPON SLOTS
        for (unsigned int i=0; i<vehicle->GetKorpusData().slot_weapon_num; i++)
        {
        	ItemSlot* weapon_slot = GetNewItemSlot(ENTITY::WEAPON_SLOT_ID);
        	rect = Rect( -3*GUI::ITEMSLOT::WIDTH_FOR_SHIP    + 1.1*i*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                             -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 2*1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
       			     GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);        
        	vehicle->AddItemSlot(weapon_slot, rect);
        }
        //
                
	ItemSlot* radar_slot = GetNewItemSlot(ENTITY::RADAR_SLOT_ID);
        rect = Rect(4*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
		    GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
	vehicle->AddItemSlot(radar_slot, rect);
	
	
	ItemSlot* scaner_slot = GetNewItemSlot(ENTITY::SCANER_SLOT_ID); 
	rect = Rect(4*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
		    GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
	vehicle->AddItemSlot(scaner_slot, rect);
	
	
	ItemSlot* energizer_slot = GetNewItemSlot(ENTITY::ENERGIZER_SLOT_ID); 
	rect = Rect(-2*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
		    GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
	vehicle->AddItemSlot(energizer_slot, rect);
    		
    		
	if (vehicle->GetKorpusData().slot_grapple_num != 0)
	{
		ItemSlot* grapple_slot = GetNewItemSlot(ENTITY::GRAPPLE_SLOT_ID);
		rect = Rect(-3*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
                            -GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
                            GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);					 
    		vehicle->AddItemSlot(grapple_slot, rect); 
    	}
    	
	ItemSlot* droid_slot = GetNewItemSlot(ENTITY::DROID_SLOT_ID);
	rect = Rect(-1*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
		    GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);				    
    	vehicle->AddItemSlot(droid_slot, rect); 
    	
    	
	ItemSlot* freezer_slot = GetNewItemSlot(ENTITY::FREEZER_SLOT_ID);
	rect = Rect(-1*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
		    GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);	
	vehicle->AddItemSlot(freezer_slot, rect);   
        
        
        ItemSlot* protector_slot = GetNewItemSlot(ENTITY::PROTECTOR_SLOT_ID); 
	rect = Rect(-3*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
		    GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);	    
    	vehicle->AddItemSlot(protector_slot, rect); 
        
        
        ItemSlot* drive_slot = GetNewItemSlot(ENTITY::DRIVE_SLOT_ID); 
	rect = Rect(-5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 + 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
                    GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
	vehicle->AddItemSlot(drive_slot, rect);
	
	
        ItemSlot* bak_slot = GetNewItemSlot(ENTITY::BAK_SLOT_ID);  
	rect = Rect(-5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
		    -1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2 - 1.1*GUI::ITEMSLOT::HEIGHT_FOR_SHIP/2,
		    GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
	vehicle->AddItemSlot(bak_slot, rect);
	////////////////////////////////////////////////////


    	//////// OTSEC SLOT ////////////////////////////////
    	for (int i=0; i<=10; i++)
    	{
         	ItemSlot* otsec_slot = GetNewItemSlot(ENTITY::CARGO_SLOT_ID);
         	rect = Rect((i-6)*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
         		    -3*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
         		    GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);         					
         	vehicle->AddItemSlot(otsec_slot, rect);         
    	}
    	////////////////////////////////////////////////////


    	//////////// GATE SLOT /////////////////////////////
    	ItemSlot* gate_slot = GetNewItemSlot(ENTITY::GATE_SLOT_ID);
   	rect = Rect(-5*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
    		    3*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
    		    GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
    	vehicle->AddItemSlot(gate_slot, rect);
    	
    	//////////// ARTEFACT SLOT /////////////////////////  	  	
    	for (int i=0; i<4; i++)
    	{
    		ItemSlot* artefact_slot = GetNewItemSlot(ENTITY::ARTEFACT_SLOT_ID);
   		rect = Rect(i*GUI::ITEMSLOT::WIDTH_FOR_SHIP, 
    	        	    4*GUI::ITEMSLOT::HEIGHT_FOR_SHIP,
    		   	    GUI::ITEMSLOT::WIDTH_FOR_SHIP, GUI::ITEMSLOT::HEIGHT_FOR_SHIP);
    		vehicle->AddItemSlot(artefact_slot, rect);         
    	}
    	
}	

void BaseVehicleBuilder::CreateDriveComplex(Vehicle* vehicle) const
{   	
    	DriveComplex* drive_complex = new DriveComplex(vehicle);  
    	vehicle->SetDriveComplex(drive_complex);
}

void BaseVehicleBuilder::CreateWeaponsComplex(Vehicle* vehicle) const
{
 	WeaponComplex* weapon_complex = new WeaponComplex(vehicle);
 	vehicle->SetWeaponComplex(weapon_complex);
}

void BaseVehicleBuilder::CreateProtectionComplex(Vehicle* vehicle) const
{
	ProtectionComplex* protection_complex = new ProtectionComplex(vehicle); 	
 	vehicle->SetProtectionComplex(protection_complex);
}

void BaseVehicleBuilder::CreateDriveComplexTextureDependedStuff(Vehicle* vehicle) const
{
    	vehicle->GetPoints().initMidLeftPoint();
    	vehicle->GetPoints().addMidLeftPoint();

    	vehicle->GetPoints().initMidFarLeftPoint();
    	vehicle->GetPoints().addMidFarLeftPoint();
    	
	DriveEffect* drive_effect = GetNewDriveEffect(vehicle->GetTextureOb()->size_id, vehicle->GetPoints().GetpMidLeft(), vehicle->GetPoints().GetpMidFarLeft());
 	vehicle->GetDriveComplex()->SetDriveEffect(drive_effect);
}               

void BaseVehicleBuilder::CreateProtectionComplexTextureDependedStuff(Vehicle* vehicle) const
{
	vehicle->GetProtectionComplex()->Resize(1.2*vehicle->GetTextureOb()->GetFrameWidth(), 1.2*vehicle->GetTextureOb()->GetFrameHeight());
}          

void BaseVehicleBuilder::Equip(Vehicle* vehicle) const
{
    	for (unsigned int i=0; i<vehicle->GetKorpusData().slot_weapon_num; i++)
    	{
    		if (getRandBool())
    		{
    	    		RocketEquipmentBuilder::Instance().CreateNewRocketEquipment();
        		RocketEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID); 
       			vehicle->GetWeaponComplex()->AddItem(RocketEquipmentBuilder::Instance().GetRocketEquipment());
		}
		else
		{
    	        	LazerEquipmentBuilder::Instance().CreateNewLazerEquipment();
        		LazerEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID); 
       			vehicle->GetWeaponComplex()->AddItem(LazerEquipmentBuilder::Instance().GetLazerEquipment()); 
       		}
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
        
        //EnergizerEquipmentBuilder::Instance().CreateNewEnergizerEquipment();
        //EnergizerEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
    	//vehicle->GetEnergizerSlot()->InsertItem(EnergizerEquipmentBuilder::Instance().GetEnergizerEquipment());     

 	//FreezerEquipmentBuilder::Instance().CreateNewFreezerEquipment();
        //FreezerEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
   	//vehicle->GetFreezerSlot()->InsertItem(FreezerEquipmentBuilder::Instance().GetFreezerEquipment());  
   	
   	ProtectorEquipmentBuilder::Instance().CreateNewProtectorEquipment();
        ProtectorEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
   	vehicle->GetProtectionComplex()->GetProtectorSlot()->InsertItem(ProtectorEquipmentBuilder::Instance().GetProtectorEquipment()); 
   	
   	DroidEquipmentBuilder::Instance().CreateNewDroidEquipment();
        DroidEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
   	vehicle->GetDroidSlot()->InsertItem(DroidEquipmentBuilder::Instance().GetDroidEquipment()); 

   	ScanerEquipmentBuilder::Instance().CreateNewScanerEquipment();
        ScanerEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
   	vehicle->GetScanerSlot()->InsertItem(ScanerEquipmentBuilder::Instance().GetScanerEquipment()); 
    
    	if (vehicle->GetKorpusData().slot_grapple_num != 0) 
    	{
    	   	GrappleEquipmentBuilder::Instance().CreateNewGrappleEquipment();
        	GrappleEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
      		vehicle->GetGrappleSlot()->InsertItem(GrappleEquipmentBuilder::Instance().GetGrappleEquipment()); 
   	}

    	for (unsigned int i=0; i<3; i++) 
    	{        
    	    	DroidModuleBuilder::Instance().CreateNewDroidModule();
        	DroidModuleBuilder::Instance().CreateNewInternals();
        	vehicle->AddItemToCargoSlot(DroidModuleBuilder::Instance().GetDroidModule());
    	}  
    	
    	//for (unsigned int i=0; i<3; i++) 
    	//{        
    	    	//RadarModuleBuilder::Instance().CreateNewRadarModule();
        	//RadarModuleBuilder::Instance().CreateNewInternals();
        	//vehicle->AddItemToCargoSlot(RadarModuleBuilder::Instance().GetRadarModule());
    	//}  
    	    	
    	for (unsigned int i=0; i<3; i++) 
    	{        
    	    	BombBuilder::Instance().CreateNewBomb();
        	BombBuilder::Instance().CreateNewInternals();
        	vehicle->AddItemToCargoSlot(BombBuilder::Instance().GetBomb());
    	}   

    	for (unsigned int i=0; i<3; i++) 
    	{        
    	    	GravityArtefactBuilder::Instance().CreateNewGravityArtefact();
        	GravityArtefactBuilder::Instance().CreateNewInternals();
        	vehicle->AddItemToCargoSlot(GravityArtefactBuilder::Instance().GetGravityArtefact());
    	}   

    	for (unsigned int i=0; i<3; i++) 
    	{        
    	    	ProtectorArtefactBuilder::Instance().CreateNewProtectorArtefact();
        	ProtectorArtefactBuilder::Instance().CreateNewInternals();
        	vehicle->AddItemToCargoSlot(ProtectorArtefactBuilder::Instance().GetProtectorArtefact());
    	}   
}






