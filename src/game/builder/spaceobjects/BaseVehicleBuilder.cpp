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
#include "../../spaceobjects/Vehicle.hpp"

#include "../../garbage/EntityGarbage.hpp"

#include "../../parts/WeaponComplex.hpp"

#include "../../items/equipment/BakEquipment.hpp"
#include "../../items/equipment/DriveEquipment.hpp"
#include "../../items/equipment/DroidEquipment.hpp"
#include "../../items/equipment/GrappleEquipment.hpp"
#include "../../items/equipment/LazerEquipment.hpp"
#include "../../items/equipment/ProtectorEquipment.hpp"
#include "../../items/equipment/RadarEquipment.hpp"
#include "../../items/equipment/RocketEquipment.hpp"
#include "../../items/equipment/ScanerEquipment.hpp"
#include "../../items/equipment/EnergizerEquipment.hpp"

#include "../../items/modules/LazerModule.hpp"
#include "../../items/modules/RocketModule.hpp"
#include "../../items/modules/DriveModule.hpp"
#include "../../items/modules/DroidModule.hpp"
#include "../../items/modules/RadarModule.hpp"
#include "../../items/modules/BakModule.hpp"
#include "../../items/modules/ProtectorModule.hpp"
#include "../../items/modules/GrappleModule.hpp"
#include "../../items/modules/ScanerModule.hpp"

#include "../../items/others/Bomb.hpp"

#include "../../items/artefacts/GravityArtefact.hpp"
#include "../../items/artefacts/ProtectorArtefact.hpp"

#include "../../builder/items/IncludeItemBuilders.hpp"

#include "../../builder/ItemSlotBuilder.hpp"

#include "../../common/rand.hpp"
#include "../../effects/particlesystem/DriveEffect.hpp"

BaseVehicleBuilder& BaseVehicleBuilder::Instance()
{	
	static BaseVehicleBuilder instance;
	return instance;
}	

void BaseVehicleBuilder::CreateKorpusGeometry(Vehicle* vehicle) const
{}
       
void BaseVehicleBuilder::CreateItemSlots(Vehicle* vehicle) const
{     
        // WEAPON SLOTS
        unsigned int slot_weapon_num = vehicle->GetKorpusData().slot_weapon_num;
        for (unsigned int i=0; i<slot_weapon_num; i++)
        {
        	ItemSlot* weapon_slot = GetNewItemSlot(ENTITY::WEAPON_SLOT_ID);  
        	weapon_slot->SetSubSubTypeId(ENTITY::WEAPON_SLOT1_ID + i);   
        	vehicle->AddItemSlot(weapon_slot);
        }
            
        if (vehicle->GetKorpusData().slot_radar_num)
        {
                ItemSlot* radar_slot = GetNewItemSlot(ENTITY::RADAR_SLOT_ID);
                vehicle->AddItemSlot(radar_slot);
	}
                
        if (vehicle->GetKorpusData().slot_scaner_num)
        {
                ItemSlot* scaner_slot = GetNewItemSlot(ENTITY::SCANER_SLOT_ID); 
                vehicle->AddItemSlot(scaner_slot);
        }
	
        if (vehicle->GetKorpusData().slot_energizer_num)
        {
                ItemSlot* energizer_slot = GetNewItemSlot(ENTITY::ENERGIZER_SLOT_ID); 
                vehicle->AddItemSlot(energizer_slot);
        }
        
    	if (vehicle->GetKorpusData().slot_grapple_num)
	{
		ItemSlot* grapple_slot = GetNewItemSlot(ENTITY::GRAPPLE_SLOT_ID);
    		vehicle->AddItemSlot(grapple_slot); 
    	}
    	
        if (vehicle->GetKorpusData().slot_droid_num)
        {
                ItemSlot* droid_slot = GetNewItemSlot(ENTITY::DROID_SLOT_ID);  
                vehicle->AddItemSlot(droid_slot); 
        }
        
        if (vehicle->GetKorpusData().slot_freezer_num)
        {
                //ItemSlot* freezer_slot = GetNewItemSlot(ENTITY::FREEZER_SLOT_ID);
                //vehicle->AddItemSlot(freezer_slot);           
        }
        
        if (vehicle->GetKorpusData().slot_protector_num)
        {
                ItemSlot* protector_slot = GetNewItemSlot(ENTITY::PROTECTOR_SLOT_ID);  
                vehicle->AddItemSlot(protector_slot);         
        }
        
        if (vehicle->GetKorpusData().slot_drive_num)
        {
                ItemSlot* drive_slot = GetNewItemSlot(ENTITY::DRIVE_SLOT_ID); 
                vehicle->AddItemSlot(drive_slot);
        }
        
        if (vehicle->GetKorpusData().slot_bak_num)
        {
                ItemSlot* bak_slot = GetNewItemSlot(ENTITY::BAK_SLOT_ID);  
                vehicle->AddItemSlot(bak_slot);
        }
        
    	//////////// ARTEFACT SLOT /////////////////////////
    	int artefact_num = vehicle->GetKorpusData().slot_artefact_num;
        for (int i=0; i<artefact_num; i++)
    	{
    		ItemSlot* artefact_slot = GetNewItemSlot(ENTITY::ARTEFACT_SLOT_ID);
    		vehicle->AddItemSlot(artefact_slot);         
    	} 

    	//////// OTSEC SLOT ////////////////////////////////
        int otsec_num = vehicle->GetKorpusData().slot_otsec_num;
    	for (int i=0; i<otsec_num; i++)
    	{
         	ItemSlot* otsec_slot = GetNewItemSlot(ENTITY::CARGO_SLOT_ID);   
         	vehicle->AddItemSlot(otsec_slot);         
    	}
}

