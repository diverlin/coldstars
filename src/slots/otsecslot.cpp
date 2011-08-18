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

bool OtsecSlot :: insertItem(RocketItem* pTo_item)
{
	pTo_rocketEquipment = pTo_item;
    
        item_type_id    = pTo_item->type_id;
	item_subtype_id = pTo_item->subtype_id;  
	
	is_EQUIPED = true; 
   
	if (type_id == WEAPON_SLOT_ID)
	{
		pTo_ship->updateFireAbility();
	}

	return true;
}

bool OtsecSlot :: insertItem(LazerItem* pTo_item)
{
	pTo_lazerEquipment = pTo_item;
    
	item_type_id    = pTo_item->type_id;
	item_subtype_id = pTo_item->subtype_id;
	          
	is_EQUIPED = true;
    
	if (type_id == WEAPON_SLOT_ID)
	{
		pTo_ship->updateFireAbility();
	}
	
	return true;
}

bool OtsecSlot :: insertItem(RadarItem* pTo_item)
{
	pTo_radarEquipment = pTo_item;
    
	item_type_id    = pTo_item->type_id;
	item_subtype_id = pTo_item->subtype_id;
	 
	is_EQUIPED = true; 
    
	if (type_id == RADAR_ID)
	{
		pTo_ship->updateRadarAbility();
	}
    	
    	return true;
}

bool OtsecSlot :: insertItem(DriveItem* pTo_item)
{
	pTo_driveEquipment = pTo_item;
   
	item_type_id    = pTo_item->type_id;
	item_subtype_id = pTo_item->subtype_id;
	  
	is_EQUIPED = true; 
    
	if (type_id == DRIVE_ID)
	{
		pTo_ship->updateDriveAbility();
		pTo_ship->updateJumpAbility();
	}

	return true;
}

bool OtsecSlot :: insertItem(BakItem* pTo_item)
{
	pTo_bakItem = pTo_item;
    
	item_type_id    = pTo_item->type_id;
	item_subtype_id = pTo_item->subtype_id;
	 
	is_EQUIPED = true; 
    
	if (type_id == BAK_ID)
	{
		pTo_ship->updateDriveAbility();
		pTo_ship->updateJumpAbility();
	}

	return true;
}

bool OtsecSlot :: insertItem(EnergizerItem* pTo_item)
{
	pTo_energizerItem = pTo_item;
    
	item_type_id    = pTo_item->type_id;
	item_subtype_id = pTo_item->subtype_id;
	 
	is_EQUIPED = true; 
    
	if (type_id == ENERGIZER_ID)
	{
		pTo_ship->updateEnergyAbility();
	}

	return true;
}

bool OtsecSlot :: insertItem(ProtectorItem* pTo_item)
{
	pTo_protectorItem = pTo_item;
    
	item_type_id    = pTo_item->type_id;
	item_subtype_id = pTo_item->subtype_id;
	
	is_EQUIPED = true; 
    
	if (type_id == PROTECTOR_ID)
	{
		pTo_ship->updateProtectionAbility();
	}

	return true;
}

bool OtsecSlot :: insertItem(DroidItem* pTo_item)
{
	pTo_droidItem = pTo_item;

	item_type_id    = pTo_item->type_id;
	item_subtype_id = pTo_item->subtype_id;
	  
	is_EQUIPED = true; 
    
	if (type_id == DROID_ID)
	{
		pTo_ship->updateRepairAbility();
	}

	return true;
}

bool OtsecSlot :: insertItem(FreezerItem* pTo_item)
{
	pTo_freezerItem = pTo_item;

	item_type_id    = pTo_item->type_id;
	item_subtype_id = pTo_item->subtype_id;
	 
	is_EQUIPED = true; 
    
	if (type_id == FREEZER_ID)
	{
		pTo_ship->updateFreezeAbility();
	}

	return true;
}

bool OtsecSlot :: insertItem(ScanerItem* pTo_item)
{
	pTo_scanerItem = pTo_item;

	item_type_id    = pTo_item->type_id;
	item_subtype_id = pTo_item->subtype_id;
	
	is_EQUIPED = true; 
    
	if (type_id == SCANER_ID)
	{
		pTo_ship->updateScanAbility();
	}

	return true;
}

