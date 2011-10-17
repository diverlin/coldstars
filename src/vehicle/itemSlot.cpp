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

#include "itemSlot.hpp"


ItemSlot :: ItemSlot()
{}


ItemSlot :: ItemSlot(int _subtype_id, Ship* _ship, TextureOb* _texOb, int _pos_x, int _pos_y)
{
/* 
        The class provides implementation to insert/hold/remove all game items (equipments, modules and so on)
        Depending on slot subtype there is the rule what items can be used with slot (for example 
        Lazer weapon item cannot be inserted to drive slot and so on).
*/

        type_id    = SLOT_ID;
	subtype_id = _subtype_id;
        
        ship  = _ship; 
        turrel = NULL;

        texOb = _texOb;
        w = texOb->w;
        h = texOb->h;
     
        rect = Rect(_pos_x, _pos_y, w, h);         // create rect with size of the texture

        item_type_id    = -1;
        item_subtype_id = -1;
     
        is_EQUIPED       = false;
        is_FLASHING      = false;
        is_CURSORED      = false;         
}

int ItemSlot :: getType()        const { return type_id; }
int ItemSlot :: getSubType()     const { return subtype_id; }
int ItemSlot :: getItemType()    const { return item_type_id; }
int ItemSlot :: getItemSubType() const { return item_subtype_id; }

Turrel* ItemSlot :: getTurrel() const { return turrel; }
Turrel* ItemSlot :: bindTurrel( Turrel* _turrel) {turrel = _turrel; }
                                
bool ItemSlot :: getEquipedStatus() const  { return is_EQUIPED; }
bool ItemSlot :: getCursoredStatus()            const { return is_CURSORED; }
void ItemSlot :: setCursoredStatus(bool new_status) { is_CURSORED = new_status; }
bool ItemSlot :: getFlashingStatus() const { return is_FLASHING; }
void ItemSlot :: setFlashingStatus(bool new_status) { is_FLASHING = new_status; }
                
Rect& ItemSlot :: getRect() { return rect; }

Ship* ItemSlot :: getShip() const { return ship; }
                                
RocketEquipment*    ItemSlot :: getRocketEquipment()    const { return rocket_equipment; }
LazerEquipment*     ItemSlot :: getLazerEquipment()     const { return lazer_equipment; }
RadarEquipment*     ItemSlot :: getRadarEquipment()     const { return radar_equipment; }
DriveEquipment*     ItemSlot :: getDriveEquipment()     const { return drive_equipment; }
BakEquipment*       ItemSlot :: getBakEquipment()       const { return bak_equipment; }
EnergizerEquipment* ItemSlot :: getEnergizerEquipment() const { return energizer_equipment; }
ProtectorEquipment* ItemSlot :: getProtectorEquipment() const { return protector_equipment; }
DroidEquipment*     ItemSlot :: getDroidEquipment()     const { return droid_equipment; }
FreezerEquipment*   ItemSlot :: getFreezerEquipment()   const { return freezer_equipment; }
ScanerEquipment*    ItemSlot :: getScanerEquipment()    const { return scaner_equipment; }
GrappleEquipment*   ItemSlot :: getGrappleEquipment()   const { return grapple_equipment; }
RocketModule*       ItemSlot :: getRocketModule()       const { return rocket_module; }
LazerModule*        ItemSlot :: getLazerModule()        const { return lazer_module; }
RadarModule*        ItemSlot :: getRadarModule()        const { return radar_module; }
DriveModule*        ItemSlot :: getDriveModule()        const { return drive_module; }
BakModule*          ItemSlot :: getBakModule()          const { return bak_module; }
EnergizerModule*    ItemSlot :: getEnergizerModule()    const { return energizer_module; }
ProtectorModule*    ItemSlot :: getProtectorModule()    const { return protector_module; }
DroidModule*        ItemSlot :: getDroidModule()        const { return droid_module; }
FreezerModule*      ItemSlot :: getFreezerModule()      const { return freezer_module; }
ScanerModule*       ItemSlot :: getScanerModule()       const { return scaner_module; }
GrappleModule*      ItemSlot :: getGrappleModule()      const { return grapple_module; }


