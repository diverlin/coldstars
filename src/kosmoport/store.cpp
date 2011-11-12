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


#include "store.hpp"

Store :: Store(TextureOb* _texOb_background, TextureOb* _texOb_slot)
{
        texOb_background = _texOb_background; 
        texOb_slot       = _texOb_slot; 

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
}


Store :: ~Store()
{}


void Store :: createSlots()
{
        int row = 3;
        int clm = 10;
        int x0 = 120;
        int y0 = g_VIEW_HEIGHT - (row + 2) * texOb_slot->h;

        int row_act = 1;
        while (row_act <= row)
        {
                int clm_act = 1;
                while (clm_act <= clm)
                {
                        ItemSlot* slot = new ItemSlot(UNIVERSAL_SLOT_ID, 
                                                      NULL, 
                                                      texOb_slot, 
                                                      x0 + clm_act * 1.1 * texOb_slot->w, 
                                                      y0 + row_act * 1.1 * texOb_slot->h);
                                                 
                        slot_pList.push_back(slot);
                        clm_act++;
                }
                row_act++;
        }
}



ItemSlot* Store :: getEmptySlot()
{
        for (unsigned int si = 0; si < slot_pList.size(); si++)
        {
                if (slot_pList[si]->getEquipedStatus() == false)
                        return slot_pList[si];
        }
      
        return NULL;
}


void Store :: initItemsGenerator()
{
        //int race_id = RACES_GOOD_LIST[getRandInt(0, RACES_GOOD_LIST.size() - 1)];
        //int revision_id = 0;

        for (unsigned int lii = 0; lii < lazer_num; lii++)
        { 
                LazerEquipment* pTo_lazer = lazerEquipmentGenerator(RACE_0_ID); 
                addLazerEquipment(pTo_lazer);
        }

        for (unsigned int rii = 0; rii < rocket_num; rii++)
        { 
                RocketEquipment* pTo_rocket = rocketEquipmentGenerator(RACE_0_ID); 
                addRocketEquipment(pTo_rocket);
        }

        for (unsigned int tii = 0; tii < torped_num; tii++)
        { 
        }

        for (unsigned int rii = 0; rii < radar_num; rii++)
        { 
                RadarEquipment* pTo_radar = radarEquipmentGenerator(RACE_0_ID); 
                addRadarEquipment(pTo_radar);
        }

        for (unsigned int gii = 0; gii < grapple_num; gii++)
        { 
                GrappleEquipment* pTo_grapple = grappleEquipmentGenerator(RACE_0_ID); 
                addGrappleEquipment(pTo_grapple);
        }

        for (unsigned int dii = 0; dii < drive_num; dii++)
        { 
                DriveEquipment* pTo_drive = driveEquipmentGenerator(RACE_0_ID); 
                addDriveEquipment(pTo_drive);
        }

        for (unsigned int pii = 0; pii < protector_num; pii++)
        { 
                ProtectorEquipment* pTo_protector = protectorEquipmentGenerator(RACE_0_ID); 
                addProtectorEquipment(pTo_protector);
        }

        for (unsigned int bii = 0; bii < bak_num; bii++)
        { 
                BakEquipment* pTo_bak = bakEquipmentGenerator(RACE_0_ID); 
                addBakEquipment(pTo_bak);
        }

        for (unsigned int dii = 0; dii < droid_num; dii++)
        { 
                DroidEquipment* pTo_droid = droidEquipmentGenerator(RACE_0_ID); 
                addDroidEquipment(pTo_droid);
        }

        for (unsigned int sii = 0; sii < scaner_num; sii++)
        { 
                ScanerEquipment* pTo_scaner = scanerEquipmentGenerator(RACE_0_ID); 
                addScanerEquipment(pTo_scaner);
        }

        for (unsigned int fii = 0; fii < freezer_num; fii++)
        { 
                FreezerEquipment* pTo_freezer = freezerEquipmentGenerator(RACE_0_ID); 
                addFreezerEquipment(pTo_freezer);
        }

        for (unsigned int ebi = 0; ebi < energyBlock_num; ebi++) 
        { 
                EnergizerEquipment* pTo_energizer = energizerEquipmentGenerator(RACE_0_ID); 
                addEnergizerEquipment(pTo_energizer);
        }
}
         


 