bool OtsecSlot :: insertItem(GrappleItem* pTo_item)
{
	pTo_grappleItem = pTo_item;

	item_type_id    = pTo_item->type_id;
	item_subtype_id = pTo_item->subtype_id;
	
	is_EQUIPED = true; 
    
	if (type_id == GRAPPLE_ID)
	{
		pTo_ship->updateGrabAbility();
	}

	return true;
}

//MODULES
bool OtsecSlot :: insertItem(RocketModule* pTo_item)
{
     	if ( (type_id == OTSEC_SLOT_ID) || (type_id == WEAPON_SLOT_ID) )
	{       
		if ( (is_EQUIPED == true) && (item_subtype_id == ROCKET_ID) )
	        {
			if (pTo_rocketEquipment->insertModule(pTo_item) == true)
			{
				return true;
			}
	        }
	        else
	        {
	        	if (type_id == OTSEC_SLOT_ID)
	        	{
				pTo_rocketModule = pTo_item;
				pTo_rocketModule->rect.setNewCenter(rect.center_x, rect.center_y);

				item_type_id    = pTo_item->type_id;
				item_subtype_id = pTo_item->subtype_id;
	
				is_EQUIPED = true;
				return true;
			}
		}
	}
	  
	return false;
}

bool OtsecSlot :: insertItem(LazerModule* pTo_item)
{
     	if (type_id == OTSEC_SLOT_ID)
	{
		pTo_lazerModule = pTo_item;
		pTo_lazerModule->rect.setNewCenter(rect.center_x, rect.center_y);

		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	
		is_EQUIPED = true;
		return true;
	}
	else
		return false; 
}

bool OtsecSlot :: insertItem(RadarModule* pTo_item)
{
     	if ( (type_id == OTSEC_SLOT_ID) || (type_id == RADAR_ID) )
	{       
		if (is_EQUIPED == true)
		{ 
			if ( (item_type_id == EQUIPMENT_ID) && (item_subtype_id == RADAR_ID) )
	        	{
				if (pTo_radarEquipment->insertModule(pTo_item) == true)
				{
					return true;
				}
	        	}
	        }
	        else
	        {
	        	if (type_id == OTSEC_SLOT_ID)
	        	{
				pTo_radarModule = pTo_item;
				pTo_radarModule->rect.setNewCenter(rect.center_x, rect.center_y);

				item_type_id    = pTo_item->type_id;
				item_subtype_id = pTo_item->subtype_id;
	
				is_EQUIPED = true;
				printf("work DONE once\n");
				return true;
			}
		}
	}
	  
	return false;
}

bool OtsecSlot :: insertItem(DriveModule* pTo_item)
{
     	if (type_id == OTSEC_SLOT_ID)
	{
		pTo_driveModule = pTo_item;
		pTo_driveModule->rect.setNewCenter(rect.center_x, rect.center_y);

		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	 
		is_EQUIPED = true; 
		return true;
	}
	else
		return false; 
}

bool OtsecSlot :: insertItem(BakModule* pTo_item)
{
     	if (type_id == OTSEC_SLOT_ID)
	{
		pTo_bakModule = pTo_item;
		pTo_bakModule->rect.setNewCenter(rect.center_x, rect.center_y);

		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	
		is_EQUIPED = true;
		return true;
	}
	else
		return false; 
		 
}

bool OtsecSlot :: insertItem(EnergizerModule* pTo_item)
{
     	if (type_id == OTSEC_SLOT_ID)
	{
		pTo_energizerModule = pTo_item;
		pTo_energizerModule->rect.setNewCenter(rect.center_x, rect.center_y);

		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	
		is_EQUIPED = true;
		return true;
	}
	else
		return false; 
}

bool OtsecSlot :: insertItem(ProtectorModule* pTo_item)
{
     	if (type_id == OTSEC_SLOT_ID)
	{
		pTo_protectorModule = pTo_item;
		pTo_protectorModule->rect.setNewCenter(rect.center_x, rect.center_y);

		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	  
		is_EQUIPED = true;
		return true;
	}
	else
		return false; 
}

bool OtsecSlot :: insertItem(DroidModule* pTo_item)
{
     	if (type_id == OTSEC_SLOT_ID)
	{
		pTo_droidModule = pTo_item;
		pTo_droidModule->rect.setNewCenter(rect.center_x, rect.center_y);

		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	 
		is_EQUIPED = true;
		return true;
	}
	else
		return false; 
}