bool ItemSlot :: insertItem(RocketEquipment* item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == WEAPON_SLOT_ID))
	{
		rocket_equipment = item;
    
        	item_type_id    = item->getType();
		item_subtype_id = item->getSubType();  
	
		is_EQUIPED = true; 
   
		if (subtype_id == WEAPON_SLOT_ID)
		{
			ship->updateFireAbility();
		}
                
                if (ship != NULL)
                {
                        item->bindSlot(this);
                }

		return true;
	}
	else
		return false;
	
}

bool ItemSlot :: insertItem(LazerEquipment* item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == WEAPON_SLOT_ID))
	{	
		lazer_equipment = item;
    
		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	          
		is_EQUIPED = true;
    
		if (subtype_id == WEAPON_SLOT_ID)
		{
			ship->updateFireAbility();
		}
	
                if (ship != NULL)
                {
                        item->bindSlot(this);
                }
                
		return true;
	}
	else
		return false;
}

bool ItemSlot :: insertItem(RadarEquipment* item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == RADAR_ID))
	{	
		radar_equipment = item;
    
		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	 
		is_EQUIPED = true; 
    
		if (subtype_id == RADAR_ID)
		{
			ship->updateRadarAbility();
		}
    	
                if (ship != NULL)
                {
                        item->bindSlot(this);
                }
                
		return true;
	}
	else
		return false;
}

bool ItemSlot :: insertItem(DriveEquipment* item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == DRIVE_ID))
	{	
		drive_equipment = item;
   
		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	  
		is_EQUIPED = true; 
    
		if (subtype_id == DRIVE_ID)
		{
			ship->updateDriveAbility();
			ship->updateJumpAbility();
		}

                if (ship != NULL)
                {
                        item->bindSlot(this);
                }
                
		return true;
	}
	else
		return false;
}

bool ItemSlot :: insertItem(BakEquipment* item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == BAK_ID))
	{
		bak_equipment = item;
    
		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	 
		is_EQUIPED = true; 
    
		if (subtype_id == BAK_ID)
		{
			ship->updateDriveAbility();
			ship->updateJumpAbility();
		}

                if (ship != NULL)
                {
                        item->bindSlot(this);
                }
                
		return true;
	}
	else
		return false;
}

bool ItemSlot :: insertItem(EnergizerEquipment* item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == ENERGIZER_ID))
	{
		energizer_equipment = item;
    
		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	 
		is_EQUIPED = true; 
    
		if (subtype_id == ENERGIZER_ID)
		{
			ship->updateEnergyAbility();
		}

                if (ship != NULL)
                {
                        item->bindSlot(this);
                }
                
		return true;
	}
	else
		return false;
}

bool ItemSlot :: insertItem(ProtectorEquipment* item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == PROTECTOR_ID))
	{
		protector_equipment = item;
    
		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	
		is_EQUIPED = true; 
    
		if (subtype_id == PROTECTOR_ID)
		{
			ship->updateProtectionAbility();
		}

                if (ship != NULL)
                {
                        item->bindSlot(this);
                }
                
		return true;
	}
	else
		return false;
}

bool ItemSlot :: insertItem(DroidEquipment* item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == DROID_ID))
	{
		droid_equipment = item;

		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	  
		is_EQUIPED = true; 
    
		if (subtype_id == DROID_ID)
		{
			ship->updateRepairAbility();
		}

                if (ship != NULL)
                {
                        item->bindSlot(this);
                }
                
		return true;
	}
	else
		return false;	
}

bool ItemSlot :: insertItem(FreezerEquipment* item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == FREEZER_ID))
	{
		freezer_equipment = item;

		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	 
		is_EQUIPED = true; 
    
		if (subtype_id == FREEZER_ID)
		{
			ship->updateFreezeAbility();
		}

                if (ship != NULL)
                {
                        item->bindSlot(this);
                }
                
		return true;
	}
	else
		return false;	
}

bool ItemSlot :: insertItem(ScanerEquipment* item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == SCANER_ID))
	{
		scaner_equipment = item;

		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	
		is_EQUIPED = true; 
    
		if (subtype_id == SCANER_ID)
		{
			ship->updateScanAbility();
		}

                if (ship != NULL)
                {
                        item->bindSlot(this);
                }
                
		return true;
	}
	else
		return false;	
}

