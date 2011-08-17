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

#include "otsecslot.h"


OtsecSlot :: OtsecSlot()
{}


OtsecSlot :: OtsecSlot(int _type_id, Ship* _pTo_ship, TextureOb* _pTo_texOb, int _pos_x, int _pos_y)
{
	CommonForSlot_init(_pTo_ship, _pTo_texOb, _pos_x, _pos_y);
	type_id = _type_id;
}

void OtsecSlot :: insertItem(RocketItem* pTo_item)
{
	pTo_rocketItem = pTo_item;
    
	item_subtype_id = pTo_item->subtype_id;  
	is_EQUIPED = true; 
    
	if (pTo_ship != NULL)
	{
    		pTo_ship->updateFireAbility();
    	}
}

void OtsecSlot :: insertItem(LazerItem* pTo_item)
{
	pTo_lazerItem = pTo_item;
    
	item_subtype_id = pTo_item->subtype_id;  
	is_EQUIPED = true;
    
    	if (pTo_ship != NULL)
	{
    		pTo_ship->updateFireAbility();
    	} 
}

void OtsecSlot :: insertItem(RadarItem* pTo_item)
{
	pTo_radarItem = pTo_item;
    
	item_subtype_id = pTo_item->subtype_id;  
	is_EQUIPED = true; 
    
    	if (pTo_ship != NULL)
	{
    		pTo_ship->updateRadarAbility();
    	}
}

void OtsecSlot :: insertItem(DriveItem* pTo_item)
{
	pTo_driveItem = pTo_item;
   
	item_subtype_id = pTo_item->subtype_id;  
	is_EQUIPED = true; 
    
        if (pTo_ship != NULL)
	{
    		pTo_ship->updateDriveAbility();
    		pTo_ship->updateJumpAbility();
    	}
}

void OtsecSlot :: insertItem(BakItem* pTo_item)
{
	pTo_bakItem = pTo_item;
    
	item_subtype_id = pTo_item->subtype_id;  
	is_EQUIPED = true; 
    
	if (pTo_ship != NULL)
	{
    		pTo_ship->updateDriveAbility();
    		pTo_ship->updateJumpAbility();
    	}
}

void OtsecSlot :: insertItem(EnergizerItem* pTo_item)
{
	pTo_energizerItem = pTo_item;
    
	item_subtype_id = pTo_item->subtype_id;  
	is_EQUIPED = true; 
    
        if (pTo_ship != NULL)
	{
    		pTo_ship->updateEnergyAbility();
    	}
}

void OtsecSlot :: insertItem(ProtectorItem* pTo_item)
{
	pTo_protectorItem = pTo_item;
    
	item_subtype_id = pTo_item->subtype_id;  
	is_EQUIPED = true; 
    
        if (pTo_ship != NULL)
	{
    		pTo_ship->updateProtectionAbility();
    	}
}

void OtsecSlot :: insertItem(DroidItem* pTo_item)
{
	pTo_droidItem = pTo_item;

	item_subtype_id = pTo_item->subtype_id;  
	is_EQUIPED = true; 
    
        if (pTo_ship != NULL)
	{
    		pTo_ship->updateRepairAbility();
    	}
}

void OtsecSlot :: insertItem(FreezerItem* pTo_item)
{
	pTo_freezerItem = pTo_item;

	item_subtype_id = pTo_item->subtype_id;  
	is_EQUIPED = true; 
    
	if (pTo_ship != NULL)
	{
    		pTo_ship->updateFreezeAbility();
    	}
}

void OtsecSlot :: insertItem(ScanerItem* pTo_item)
{
	pTo_scanerItem = pTo_item;

	item_subtype_id = pTo_item->subtype_id;  
	is_EQUIPED = true; 
    
	if (pTo_ship != NULL)
	{
    		pTo_ship->updateScanAbility();
    	}
}