bool OtsecSlot :: insertItem(FreezerModule* pTo_item)
{
     	if (type_id == OTSEC_SLOT_ID)
	{
		pTo_freezerModule = pTo_item;
		pTo_freezerModule->rect.setNewCenter(rect.center_x, rect.center_y);
    
		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	 
		is_EQUIPED = true;
		return true;
	}
	else
		return false; 
}

bool OtsecSlot :: insertItem(ScanerModule* pTo_item)
{
     	if (type_id == OTSEC_SLOT_ID)
	{
		pTo_scanerModule = pTo_item;
		pTo_scanerModule->rect.setNewCenter(rect.center_x, rect.center_y);

		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	
		is_EQUIPED = true;
		return true;
	}
	else
		return false;  
}

bool OtsecSlot :: insertItem(GrappleModule* pTo_item)
{
     	if (type_id == OTSEC_SLOT_ID)
	{
		pTo_grappleModule = pTo_item;
		pTo_grappleModule->rect.setNewCenter(rect.center_x, rect.center_y);
        
		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
		is_EQUIPED = true; 
		return true;
	}
	else
		return false;
}


void OtsecSlot :: removeItem()
{
	is_EQUIPED = false; 
	
	if (item_type_id == EQUIPMENT_ID)
	{
		if (item_subtype_id == ROCKET_ID)
		{
    			pTo_rocketEquipment = NULL;
    			if (type_id != OTSEC_SLOT_ID)
    				pTo_ship->updateFireAbility();
    		}
    	
    		if (item_subtype_id == LAZER_ID)
		{
    			pTo_lazerEquipment = NULL;
    			if (type_id != OTSEC_SLOT_ID)
    				pTo_ship->updateFireAbility();
    		}
    
        	if (item_subtype_id == RADAR_ID)
		{
    			pTo_radarEquipment = NULL;
    			if (type_id != OTSEC_SLOT_ID)
    				pTo_ship->updateRadarAbility();
    		}
    						
        	if (item_subtype_id == DRIVE_ID)
		{
    			pTo_driveEquipment = NULL;
    			if (type_id != OTSEC_SLOT_ID)
    			{ 
    				pTo_ship->updateDriveAbility();
    				pTo_ship->updateJumpAbility();
    			}	
    		}

        	if (item_subtype_id == BAK_ID)
		{
    			pTo_bakItem = NULL;
    			if (type_id != OTSEC_SLOT_ID)
    			{ 
    				pTo_ship->updateDriveAbility();
    				pTo_ship->updateJumpAbility();
    			}
    		}

        	if (item_subtype_id == ENERGIZER_ID)
		{
    			pTo_energizerItem = NULL;
    			if (type_id != OTSEC_SLOT_ID)
    				pTo_ship->updateEnergyAbility();
    		}

        	if (item_subtype_id == PROTECTOR_ID)
		{
    			pTo_protectorItem = NULL;
    			if (type_id != OTSEC_SLOT_ID)
    				pTo_ship->updateProtectionAbility();
    		}
    	
        	if (item_subtype_id == DROID_ID)
		{
    			pTo_droidItem = NULL;
    			if (type_id != OTSEC_SLOT_ID)
    				pTo_ship->updateRepairAbility();
    		}

        	if (item_subtype_id == FREEZER_ID)
		{
    			pTo_freezerItem = NULL;
    			if (type_id != OTSEC_SLOT_ID)
    				pTo_ship->updateFreezeAbility();
    		}
    	

 	       if (item_subtype_id == SCANER_ID)
		{
    			pTo_scanerItem = NULL;
    			if (type_id != OTSEC_SLOT_ID)
    				pTo_ship->updateScanAbility();
    		}
    	
        	if (item_subtype_id == GRAPPLE_ID)
		{
    			pTo_grappleItem = NULL;
    			if (type_id != OTSEC_SLOT_ID)
    				pTo_ship->updateGrabAbility();
    		}
    	}
    	
    	if (item_type_id == MODULE_ID)
	{
        	if (item_subtype_id == ROCKET_ID)
		{
    			pTo_rocketModule = NULL;
    		}	 

        	if (item_subtype_id == LAZER_ID)
		{
    			pTo_lazerModule = NULL;
    		}	 
    	
        	if (item_subtype_id == RADAR_ID)
		{
    			pTo_radarModule = NULL;
    		}	 
    	
        	if (item_subtype_id == DRIVE_ID)
		{
    			pTo_driveModule = NULL;
    		}	 
    		
        	if (item_subtype_id == BAK_ID)
		{
    			pTo_bakModule = NULL;
    		}
    	
        	if (item_subtype_id == ENERGIZER_ID)
		{
    			pTo_energizerModule = NULL;
    		}

       		if (item_subtype_id == PROTECTOR_ID)
		{
    			pTo_protectorModule = NULL;
    		}

        	if (item_subtype_id == DROID_ID)
		{
    			pTo_droidModule = NULL;
    		}

        	if (item_subtype_id == FREEZER_ID)
		{
    			pTo_freezerModule = NULL;
    		}	
    	
    		if (item_subtype_id == SCANER_ID)
		{
    			pTo_scanerModule = NULL;
    		}

    		if (item_subtype_id == GRAPPLE_ID)
		{
    			pTo_grappleModule = NULL;
    		}
    	}

		item_type_id    = -1;
		item_subtype_id = -1;
}



