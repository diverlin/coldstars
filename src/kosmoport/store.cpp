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


#include "store.h"

Store :: Store(TextureOb* _pTo_bg_texOb, TextureOb* _pTo_slot_texOb)
{
        pTo_bg_texOb   = _pTo_bg_texOb; 
        pTo_slot_texOb = _pTo_slot_texOb; 

        korpus_num      = 3;
        lazer_num       = 3;
        rocket_num      = 2;
        torped_num      = 2;
        radar_num       = 1;
        grapple_num     = 1;
        drive_num       = 1;
        protector_num   = 1;
        bak_num         = 1;
        droid_num       = 1;
        scaner_num      = 1;
        freezer_num     = 1;
        energyBlock_num = 1;


        createSlots();
        initItemsGenerator();

        manageInitItems();
}


Store :: ~Store()
{}


void Store :: linkTexture()
{
     // self.background_tex = self.bg_texOb.texture
}

void Store :: unlinkTexture()
{
     // self.background_tex = None
}

void Store :: createSlots()
{
     int row = 3;
     int clm = 10;
     int x0 = 120;
     int y0 = g_VIEW_HEIGHT - (row + 2) * pTo_slot_texOb->h;

     int row_act = 1;
     while (row_act <= row)
     {
            int clm_act = 1;
            while (clm_act <= clm)
            {
                   OtsecSlot* pTo_slot = new OtsecSlot(OTSEC_SLOT_ID, NULL, pTo_slot_texOb, (x0 + clm_act * 1.1 * pTo_slot_texOb->w), (y0 + row_act * 1.1 * pTo_slot_texOb->h));
                   slot_pList.push_back(pTo_slot);
                   clm_act++;
            }
            row_act++;
     }
}

void Store :: manageInitItems()
{
    /*    # used only once
        for item in self.items_list:
            slot = returnFirstFreeSlotBySlotType(STORE_SLOT_ID, None, self.slot_list)
            if slot != None:
               slot.item = item
               item.rect = slot.rect
    */
}

/*
void Store :: soldItem( ob, slot):
        store_slot = returnFirstFreeSlotBySlotType(STORE_SLOT_ID, None, self.slot_list)
        if store_slot != None:
           store_slot.item = slot.item
                           
           ob.credits += slot.item.price
           slot.item = None


    def buyItem(self, ob, slot):
        otsec_slot = returnFirstFreeSlotBySlotType(OTSEC_SLOT_ID, None, ob.korpus.otsec_slot_list)
        if otsec_slot != None:
           otsec_slot.item = slot.item
           ob.credits -= slot.item.price
           slot.item = None


    def buyKorpus(self, ob, slot):
        new_korpus = slot.item 
        slot.item = ob.korpus
        slot.item.owner = None
        ob.credits += slot.item.price 
        ob.credits -= new_korpus.price
        ob.setKorpus(new_korpus)  
*/

/*
void Store :: manager()
{

        for slot in player.korpus.total_slot_list:
            slot_cursor_dist = lengthBetweenPoints((slot.rect.centerx, slot.rect.centery), (mx, my))
            if slot_cursor_dist < slot.rect[2]/2:
               ############## sold item ##############
               if slot.item != None:
                  drawDynamicLabelList(text_background_tex, (slot.rect.right, slot.rect.bottom), slot.item.info)
                  if left_button_click == True:
                     self.soldItem(player, slot)


        for slot in self.slot_list:
            slot_cursor_dist = lengthBetweenPoints((slot.rect.centerx, slot.rect.centery), (mx, my))
            if slot_cursor_dist < slot.rect[2]/2:
               ############## buy item ##############
               if slot.item != None:
                  drawDynamicLabelList(text_background_tex, (slot.rect.right, slot.rect.bottom), slot.item.info)
                  if left_button_click == True:
                     if player.credits >= slot.item.price:
                        if slot.item.type != KORPUS_ID:
                           self.buyItem(player, slot)
                        else:
                           self.buyKorpus(player, slot)

}
*/  

OtsecSlot* Store :: return_pToEmptySlot()
{
      for (unsigned int si = 0; si < slot_pList.size(); si++)
          if (slot_pList[si]->is_EQUIPED == false)
             return slot_pList[si];
      return NULL;
}