void OtsecSlot :: insertItem(GrappleItem* pTo_item)
{
	pTo_grappleItem = pTo_item;

	item_subtype_id = pTo_item->subtype_id;  
	is_EQUIPED = true; 
    
        if (pTo_ship != NULL)
	{
    		pTo_ship->updateGrabAbility();
    	}
}

//MODULES
void OtsecSlot :: insertItem(RocketModule* pTo_module)
{
	pTo_rocketModule = pTo_module;
	pTo_rocketModule->rect.setNewCenter(rect.center_x, rect.center_y);

	item_subtype_id = pTo_module->subtype_id;  
	is_EQUIPED = true;  
}

void OtsecSlot :: insertItem(LazerModule* pTo_module)
{
	pTo_lazerModule = pTo_module;
	pTo_lazerModule->rect.setNewCenter(rect.center_x, rect.center_y);

	item_subtype_id = pTo_module->subtype_id;  
	is_EQUIPED = true;   
}

void OtsecSlot :: insertItem(RadarModule* pTo_module)
{
	pTo_radarModule = pTo_module;
	pTo_radarModule->rect.setNewCenter(rect.center_x, rect.center_y);

	item_subtype_id = pTo_module->subtype_id;  
	is_EQUIPED = true; 
}

void OtsecSlot :: insertItem(DriveModule* pTo_module)
{
	pTo_driveModule = pTo_module;
	pTo_driveModule->rect.setNewCenter(rect.center_x, rect.center_y);

	item_subtype_id = pTo_module->subtype_id;  
	is_EQUIPED = true; 
}

void OtsecSlot :: insertItem(BakModule* pTo_module)
{
	pTo_bakModule = pTo_module;
	pTo_bakModule->rect.setNewCenter(rect.center_x, rect.center_y);

	item_subtype_id = pTo_module->subtype_id;  
	is_EQUIPED = true; 
}

void OtsecSlot :: insertItem(EnergizerModule* pTo_module)
{
	pTo_energizerModule = pTo_module;
	pTo_energizerModule->rect.setNewCenter(rect.center_x, rect.center_y);

	item_subtype_id = pTo_module->subtype_id;  
	is_EQUIPED = true; 
}

void OtsecSlot :: insertItem(ProtectorModule* pTo_module)
{
	pTo_protectorModule = pTo_module;
	pTo_protectorModule->rect.setNewCenter(rect.center_x, rect.center_y);

	item_subtype_id = pTo_module->subtype_id;  
	is_EQUIPED = true; 
}

void OtsecSlot :: insertItem(DroidModule* pTo_module)
{
	pTo_droidModule = pTo_module;
	pTo_droidModule->rect.setNewCenter(rect.center_x, rect.center_y);

	item_subtype_id = pTo_module->subtype_id;  
	is_EQUIPED = true; 
}

void OtsecSlot :: insertItem(FreezerModule* pTo_module)
{
	pTo_freezerModule = pTo_module;
	pTo_freezerModule->rect.setNewCenter(rect.center_x, rect.center_y);
    
	item_subtype_id = pTo_module->subtype_id;  
	is_EQUIPED = true; 
}

void OtsecSlot :: insertItem(ScanerModule* pTo_module)
{
	pTo_scanerModule = pTo_module;
	pTo_scanerModule->rect.setNewCenter(rect.center_x, rect.center_y);

	item_subtype_id = pTo_module->subtype_id;  
	is_EQUIPED = true; 
}

void OtsecSlot :: insertItem(GrappleModule* pTo_module)
{
	pTo_grappleModule = pTo_module;
	pTo_grappleModule->rect.setNewCenter(rect.center_x, rect.center_y);
        
	item_subtype_id = pTo_module->subtype_id;  
	is_EQUIPED = true; 
}