void Store :: addKorpusItem(Ship*         _pTo_ship)
{

}

void Store :: addLazerEquipment(LazerEquipment*             _lazerEquipment)
{
        getEmptySlot()->insertEquipment(_lazerEquipment);
}

void Store :: addRocketEquipment(RocketEquipment*           _rocketEquipment)
{
        getEmptySlot()->insertEquipment(_rocketEquipment);
}

//void addTorpedItem(     int _race_id, int _revision_id)

void Store :: addRadarEquipment(RadarEquipment*             _radarEquipment)
{
        getEmptySlot()->insertEquipment(_radarEquipment);
}

void Store :: addGrappleEquipment(GrappleEquipment*         _grappleEquipment)
{
        getEmptySlot()->insertEquipment(_grappleEquipment);
}

void Store :: addDriveEquipment(DriveEquipment*             _driveEquipment)
{
        getEmptySlot()->insertEquipment(_driveEquipment);
}

void Store :: addProtectorEquipment(ProtectorEquipment*     _protectorEquipment)
{
        getEmptySlot()->insertEquipment(_protectorEquipment);
}

void Store :: addBakEquipment(BakEquipment*                 _bakEquipment)
{
        getEmptySlot()->insertEquipment(_bakEquipment);
}

void Store :: addDroidEquipment(DroidEquipment*             _droidEquipment)
{
        getEmptySlot()->insertEquipment(_droidEquipment);
}

void Store :: addScanerEquipment(ScanerEquipment*           _scanerEquipment)
{
        getEmptySlot()->insertEquipment(_scanerEquipment);
}

void Store :: addFreezerEquipment(FreezerEquipment*         _freezerEquipment)
{
        getEmptySlot()->insertEquipment(_freezerEquipment);
}

void Store :: addEnergizerEquipment(EnergizerEquipment* _energizerEquipment)
{
        getEmptySlot()->insertEquipment(_energizerEquipment);
}




int Store :: buyWeaponSlotItem(ItemSlot* _weapon_slot)
{
        int price = 0;

        if (_weapon_slot->getItemSubTypeId() == LAZER_ID)
        {
                price = _weapon_slot->getLazerEquipment()->getPrice();
                addLazerEquipment(_weapon_slot->getLazerEquipment());
                _weapon_slot->removeItem();
        }

        if (_weapon_slot->getItemSubTypeId() == ROCKET_ID)
        {
                price = _weapon_slot->getRocketEquipment()->getPrice();
                addRocketEquipment(_weapon_slot->getRocketEquipment());
                _weapon_slot->removeItem();
        } 
        
        return price;
}


int Store :: buyDriveSlotItem(ItemSlot* _drive_slot)
{
        int price = _drive_slot->getDriveEquipment()->getPrice();
        addDriveEquipment(_drive_slot->getDriveEquipment());
        _drive_slot->removeItem();
    
        return price;
} 


int Store :: buyBakSlotItem(ItemSlot* _bak_slot)
{
        int price = _bak_slot->getBakEquipment()->getPrice();
        addBakEquipment(_bak_slot->getBakEquipment());
        _bak_slot->removeItem();
    
        return price;
} 


int Store :: buyRadarSlotItem(ItemSlot* _radar_slot)
{
        int price = _radar_slot->getRadarEquipment()->getPrice();
        addRadarEquipment(_radar_slot->getRadarEquipment());
        _radar_slot->removeItem();
    
        return price;
} 


int Store :: buyScanerSlotItem(ItemSlot* _scaner_slot)
{
        int price = _scaner_slot->getScanerEquipment()->getPrice();
        addScanerEquipment(_scaner_slot->getScanerEquipment());
        _scaner_slot->removeItem();
    
        return price;
} 

int Store :: buyEnergizerSlotItem(ItemSlot* _energizer_slot)
{
        int price = _energizer_slot->getEnergizerEquipment()->getPrice();
        addEnergizerEquipment(_energizer_slot->getEnergizerEquipment());
        _energizer_slot->removeItem();
        
        return price;
} 

int Store :: buyGrappleSlotItem(ItemSlot* _grapple_slot)
{
        int price = _grapple_slot->getGrappleEquipment()->getPrice();
        addGrappleEquipment(_grapple_slot->getGrappleEquipment());
        _grapple_slot->removeItem();
        
        return price;
} 

