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
	TextureOb* texOb_slot = g_TEXTURE_MANAGER.GetRandomTextureOb(TEXTURE::SLOT_ID);
	        
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
                        ItemSlot* slot = new ItemSlot();
                        slot->SetSubTypeId(SLOT::CARGO_ID);
                        slot->SetTextureOb(texOb_slot);   
                        slot->SetRect(x0 + clm_act * 1.1 * GUI::SLOT::WIDTH_FOR_STORE, 
                        	      y0 + row_act * 1.1 * GUI::SLOT::HEIGHT_FOR_STORE,
                        	      GUI::SLOT::WIDTH_FOR_STORE,
                                      GUI::SLOT::HEIGHT_FOR_STORE);
                                                        
                        store->Add(slot);
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
                store->Add(getNewLazerEquipment(RACE::R0_ID));
        }

        for (unsigned int rii = 0; rii < rocket_num; rii++)
        { 
                store->Add(getNewRocketEquipment(RACE::R0_ID));
        }

        for (unsigned int rii = 0; rii < radar_num; rii++)
        { 
                store->Add(getNewRadarEquipment(RACE::R0_ID));
        }

        for (unsigned int gii = 0; gii < grapple_num; gii++)
        { 
                store->Add(getNewGrappleEquipment(RACE::R0_ID));
        }

        for (unsigned int dii = 0; dii < drive_num; dii++)
        { 
                store->Add(getNewDriveEquipment(RACE::R0_ID));
        }

        for (unsigned int pii = 0; pii < protector_num; pii++)
        { 
                store->Add(getNewProtectorEquipment(RACE::R0_ID));
        }

        for (unsigned int bii = 0; bii < bak_num; bii++)
        { 
                store->Add(getNewBakEquipment(RACE::R0_ID));
        }

        for (unsigned int dii = 0; dii < droid_num; dii++)
        { 
                store->Add(getNewDroidEquipment(RACE::R0_ID));
        }

        for (unsigned int sii = 0; sii < scaner_num; sii++)
        { 
                store->Add(getNewScanerEquipment(RACE::R0_ID));
        }

        for (unsigned int fii = 0; fii < freezer_num; fii++)
        { 
                store->Add(getNewFreezerEquipment(RACE::R0_ID));
        }

        for (unsigned int ebi = 0; ebi < energyBlock_num; ebi++) 
        { 
                store->Add(getNewEnergizerEquipment(RACE::R0_ID));
        }
}



  	