void OtsecSlot :: removeItem()
{
	is_EQUIPED = false; 
	
	if (item_subtype_id == ROCKET_ITEM_ID)
	{
    		pTo_rocketItem = NULL;
    		if (pTo_ship != NULL)
    			pTo_ship->updateFireAbility();
    	}
    	
    	if (item_subtype_id == LAZER_ITEM_ID)
	{
    		pTo_lazerItem = NULL;
    		if (pTo_ship != NULL)
    			pTo_ship->updateFireAbility();
    	}
    
        if (item_subtype_id == RADAR_ITEM_ID)
	{
    		pTo_radarItem = NULL;
    		if (pTo_ship != NULL)
    			pTo_ship->updateRadarAbility();
    	}
    						
        if (item_subtype_id == DRIVE_ITEM_ID)
	{
    		pTo_driveItem = NULL;
    		if (pTo_ship != NULL)
    		{ 
    			pTo_ship->updateDriveAbility();
    			pTo_ship->updateJumpAbility();
    		}	
    	}

        if (item_subtype_id == BAK_ITEM_ID)
	{
    		pTo_bakItem = NULL;
    		if (pTo_ship != NULL)
    		{ 
    			pTo_ship->updateDriveAbility();
    			pTo_ship->updateJumpAbility();
    		}
    	}

        if (item_subtype_id == ENERGIZER_ITEM_ID)
	{
    		pTo_energizerItem = NULL;
    		if (pTo_ship != NULL)
    			pTo_ship->updateEnergyAbility();
    	}

        if (item_subtype_id == PROTECTOR_ITEM_ID)
	{
    		pTo_protectorItem = NULL;
    		if (pTo_ship != NULL)
    			pTo_ship->updateProtectionAbility();
    	}
    	
        if (item_subtype_id == DROID_ITEM_ID)
	{
    		pTo_droidItem = NULL;
    		if (pTo_ship != NULL)
    			pTo_ship->updateRepairAbility();
    	}

        if (item_subtype_id == FREEZER_ITEM_ID)
	{
    		pTo_freezerItem = NULL;
    		if (pTo_ship != NULL)
    			pTo_ship->updateFreezeAbility();
    	}
    	

        if (item_subtype_id == SCANER_ITEM_ID)
	{
    		pTo_scanerItem = NULL;
    		if (pTo_ship != NULL)
    			pTo_ship->updateScanAbility();
    	}
    	
        if (item_subtype_id == GRAPPLE_ITEM_ID)
	{
    		pTo_grappleItem = NULL;
    		if (pTo_ship != NULL)
    			pTo_ship->updateGrabAbility();
    	}
    	
    	
        if (item_subtype_id == ROCKET_MODULE_ID)
	{
    		pTo_rocketModule = NULL;
    	} 

        if (item_subtype_id == LAZER_MODULE_ID)
	{
    		pTo_lazerModule = NULL;
    	} 
    	
        if (item_subtype_id == RADAR_MODULE_ID)
	{
    		pTo_radarModule = NULL;
    	} 
    	
        if (item_subtype_id == DRIVE_MODULE_ID)
	{
    		pTo_driveModule = NULL;
    	} 
    		
        if (item_subtype_id == BAK_MODULE_ID)
	{
    		pTo_bakModule = NULL;
    	}
    	
        if (item_subtype_id == ENERGIZER_MODULE_ID)
	{
    		pTo_energizerModule = NULL;
    	}

        if (item_subtype_id == PROTECTOR_MODULE_ID)
	{
    		pTo_protectorModule = NULL;
    	}

        if (item_subtype_id == DROID_MODULE_ID)
	{
    		pTo_droidModule = NULL;
    	}

        if (item_subtype_id == FREEZER_MODULE_ID)
	{
    		pTo_freezerModule = NULL;
    	}
    	
    	if (item_subtype_id == SCANER_MODULE_ID)
	{
    		pTo_scanerModule = NULL;
    	}

    	if (item_subtype_id == GRAPPLE_MODULE_ID)
	{
    		pTo_grappleModule = NULL;
    	}

	item_subtype_id = -1;
}