int Store :: buyProtectorSlotItem(ItemSlot* _protector_slot)
{
        int price = _protector_slot->getProtectorEquipment()->getPrice();
        addProtectorEquipment(_protector_slot->getProtectorEquipment());
        _protector_slot->removeItem();
        
        return price;
} 

int Store :: buyDroidSlotItem(ItemSlot* _droid_slot)
{
        int price = _droid_slot->getDroidEquipment()->getPrice();
        addDroidEquipment(_droid_slot->getDroidEquipment());
        _droid_slot->removeItem();
    
        return price;
} 

int Store :: buyFreezerSlotItem(ItemSlot* _freezer_slot)
{
        int price = _freezer_slot->getFreezerEquipment()->getPrice();
        addFreezerEquipment(_freezer_slot->getFreezerEquipment());
        _freezer_slot->removeItem();
        
        return price;
} 


int Store :: buyOtsecSlotItem(ItemSlot* _otsec_slot)
{
	int price = _otsec_slot->getItemPrice();

	// weapons
	if (_otsec_slot->getItemTypeId() == EQUIPMENT_ID)
	{
		if (_otsec_slot->getItemSubTypeId() == LAZER_ID)
		{
			addLazerEquipment(_otsec_slot->getLazerEquipment());
			_otsec_slot->removeItem();
		}
        
		if (_otsec_slot->getItemSubTypeId() == ROCKET_ID)
		{
			addRocketEquipment(_otsec_slot->getRocketEquipment());
			_otsec_slot->removeItem();
		}

		// items
		if (_otsec_slot->getItemSubTypeId() == RADAR_ID)
		{
			addRadarEquipment(_otsec_slot->getRadarEquipment());
			_otsec_slot->removeItem();
		}
   
		if (_otsec_slot->getItemSubTypeId() == DRIVE_ID)
		{
			addDriveEquipment(_otsec_slot->getDriveEquipment());
			_otsec_slot->removeItem();
		}
   
		if (_otsec_slot->getItemSubTypeId() == BAK_ID)
		{
			addBakEquipment(_otsec_slot->getBakEquipment());
			_otsec_slot->removeItem();
		}

		if (_otsec_slot->getItemSubTypeId() == ENERGIZER_ID)
		{
			addEnergizerEquipment(_otsec_slot->getEnergizerEquipment());
			_otsec_slot->removeItem();
		}
   
		if (_otsec_slot->getItemSubTypeId() == PROTECTOR_ID)
		{
			addProtectorEquipment(_otsec_slot->getProtectorEquipment());
			_otsec_slot->removeItem();
		}
   
		if (_otsec_slot->getItemSubTypeId() == DROID_ID)
		{
			addDroidEquipment(_otsec_slot->getDroidEquipment());
			_otsec_slot->removeItem();
		}
   
		if (_otsec_slot->getItemSubTypeId() == FREEZER_ID)
		{
			addFreezerEquipment(_otsec_slot->getFreezerEquipment());
			_otsec_slot->removeItem();
		}
   
		if (_otsec_slot->getItemSubTypeId() == SCANER_ID)
		{
			addScanerEquipment(_otsec_slot->getScanerEquipment());
			_otsec_slot->removeItem();
		}

		if (_otsec_slot->getItemSubTypeId() == GRAPPLE_ID)
		{
			addGrappleEquipment(_otsec_slot->getGrappleEquipment());
			_otsec_slot->removeItem();
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
        {
                slot_pList[i]->setCursoredStatus(false);
        }
}


void Store :: mouseControl()
{
        bool lmb = g_MOUSE_LEFT_BUTTON; 
        //bool rmb = g_MOUSE_RIGHT_BUTTON; 

                                                                resetSlotsRenderInfoFlag();

        for (unsigned int i = 0; i < slot_pList.size(); i++)
        { 
                float dist = distBetweenPoints(g_MOUSE_POS_X, 
                                                g_VIEW_HEIGHT - g_MOUSE_POS_Y, 
                                                slot_pList[i]->getRect().getCenter().x, 
                                                slot_pList[i]->getRect().getCenter().y);
        				
                if (dist < slot_pList[i]->getRect().getWidth()/2)
                {
                        slot_pList[i]->setCursoredStatus(true);
                        if (lmb == true)
                        {
                                if (slot_pList[i]->getEquipedStatus() == true)
                                {
                                        // weapons
                                        if (slot_pList[i]->getItemSubTypeId() == LAZER_ID)
                                        {
                                                pPLAYER->getShip()->getEmptyOtsecSlot()->insertEquipment(slot_pList[i]->getLazerEquipment());
                                                slot_pList[i]->removeItem();
                                        }
                                        if (slot_pList[i]->getItemSubTypeId() == ROCKET_ID)
                                        {
                                                pPLAYER->getShip()->getEmptyOtsecSlot()->insertEquipment(slot_pList[i]->getRocketEquipment());
                                                slot_pList[i]->removeItem();
                                        }

                                        // items
                                        if (slot_pList[i]->getItemSubTypeId() == RADAR_ID)
                                        {
                                                pPLAYER->getShip()->getEmptyOtsecSlot()->insertEquipment(slot_pList[i]->getRadarEquipment());
                                                slot_pList[i]->removeItem();
                                        }
                                        if (slot_pList[i]->getItemSubTypeId() == DRIVE_ID)
                                        {
                                                pPLAYER->getShip()->getEmptyOtsecSlot()->insertEquipment(slot_pList[i]->getDriveEquipment());
                                                slot_pList[i]->removeItem();
                                        }
                                        if (slot_pList[i]->getItemSubTypeId() == BAK_ID)
                                        {
                                                pPLAYER->getShip()->getEmptyOtsecSlot()->insertEquipment(slot_pList[i]->getBakEquipment());
                                                slot_pList[i]->removeItem();
                                        }
                                        if (slot_pList[i]->getItemSubTypeId() == ENERGIZER_ID)
                                        {
                                                pPLAYER->getShip()->getEmptyOtsecSlot()->insertEquipment(slot_pList[i]->getEnergizerEquipment());
                                                slot_pList[i]->removeItem();
                                        }
                                        if (slot_pList[i]->getItemSubTypeId() == PROTECTOR_ID)
                                        {
                                                pPLAYER->getShip()->getEmptyOtsecSlot()->insertEquipment(slot_pList[i]->getProtectorEquipment());
                                                slot_pList[i]->removeItem();
                                        }
                                        if (slot_pList[i]->getItemSubTypeId() == DROID_ID)
                                        {
                                                pPLAYER->getShip()->getEmptyOtsecSlot()->insertEquipment(slot_pList[i]->getDroidEquipment());
                                                slot_pList[i]->removeItem();
                                        }
                                        if (slot_pList[i]->getItemSubTypeId() == FREEZER_ID)
                                        {
                                                pPLAYER->getShip()->getEmptyOtsecSlot()->insertEquipment(slot_pList[i]->getFreezerEquipment());
                                                slot_pList[i]->removeItem();
                                        }
                                        if (slot_pList[i]->getItemSubTypeId() == SCANER_ID)
                                        {
                                                pPLAYER->getShip()->getEmptyOtsecSlot()->insertEquipment(slot_pList[i]->getScanerEquipment());
                                                slot_pList[i]->removeItem();
                                        }
                                        if (slot_pList[i]->getItemSubTypeId() == GRAPPLE_ID)
                                        {
                                                pPLAYER->getShip()->getEmptyOtsecSlot()->insertEquipment(slot_pList[i]->getGrappleEquipment());
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


void Store :: renderBackground() const
{
     	Rect screen_rect = Rect(0, 0, g_VIEW_WIDTH, g_VIEW_HEIGHT);
     	drawTexturedRect(texOb_background->texture, screen_rect, -1);  
}

void Store :: renderInternals() const
{
        for (unsigned int sli = 0; sli < slot_pList.size(); sli ++)
        {
                slot_pList[sli]->renderFrame(-1);
        }
}

void Store :: renderItemInfo() const
{
        for (unsigned int i = 0; i < slot_pList.size(); i++)
        {
                if (slot_pList[i]->getCursoredStatus() == true)
                        if (slot_pList[i]->getEquipedStatus() == true)
                                slot_pList[i]->renderItemInfo();
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
                renderItemInfo();
        disable_BLEND();
}

