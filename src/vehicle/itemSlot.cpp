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


ItemSlot :: ItemSlot(int _subtype_id, Ship* _owner_ship, TextureOb* _texOb, int _pos_x, int _pos_y)
{
/* 
        The class provides implementation to insert/hold/remove all game items (equipments, modules and so on)
        Depending on slot subtype there is the rule what items can be used with slot (for example 
        Lazer weapon item cannot be inserted to drive slot and so on).
*/

        type_id    = SLOT_ID;
	subtype_id = _subtype_id;
        
        owner_ship  = _owner_ship; 
        turrel = NULL;

        texOb = _texOb;
        w = texOb->w;
        h = texOb->h;
     
        rect = Rect(_pos_x, _pos_y, w, h);         // create rect with size of the texture

        item_type_id    = NONE_ID;
        item_subtype_id = NONE_ID;
     
        is_EQUIPED       = false;
        is_FLASHING      = false;
        is_CURSORED      = false;         
}

ItemSlot :: ~ItemSlot()
{
	if (item_type_id == EQUIPMENT_ID)
	{
		if (item_subtype_id == ROCKET_ID)
		{
    			delete rocket_equipment;
    		}
    	
    		if (item_subtype_id == LAZER_ID)
		{
    			delete lazer_equipment;
    		}
    
        	if (item_subtype_id == RADAR_ID)
		{
    			delete radar_equipment;
      		}
    						
        	if (item_subtype_id == DRIVE_ID)
		{
    			delete drive_equipment;
    		}

        	if (item_subtype_id == BAK_ID)
		{
    			delete bak_equipment;
    		}

        	if (item_subtype_id == ENERGIZER_ID)
		{
    			delete energizer_equipment;
    		}

        	if (item_subtype_id == PROTECTOR_ID)
		{
    			delete protector_equipment;
    		}
    	
        	if (item_subtype_id == DROID_ID)
		{
    			delete droid_equipment;
    		}

        	if (item_subtype_id == FREEZER_ID)
		{
    			delete freezer_equipment;
    		}
    	
 	        if (item_subtype_id == SCANER_ID)
		{
    			delete scaner_equipment;
    		}
    	
        	if (item_subtype_id == GRAPPLE_ID)
		{
    			delete grapple_equipment;
    		}
    	}
    	
    	if (item_type_id == MODULE_ID)
	{
        	if (item_subtype_id == ROCKET_ID)
		{
    			delete rocket_module;
    		}	 

        	if (item_subtype_id == LAZER_ID)
		{
    			delete lazer_module;
    		}	 
    	
        	if (item_subtype_id == RADAR_ID)
		{
    			delete radar_module;
    		}	 
    	
        	if (item_subtype_id == DRIVE_ID)
		{
    			delete drive_module;
    		}	 
    		
        	if (item_subtype_id == BAK_ID)
		{
    			delete bak_module;
    		}
    	
        	if (item_subtype_id == ENERGIZER_ID)
		{
    			delete energizer_module;
    		}

       		if (item_subtype_id == PROTECTOR_ID)
		{
    			delete protector_module;
    		}

        	if (item_subtype_id == DROID_ID)
		{
    			delete droid_module;
    		}

        	if (item_subtype_id == FREEZER_ID)
		{
    			delete freezer_module;
    		}	
    	
    		if (item_subtype_id == SCANER_ID)
		{
    			delete scaner_module;
    		}

    		if (item_subtype_id == GRAPPLE_ID)
		{
    			delete grapple_module;
    		}
    	}    
    	
    	if (item_type_id == GOODS_ID)
    	{
		delete goods_pack;
	}
}


int ItemSlot :: getTypeId()          const { return type_id; }
int ItemSlot :: getSubTypeId()       const { return subtype_id; }
int ItemSlot :: getItemTypeId()    const { return item_type_id; }
int ItemSlot :: getItemSubTypeId() const { return item_subtype_id; }

Turrel* ItemSlot :: getTurrel() const { return turrel; }
void ItemSlot :: bindTurrel( Turrel* _turrel) {turrel = _turrel; }
                                
bool ItemSlot :: getEquipedStatus() const  { return is_EQUIPED; }
bool ItemSlot :: getCursoredStatus()            const { return is_CURSORED; }
void ItemSlot :: setCursoredStatus(bool new_status) { is_CURSORED = new_status; }
bool ItemSlot :: getFlashingStatus() const { return is_FLASHING; }
void ItemSlot :: setFlashingStatus(bool new_status) { is_FLASHING = new_status; }
                