void Store :: initItemsGenerator()
{
        int race_id = RACES_GOOD_LIST[randIntInRange(0, RACES_GOOD_LIST.size() - 1)];
        int revision_id = 0;

        //for i in xrange(0, int(self.korpus_num)):
        //    self.createAndAddKorpusItem(race_id, revision_id)
         

        for (unsigned int lii = 0; lii < lazer_num; lii++)
        { 
            LazerEquipment* pTo_lazer = lazerGenerator(RACE_0_ID); 
            addLazerEquipment(pTo_lazer);
        }

        for (unsigned int rii = 0; rii < rocket_num; rii++)
        { 
            RocketEquipment* pTo_rocket = rocketGenerator(RACE_0_ID); 
            addRocketEquipment(pTo_rocket);
        }

        for (unsigned int tii = 0; tii < torped_num; tii++)
        { 
        }

        for (unsigned int rii = 0; rii < radar_num; rii++)
        { 
            RadarEquipment* pTo_radar = radarGenerator(RACE_0_ID); 
            addRadarEquipment(pTo_radar);
        }

        for (unsigned int gii = 0; gii < grapple_num; gii++)
        { 
            GrappleEquipment* pTo_grapple = grappleGenerator(RACE_0_ID); 
            addGrappleEquipment(pTo_grapple);
        }

        for (unsigned int dii = 0; dii < drive_num; dii++)
        { 
            DriveEquipment* pTo_drive = driveGenerator(RACE_0_ID); 
            addDriveEquipment(pTo_drive);
        }

        for (unsigned int pii = 0; pii < protector_num; pii++)
        { 
            ProtectorEquipment* pTo_protector = protectorGenerator(RACE_0_ID); 
            addProtectorEquipment(pTo_protector);
        }

        for (unsigned int bii = 0; bii < bak_num; bii++)
        { 
            BakEquipment* pTo_bak = bakGenerator(RACE_0_ID); 
            addBakEquipment(pTo_bak);
        }

        for (unsigned int dii = 0; dii < droid_num; dii++)
        { 
            DroidEquipment* pTo_droid = droidGenerator(RACE_0_ID); 
            addDroidEquipment(pTo_droid);
        }

        for (unsigned int sii = 0; sii < scaner_num; sii++)
        { 
            ScanerEquipment* pTo_scaner = ScanerEquipmentGenerator(RACE_0_ID); 
            addScanerEquipment(pTo_scaner);
        }

        for (unsigned int fii = 0; fii < freezer_num; fii++)
        { 
            FreezerEquipment* pTo_freezer = freezerGenerator(RACE_0_ID); 
            addFreezerEquipment(pTo_freezer);
        }

        for (unsigned int ebi = 0; ebi < energyBlock_num; ebi++) 
        { 
            EnergizerEquipment* pTo_energizer = energizerGenerator(RACE_0_ID); 
            addEnergizerEquipment(pTo_energizer);
        }
}
         


 

void Store :: addKorpusItem(Ship*         _pTo_ship)
{

}

void Store :: addLazerEquipment(LazerEquipment*             _pTo_lazerEquipment)
{
     return_pToEmptySlot()->insertItem(_pTo_lazerEquipment);
}

void Store :: addRocketEquipment(RocketEquipment*           _pTo_rocketEquipment)
{
     return_pToEmptySlot()->insertItem(_pTo_rocketEquipment);
}

//void addTorpedItem(     int _race_id, int _revision_id)

void Store :: addRadarEquipment(RadarEquipment*             _pTo_radarEquipment)
{
     return_pToEmptySlot()->insertItem(_pTo_radarEquipment);
}

void Store :: addGrappleEquipment(GrappleEquipment*         _pTo_grappleEquipment)
{
     return_pToEmptySlot()->insertItem(_pTo_grappleEquipment);
}

void Store :: addDriveEquipment(DriveEquipment*             _pTo_driveEquipment)
{
     return_pToEmptySlot()->insertItem(_pTo_driveEquipment);
}

void Store :: addProtectorEquipment(ProtectorEquipment*     _pTo_protectorEquipment)
{
     return_pToEmptySlot()->insertItem(_pTo_protectorEquipment);
}