bool ItemSlot :: insertItem(GrappleEquipment* item)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == GRAPPLE_ID))
	{
		grapple_equipment = item;

		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	
		is_EQUIPED = true; 
    
		if (subtype_id == GRAPPLE_ID)
		{
			ship->updateGrabAbility();
		}

                if (ship != NULL)
                {
                        item->bindSlot(this);
                }
                
		return true;
	}
	else
		return false;
}

//_moduleS
bool ItemSlot :: insertItem(RocketModule* item)
{
	if (subtype_id == UNIVERSAL_SLOT_ID)
	{
		rocket_module = item;
		//rocket_module->rect.setNewCenter(rect.getCenter());

		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	
		is_EQUIPED = true;
		return true;
	}
	else
		return false; 
}

bool ItemSlot :: insertItem(LazerModule* item)
{
	if (subtype_id == UNIVERSAL_SLOT_ID)
	{
		lazer_module = item;
		//lazer_module->rect.setNewCenter(rect.getCenter());

		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	
		is_EQUIPED = true;
		return true;
	}
	else
		return false; 	
}

bool ItemSlot :: insertItem(RadarModule* item)
{
	if (subtype_id == UNIVERSAL_SLOT_ID)
	{
		radar_module = item;
		//radar_module->rect.setNewCenter(rect.getCenter());

		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	
		is_EQUIPED = true;

		return true;
	}
	else
		return false; 
		
}

bool ItemSlot :: insertItem(DriveModule* item)
{
	if (subtype_id == UNIVERSAL_SLOT_ID)
	{
		drive_module = item;
		//drive_module->rect.setNewCenter(rect.getCenter());

		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	 
		is_EQUIPED = true; 
		return true;
	}
	else
		return false; 
}

bool ItemSlot :: insertItem(BakModule* item)
{     	
	if (subtype_id == UNIVERSAL_SLOT_ID)
	{
		bak_module = item;
		//bak_module->rect.setNewCenter(rect.getCenter());

		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	
		is_EQUIPED = true;
		return true;
	}
	else
		return false; 
}

bool ItemSlot :: insertItem(EnergizerModule* item)
{
     	if (subtype_id == UNIVERSAL_SLOT_ID)
	{
		energizer_module = item;
		//energizer_module->rect.setNewCenter(rect.getCenter());

		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	
		is_EQUIPED = true;
		return true;
	}
	else
		return false; 
}

bool ItemSlot :: insertItem(ProtectorModule* item)
{
     	if (subtype_id == UNIVERSAL_SLOT_ID)
	{
		protector_module = item;
		//protector_module->rect.setNewCenter(rect.getCenter());

		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	  
		is_EQUIPED = true;
		return true;
	}
	else
		return false; 
}

bool ItemSlot :: insertItem(DroidModule* item)
{
     	if (subtype_id == UNIVERSAL_SLOT_ID)
	{
		droid_module = item;
		//droid_module->rect.setNewCenter(rect.getCenter());

		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	 
		is_EQUIPED = true;
		return true;
	}
	else
		return false; 
}

bool ItemSlot :: insertItem(FreezerModule* item)
{
     	if (subtype_id == UNIVERSAL_SLOT_ID)
	{
		freezer_module = item;
		//freezer_module->rect.setNewCenter(rect.getCenter());
    
		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	 
		is_EQUIPED = true;
		return true;
	}
	else
		return false; 
}

bool ItemSlot :: insertItem(ScanerModule* item)
{
     	if (subtype_id == UNIVERSAL_SLOT_ID)
	{
		scaner_module = item;
		//scaner_module->rect.setNewCenter(rect.getCenter());

		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
	
		is_EQUIPED = true;
		return true;
	}
	else
		return false;  
}

