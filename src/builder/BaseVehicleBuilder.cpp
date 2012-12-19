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

#include "BaseVehicleBuilder.hpp"
#include "../spaceobjects/Vehicle.hpp"

#include "../parts/WeaponComplex.hpp"

#include "../items/equipment/BakEquipment.hpp"
#include "../items/equipment/DriveEquipment.hpp"
#include "../items/equipment/DroidEquipment.hpp"
#include "../items/equipment/GrappleEquipment.hpp"
#include "../items/equipment/LazerEquipment.hpp"
#include "../items/equipment/ProtectorEquipment.hpp"
#include "../items/equipment/RadarEquipment.hpp"
#include "../items/equipment/RocketEquipment.hpp"
#include "../items/equipment/ScanerEquipment.hpp"
#include "../items/equipment/EnergizerEquipment.hpp"

#include "../items/modules/LazerModule.hpp"
#include "../items/modules/RocketModule.hpp"
#include "../items/modules/DriveModule.hpp"
#include "../items/modules/DroidModule.hpp"
#include "../items/modules/RadarModule.hpp"
#include "../items/modules/BakModule.hpp"
#include "../items/modules/ProtectorModule.hpp"
#include "../items/modules/GrappleModule.hpp"
#include "../items/modules/ScanerModule.hpp"

#include "../items/others/Bomb.hpp"

#include "../items/artefacts/GravityArtefact.hpp"
#include "../items/artefacts/ProtectorArtefact.hpp"

#include "../builder/items/equipment/BakEquipmentBuilder.hpp"
#include "../builder/items/equipment/DriveEquipmentBuilder.hpp"
#include "../builder/items/equipment/GrappleEquipmentBuilder.hpp"
#include "../builder/items/equipment/LazerEquipmentBuilder.hpp"
#include "../builder/items/equipment/ProtectorEquipmentBuilder.hpp"
#include "../builder/items/equipment/RocketEquipmentBuilder.hpp"
#include "../builder/items/equipment/ScanerEquipmentBuilder.hpp"
#include "../builder/items/equipment/DroidEquipmentBuilder.hpp"
#include "../builder/items/equipment/RadarEquipmentBuilder.hpp"
#include "../builder/items/equipment/FreezerEquipmentBuilder.hpp"
#include "../builder/items/equipment/EnergizerEquipmentBuilder.hpp"

#include "../builder/items/modules/BakModuleBuilder.hpp"
#include "../builder/items/modules/DriveModuleBuilder.hpp"
#include "../builder/items/modules/GrappleModuleBuilder.hpp"
#include "../builder/items/modules/LazerModuleBuilder.hpp"
#include "../builder/items/modules/ProtectorModuleBuilder.hpp"
#include "../builder/items/modules/RocketModuleBuilder.hpp"
#include "../builder/items/modules/ScanerModuleBuilder.hpp"
#include "../builder/items/modules/DroidModuleBuilder.hpp"
#include "../builder/items/modules/RadarModuleBuilder.hpp"

#include "../builder/items/artefacts/GravityArtefactBuilder.hpp"
#include "../builder/items/artefacts/ProtectorArtefactBuilder.hpp"

#include "../builder/items/other/BombBuilder.hpp"

#include "../builder/ItemSlotBuilder.hpp"

#include "../common/rand.hpp"
#include "../effects/particlesystem/DriveEffect.hpp"

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
       
void BaseVehicleBuilder::CreateItemSlots(Vehicle* vehicle) const
{     
        // WEAPON SLOTS
        int slot_weapon_num = vehicle->GetKorpusData().slot_weapon_num;
        for (unsigned int i=0; i<slot_weapon_num; i++)
        {
        	ItemSlot* weapon_slot = GetNewItemSlot(ENTITY::WEAPON_SLOT_ID);  
        	weapon_slot->SetSubSubTypeId(ENTITY::WEAPON_SLOT1_ID + i);   
        	vehicle->AddItemSlot(weapon_slot);
        }
                
	ItemSlot* radar_slot = GetNewItemSlot(ENTITY::RADAR_SLOT_ID);
	vehicle->AddItemSlot(radar_slot);	
	
	ItemSlot* scaner_slot = GetNewItemSlot(ENTITY::SCANER_SLOT_ID); 
	vehicle->AddItemSlot(scaner_slot);	
	
	ItemSlot* energizer_slot = GetNewItemSlot(ENTITY::ENERGIZER_SLOT_ID); 
	vehicle->AddItemSlot(energizer_slot);
    		
    	if (vehicle->GetKorpusData().slot_grapple_num != 0)
	{
		ItemSlot* grapple_slot = GetNewItemSlot(ENTITY::GRAPPLE_SLOT_ID);			 
    		vehicle->AddItemSlot(grapple_slot); 
    	}
    	
	ItemSlot* droid_slot = GetNewItemSlot(ENTITY::DROID_SLOT_ID);	    
    	vehicle->AddItemSlot(droid_slot); 
    	    	
	ItemSlot* freezer_slot = GetNewItemSlot(ENTITY::FREEZER_SLOT_ID);
	vehicle->AddItemSlot(freezer_slot);           
        
        ItemSlot* protector_slot = GetNewItemSlot(ENTITY::PROTECTOR_SLOT_ID);  
    	vehicle->AddItemSlot(protector_slot);         
        
        ItemSlot* drive_slot = GetNewItemSlot(ENTITY::DRIVE_SLOT_ID); 
	vehicle->AddItemSlot(drive_slot);	
	
        ItemSlot* bak_slot = GetNewItemSlot(ENTITY::BAK_SLOT_ID);  
	vehicle->AddItemSlot(bak_slot);

    	//////////// ARTEFACT SLOT /////////////////////////  	  	
    	for (int i=0; i<4; i++)
    	{
    		ItemSlot* artefact_slot = GetNewItemSlot(ENTITY::ARTEFACT_SLOT_ID);
    		vehicle->AddItemSlot(artefact_slot);         
    	} 
    	
    	//////// OTSEC SLOT ////////////////////////////////
    	for (int i=0; i<=10; i++)
    	{
         	ItemSlot* otsec_slot = GetNewItemSlot(ENTITY::CARGO_SLOT_ID);   					
         	vehicle->AddItemSlot(otsec_slot);         
    	}
}	

