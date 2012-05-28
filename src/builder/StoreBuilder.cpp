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
		id = g_ID_GENERATOR.getNextId();
	}
        store = new Store(id);
        EntityManager::Instance().RegisterEntity(store);
} 
        	
void StoreBuilder::CreateNewInternals()
{
	// create slots
	TextureOb* texOb_slot = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::ITEMSLOT_ID);
	        
 	int row = 3;
        int clm = 10;
        int x0 = 120;
        int y0 = Config::Instance().SCREEN_HEIGHT - (row + 2) * texOb_slot->getFrameHeight();

        int row_act = 1;
        while (row_act <= row)
        {
                int clm_act = 1;
                while (clm_act <= clm)
                {
                        ItemSlot* slot = GetNewItemSlot(ITEMSLOT::CARGO_ID);
 
                        Rect rect(x0 + clm_act * 1.1 * GUI::ITEMSLOT::WIDTH_FOR_STORE, 
                        	  y0 + row_act * 1.1 * GUI::ITEMSLOT::HEIGHT_FOR_STORE,
                        	  GUI::ITEMSLOT::WIDTH_FOR_STORE,
                                  GUI::ITEMSLOT::HEIGHT_FOR_STORE);
                                                        
                        store->AddSlot(slot, rect);
                        clm_act++;
                }
                row_act++;
        }
        
	
	TextureOb* texOb_bg  = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::STORE_BACKGROUND_ID); 
	store->SetTextureObBackground(texOb_bg);

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
    	   	GrappleEquipmentBuilder::Instance().CreateNewGrappleEquipment();
        	GrappleEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
      		store->AddItem(GrappleEquipmentBuilder::Instance().GetGrappleEquipment()); 
        }

        for (unsigned int dii = 0; dii < drive_num; dii++)
        { 
                DriveEquipmentBuilder::Instance().CreateNewDriveEquipment();
                DriveEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
        
                store->AddItem(DriveEquipmentBuilder::Instance().GetDriveEquipment());
        }

        for (unsigned int pii = 0; pii < protector_num; pii++)
        { 
   		ProtectorEquipmentBuilder::Instance().CreateNewProtectorEquipment();
       		ProtectorEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
   		store->AddItem(ProtectorEquipmentBuilder::Instance().GetProtectorEquipment()); 
        }

        for (unsigned int bii = 0; bii < bak_num; bii++)
        { 
                BakEquipmentBuilder::Instance().CreateNewBakEquipment();
                BakEquipmentBuilder::Instance().CreateNewInternals();
                store->AddItem(BakEquipmentBuilder::Instance().GetBakEquipment());
        }

        for (unsigned int dii = 0; dii < droid_num; dii++)
        { 
   		DroidEquipmentBuilder::Instance().CreateNewDroidEquipment();
        	DroidEquipmentBuilder::Instance().CreateNewInternals(RACE::R0_ID);
   		store->AddItem(DroidEquipmentBuilder::Instance().GetDroidEquipment()); 
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



  	