bool ItemSlot :: insertItem(GrappleModule* item)
{
     	if (subtype_id == UNIVERSAL_SLOT_ID)
	{
		grapple_module = item;
		//grapple_module->rect.setNewCenter(rect.getCenter());
        
		item_type_id    = item->getType();
		item_subtype_id = item->getSubType();
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
    			rocket_equipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				ship->updateFireAbility();
    		}
    	
    		if (item_subtype_id == LAZER_ID)
		{
    			lazer_equipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				ship->updateFireAbility();
    		}
    
        	if (item_subtype_id == RADAR_ID)
		{
    			radar_equipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				ship->updateRadarAbility();
      		}
    						
        	if (item_subtype_id == DRIVE_ID)
		{
    			drive_equipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    			{ 
    				ship->updateDriveAbility();
    				ship->updateJumpAbility();
    			}	
    		}

        	if (item_subtype_id == BAK_ID)
		{
    			bak_equipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    			{ 
    				ship->updateDriveAbility();
    				ship->updateJumpAbility();
    			}
    		}

        	if (item_subtype_id == ENERGIZER_ID)
		{
    			energizer_equipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				ship->updateEnergyAbility();
    		}

        	if (item_subtype_id == PROTECTOR_ID)
		{
    			protector_equipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				ship->updateProtectionAbility();
    		}
    	
        	if (item_subtype_id == DROID_ID)
		{
    			droid_equipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				ship->updateRepairAbility();
    		}

        	if (item_subtype_id == FREEZER_ID)
		{
    			freezer_equipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				ship->updateFreezeAbility();
    		}
    	

 	       if (item_subtype_id == SCANER_ID)
		{
    			scaner_equipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				ship->updateScanAbility();
    		}
    	
        	if (item_subtype_id == GRAPPLE_ID)
		{
    			grapple_equipment = NULL;
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				ship->updateGrabAbility();
    		}
    	}
    	
    	if (item_type_id == MODULE_ID)
	{
        	if (item_subtype_id == ROCKET_ID)
		{
    			rocket_module = NULL;
    		}	 

        	if (item_subtype_id == LAZER_ID)
		{
    			lazer_module = NULL;
    		}	 
    	
        	if (item_subtype_id == RADAR_ID)
		{
    			radar_module = NULL;
    		}	 
    	
        	if (item_subtype_id == DRIVE_ID)
		{
    			drive_module = NULL;
    		}	 
    		
        	if (item_subtype_id == BAK_ID)
		{
    			bak_module = NULL;
    		}
    	
        	if (item_subtype_id == ENERGIZER_ID)
		{
    			energizer_module = NULL;
    		}

       		if (item_subtype_id == PROTECTOR_ID)
		{
    			protector_module = NULL;
    		}

        	if (item_subtype_id == DROID_ID)
		{
    			droid_module = NULL;
    		}

        	if (item_subtype_id == FREEZER_ID)
		{
    			freezer_module = NULL;
    		}	
    	
    		if (item_subtype_id == SCANER_ID)
		{
    			scaner_module = NULL;
    		}

    		if (item_subtype_id == GRAPPLE_ID)
		{
    			grapple_module = NULL;
    		}
    	}

		item_type_id    = -1;
		item_subtype_id = -1;
}



int ItemSlot :: getItemMass() const
{  
	if (item_type_id == EQUIPMENT_ID)
	{
		if (item_subtype_id == LAZER_ID)  
			return lazer_equipment->getMass();
		if (item_subtype_id == ROCKET_ID)
			return rocket_equipment->getMass();
		if (item_subtype_id == ENERGIZER_ID)
			return energizer_equipment->getMass();
		if (item_subtype_id == FREEZER_ID)
			return freezer_equipment->getMass();
		if (item_subtype_id == GRAPPLE_ID)
			return grapple_equipment->getMass();
		if (item_subtype_id == RADAR_ID)
			return radar_equipment->getMass();
		if (item_subtype_id == DRIVE_ID)
			return drive_equipment->getMass();
		if (item_subtype_id == PROTECTOR_ID)
			return protector_equipment->getMass();
		if (item_subtype_id == BAK_ID)
			return bak_equipment->getMass();
		if (item_subtype_id == DROID_ID)
			return droid_equipment->getMass();
		if (item_subtype_id == SCANER_ID)
			return scaner_equipment->getMass();
	}
	
	if (item_type_id == MODULE_ID)
	{
		return 1;
	}
	
}