void Store :: addBakEquipment(BakEquipment*                 _pTo_bakEquipment)
{
     return_pToEmptySlot()->insertItem(_pTo_bakEquipment);
}

void Store :: addDroidEquipment(DroidEquipment*             _pTo_droidEquipment)
{
     return_pToEmptySlot()->insertItem(_pTo_droidEquipment);
}

void Store :: addScanerEquipment(ScanerEquipment*           _pTo_scanerEquipment)
{
     return_pToEmptySlot()->insertItem(_pTo_scanerEquipment);
}

void Store :: addFreezerEquipment(FreezerEquipment*         _pTo_freezerEquipment)
{
     return_pToEmptySlot()->insertItem(_pTo_freezerEquipment);
}

void Store :: addEnergizerEquipment(EnergizerEquipment* _pTo_energizerEquipment)
{
     return_pToEmptySlot()->insertItem(_pTo_energizerEquipment);
}




int Store :: buyWeaponSlotItem(WeaponSlot* pTo_weapon_slot)
{
    int price = 0;

    if (pTo_weapon_slot->item_subtype_id == LAZER_ID)
    {
       price = pTo_weapon_slot->pTo_lazerEquipment->price;
       addLazerEquipment(pTo_weapon_slot->pTo_lazerEquipment);
       pTo_weapon_slot->removeLazerEquipment();
    }

    if (pTo_weapon_slot->item_subtype_id == ROCKET_ID)
    {
       price = pTo_weapon_slot->pTo_rocketEquipment->price;
       addRocketEquipment(pTo_weapon_slot->pTo_rocketEquipment);
       pTo_weapon_slot->removeRocketEquipment();
    } 
    return price;
}


int Store :: buyDriveSlotItem(OtsecSlot* pTo_drive_slot)
{
    int price = pTo_drive_slot->get_pToDriveEquipment()->price;
    addDriveEquipment(pTo_drive_slot->get_pToDriveEquipment());
    pTo_drive_slot->removeItem();
    return price;
} 


int Store :: buyBakSlotItem(OtsecSlot* pTo_bak_slot)
{
    int price = pTo_bak_slot->get_pToBakEquipment()->price;
    addBakEquipment(pTo_bak_slot->get_pToBakEquipment());
    pTo_bak_slot->removeItem();
    return price;
} 


int Store :: buyRadarSlotItem(OtsecSlot* pTo_radar_slot)
{
    int price = pTo_radar_slot->get_pToRadarEquipment()->price;
    addRadarEquipment(pTo_radar_slot->get_pToRadarEquipment());
    pTo_radar_slot->removeItem();
    return price;
} 


int Store :: buyScanerSlotItem(OtsecSlot* pTo_scaner_slot)
{
    int price = pTo_scaner_slot->get_pToScanerEquipment()->price;
    addScanerEquipment(pTo_scaner_slot->get_pToScanerEquipment());
    pTo_scaner_slot->removeItem();
    return price;
} 

int Store :: buyEnergizerSlotItem(OtsecSlot* pTo_energizer_slot)
{
    int price = pTo_energizer_slot->get_pToEnergizerEquipment()->price;
    addEnergizerEquipment(pTo_energizer_slot->get_pToEnergizerEquipment());
    pTo_energizer_slot->removeItem();
    return price;
} 

int Store :: buyGrappleSlotItem(OtsecSlot* pTo_grapple_slot)
{
    int price = pTo_grapple_slot->get_pToGrappleEquipment()->price;
    addGrappleEquipment(pTo_grapple_slot->get_pToGrappleEquipment());
    pTo_grapple_slot->removeItem();
    return price;
} 

int Store :: buyProtectorSlotItem(OtsecSlot* pTo_protector_slot)
{
    int price = pTo_protector_slot->get_pToProtectorEquipment()->price;
    addProtectorEquipment(pTo_protector_slot->get_pToProtectorEquipment());
    pTo_protector_slot->removeItem();
    return price;
} 

int Store :: buyDroidSlotItem(OtsecSlot* pTo_droid_slot)
{
    int price = pTo_droid_slot->get_pToDroidEquipment()->price;
    addDroidEquipment(pTo_droid_slot->get_pToDroidEquipment());
    pTo_droid_slot->removeItem();
    return price;
} 