int OtsecSlot :: getItemMass()
{  
	if (item_type_id == EQUIPMENT_ID)
	{
		if (item_subtype_id == LAZER_ID)  
			return pTo_lazerEquipment->mass;
		if (item_subtype_id == ROCKET_ID)
			return pTo_rocketEquipment->mass;
		if (item_subtype_id == ENERGIZER_ID)
			return pTo_energizerItem->mass;
		if (item_subtype_id == FREEZER_ID)
			return pTo_freezerItem->mass;
		if (item_subtype_id == GRAPPLE_ID)
			return pTo_grappleItem->mass;
		if (item_subtype_id == RADAR_ID)
			return pTo_radarEquipment->mass;
		if (item_subtype_id == DRIVE_ID)
			return pTo_driveEquipment->mass;
		if (item_subtype_id == PROTECTOR_ID)
			return pTo_protectorItem->mass;
		if (item_subtype_id == BAK_ID)
			return pTo_bakItem->mass;
		if (item_subtype_id == DROID_ID)
			return pTo_droidItem->mass;
		if (item_subtype_id == SCANER_ID)
			return pTo_scanerItem->mass;
	}
	
	if (item_type_id == MODULE_ID)
	{
		return 1;
	}
	
}





int OtsecSlot :: getItemPrice()
{  
	if (item_type_id == EQUIPMENT_ID)
	{
		if (item_subtype_id == LAZER_ID)  
			return pTo_lazerEquipment->price;
		if (item_subtype_id == ROCKET_ID)
			return pTo_rocketEquipment->price;
		if (item_subtype_id == ENERGIZER_ID)
			return pTo_energizerItem->price;
		if (item_subtype_id == FREEZER_ID)
			return pTo_freezerItem->price;
		if (item_subtype_id == GRAPPLE_ID)
			return pTo_grappleItem->price;
		if (item_subtype_id == RADAR_ID)
			return pTo_radarEquipment->price;
		if (item_subtype_id == DRIVE_ID)
			return pTo_driveEquipment->price;
		if (item_subtype_id == PROTECTOR_ID)
			return pTo_protectorItem->price;
		if (item_subtype_id == BAK_ID)
			return pTo_bakItem->price;
		if (item_subtype_id == DROID_ID)
			return pTo_droidItem->price;
		if (item_subtype_id == SCANER_ID)
			return pTo_scanerItem->price;
	}
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
		if (item_type_id == EQUIPMENT_ID)
		{
			//items 
			if (item_subtype_id == LAZER_ID)
				pTo_lazerEquipment->render(rect);
			if (item_subtype_id == ROCKET_ID)
				pTo_rocketEquipment->render(rect);
			if (item_subtype_id == RADAR_ID)
				pTo_radarEquipment->render(rect);
			if (item_subtype_id == DRIVE_ID)
				pTo_driveEquipment->render(rect);
			if (item_subtype_id == BAK_ID)
				pTo_bakItem->render(rect);
			if (item_subtype_id == ENERGIZER_ID)
				pTo_energizerItem->render(rect);
			if (item_subtype_id == PROTECTOR_ID)
          			pTo_protectorItem->render(rect);   
			if (item_subtype_id == DROID_ID)
				pTo_droidItem->render(rect);
			if (item_subtype_id == FREEZER_ID)
				pTo_freezerItem->render(rect);
			if (item_subtype_id == SCANER_ID)
				pTo_scanerItem->render(rect);
			if (item_subtype_id == GRAPPLE_ID)
				pTo_grappleItem->render(rect);
    		}
    		
    		if (item_type_id == MODULE_ID)
    		{
			//modules 
			if (item_subtype_id == LAZER_ID)
				pTo_lazerModule->render(rect);
			if (item_subtype_id == ROCKET_ID)
				pTo_rocketModule->render(rect);
			if (item_subtype_id == RADAR_ID)
				pTo_radarModule->render(rect);
			if (item_subtype_id == DRIVE_ID)
				pTo_driveModule->render(rect);
			if (item_subtype_id == BAK_ID)
				pTo_bakModule->render(rect);
			if (item_subtype_id == ENERGIZER_ID)
				pTo_energizerModule->render(rect);
			if (item_subtype_id == PROTECTOR_ID)
				pTo_protectorModule->render(rect);   
			if (item_subtype_id == DROID_ID)
				pTo_droidModule->render(rect);
			if (item_subtype_id == FREEZER_ID)
				pTo_freezerModule->render(rect);
			if (item_subtype_id == SCANER_ID)
				pTo_scanerModule->render(rect);
			if (item_subtype_id == GRAPPLE_ID)
				pTo_grappleModule->render(rect);
		}
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
		if (item_type_id == EQUIPMENT_ID)
		{
			// items
			if (item_subtype_id == LAZER_ID)
          			pTo_lazerEquipment->renderInfo(rect);
			if (item_subtype_id == ROCKET_ID)
				pTo_rocketEquipment->renderInfo(rect);
			if (item_subtype_id == RADAR_ID)
				pTo_radarEquipment->renderInfo(rect);
			if (item_subtype_id == DRIVE_ID)
				pTo_driveEquipment->renderInfo(rect);
			if (item_subtype_id == BAK_ID)
				pTo_bakItem->renderInfo(rect);
			if (item_subtype_id == ENERGIZER_ID)
				pTo_energizerItem->renderInfo(rect);
			if (item_subtype_id == PROTECTOR_ID)
				pTo_protectorItem->renderInfo(rect);   
			if (item_subtype_id == DROID_ID)
				pTo_droidItem->renderInfo(rect);
			if (item_subtype_id == FREEZER_ID)
				pTo_freezerItem->renderInfo(rect);
			if (item_subtype_id == SCANER_ID)
				pTo_scanerItem->renderInfo(rect);
			if (item_subtype_id == GRAPPLE_ID)
				pTo_grappleItem->renderInfo(rect);
     		}
     		
     		if (item_type_id == MODULE_ID)
     		{
			// modules
			if (item_subtype_id == LAZER_ID)
				pTo_lazerModule->renderInfo(rect);
			if (item_subtype_id == ROCKET_ID)
				pTo_rocketModule->renderInfo(rect);
			if (item_subtype_id == RADAR_ID)
				pTo_radarModule->renderInfo(rect);
			if (item_subtype_id == DRIVE_ID)
				pTo_driveModule->renderInfo(rect);
			if (item_subtype_id == BAK_ID)
				pTo_bakModule->renderInfo(rect);
			if (item_subtype_id == ENERGIZER_ID)
				pTo_energizerModule->renderInfo(rect);
        		if (item_subtype_id == PROTECTOR_ID)
				pTo_protectorModule->renderInfo(rect);   
			if (item_subtype_id == DROID_ID)
				pTo_droidModule->renderInfo(rect);
			if (item_subtype_id == FREEZER_ID)
				pTo_freezerModule->renderInfo(rect);
			if (item_subtype_id == SCANER_ID)
				pTo_scanerModule->renderInfo(rect);
			if (item_subtype_id == GRAPPLE_ID)
				pTo_grappleModule->renderInfo(rect);
		}
	}      
}