Rect& ItemSlot :: getRect() { return rect; }

Ship* ItemSlot :: getOwnerShip() { return owner_ship; }
                                
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



template<typename EQUIPMENT_TYPE>
bool ItemSlot :: insertEquipment(EQUIPMENT_TYPE* equipment)
{
	if ((subtype_id == UNIVERSAL_SLOT_ID) || (subtype_id == equipment->getFunctionalSlotSubtypeId()))
	{
		insert(equipment);
    
		item_type_id    = equipment->getTypeId();
		item_subtype_id = equipment->getSubTypeId(); 
	
		is_EQUIPED = true; 
   
		if (subtype_id == equipment->getFunctionalSlotSubtypeId())
		{
			equipment->bindSlot(this);
			equipment->updateOwnerPropetries();
		}

		return true;
	}
	else
		return false;	
}


template<typename MODULE_TYPE>
bool ItemSlot :: insertModule(MODULE_TYPE* _module)
{
	if (subtype_id == UNIVERSAL_SLOT_ID)
	{
		insert(_module);
		
		item_type_id    = _module->getTypeId();
		item_subtype_id = _module->getSubTypeId();
	
		is_EQUIPED = true;
		return true;
	}
	else
		return false; 
}
	
void ItemSlot :: insert(RocketEquipment* item) 		{ rocket_equipment = item; }     
void ItemSlot :: insert(LazerEquipment* item)  		{ lazer_equipment = item; }      
void ItemSlot :: insert(RadarEquipment* item)  		{ radar_equipment = item; }      
void ItemSlot :: insert(DriveEquipment* item)  		{ drive_equipment = item; }      
void ItemSlot :: insert(BakEquipment* item)    		{ bak_equipment = item; }        
void ItemSlot :: insert(EnergizerEquipment* item) 	{ energizer_equipment = item; }  
void ItemSlot :: insert(ProtectorEquipment* item) 	{ protector_equipment = item; } 
void ItemSlot :: insert(DroidEquipment* item)     	{ droid_equipment = item; }      
void ItemSlot :: insert(FreezerEquipment* item) 	{ freezer_equipment = item; }    
void ItemSlot :: insert(ScanerEquipment* item)		{ scaner_equipment = item; }     
void ItemSlot :: insert(GrappleEquipment* item)		{ grapple_equipment = item; }    // owner_ship->updateGrabAbility(); item->reshapeTargetObSlot(this);  GRAPPLE_ID


		
void ItemSlot :: insert(RocketModule* item) 	{ rocket_module = item; }
void ItemSlot :: insert(LazerModule* item)  	{ lazer_module = item; }
void ItemSlot :: insert(RadarModule* item)  	{ radar_module = item; }
void ItemSlot :: insert(DriveModule* item) 	{ drive_module = item; }
void ItemSlot :: insert(BakModule* item)	{ bak_module = item; }
void ItemSlot :: insert(EnergizerModule* item) 	{ energizer_module = item; }
void ItemSlot :: insert(ProtectorModule* item) 	{ protector_module = item; }
void ItemSlot :: insert(DroidModule* item)     	{ droid_module = item; }
void ItemSlot :: insert(FreezerModule* item)   	{ freezer_module = item; }
void ItemSlot :: insert(ScanerModule* item)    	{ scaner_module = item; }
void ItemSlot :: insert(GrappleModule* item)  	{ grapple_module = item; }


bool ItemSlot :: insertGoods(GoodsPack* item)
{
     	if (subtype_id == UNIVERSAL_SLOT_ID)
	{
		goods_pack = item;
        
		item_type_id    = item->getTypeId();
		item_subtype_id = item->getSubTypeId();
		
		is_EQUIPED = true; 
		return true;
	}
	else
		return false;
}
		
		