int ItemSlot :: getItemPrice() const
{  
	if (item_type_id == EQUIPMENT_ID)
	{
		if (item_subtype_id == LAZER_ID)  
			return lazer_equipment->getPrice();
		if (item_subtype_id == ROCKET_ID)
			return rocket_equipment->getPrice();
		if (item_subtype_id == ENERGIZER_ID)
			return energizer_equipment->getPrice();
		if (item_subtype_id == FREEZER_ID)
			return freezer_equipment->getPrice();
		if (item_subtype_id == GRAPPLE_ID)
			return grapple_equipment->getPrice();
		if (item_subtype_id == RADAR_ID)
			return radar_equipment->getPrice();
		if (item_subtype_id == DRIVE_ID)
			return drive_equipment->getPrice();
		if (item_subtype_id == PROTECTOR_ID)
			return protector_equipment->getPrice();
		if (item_subtype_id == BAK_ID)
			return bak_equipment->getPrice();
		if (item_subtype_id == DROID_ID)
			return droid_equipment->getPrice();
		if (item_subtype_id == SCANER_ID)
			return scaner_equipment->getPrice();
	}
}


void ItemSlot :: renderFrame(GLuint flash_tex)
{
	drawTexturedRect(texOb->texture, rect, -1.5);

	//if self.flash == True:
		//drawTexturedRect(flash_tex, self.rect, -1.0)
	renderEquipedItem();
        
}


TextureOb* ItemSlot :: getItemTexOb() const
{
        if (item_type_id == EQUIPMENT_ID)
	{
		//items 
		if (item_subtype_id == LAZER_ID)
			return lazer_equipment->getTexOb();
		if (item_subtype_id == ROCKET_ID)
			return rocket_equipment->getTexOb();
        }
}
                
                
int ItemSlot :: getItemRadius() const
{ 
        if (item_type_id == EQUIPMENT_ID)
	{
		//items 
		if (item_subtype_id == LAZER_ID)
			return lazer_equipment->getRadius();
		if (item_subtype_id == ROCKET_ID)
			return rocket_equipment->getRadius();
        }
}


int ItemSlot :: getItemDamage() const
{
        if (item_type_id == EQUIPMENT_ID)
	{
		//items 
		if (item_subtype_id == LAZER_ID)
			return lazer_equipment->getDamage();
		if (item_subtype_id == ROCKET_ID)
			return rocket_equipment->getDamage();
        }
}



int ItemSlot :: getItemCondition() const
{  
        return 1000;
}

