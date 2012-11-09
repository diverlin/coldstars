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

#include "StoreBuilder.hpp"

#include "../common/id.hpp"
#include "../common/EntityManager.hpp"
#include "../common/Logger.hpp"
#include "../common/rand.hpp"
#include "../resources/TextureManager.hpp"

#include "../builder/ItemSlotBuilder.hpp"

#include "../items/equipment/BakEquipment.hpp"
#include "../items/equipment/DriveEquipment.hpp"
#include "../items/equipment/DroidEquipment.hpp"
#include "../items/equipment/GrappleEquipment.hpp"

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


StoreBuilder& StoreBuilder::Instance()
{
	static StoreBuilder instance;
	return instance;
}

StoreBuilder::~StoreBuilder()
{}

void StoreBuilder::CreateNewStore(int id)
{
	if (id == NONE_ID)
	{
		id = SimpleIdGenerator::Instance().GetNextId();
	}

        try 
        { 
        	store = new Store(id);
        }
        catch(std::bad_alloc)
        {
        	Logger::Instance().Log("EXEPTION:bad_dynamic_memory_allocation\n");
        }
        
        EntityManager::Instance().RegisterEntity(store);
} 
        	
void StoreBuilder::CreateNewInternals()
{
        for (unsigned int i=0; i<STORE_ITEM_SLOTS_NUM; i++)
        {
		ItemSlot* item_slot = GetNewItemSlot(ENTITY::CARGO_SLOT_ID);
                store->AddItemSlot(item_slot);
        }

	store->SetTextureObBackground(TextureManager::Instance().GetRandomTextureOb(TEXTURE::STORE_BACKGROUND_ID));
}


void StoreBuilder::PutRandomEquipment()
{
        //int race_id = RACES_GOOD_LIST[getRandInt(0, RACES_GOOD_LIST.size() - 1)];
        //int revision_id = 0;

        //unsigned int korpus_num      = 3;
        unsigned int lazer_num       = 3;
        unsigned int rocket_num      = 2;
        //unsigned int torped_num      = 2;
        unsigned int radar_num       = 1;
        unsigned int grapple_num     = 1;
        unsigned int drive_num       = 1;
        unsigned int protector_num   = 1;
        unsigned int bak_num         = 1;
        unsigned int droid_num       = 1;
        unsigned int scaner_num      = 1;
        unsigned int freezer_num     = 1;
        unsigned int energyBlock_num = 1;
        
        for (unsigned int lii = 0; lii < lazer_num; lii++)
        { 
    	        LazerEquipmentBuilder::Instance().CreateNewLazerEquipment();
        	LazerEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID); 
       		store->AddItem(LazerEquipmentBuilder::Instance().GetLazerEquipment()); 
        }

        for (unsigned int rii = 0; rii < rocket_num; rii++)
        { 
    	    	RocketEquipmentBuilder::Instance().CreateNewRocketEquipment();
        	RocketEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID); 
       		store->AddItem(RocketEquipmentBuilder::Instance().GetRocketEquipment());
        }

        for (unsigned int rii = 0; rii < radar_num; rii++)
        { 
        	RadarEquipmentBuilder::Instance().CreateNewRadarEquipment();
        	RadarEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID); 
    		store->AddItem(RadarEquipmentBuilder::Instance().GetRadarEquipment()); 
        }

        for (unsigned int gii = 0; gii < grapple_num; gii++)
        { 
      		store->AddItem(GrappleEquipmentBuilder::Instance().GetNewGrappleEquipment()); 
        }

        for (unsigned int dii = 0; dii < drive_num; dii++)
        {        
                store->AddItem(DriveEquipmentBuilder::Instance().GetNewDriveEquipment());
        }

        for (unsigned int pii = 0; pii < protector_num; pii++)
        { 
   		ProtectorEquipmentBuilder::Instance().CreateNewProtectorEquipment();
       		ProtectorEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
   		store->AddItem(ProtectorEquipmentBuilder::Instance().GetProtectorEquipment()); 
        }

        for (unsigned int bii = 0; bii < bak_num; bii++)
        { 
                store->AddItem(BakEquipmentBuilder::Instance().GetNewBakEquipment());
        }

        for (unsigned int dii = 0; dii < droid_num; dii++)
        { 
   		store->AddItem(DroidEquipmentBuilder::Instance().GetNewDroidEquipment()); 
        }

        for (unsigned int sii = 0; sii < scaner_num; sii++)
        { 
   		ScanerEquipmentBuilder::Instance().CreateNewScanerEquipment();
        	ScanerEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
   		store->AddItem(ScanerEquipmentBuilder::Instance().GetScanerEquipment()); 
        }

        for (unsigned int fii = 0; fii < freezer_num; fii++)
        { 
   		FreezerEquipmentBuilder::Instance().CreateNewFreezerEquipment();
        	FreezerEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
   		store->AddItem(FreezerEquipmentBuilder::Instance().GetFreezerEquipment()); 
        }

        for (unsigned int ebi = 0; ebi < energyBlock_num; ebi++) 
        { 
        	EnergizerEquipmentBuilder::Instance().CreateNewEnergizerEquipment();
        	EnergizerEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
    		store->AddItem(EnergizerEquipmentBuilder::Instance().GetEnergizerEquipment());  
        }
}



  	
