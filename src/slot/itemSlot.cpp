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

#include "itemSlot.h"


ItemSlot :: ItemSlot()
{}


ItemSlot :: ItemSlot(int _subtype_id, Ship* _pTo_ship, TextureOb* _pTo_texOb, int _pos_x, int _pos_y)
{
        type_id    = SLOT_ID;
	subtype_id = _subtype_id;
        
        pTo_ship  = _pTo_ship; 

        pTo_texOb = _pTo_texOb;
        w = pTo_texOb->w;
        h = pTo_texOb->h;
     
        rect = Rect(_pos_x, _pos_y, w, h);         // create rect with size of the texture

        item_type_id    = -1;
        item_subtype_id = -1;
     
        is_EQUIPED       = false;
        is_FLASHING      = false;
        is_CURSORED      = false;         
}

RocketEquipment* ItemSlot :: get_pToRocketEquipment() const
{
        return pTo_rocketEquipment;
}

LazerEquipment* ItemSlot :: get_pToLazerEquipment() const
{
        return pTo_lazerEquipment;
}

RadarEquipment* ItemSlot :: get_pToRadarEquipment() const
{
        return pTo_radarEquipment;
}

DriveEquipment* ItemSlot :: get_pToDriveEquipment() const
{
        return pTo_driveEquipment;
}

BakEquipment* ItemSlot :: get_pToBakEquipment() const
{
        return pTo_bakEquipment;
}

EnergizerEquipment* ItemSlot :: get_pToEnergizerEquipment() const
{
        return pTo_energizerEquipment;
}

ProtectorEquipment* ItemSlot :: get_pToProtectorEquipment() const
{
        return pTo_protectorEquipment;
}

DroidEquipment* ItemSlot :: get_pToDroidEquipment() const
{
        return pTo_droidEquipment;
}

FreezerEquipment* ItemSlot :: get_pToFreezerEquipment() const
{
        return pTo_freezerEquipment;
}

ScanerEquipment* ItemSlot :: get_pToScanerEquipment() const
{
        return pTo_scanerEquipment;
}

GrappleEquipment* ItemSlot :: get_pToGrappleEquipment() const
{
        return pTo_grappleEquipment;
}

RocketModule* ItemSlot :: get_pToRocketModule() const
{
        return pTo_rocketModule;
}

LazerModule* ItemSlot :: get_pToLazerModule() const
{
        return pTo_lazerModule;
}

RadarModule* ItemSlot :: get_pToRadarModule() const
{
        return pTo_radarModule;
}

DriveModule* ItemSlot :: get_pToDriveModule() const
{
        return pTo_driveModule;
}

BakModule* ItemSlot :: get_pToBakModule() const
{
        return pTo_bakModule;
}

EnergizerModule* ItemSlot :: get_pToEnergizerModule() const
{
        return pTo_energizerModule;
}

ProtectorModule* ItemSlot :: get_pToProtectorModule() const
{
        return pTo_protectorModule;
}

DroidModule* ItemSlot :: get_pToDroidModule() const
{
        return pTo_droidModule;
}

FreezerModule* ItemSlot :: get_pToFreezerModule() const
{
        return pTo_freezerModule;
}

ScanerModule* ItemSlot :: get_pToScanerModule() const
{
        return pTo_scanerModule;
}

GrappleModule* ItemSlot :: get_pToGrappleModule() const
{
        return pTo_grappleModule;
}


bool ItemSlot :: insertItem(RocketEquipment* pTo_item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == WEAPON_SLOT_ID))
	{
		pTo_rocketEquipment = pTo_item;
    
        	item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;  
	
		is_EQUIPED = true; 
   
		if (subtype_id == WEAPON_SLOT_ID)
		{
			pTo_ship->updateFireAbility();
		}

		return true;
	}
	else
		return false;
	
}

bool ItemSlot :: insertItem(LazerEquipment* pTo_item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == WEAPON_SLOT_ID))
	{	
		pTo_lazerEquipment = pTo_item;
    
		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	          
		is_EQUIPED = true;
    
		if (subtype_id == WEAPON_SLOT_ID)
		{
			pTo_ship->updateFireAbility();
		}
	
		return true;
	}
	else
		return false;
}

bool ItemSlot :: insertItem(RadarEquipment* pTo_item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == RADAR_ID))
	{	
		pTo_radarEquipment = pTo_item;
    
		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	 
		is_EQUIPED = true; 
    
		if (subtype_id == RADAR_ID)
		{
			pTo_ship->updateRadarAbility();
		}
    	
		return true;
	}
	else
		return false;
}