void BaseVehicleBuilder::Equip(Vehicle* vehicle, int tech_level) const
{
    	for (unsigned int i=0; i<vehicle->GetKorpusData().slot_weapon_num + 2; i++)
    	{
    		if (getRandBool())
    		{
       			vehicle->AddAndManageItem(RocketEquipmentBuilder::Instance().GetNewRocketEquipment(tech_level));
		}
		else
		{
       			vehicle->AddAndManageItem(LazerEquipmentBuilder::Instance().GetNewLazerEquipment(tech_level)); 
       		}
    	}   
           
    	vehicle->AddAndManageItem(RadarEquipmentBuilder::Instance().GetNewRadarEquipment(tech_level)); 

    	vehicle->AddAndManageItem(DriveEquipmentBuilder::Instance().GetNewDriveEquipment(1)); 
    	vehicle->AddAndManageItem(DriveEquipmentBuilder::Instance().GetNewDriveEquipment(3)); 
    	vehicle->AddAndManageItem(DriveEquipmentBuilder::Instance().GetNewDriveEquipment(tech_level)); 

    	vehicle->AddAndManageItem(BakEquipmentBuilder::Instance().GetNewBakEquipment(tech_level));         
    	vehicle->AddAndManageItem(EnergizerEquipmentBuilder::Instance().GetNewEnergizerEquipment(tech_level));     
   	//vehicle->AddAndManageItem(FreezerEquipmentBuilder::Instance().GetNewFreezerEquipment(tech_level));  
   	
   	vehicle->AddAndManageItem(ProtectorEquipmentBuilder::Instance().GetNewProtectorEquipment(tech_level)); 
   	vehicle->AddAndManageItem(DroidEquipmentBuilder::Instance().GetNewDroidEquipment(tech_level)); 
   	vehicle->AddAndManageItem(ScanerEquipmentBuilder::Instance().GetNewScanerEquipment(tech_level)); 
    
    	if (vehicle->GetKorpusData().slot_grapple_num != 0) 
    	{
      		vehicle->AddAndManageItem(GrappleEquipmentBuilder::Instance().GetNewGrappleEquipment(tech_level)); 
   	}
    	
    	for (unsigned int i=0; i<4; i++) 
    	{     
    		int module_subtype_id = getRandInt(ENTITY::LAZER_MODULE_ID, ENTITY::SCANER_MODULE_ID); 
    		switch(module_subtype_id)  
    		{
    			case ENTITY::LAZER_MODULE_ID: 		{ vehicle->AddItemToCargoSlot(LazerModuleBuilder::Instance().GetNewLazerModule()); break; }
    			case ENTITY::ROCKET_MODULE_ID: 		{ vehicle->AddItemToCargoSlot(RocketModuleBuilder::Instance().GetNewRocketModule()); break; }    		
    			case ENTITY::DRIVE_MODULE_ID: 		{ vehicle->AddItemToCargoSlot(DriveModuleBuilder::Instance().GetNewDriveModule()); break; }
    			case ENTITY::RADAR_MODULE_ID: 		{ vehicle->AddItemToCargoSlot(RadarModuleBuilder::Instance().GetNewRadarModule()); break; }
    			case ENTITY::BAK_MODULE_ID: 		{ vehicle->AddItemToCargoSlot(BakModuleBuilder::Instance().GetNewBakModule()); break; }
    			//case ENTITY::ENERGIZER_MODULE_ID:	{ vehicle->AddItemToCargoSlot(EnergizerModuleBuilder::Instance().GetNewEnergizerModule()); break; }
    			case ENTITY::PROTECTOR_MODULE_ID: 	{ vehicle->AddItemToCargoSlot(ProtectorModuleBuilder::Instance().GetNewProtectorModule()); break; }
    			case ENTITY::DROID_MODULE_ID: 		{ vehicle->AddItemToCargoSlot(DroidModuleBuilder::Instance().GetNewDroidModule()); break; }
    			//case ENTITY::FREEZER_MODULE_ID: 	{ vehicle->AddItemToCargoSlot(FreezerModuleBuilder::Instance().GetNewFreezerModule()); break; }
    			case ENTITY::GRAPPLE_MODULE_ID: 	{ vehicle->AddItemToCargoSlot(GrappleModuleBuilder::Instance().GetNewGrappleModule()); break; }
    			case ENTITY::SCANER_MODULE_ID: 		{ vehicle->AddItemToCargoSlot(ScanerModuleBuilder::Instance().GetNewScanerModule()); break; }
    		}
    	}  
    	    	
    	for (unsigned int i=0; i<1; i++) 
    	{        
        	vehicle->AddItemToCargoSlot(BombBuilder::Instance().GetNewBomb());
    	}   

    	for (unsigned int i=0; i<2; i++) 
    	{        
        	vehicle->AddAndManageItem(GravityArtefactBuilder::Instance().GetNewGravityArtefact());
    	}   

    	for (unsigned int i=0; i<2; i++) 
    	{        
        	vehicle->AddAndManageItem(ProtectorArtefactBuilder::Instance().GetNewProtectorArtefact());
    	}  
}