void ItemSlot :: renderEquipedItem()
{
	if (item_type_id == EQUIPMENT_ID)
	{
		//items 
		if (item_subtype_id == LAZER_ID)
			lazer_equipment->render(rect);
		if (item_subtype_id == ROCKET_ID)
			rocket_equipment->render(rect);
		if (item_subtype_id == RADAR_ID)
                        radar_equipment->render(rect);
                if (item_subtype_id == DRIVE_ID)
			drive_equipment->render(rect);
		if (item_subtype_id == BAK_ID)
			bak_equipment->render(rect);
		if (item_subtype_id == ENERGIZER_ID)
			energizer_equipment->render(rect);
		if (item_subtype_id == PROTECTOR_ID)
          		protector_equipment->render(rect);   
		if (item_subtype_id == DROID_ID)
			droid_equipment->render(rect);
		if (item_subtype_id == FREEZER_ID)
			freezer_equipment->render(rect);
		if (item_subtype_id == SCANER_ID)
			scaner_equipment->render(rect);
		if (item_subtype_id == GRAPPLE_ID)
			grapple_equipment->render(rect);
        }
    		
        if (item_type_id == MODULE_ID)
    	{
		//_modules 
		if (item_subtype_id == LAZER_ID)
			lazer_module->render(rect);
		if (item_subtype_id == ROCKET_ID)
			rocket_module->render(rect);
		if (item_subtype_id == RADAR_ID)
			radar_module->render(rect);
		if (item_subtype_id == DRIVE_ID)
			drive_module->render(rect);
		if (item_subtype_id == BAK_ID)
			bak_module->render(rect);
		if (item_subtype_id == ENERGIZER_ID)
			energizer_module->render(rect);
		if (item_subtype_id == PROTECTOR_ID)
			protector_module->render(rect);   
		if (item_subtype_id == DROID_ID)
			droid_module->render(rect);
		if (item_subtype_id == FREEZER_ID)
			freezer_module->render(rect);
		if (item_subtype_id == SCANER_ID)
			scaner_module->render(rect);
		if (item_subtype_id == GRAPPLE_ID)
			grapple_module->render(rect);
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




void ItemSlot :: renderItemInfo(float offset_x, float offset_y)
{
	if (item_type_id == EQUIPMENT_ID)
	{
                //switch (item_subtype_id)
                //{
                        //case LAZER_ID: lazer_equipment->renderInfo(rect); break;
                //}
                // items
		if (item_subtype_id == LAZER_ID)
		{	lazer_equipment->updateInfo();
        		lazer_equipment->renderInfo(rect, offset_x, offset_y);
		}
		if (item_subtype_id == ROCKET_ID)
		{	
			rocket_equipment->updateInfo();
			rocket_equipment->renderInfo(rect, offset_x, offset_y);
		}
		if (item_subtype_id == RADAR_ID)
		{
			radar_equipment->updateInfo();
			radar_equipment->renderInfo(rect, offset_x, offset_y);
		}
		if (item_subtype_id == DRIVE_ID)
		{
			drive_equipment->updateInfo();
			drive_equipment->renderInfo(rect, offset_x, offset_y);
		}
		if (item_subtype_id == BAK_ID)
		{
			bak_equipment->updateInfo();
			bak_equipment->renderInfo(rect, offset_x, offset_y);
		}
		if (item_subtype_id == ENERGIZER_ID)
		{
			energizer_equipment->updateInfo();
			energizer_equipment->renderInfo(rect, offset_x, offset_y);
		}
		if (item_subtype_id == PROTECTOR_ID)
		{
			protector_equipment->updateInfo();
			protector_equipment->renderInfo(rect, offset_x, offset_y);
		}
		if (item_subtype_id == DROID_ID)
		{
			droid_equipment->updateInfo();
			droid_equipment->renderInfo(rect, offset_x, offset_y);
		}
		if (item_subtype_id == FREEZER_ID)
		{
			freezer_equipment->updateInfo();
			freezer_equipment->renderInfo(rect, offset_x, offset_y);
		}
		if (item_subtype_id == SCANER_ID)
		{
			scaner_equipment->updateInfo();
			scaner_equipment->renderInfo(rect, offset_x, offset_y);
		}
		if (item_subtype_id == GRAPPLE_ID)
		{
			grapple_equipment->updateInfo();
			grapple_equipment->renderInfo(rect, offset_x, offset_y);
		}
     	}
     		
     	if (item_type_id == MODULE_ID)
     	{
		// _modules
		if (item_subtype_id == LAZER_ID)
		{
			lazer_module->updateInfo();
			lazer_module->renderInfo(rect);
		}
		if (item_subtype_id == ROCKET_ID)
		{
			rocket_module->updateInfo();
			rocket_module->renderInfo(rect);
		}
		if (item_subtype_id == RADAR_ID)
		{
			radar_module->updateInfo();
			radar_module->renderInfo(rect);
		}
		if (item_subtype_id == DRIVE_ID)
		{
			drive_module->updateInfo();
			drive_module->renderInfo(rect);
		}
		if (item_subtype_id == BAK_ID)
		{
			bak_module->updateInfo();
			bak_module->renderInfo(rect);
		}
		if (item_subtype_id == ENERGIZER_ID)
		{
			energizer_module->updateInfo();
			energizer_module->renderInfo(rect);
		}
        	if (item_subtype_id == PROTECTOR_ID)
		{
			protector_module->updateInfo();
			protector_module->renderInfo(rect);
		}
		if (item_subtype_id == DROID_ID)
		{
			droid_module->updateInfo();
			droid_module->renderInfo(rect);
		}
		if (item_subtype_id == FREEZER_ID)
		{
			freezer_module->updateInfo();
			freezer_module->renderInfo(rect);
		}
		if (item_subtype_id == SCANER_ID)
		{
			scaner_module->updateInfo();
			scaner_module->renderInfo(rect);
		}
		if (item_subtype_id == GRAPPLE_ID)
		{
			grapple_module->updateInfo();
			grapple_module->renderInfo(rect);
		}
	}
}



bool ItemSlot :: interaction(int _x, int _y)
{        
        float dist = distBetweenCenters(rect.getCenter().x, rect.getCenter().y, _x, _y);
        if (dist < rect.getWidth()/2)
                return true;
        else
                return false;    
}