bool ItemSlot :: insertItem(DriveEquipment* pTo_item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == DRIVE_ID))
	{	
		pTo_driveEquipment = pTo_item;
   
		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	  
		is_EQUIPED = true; 
    
		if (subtype_id == DRIVE_ID)
		{
			pTo_ship->updateDriveAbility();
			pTo_ship->updateJumpAbility();
		}

		return true;
	}
	else
		return false;
}

bool ItemSlot :: insertItem(BakEquipment* pTo_item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == BAK_ID))
	{
		pTo_bakEquipment = pTo_item;
    
		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	 
		is_EQUIPED = true; 
    
		if (subtype_id == BAK_ID)
		{
			pTo_ship->updateDriveAbility();
			pTo_ship->updateJumpAbility();
		}

		return true;
	}
	else
		return false;
}

bool ItemSlot :: insertItem(EnergizerEquipment* pTo_item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == ENERGIZER_ID))
	{
		pTo_energizerEquipment = pTo_item;
    
		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	 
		is_EQUIPED = true; 
    
		if (subtype_id == ENERGIZER_ID)
		{
			pTo_ship->updateEnergyAbility();
		}

		return true;
	}
	else
		return false;
}

bool ItemSlot :: insertItem(ProtectorEquipment* pTo_item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == PROTECTOR_ID))
	{
		pTo_protectorEquipment = pTo_item;
    
		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	
		is_EQUIPED = true; 
    
		if (subtype_id == PROTECTOR_ID)
		{
			pTo_ship->updateProtectionAbility();
		}

		return true;
	}
	else
		return false;
}

bool ItemSlot :: insertItem(DroidEquipment* pTo_item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == DROID_ID))
	{
		pTo_droidEquipment = pTo_item;

		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	  
		is_EQUIPED = true; 
    
		if (subtype_id == DROID_ID)
		{
			pTo_ship->updateRepairAbility();
		}

		return true;
	}
	else
		return false;	
}

bool ItemSlot :: insertItem(FreezerEquipment* pTo_item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == FREEZER_ID))
	{
		pTo_freezerEquipment = pTo_item;

		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	 
		is_EQUIPED = true; 
    
		if (subtype_id == FREEZER_ID)
		{
			pTo_ship->updateFreezeAbility();
		}

		return true;
	}
	else
		return false;	
}

bool ItemSlot :: insertItem(ScanerEquipment* pTo_item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == SCANER_ID))
	{
		pTo_scanerEquipment = pTo_item;

		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	
		is_EQUIPED = true; 
    
		if (subtype_id == SCANER_ID)
		{
			pTo_ship->updateScanAbility();
		}

		return true;
	}
	else
		return false;	
}

bool ItemSlot :: insertItem(GrappleEquipment* pTo_item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == GRAPPLE_ID))
	{
		pTo_grappleEquipment = pTo_item;

		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	
		is_EQUIPED = true; 
    
		if (subtype_id == GRAPPLE_ID)
		{
			pTo_ship->updateGrabAbility();
		}

		return true;
	}
	else
		return false;
}

//MODULES
bool ItemSlot :: insertItem(RocketModule* pTo_item)
{
	if (subtype_id == UNIVERSAL_SLOT_ID)
	{
		pTo_rocketModule = pTo_item;
		pTo_rocketModule->rect.setNewCenter(rect.center_x, rect.center_y);

		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	
		is_EQUIPED = true;
		return true;
	}
	else
		return false; 
}