int OtsecSlot :: getItemMass()
{  
	if (item_subtype_id == LAZER_ITEM_ID)  
		return pTo_lazerItem->mass;
	if (item_subtype_id == ROCKET_ITEM_ID)
		return pTo_rocketItem->mass;
	if (item_subtype_id == ENERGIZER_ITEM_ID)
		return pTo_energizerItem->mass;
	if (item_subtype_id == FREEZER_ITEM_ID)
		return pTo_freezerItem->mass;
	if (item_subtype_id == GRAPPLE_ITEM_ID)
		return pTo_grappleItem->mass;
	if (item_subtype_id == RADAR_ITEM_ID)
		return pTo_radarItem->mass;
	if (item_subtype_id == DRIVE_ITEM_ID)
		return pTo_driveItem->mass;
	if (item_subtype_id == PROTECTOR_ITEM_ID)
		return pTo_protectorItem->mass;
	if (item_subtype_id == BAK_ITEM_ID)
		return pTo_bakItem->mass;
	if (item_subtype_id == DROID_ITEM_ID)
		return pTo_droidItem->mass;
	if (item_subtype_id == SCANER_ITEM_ID)
		return pTo_scanerItem->mass;
}





int OtsecSlot :: getItemPrice()
{  
	if (item_subtype_id == LAZER_ITEM_ID)  
		return pTo_lazerItem->price;
	if (item_subtype_id == ROCKET_ITEM_ID)
		return pTo_rocketItem->price;
	if (item_subtype_id == ENERGIZER_ITEM_ID)
		return pTo_energizerItem->price;
	if (item_subtype_id == FREEZER_ITEM_ID)
		return pTo_freezerItem->price;
	if (item_subtype_id == GRAPPLE_ITEM_ID)
		return pTo_grappleItem->price;
	if (item_subtype_id == RADAR_ITEM_ID)
		return pTo_radarItem->price;
	if (item_subtype_id == DRIVE_ITEM_ID)
		return pTo_driveItem->price;
	if (item_subtype_id == PROTECTOR_ITEM_ID)
		return pTo_protectorItem->price;
	if (item_subtype_id == BAK_ITEM_ID)
		return pTo_bakItem->price;
	if (item_subtype_id == DROID_ITEM_ID)
		return pTo_droidItem->price;
	if (item_subtype_id == SCANER_ITEM_ID)
		return pTo_scanerItem->price;
}


void OtsecSlot :: renderFrame(GLuint flash_tex)
{
	drawTexturedRect(pTo_texOb->texture, rect, -1.5);

	//if self.flash == True:
		//drawTexturedRect(flash_tex, self.rect, -1.0)
	renderEquipedItem();
        
}

void OtsecSlot :: renderEquipedItem()
{
	if (is_EQUIPED == true)
	{
		//items 
		if (item_subtype_id == LAZER_ITEM_ID)
			pTo_lazerItem->render(rect);
		if (item_subtype_id == ROCKET_ITEM_ID)
			pTo_rocketItem->render(rect);
		if (item_subtype_id == RADAR_ITEM_ID)
			pTo_radarItem->render(rect);
		if (item_subtype_id == DRIVE_ITEM_ID)
			pTo_driveItem->render(rect);
		if (item_subtype_id == BAK_ITEM_ID)
			pTo_bakItem->render(rect);
		if (item_subtype_id == ENERGIZER_ITEM_ID)
			pTo_energizerItem->render(rect);
		if (item_subtype_id == PROTECTOR_ITEM_ID)
          		pTo_protectorItem->render(rect);   
		if (item_subtype_id == DROID_ITEM_ID)
			pTo_droidItem->render(rect);
		if (item_subtype_id == FREEZER_ITEM_ID)
			pTo_freezerItem->render(rect);
		if (item_subtype_id == SCANER_ITEM_ID)
			pTo_scanerItem->render(rect);
		if (item_subtype_id == GRAPPLE_ITEM_ID)
			pTo_grappleItem->render(rect);
    
		//modules 
		if (item_subtype_id == LAZER_MODULE_ID)
			pTo_lazerModule->render(rect);
		if (item_subtype_id == ROCKET_MODULE_ID)
			pTo_rocketModule->render(rect);
		if (item_subtype_id == RADAR_MODULE_ID)
			pTo_radarModule->render(rect);
		if (item_subtype_id == DRIVE_MODULE_ID)
			pTo_driveModule->render(rect);
		if (item_subtype_id == BAK_MODULE_ID)
			pTo_bakModule->render(rect);
		if (item_subtype_id == ENERGIZER_MODULE_ID)
			pTo_energizerModule->render(rect);
		if (item_subtype_id == PROTECTOR_MODULE_ID)
			pTo_protectorModule->render(rect);   
		if (item_subtype_id == DROID_MODULE_ID)
			pTo_droidModule->render(rect);
		if (item_subtype_id == FREEZER_MODULE_ID)
			pTo_freezerModule->render(rect);
		if (item_subtype_id == SCANER_MODULE_ID)
			pTo_scanerModule->render(rect);
		if (item_subtype_id == GRAPPLE_MODULE_ID)
			pTo_grappleModule->render(rect);
	}
}