void BaseVehicleBuilder::EquipEquipment(Vehicle* vehicle, int tech_level) const
{
        int weapons_num = getRandInt(1, vehicle->GetKorpusData().slot_weapon_num);
    	for (unsigned int i=0; i<weapons_num; i++)
    	{
    		if (getRandBool())
    		{
                        RocketEquipment* rocket_equipment = RocketEquipmentBuilder::Instance().GetNewRocketEquipment(tech_level);
       			if (vehicle->AddAndManageItem(rocket_equipment) == false)
                        {
                                EntityGarbage::Instance().Add(rocket_equipment);
                        }
		}
		else
		{
                        LazerEquipment* lazer_equipment = LazerEquipmentBuilder::Instance().GetNewLazerEquipment(tech_level);
       			if (vehicle->AddAndManageItem(lazer_equipment) == false)
                        {
                                EntityGarbage::Instance().Add(lazer_equipment); 
                        }
       		}
    	}   
        
        if (vehicle->CheckItemSlotPresenceBySubTypeId(ENTITY::RADAR_SLOT_ID) == true)
        {
                RadarEquipment* radar_equipment = RadarEquipmentBuilder::Instance().GetNewRadarEquipment(tech_level);
                if (vehicle->AddAndManageItem(radar_equipment) == false)
                {	
                        EntityGarbage::Instance().Add(radar_equipment); 
                }
        }
        
        if (vehicle->CheckItemSlotPresenceBySubTypeId(ENTITY::DRIVE_SLOT_ID) == true)
        {
                DriveEquipment* drive_equipment = DriveEquipmentBuilder::Instance().GetNewDriveEquipment(tech_level);
                if (vehicle->AddAndManageItem(drive_equipment) == false)
                {
                        EntityGarbage::Instance().Add(drive_equipment); 
                }
        }
        
        if (vehicle->CheckItemSlotPresenceBySubTypeId(ENTITY::BAK_SLOT_ID) == true)
        {
                BakEquipment* bak_equipment = BakEquipmentBuilder::Instance().GetNewBakEquipment(tech_level);
                if (vehicle->AddAndManageItem(bak_equipment) == false)
                {
                        EntityGarbage::Instance().Add(bak_equipment); 
                } 
        }
        
        if (vehicle->CheckItemSlotPresenceBySubTypeId(ENTITY::ENERGIZER_SLOT_ID) == true)
        {
                EnergizerEquipment* energizer_equipment = EnergizerEquipmentBuilder::Instance().GetNewEnergizerEquipment(tech_level);
                if (vehicle->AddAndManageItem(energizer_equipment) == false)
                {
                        EntityGarbage::Instance().Add(energizer_equipment); 
                }     
   	}
        
        if (vehicle->CheckItemSlotPresenceBySubTypeId(ENTITY::FREEZER_SLOT_ID) == true)
        {
                //FreezerEquipment* freezer_equipment = FreezerEquipmentBuilder::Instance().GetNewFreezerEquipment(tech_level);
                //if (vehicle->AddAndManageItem(freezer_equipment) == false)
                //{
                        //EntityGarbage::Instance().Add(freezer_equipment); 
                //}  
        }
        
        if (vehicle->CheckItemSlotPresenceBySubTypeId(ENTITY::PROTECTOR_SLOT_ID) == true)
        {
                ProtectorEquipment* protector_equipment = ProtectorEquipmentBuilder::Instance().GetNewProtectorEquipment(tech_level);
                if (vehicle->AddAndManageItem(protector_equipment) == false)
                {
                        EntityGarbage::Instance().Add(protector_equipment); 
                }  
   	}
        
        if (vehicle->CheckItemSlotPresenceBySubTypeId(ENTITY::DROID_SLOT_ID) == true)
        {
                DroidEquipment* droid_equipment = DroidEquipmentBuilder::Instance().GetNewDroidEquipment(tech_level);
                if (vehicle->AddAndManageItem(droid_equipment) == false)
                {
                        EntityGarbage::Instance().Add(droid_equipment); 
                }  
   	}
        
        if (vehicle->CheckItemSlotPresenceBySubTypeId(ENTITY::SCANER_SLOT_ID) == true)
        {
                ScanerEquipment* scaner_equipment = ScanerEquipmentBuilder::Instance().GetNewScanerEquipment(tech_level);
                if (vehicle->AddAndManageItem(scaner_equipment) == false)
                {
                        EntityGarbage::Instance().Add(scaner_equipment); 
                }  
        }
        
        if (vehicle->CheckItemSlotPresenceBySubTypeId(ENTITY::GRAPPLE_SLOT_ID) == true)
        {
                GrappleEquipment* grapple_equipment = GrappleEquipmentBuilder::Instance().GetNewGrappleEquipment(tech_level);
                if (vehicle->AddAndManageItem(grapple_equipment) == false)
                {
                        EntityGarbage::Instance().Add(grapple_equipment); 
                } 
   	}
}

void BaseVehicleBuilder::EquipModules(Vehicle* vehicle, int tech_level) const
{
    	for (unsigned int i=0; i<4; i++) 
    	{     
                if (vehicle->GetEmptyCargoSlot() == nullptr)
                {
                        return;
                }
                
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
}

void BaseVehicleBuilder::EquipArtefacts(Vehicle* vehicle, int tech_level) const
{
    	for (unsigned int i=0; i<2; i++) 
    	{
                if (vehicle->GetEmptyCargoSlot() == nullptr)
                {
                        return;
                }
                        
        	vehicle->AddAndManageItem(GravityArtefactBuilder::Instance().GetNewGravityArtefact());
    	}   

    	for (unsigned int i=0; i<2; i++) 
    	{        
                if (vehicle->GetEmptyCargoSlot() == nullptr)
                {
                        return;
                }
                
        	vehicle->AddAndManageItem(ProtectorArtefactBuilder::Instance().GetNewProtectorArtefact());
    	}  
}

void BaseVehicleBuilder::EquipBomb(Vehicle* vehicle, int tech_level) const
{
        for (unsigned int i=0; i<2; i++) 
    	{        
        	vehicle->AddItemToCargoSlot(BombBuilder::Instance().GetNewBomb());
    	}    
}