int Store :: buyFreezerSlotItem(OtsecSlot* pTo_freezer_slot)
{
    int price = pTo_freezer_slot->get_pToFreezerEquipment()->price;
    addFreezerEquipment(pTo_freezer_slot->get_pToFreezerEquipment());
    pTo_freezer_slot->removeItem();
    return price;
} 


int Store :: buyOtsecSlotItem(OtsecSlot* pTo_otsec_slot)
{
	int price = pTo_otsec_slot->getItemPrice();

	// weapons
	if (pTo_otsec_slot->item_type_id == EQUIPMENT_ID)
	{
		if (pTo_otsec_slot->item_subtype_id == LAZER_ID)
		{
			addLazerEquipment(pTo_otsec_slot->get_pToLazerEquipment());
			pTo_otsec_slot->removeItem();
		}
        
		if (pTo_otsec_slot->item_subtype_id == ROCKET_ID)
		{
			addRocketEquipment(pTo_otsec_slot->get_pToRocketEquipment());
			pTo_otsec_slot->removeItem();
		}

		// items
		if (pTo_otsec_slot->item_subtype_id == RADAR_ID)
		{
			addRadarEquipment(pTo_otsec_slot->get_pToRadarEquipment());
			pTo_otsec_slot->removeItem();
		}
   
		if (pTo_otsec_slot->item_subtype_id == DRIVE_ID)
		{
			addDriveEquipment(pTo_otsec_slot->get_pToDriveEquipment());
			pTo_otsec_slot->removeItem();
		}
   
		if (pTo_otsec_slot->item_subtype_id == BAK_ID)
		{
			addBakEquipment(pTo_otsec_slot->get_pToBakEquipment());
			pTo_otsec_slot->removeItem();
		}

		if (pTo_otsec_slot->item_subtype_id == ENERGIZER_ID)
		{
			addEnergizerEquipment(pTo_otsec_slot->get_pToEnergizerEquipment());
			pTo_otsec_slot->removeItem();
		}
   
		if (pTo_otsec_slot->item_subtype_id == PROTECTOR_ID)
		{
			addProtectorEquipment(pTo_otsec_slot->get_pToProtectorEquipment());
			pTo_otsec_slot->removeItem();
		}
   
		if (pTo_otsec_slot->item_subtype_id == DROID_ID)
		{
			addDroidEquipment(pTo_otsec_slot->get_pToDroidEquipment());
			pTo_otsec_slot->removeItem();
		}
   
		if (pTo_otsec_slot->item_subtype_id == FREEZER_ID)
		{
			addFreezerEquipment(pTo_otsec_slot->get_pToFreezerEquipment());
			pTo_otsec_slot->removeItem();
		}
   
		if (pTo_otsec_slot->item_subtype_id == SCANER_ID)
		{
			addScanerEquipment(pTo_otsec_slot->get_pToScanerEquipment());
			pTo_otsec_slot->removeItem();
		}

		if (pTo_otsec_slot->item_subtype_id == GRAPPLE_ID)
		{
			addGrappleEquipment(pTo_otsec_slot->get_pToGrappleEquipment());
			pTo_otsec_slot->removeItem();
		}
                
  	}                   
   	//// modules
   	//// artifacts
   	//// bomb


	return price;
}



void Store :: resetSlotsRenderInfoFlag()
{
    for (unsigned int i = 0; i < slot_pList.size(); i++)
        slot_pList[i]->is_CURSORED = false;
}


