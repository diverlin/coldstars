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



Store :: Store(TextureOb* _texOb_background, TextureOb* _texOb_slot)
{
        texOb_background = _texOb_background; 
        texOb_slot       = _texOb_slot; 

        createSlots();
}


Store :: ~Store()
{}


void Store :: createSlots()
{
        int row = 3;
        int clm = 10;
        int x0 = 120;
        int y0 = SCREEN_HEIGHT_MIN - (row + 2) * texOb_slot->getFrameHeight();

        int row_act = 1;
        while (row_act <= row)
        {
                int clm_act = 1;
                while (clm_act <= clm)
                {
                        ItemSlot* slot = new ItemSlot(CARGO_SLOT_ID, NULL, texOb_slot);
                        slot->setRect(x0 + clm_act * 1.1 * STORE_SLOT_WIDTH, 
                        	      y0 + row_act * 1.1 * STORE_SLOT_HEIGHT,
                        	      STORE_SLOT_WIDTH,
                                      STORE_SLOT_HEIGHT);      
                                                        
                        slot_vec.push_back(slot);
                        clm_act++;
                }
                row_act++;
        }
}



ItemSlot* Store :: getEmptySlot()
{
        for (unsigned int si = 0; si < slot_vec.size(); si++)
        {
                if (slot_vec[si]->getEquipedStatus() == false)
                        return slot_vec[si];
        }
      
        return NULL;
}

        


bool Store :: add(ItemBase* item)
{
	getEmptySlot()->insertItem(item);
	return true;
}


bool Store :: sellItemFromSlot(Npc* npc, ItemSlot* slot)
{
	unsigned int price = slot->getItem()->getPrice();
        if (npc->getCredits() >= price)
        {
        	npc->getVehicle()->getEmptyOtsecSlot()->SwapItemWith(slot); 
                npc->increaseCredits(price);    
                
                return true;                 	                                       
        }
        
        return false;
}		

bool Store :: buyItemFromSlot(Npc* npc, ItemSlot* slot)
{
	unsigned int price = slot->getItem()->getPrice();
	
	ItemSlot* free_slot = getEmptySlot();
	
	if (free_slot != NULL)
	{
		npc->increaseCredits(price);
		return free_slot->SwapItemWith(slot);
	}
	else
	{
		return false;
	}
}

void equipStore(Store* store)
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
                store->add(getNewLazerEquipment(RACE_0_ID));
        }

        for (unsigned int rii = 0; rii < rocket_num; rii++)
        { 
                store->add(getNewRocketEquipment(RACE_0_ID));
        }

        for (unsigned int rii = 0; rii < radar_num; rii++)
        { 
                store->add(getNewRadarEquipment(RACE_0_ID));
        }

        for (unsigned int gii = 0; gii < grapple_num; gii++)
        { 
                store->add(getNewGrappleEquipment(RACE_0_ID));
        }

        for (unsigned int dii = 0; dii < drive_num; dii++)
        { 
                store->add(getNewDriveEquipment(RACE_0_ID));
        }

        for (unsigned int pii = 0; pii < protector_num; pii++)
        { 
                store->add(getNewProtectorEquipment(RACE_0_ID));
        }

        for (unsigned int bii = 0; bii < bak_num; bii++)
        { 
                store->add(getNewBakEquipment(RACE_0_ID));
        }

        for (unsigned int dii = 0; dii < droid_num; dii++)
        { 
                store->add(getNewDroidEquipment(RACE_0_ID));
        }

        for (unsigned int sii = 0; sii < scaner_num; sii++)
        { 
                store->add(getNewScanerEquipment(RACE_0_ID));
        }

        for (unsigned int fii = 0; fii < freezer_num; fii++)
        { 
                store->add(getNewFreezerEquipment(RACE_0_ID));
        }

        for (unsigned int ebi = 0; ebi < energyBlock_num; ebi++) 
        { 
                store->add(getNewEnergizerEquipment(RACE_0_ID));
        }
}


//Store* createStore(int race_id)
//{
	//TextureOb* texOb_background = 
	//TextureOb* texOb_slot       =

	//Store* store = new  Store(texOb_background, texOb_slot);
        //initItemsGenerator(store);
        
        //return store;
//}