void OtsecSlot :: renderFrames(GLuint flash_tex)
{
      //def renderFrames(self, flash_tex):
          //self.renderStaticFramesLoop()
          //if self.flash == True:
             //drawTexturedRect(flash_tex, self.rect, -1.0)
          //if self.item != None:
             //self.item.renderInSlot(self.rect)
}




void OtsecSlot :: renderItemInfo()
{
	if (is_EQUIPED == true)
	{
		// items
		if (item_subtype_id == LAZER_ITEM_ID)
          		pTo_lazerItem->renderInfo(rect);
		if (item_subtype_id == ROCKET_ITEM_ID)
			pTo_rocketItem->renderInfo(rect);
		if (item_subtype_id == RADAR_ITEM_ID)
			pTo_radarItem->renderInfo(rect);
		if (item_subtype_id == DRIVE_ITEM_ID)
			pTo_driveItem->renderInfo(rect);
		if (item_subtype_id == BAK_ITEM_ID)
			pTo_bakItem->renderInfo(rect);
		if (item_subtype_id == ENERGIZER_ITEM_ID)
			pTo_energizerItem->renderInfo(rect);
		if (item_subtype_id == PROTECTOR_ITEM_ID)
			pTo_protectorItem->renderInfo(rect);   
		if (item_subtype_id == DROID_ITEM_ID)
			pTo_droidItem->renderInfo(rect);
		if (item_subtype_id == FREEZER_ITEM_ID)
			pTo_freezerItem->renderInfo(rect);
		if (item_subtype_id == SCANER_ITEM_ID)
			pTo_scanerItem->renderInfo(rect);
		if (item_subtype_id == GRAPPLE_ITEM_ID)
			pTo_grappleItem->renderInfo(rect);
     
		// modules
		if (item_subtype_id == LAZER_MODULE_ID)
			pTo_lazerModule->renderInfo(rect);
		if (item_subtype_id == ROCKET_MODULE_ID)
			pTo_rocketModule->renderInfo(rect);
		if (item_subtype_id == RADAR_MODULE_ID)
			pTo_radarModule->renderInfo(rect);
		if (item_subtype_id == DRIVE_MODULE_ID)
			pTo_driveModule->renderInfo(rect);
		if (item_subtype_id == BAK_MODULE_ID)
			pTo_bakModule->renderInfo(rect);
		if (item_subtype_id == ENERGIZER_MODULE_ID)
			pTo_energizerModule->renderInfo(rect);
        	if (item_subtype_id == PROTECTOR_MODULE_ID)
			pTo_protectorModule->renderInfo(rect);   
		if (item_subtype_id == DROID_MODULE_ID)
			pTo_droidModule->renderInfo(rect);
		if (item_subtype_id == FREEZER_MODULE_ID)
			pTo_freezerModule->renderInfo(rect);
		if (item_subtype_id == SCANER_MODULE_ID)
			pTo_scanerModule->renderInfo(rect);
		if (item_subtype_id == GRAPPLE_MODULE_ID)
			pTo_grappleModule->renderInfo(rect);
	}      
}