void Store :: mouseControl()
{
    bool lmb = g_MOUSE_LEFT_BUTTON; 
    bool rmb = g_MOUSE_RIGHT_BUTTON; 

    resetSlotsRenderInfoFlag();

    for (unsigned int i = 0; i < slot_pList.size(); i++)
    { 
        float dist = lengthBetweenPoints(g_MOUSE_POS_X, (g_VIEW_HEIGHT - g_MOUSE_POS_Y), slot_pList[i]->rect.center_x, slot_pList[i]->rect.center_y);
        if (dist < slot_pList[i]->rect.w/2)
        {
             slot_pList[i]->is_CURSORED = true;
             if (lmb == true)
             {
                 if (slot_pList[i]->is_EQUIPED == true)
                 {
                     // weapons
                     if (slot_pList[i]->item_subtype_id == LAZER_ID)
                     {
                        pTo_PLAYER->pTo_ship->return_pToEmptyOtsecSlot()->insertItem(slot_pList[i]->get_pToLazerEquipment());
                        slot_pList[i]->removeItem();
                     }
                     if (slot_pList[i]->item_subtype_id == ROCKET_ID)
                     {
                        pTo_PLAYER->pTo_ship->return_pToEmptyOtsecSlot()->insertItem(slot_pList[i]->get_pToRocketEquipment());
                        slot_pList[i]->removeItem();
                     }

                     // items
                     if (slot_pList[i]->item_subtype_id == RADAR_ID)
                     {
                        pTo_PLAYER->pTo_ship->return_pToEmptyOtsecSlot()->insertItem(slot_pList[i]->get_pToRadarEquipment());
                        slot_pList[i]->removeItem();
                     }
                     if (slot_pList[i]->item_subtype_id == DRIVE_ID)
                     {
                        pTo_PLAYER->pTo_ship->return_pToEmptyOtsecSlot()->insertItem(slot_pList[i]->get_pToDriveEquipment());
                        slot_pList[i]->removeItem();
                     }
                     if (slot_pList[i]->item_subtype_id == BAK_ID)
                     {
                        pTo_PLAYER->pTo_ship->return_pToEmptyOtsecSlot()->insertItem(slot_pList[i]->get_pToBakEquipment());
                        slot_pList[i]->removeItem();
                     }
                     if (slot_pList[i]->item_subtype_id == ENERGIZER_ID)
                     {
                        pTo_PLAYER->pTo_ship->return_pToEmptyOtsecSlot()->insertItem(slot_pList[i]->get_pToEnergizerEquipment());
                        slot_pList[i]->removeItem();
                     }
                     if (slot_pList[i]->item_subtype_id == PROTECTOR_ID)
                     {
                        pTo_PLAYER->pTo_ship->return_pToEmptyOtsecSlot()->insertItem(slot_pList[i]->get_pToProtectorEquipment());
                        slot_pList[i]->removeItem();
                     }
                     if (slot_pList[i]->item_subtype_id == DROID_ID)
                     {
                        pTo_PLAYER->pTo_ship->return_pToEmptyOtsecSlot()->insertItem(slot_pList[i]->get_pToDroidEquipment());
                        slot_pList[i]->removeItem();
                     }
                     if (slot_pList[i]->item_subtype_id == FREEZER_ID)
                     {
                        pTo_PLAYER->pTo_ship->return_pToEmptyOtsecSlot()->insertItem(slot_pList[i]->get_pToFreezerEquipment());
                        slot_pList[i]->removeItem();
                     }
                     if (slot_pList[i]->item_subtype_id == SCANER_ID)
                     {
                        pTo_PLAYER->pTo_ship->return_pToEmptyOtsecSlot()->insertItem(slot_pList[i]->get_pToScanerEquipment());
                        slot_pList[i]->removeItem();
                     }
                     if (slot_pList[i]->item_subtype_id == GRAPPLE_ID)
                     {
                        pTo_PLAYER->pTo_ship->return_pToEmptyOtsecSlot()->insertItem(slot_pList[i]->get_pToGrappleEquipment());
                        slot_pList[i]->removeItem();
                     }
                     // modules
                     // artifacts
                     // bomb
                 }
           } 
           break;
        } 
    }
}


void Store :: renderBackground()
{
     Rect screen_rect = Rect(0, 0, g_VIEW_WIDTH, g_VIEW_HEIGHT);
     drawTexturedRect(pTo_bg_texOb->texture, screen_rect, -1);  
}

void Store :: renderInternals()
{
     for (unsigned int sli = 0; sli < slot_pList.size(); sli ++)
         slot_pList[sli]->renderFrame(-1);
}

void Store :: renderItemInfo()
{
    for (unsigned int i = 0; i < slot_pList.size(); i++)
       if (slot_pList[i]->is_CURSORED == true)
          if (slot_pList[i]->is_EQUIPED == true)
              slot_pList[i]->renderItemInfo();
}



