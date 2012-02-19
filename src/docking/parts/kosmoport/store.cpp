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
        int y0 = g_VIEW_HEIGHT - (row + 2) * texOb_slot->getFrameHeight();

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

        


template <typename STORE_ITEM>
bool Store :: add(STORE_ITEM* item)
{
	getEmptySlot()->insertItem(item);
	return true;
}



bool Store :: buyItemFromSlot(ItemSlot* _slot)
{
	ItemSlot* free_slot = getEmptySlot();
	
	if (free_slot != NULL)
	{
		return free_slot->SwapItemWith(_slot);
	}
	else
	{
		return false;
	}
}


void Store :: mouseControl()
{
        bool lmb = g_MOUSE_LEFT_BUTTON; 
        //bool rmb = g_MOUSE_RIGHT_BUTTON; 

        for (unsigned int i = 0; i < slot_vec.size(); i++)
        { 
                float dist = distBetweenPoints(slot_vec[i]->getRect().getCenter(),
                			       g_MOUSE_POS_X, 
                                               g_VIEW_HEIGHT - g_MOUSE_POS_Y);
                                                       				
                if (dist < slot_vec[i]->getRect().getWidth()/2)
                {
                        pPLAYER->getCursor()->setInfoSlot(slot_vec[i]);
                        if (lmb == true)
                        {
                                if (slot_vec[i]->getEquipedStatus() == true)
                                {
                                	// get Item price, check if OK and then next
                                	unsigned int _price = slot_vec[i]->getItem()->getPrice();
                                	if (pPLAYER->getPilot()->getCredits() >= _price)
                                	{
                                		pPLAYER->getVehicle()->getEmptyOtsecSlot()->SwapItemWith(slot_vec[i]); 
                                		pPLAYER->getPilot()->decreaseCredits(_price);                     	                                       
                                        }
                                }
                        } 
                        break;
                } 
        }
}


void Store :: renderBackground() const
{
     	Rect screen_rect = Rect(0, 0, g_VIEW_WIDTH, g_VIEW_HEIGHT);
     	drawTexturedRect(texOb_background, screen_rect, -1);  
}

void Store :: renderInternals() const
{
        for (unsigned int sli = 0; sli < slot_vec.size(); sli ++)
        {
                slot_vec[sli]->render(-1);
        }
}

void Store :: update()
{
        mouseControl();
}


void Store :: render() const
{
        clearScreen();
        resetRenderTransformation();
                                                        
        renderBackground();
        
        enable_BLEND();
                renderInternals();
        disable_BLEND();
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