void ItemSlot :: removeItem()
{
	if (item_type_id == EQUIPMENT_ID)
	{
		if (item_subtype_id == ROCKET_ID)
		{
    			rocket_equipment = NULL;
    			resetFlags();
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				owner_ship->updateFireAbility();
    		}
    	
    		if (item_subtype_id == LAZER_ID)
		{
    			lazer_equipment = NULL;
    			resetFlags();
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				owner_ship->updateFireAbility();
    		}
    
        	if (item_subtype_id == RADAR_ID)
		{
    			radar_equipment = NULL;
    			resetFlags();
    			    			
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				owner_ship->updateRadarAbility();
      		}
    						
        	if (item_subtype_id == DRIVE_ID)
		{
    			drive_equipment = NULL;
    			resetFlags();
    			
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    			{ 
    				owner_ship->updateDriveAbility();
    				owner_ship->updateJumpAbility();
    			}	
    		}

        	if (item_subtype_id == BAK_ID)
		{
    			bak_equipment = NULL;
    			resetFlags();
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    			{ 
    				owner_ship->updateDriveAbility();
    				owner_ship->updateJumpAbility();
    			}
    		}

        	if (item_subtype_id == ENERGIZER_ID)
		{
    			energizer_equipment = NULL;
    			resetFlags();
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				owner_ship->updateEnergyAbility();
    		}

        	if (item_subtype_id == PROTECTOR_ID)
		{
    			protector_equipment = NULL;
    			resetFlags();
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				owner_ship->updateProtectionAbility();
    		}
    	
        	if (item_subtype_id == DROID_ID)
		{
    			droid_equipment = NULL;
    			resetFlags();
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				owner_ship->updateRepairAbility();
    		}

        	if (item_subtype_id == FREEZER_ID)
		{
    			freezer_equipment = NULL;
    			resetFlags();
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				owner_ship->updateFreezeAbility();
    		}
    	

 	       if (item_subtype_id == SCANER_ID)
		{
    			scaner_equipment = NULL;
    			resetFlags();
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				owner_ship->updateScanAbility();
    		}
    	
        	if (item_subtype_id == GRAPPLE_ID)
		{
    			grapple_equipment = NULL;
    			resetFlags();
    			if (subtype_id != UNIVERSAL_SLOT_ID)
    				owner_ship->updateGrabAbility();
    		}
    	}
    	
    	if (item_type_id == MODULE_ID)
	{
        	if (item_subtype_id == ROCKET_ID)
		{
    			rocket_module = NULL;
    			resetFlags();
    		}	 

        	if (item_subtype_id == LAZER_ID)
		{
    			lazer_module = NULL;
    			resetFlags();
    		}	 
    	
        	if (item_subtype_id == RADAR_ID)
		{
    			radar_module = NULL;
    			resetFlags();
    		}	 
    	
        	if (item_subtype_id == DRIVE_ID)
		{
    			drive_module = NULL;
    			resetFlags();
    		}	 
    		
        	if (item_subtype_id == BAK_ID)
		{
    			bak_module = NULL;
    			resetFlags();
    		}
    	
        	if (item_subtype_id == ENERGIZER_ID)
		{
    			energizer_module = NULL;
    			resetFlags();
    		}

       		if (item_subtype_id == PROTECTOR_ID)
		{
    			protector_module = NULL;
    			resetFlags();
    		}

        	if (item_subtype_id == DROID_ID)
		{
    			droid_module = NULL;
    			resetFlags();
    		}

        	if (item_subtype_id == FREEZER_ID)
		{
    			freezer_module = NULL;
    			resetFlags();
    		}	
    	
    		if (item_subtype_id == SCANER_ID)
		{
    			scaner_module = NULL;
    			resetFlags();
    		}

    		if (item_subtype_id == GRAPPLE_ID)
		{
    			grapple_module = NULL;
    			resetFlags();
    		}
    	}
    	
    	if (item_type_id == GOODS_ID)
	{
		goods_pack = NULL;
		resetFlags();
	}
}


void ItemSlot :: resetFlags()
{
	is_EQUIPED = false; 
	item_type_id    = NONE_ID;
	item_subtype_id = NONE_ID;
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
	
        return 0;
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
        
        return 0;
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
        
        return NULL;
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
			
		if (item_subtype_id == GRAPPLE_ID)
			return grapple_equipment->getRadius();
        }
        
        return 0;
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
        
        return 0;
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
	
	if (item_type_id == GOODS_ID)
	{
		drawTexturedRect(goods_pack->getTexOb()->texture, rect, -1.0);
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
        float dist = distBetweenPoints(rect.getCenter().x, rect.getCenter().y, _x, _y);
        if (dist < rect.getWidth()/2)
                return true;
        else
                return false;    
}