bool ItemSlot :: insertItem(LazerModule* pTo_item)
{
	if (subtype_id == UNIVERSAL_SLOT_ID)
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

bool ItemSlot :: insertItem(RadarModule* pTo_item)
{
	if (subtype_id == UNIVERSAL_SLOT_ID)
	{
		pTo_radarModule = pTo_item;
		pTo_radarModule->rect.setNewCenter(rect.center_x, rect.center_y);

		item_type_id    = pTo_item->type_id;
		item_subtype_id = pTo_item->subtype_id;
	
		is_EQUIPED = true;

		return true;
	}
	else
		return false; 
		
}

bool ItemSlot :: insertItem(DriveModule* pTo_item)
{
	if (subtype_id == UNIVERSAL_SLOT_ID)
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

bool ItemSlot :: insertItem(BakModule* pTo_item)
{     	
	if (subtype_id == UNIVERSAL_SLOT_ID)
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

bool ItemSlot :: insertItem(EnergizerModule* pTo_item)
{
     	if (subtype_id == UNIVERSAL_SLOT_ID)
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

bool ItemSlot :: insertItem(ProtectorModule* pTo_item)
{
     	if (subtype_id == UNIVERSAL_SLOT_ID)
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

bool ItemSlot :: insertItem(DroidModule* pTo_item)
{
     	if (subtype_id == UNIVERSAL_SLOT_ID)
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

bool ItemSlot :: insertItem(FreezerModule* pTo_item)
{
     	if (subtype_id == UNIVERSAL_SLOT_ID)
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

bool ItemSlot :: insertItem(ScanerModule* pTo_item)
{
     	if (subtype_id == UNIVERSAL_SLOT_ID)
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

bool ItemSlot :: insertItem(GrappleModule* pTo_item)
{
     	if (subtype_id == UNIVERSAL_SLOT_ID)
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


void ItemSlot :: removeItem()
{
	is_EQUIPED = false; 
	
	if (item_type_id == EQUIPMENT_ID)
	{
		if (item_subtype_id == ROCKET_ID)
		{
    			pTo_rocketEquipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				pTo_ship->updateFireAbility();
    		}
    	
    		if (item_subtype_id == LAZER_ID)
		{
    			pTo_lazerEquipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				pTo_ship->updateFireAbility();
    		}
    
        	if (item_subtype_id == RADAR_ID)
		{
    			pTo_radarEquipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				pTo_ship->updateRadarAbility();
      		}
    						
        	if (item_subtype_id == DRIVE_ID)
		{
    			pTo_driveEquipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    			{ 
    				pTo_ship->updateDriveAbility();
    				pTo_ship->updateJumpAbility();
    			}	
    		}

        	if (item_subtype_id == BAK_ID)
		{
    			pTo_bakEquipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    			{ 
    				pTo_ship->updateDriveAbility();
    				pTo_ship->updateJumpAbility();
    			}
    		}

        	if (item_subtype_id == ENERGIZER_ID)
		{
    			pTo_energizerEquipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				pTo_ship->updateEnergyAbility();
    		}

        	if (item_subtype_id == PROTECTOR_ID)
		{
    			pTo_protectorEquipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				pTo_ship->updateProtectionAbility();
    		}
    	
        	if (item_subtype_id == DROID_ID)
		{
    			pTo_droidEquipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				pTo_ship->updateRepairAbility();
    		}

        	if (item_subtype_id == FREEZER_ID)
		{
    			pTo_freezerEquipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				pTo_ship->updateFreezeAbility();
    		}
    	

 	       if (item_subtype_id == SCANER_ID)
		{
    			pTo_scanerEquipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				pTo_ship->updateScanAbility();
    		}
    	
        	if (item_subtype_id == GRAPPLE_ID)
		{
    			pTo_grappleEquipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
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



int ItemSlot :: getItemMass()
{  
	if (item_type_id == EQUIPMENT_ID)
	{
		if (item_subtype_id == LAZER_ID)  
			return pTo_lazerEquipment->mass;
		if (item_subtype_id == ROCKET_ID)
			return pTo_rocketEquipment->mass;
		if (item_subtype_id == ENERGIZER_ID)
			return pTo_energizerEquipment->mass;
		if (item_subtype_id == FREEZER_ID)
			return pTo_freezerEquipment->mass;
		if (item_subtype_id == GRAPPLE_ID)
			return pTo_grappleEquipment->mass;
		if (item_subtype_id == RADAR_ID)
			return pTo_radarEquipment->mass;
		if (item_subtype_id == DRIVE_ID)
			return pTo_driveEquipment->mass;
		if (item_subtype_id == PROTECTOR_ID)
			return pTo_protectorEquipment->mass;
		if (item_subtype_id == BAK_ID)
			return pTo_bakEquipment->mass;
		if (item_subtype_id == DROID_ID)
			return pTo_droidEquipment->mass;
		if (item_subtype_id == SCANER_ID)
			return pTo_scanerEquipment->mass;
	}
	
	if (item_type_id == MODULE_ID)
	{
		return 1;
	}
	
}





int ItemSlot :: getItemPrice()
{  
	if (item_type_id == EQUIPMENT_ID)
	{
		if (item_subtype_id == LAZER_ID)  
			return pTo_lazerEquipment->price;
		if (item_subtype_id == ROCKET_ID)
			return pTo_rocketEquipment->price;
		if (item_subtype_id == ENERGIZER_ID)
			return pTo_energizerEquipment->price;
		if (item_subtype_id == FREEZER_ID)
			return pTo_freezerEquipment->price;
		if (item_subtype_id == GRAPPLE_ID)
			return pTo_grappleEquipment->price;
		if (item_subtype_id == RADAR_ID)
			return pTo_radarEquipment->price;
		if (item_subtype_id == DRIVE_ID)
			return pTo_driveEquipment->price;
		if (item_subtype_id == PROTECTOR_ID)
			return pTo_protectorEquipment->price;
		if (item_subtype_id == BAK_ID)
			return pTo_bakEquipment->price;
		if (item_subtype_id == DROID_ID)
			return pTo_droidEquipment->price;
		if (item_subtype_id == SCANER_ID)
			return pTo_scanerEquipment->price;
	}
}


void ItemSlot :: renderFrame(GLuint flash_tex)
{
	drawTexturedRect(pTo_texOb->texture, rect, -1.5);

	//if self.flash == True:
		//drawTexturedRect(flash_tex, self.rect, -1.0)
	renderEquipedItem();
        
}



int ItemSlot :: getItemRadius()
{ 
        if (item_type_id == EQUIPMENT_ID)
	{
		//items 
		if (item_subtype_id == LAZER_ID)
			return pTo_lazerEquipment->radius;
		if (item_subtype_id == ROCKET_ID)
			return pTo_rocketEquipment->radius;
        }
}


int ItemSlot :: getItemDamage()
{
        if (item_type_id == EQUIPMENT_ID)
	{
		//items 
		if (item_subtype_id == LAZER_ID)
			return pTo_lazerEquipment->damage;
		if (item_subtype_id == ROCKET_ID)
			return pTo_rocketEquipment->damage;
        }
}



int ItemSlot :: getItemCondition()
{  
        return 1000;
}

void ItemSlot :: renderEquipedItem()
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
			pTo_bakEquipment->render(rect);
		if (item_subtype_id == ENERGIZER_ID)
			pTo_energizerEquipment->render(rect);
		if (item_subtype_id == PROTECTOR_ID)
          		pTo_protectorEquipment->render(rect);   
		if (item_subtype_id == DROID_ID)
			pTo_droidEquipment->render(rect);
		if (item_subtype_id == FREEZER_ID)
			pTo_freezerEquipment->render(rect);
		if (item_subtype_id == SCANER_ID)
			pTo_scanerEquipment->render(rect);
		if (item_subtype_id == GRAPPLE_ID)
			pTo_grappleEquipment->render(rect);
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





void ItemSlot :: renderFrames(GLuint flash_tex)
{
      //def renderFrames(self, flash_tex):
          //self.renderStaticFramesLoop()
          //if self.flash == True:
             //drawTexturedRect(flash_tex, self.rect, -1.0)
          //if self.item != None:
             //self.item.renderInSlot(self.rect)
}




void ItemSlot :: renderItemInfo()
{
	if (item_type_id == EQUIPMENT_ID)
	{
                //switch (item_subtype_id)
                //{
                        //case LAZER_ID: pTo_lazerEquipment->renderInfo(rect); break;
                //}
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
			pTo_bakEquipment->renderInfo(rect);
		if (item_subtype_id == ENERGIZER_ID)
			pTo_energizerEquipment->renderInfo(rect);
		if (item_subtype_id == PROTECTOR_ID)
			pTo_protectorEquipment->renderInfo(rect);   
		if (item_subtype_id == DROID_ID)
			pTo_droidEquipment->renderInfo(rect);
		if (item_subtype_id == FREEZER_ID)
			pTo_freezerEquipment->renderInfo(rect);
		if (item_subtype_id == SCANER_ID)
			pTo_scanerEquipment->renderInfo(rect);
		if (item_subtype_id == GRAPPLE_ID)
			pTo_grappleEquipment->renderInfo(rect);
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



bool ItemSlot :: interaction(int _x, int _y)
{        
        float dist = lengthBetweenPoints(rect.center_x, rect.center_y, _x, _y);
        if (dist < rect.w/2)
                return true;
        else
                return false;    
}