void ItemSlot :: createAndDropContainer(StarSystem* _starsystem, vec2f _center)
{
	Container* _container = createContainer(_center);
	
	if (item_type_id == EQUIPMENT_ID)
	{
		if (item_subtype_id == LAZER_ID)
		{	
			_container->getItemSlot()->insertEquipment(lazer_equipment);
        		lazer_equipment = NULL; 
        		resetFlags();
		}
		if (item_subtype_id == ROCKET_ID)
		{	
			_container->getItemSlot()->insertEquipment(rocket_equipment);
        		rocket_equipment = NULL; 
        		resetFlags();
		}
		if (item_subtype_id == RADAR_ID)
		{
			_container->getItemSlot()->insertEquipment(radar_equipment);
        		radar_equipment = NULL;
        		resetFlags();
		}
		if (item_subtype_id == DRIVE_ID)
		{
			_container->getItemSlot()->insertEquipment(drive_equipment);
        		drive_equipment = NULL;
        		resetFlags();
		}
		if (item_subtype_id == BAK_ID)
		{
			_container->getItemSlot()->insertEquipment(bak_equipment);
        		bak_equipment = NULL;
        		resetFlags();
		}
		if (item_subtype_id == ENERGIZER_ID)
		{
			_container->getItemSlot()->insertEquipment(energizer_equipment);
        		energizer_equipment = NULL;
        		resetFlags();
		}
		if (item_subtype_id == PROTECTOR_ID)
		{
			_container->getItemSlot()->insertEquipment(protector_equipment);
        		protector_equipment = NULL;
        		resetFlags();
		}
		if (item_subtype_id == DROID_ID)
		{
			_container->getItemSlot()->insertEquipment(droid_equipment);
        		droid_equipment = NULL;
        		resetFlags();
		}
		if (item_subtype_id == FREEZER_ID)
		{
			_container->getItemSlot()->insertEquipment(freezer_equipment);
        		freezer_equipment = NULL;
        		resetFlags();
		}
		if (item_subtype_id == SCANER_ID)
		{
			_container->getItemSlot()->insertEquipment(scaner_equipment);
        		scaner_equipment = NULL;
        		resetFlags();
		}
		if (item_subtype_id == GRAPPLE_ID)
		{
			_container->getItemSlot()->insertEquipment(grapple_equipment);
        		grapple_equipment = NULL;
        		resetFlags();
		}
     	}
     		
     	if (item_type_id == MODULE_ID)
     	{
		// _modules
		if (item_subtype_id == LAZER_ID)
		{
			_container->getItemSlot()->insertModule(lazer_module);
        		lazer_module = NULL;
        		resetFlags();
		}
		if (item_subtype_id == ROCKET_ID)
		{
			_container->getItemSlot()->insertModule(rocket_module);
        		rocket_module = NULL;
        		resetFlags();
		}
		if (item_subtype_id == RADAR_ID)
		{
			_container->getItemSlot()->insertModule(radar_module);
        		radar_module = NULL;
        		resetFlags();
		}
		if (item_subtype_id == DRIVE_ID)
		{
			_container->getItemSlot()->insertModule(drive_module);
        		drive_module = NULL;
        		resetFlags();
		}
		if (item_subtype_id == BAK_ID)
		{
			_container->getItemSlot()->insertModule(bak_module);
        		bak_module = NULL;
        		resetFlags();
		}
		if (item_subtype_id == ENERGIZER_ID)
		{
			_container->getItemSlot()->insertModule(energizer_module);
        		energizer_module = NULL;
        		resetFlags();
		}
        	if (item_subtype_id == PROTECTOR_ID)
		{
			_container->getItemSlot()->insertModule(protector_module);
        		protector_module = NULL;
        		resetFlags();
		}
		if (item_subtype_id == DROID_ID)
		{
			_container->getItemSlot()->insertModule(droid_module);
        		droid_module = NULL;
        		resetFlags();
		}
		if (item_subtype_id == FREEZER_ID)
		{
			_container->getItemSlot()->insertModule(freezer_module);
        		freezer_module = NULL;
        		resetFlags();
		}
		if (item_subtype_id == SCANER_ID)
		{
			_container->getItemSlot()->insertModule(scaner_module);
        		scaner_module = NULL;
        		resetFlags();
		}
		if (item_subtype_id == GRAPPLE_ID)
		{
			_container->getItemSlot()->insertModule(grapple_module);
        		grapple_module = NULL;
        		resetFlags();
		}
	}
	
	// update mass, and abilities if needed !!!!!!!!!!!!!!!!!!!

	//printf("container was created in ss_id = %i, pos = %f, %f\n", _starsystem->getId(), _container->getPoints()->getCenter().x, _container->getPoints()->getCenter().y );
	_starsystem->add(_container);	
}
